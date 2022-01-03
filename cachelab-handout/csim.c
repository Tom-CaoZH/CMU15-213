#include "cachelab.h"
#include<stdint.h>
#include<stdio.h>
#include<unistd.h>
#include<getopt.h>
#include<malloc.h>

typedef struct Cache_line{
		int tag;
		int counter;
		int valid;
}cache_line_t;

int miss,hits,evictions; // the gobal variables
int s_int,b_int;
int S,E,cache_line_block_size; // block_size ----> bytes
int flag; // to trace the whether presents as the -v(vertical format)

int mut_bin(int s); // count 2^s
int str2int(char *ch); // turn optarg(char) to the integer
void mread(cache_line_t* cache,uint64_t addr_tag,uint64_t addr_index); // to read form the cache

int main(int argc,char *argv[])
{
		// first , read from the command line 
		int ch;
		FILE *fp;
		const char *optstring = "vs:E:b:t:";
		// format : L -- data load ; M -- modify; I --- instruction load; S --- store
		while(-1 != (ch = getopt(argc,argv,optstring))){
				switch(ch){
						case 's' :
								s_int = str2int(optarg);
								S = mut_bin(s_int);
								break;
						case 'E':
								E = str2int(optarg);
								break;
						case 'b':
								b_int = str2int(optarg);
								cache_line_block_size = b_int * mut_bin(b_int - 3);
								break;
						case 't':
								fp = fopen(optarg,"r");
								break;
						case 'v':
								flag = 1;
								break;
				}
		}
		//check and allocate the cache
		/* printf("S = %d,E = %d,B(bytes) = %d\n",S,E,cache_line_block_size); */
		cache_line_t* cache = (cache_line_t *)malloc(sizeof(cache_line_t)*S*E);
		//initialization of the cache
		for(int i = 0;i < S*E;i++){
				cache[i].valid = 0;
				cache[i].counter = 0;
				cache[i].tag = 0;
		}
		/* for(int i = 0;i < S*E;i++){ */
		/* 		printf(" %d  : valid = %d,count = %d,tag = %d\n",i ,cache[i].valid,cache[i].counter,cache[i].tag); */
		/* } */

		// check whether the operation open file is ok
		if(fp == NULL){
				printf("open file error!");
				return 0;
		}

		char inst;
		uint64_t addr;
		int size;
		//then , read from the file 
		while(fscanf(fp," %c %lx,%d",&inst,&addr,&size) > 0){
				/* printf("%c %lx,%d",inst,addr,size); */
				uint64_t addr_tag= addr >> (s_int+b_int); // the tag
				uint64_t addr_index = (addr >> b_int)&(mut_bin(s_int) - 1);
				switch(inst){
						case 'L':
								if(flag){
										printf("%c %lx,%d",inst,addr,size);
								}
								mread(cache,addr_tag,addr_index);
								if(flag){
										printf(" \n");
								}
								break;
						case 'M':
								if(flag){
										printf("%c %lx,%d",inst,addr,size);
								}
								mread(cache,addr_tag,addr_index);
								mread(cache,addr_tag,addr_index);
								if(flag){
										printf(" \n");
								}
								/* modify_write(cache,addr_tag,addr_index); */
								break;
						case 'S':
								if(flag){
										printf("%c %lx,%d",inst,addr,size);
								}
								mread(cache,addr_tag,addr_index);
								if(flag){
										printf(" \n");
								}
								/* modify_write(cache,addr_tag,addr_index); */
								/* mwrite(cache,addr_tag,addr_index); */
								break;
						// ignore the I tage , do nothing
						case 'I':
								break;
				}
		}

		fclose(fp);
		printf("my solution : ");
		printSummary(hits, miss, evictions);
		free(cache);
		return 0;
}
inline int mut_bin(int s){
		return (1 << s);
}

int str2int(char *ch){
		return (*ch - '0');
}

// to read form the cache
void mread(cache_line_t* cache,uint64_t addr_tag,uint64_t addr_index){
		int candidate = -1;
		int max_counter = -1;
		int lru_obj = -1;
		int begin = addr_index*E;
		for(int i = 0;i < E*S;i++){
				//for every cache line that have not been select.
				//and my choise is to add everyone and then when it is selected followingly,i will zero it.
				cache[i].counter++;
		}
		for(int i = 0;i < E;i++){
				//searching the section number is easy
				cache_line_t temp = cache[begin+i];
				// for debug
				/* if(addr_index == 0){ */
				/* 		printf("temp.tag %d = %d ",i,temp.tag); */
				/* 		printf(" before : temp.counter %d = %d ",i,temp.counter); */
				/* } */
				//the best case ;: hit
				if(temp.valid != 0 && temp.tag == addr_tag){
						temp.counter = 0;
						cache[begin+i] = temp;
						hits++;
						if(flag){
								printf(" hit");
						}
						return;
				}
				//search for the free space 
				if(temp.valid == 0){
						candidate = i;
				}
				// according to the LRU policy,search for the candidate
				if(temp.valid != 0 && temp.counter >= max_counter){
						max_counter = temp.counter;
						lru_obj = i;
				}
		}
		if(candidate != -1){
				// there is avaliable space 
				miss++;
				cache[begin+candidate].valid = 1;
				cache[begin+candidate].tag = addr_tag;
				cache[begin+candidate].counter = 0;
				if(flag){
						printf(" miss");
				}
				return;
		}
		else{
				// there is no room to contain,replace!
				miss++;
				cache[begin+lru_obj].counter = 0;
				cache[begin+lru_obj].valid = 1;
				cache[begin+lru_obj].tag = addr_tag;
				evictions++;
				if(flag){
						printf(" miss eviction");
				}
				return;
		}
}
