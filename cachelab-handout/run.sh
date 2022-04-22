make clean
make
./test-trans -M 32 -N 32
./test-trans -M 64 -N 64
./test-trans -M 61 -N 67














# for part A

# ./csim-ref -s 4 -E 2 -b 4 -t traces/dave.trace
# ./csim -s 4 -E 2 -b 4 -t traces/dave.trace

# ./csim-ref -s 4 -E 2 -b 4 -t traces/yi.trace
# ./csim -s 4 -E 2 -b 4 -t traces/yi.trace

# ./csim-ref -v -s 4 -E 2 -b 4 -t traces/yi2.trace > ref.txt
# ./csim -v -s 4 -E 2 -b 4 -t traces/yi2.trace > result.txt

# ./csim-ref -s 4 -E 2 -b 4 -t traces/long.trace
# ./csim -s 4 -E 2 -b 4 -t traces/long.trace

# ./csim-ref -v -s 2 -E 2 -b 3 -t traces/trans.trace > ref.txt
# ./csim -v -s 2 -E 2 -b 3 -t traces/trans.trace > result.txt
# diff -u ref.txt result.txt > diff.txt


# void mwrite(cache_line_t* cache,uint64_t addr_tag,uint64_t addr_index){
# 		int begin = addr_index*E;
# 		for(int i = 0;i < E;i++){
# 				//searching the section number is easy
# 				cache_line_t temp = cache[begin+i];
# 				//the best case ;: hit and the remove it from the cache
# 				if(temp.valid != 0 && temp.tag == addr_tag){
# 						hits++;
# 						temp.counter = 0;
# 						temp.tag = 0;
# 						temp.valid = 0;
# 						return;
# 				}
# 		}
# 		miss++;
# }

# // to write to the cache . After writing to the cache ,the cache line is empty
# void modify_write(cache_line_t* cache,uint64_t addr_tag,uint64_t addr_index){
# 		int begin = addr_index*E;
# 		for(int i = 0;i < E;i++){
# 				//for every cache line that have not been select.
# 				//and my choise is to add everyone and then when it is selected followingly,i will zero it.
# 				cache[begin+i].counter++;
# 		}
# 		for(int i = 0;i < E;i++){
# 				//searching the section number is easy
# 				cache_line_t temp = cache[begin+i];
# 				//the best case ;: hit and the remove it from the cache
# 				if(temp.valid != 0 && temp.tag == addr_tag){
# 						hits++;
# 						temp.counter = 0;
# 						return;
# 				}
# 		}
# 		miss++;
# }

# /* void mwrite(cache_line_t* cache,uint64_t addr_tag,uint64_t addr_index); // to write form the cache */

# // the state modify : write is different to the writing
# void modify_write(cache_line_t* cache,uint64_t addr_tag,uint64_t addr_index);
