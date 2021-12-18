#include<stdio.h>
int main(void)
{
		int num1 = 9;
		int* p = &num1;
		printf("%p\n",p);
		printf("%p\n",(unsigned long *)num1);
}







































/* #include<string.h> */

/* typedef int* int_pointer; */
/* int main(void) */
/* { */
/* 		int num = 9; */
/* 		int_pointer ip; */
/* 		ip = &num; */
/* 		printf("%p",ip); */
/* 		return 0; */
/* } */
/* typedef unsigned char* byte_pointer; */

/* void show_bytes(byte_pointer start, size_t len) */
/* { */
/* 		size_t i; */
/* 		for(int i = 0; i < len;i++) */
/* 		{ */
/* 				printf("%.2x",start[i]); */
/* 				printf("\n"); */
/* 		} */
/* } */

/* void show_int(int x) */
/* { */
/* 		show_bytes((byte_pointer) &x,sizeof(int)); */
/* } */

/* void show_float(float x) */
/* { */
/* 		show_bytes((byte_pointer) &x,sizeof(float)); */
/* } */


/* void show_pointer(void* x) */
/* { */
/* 		show_bytes((byte_pointer) &x,sizeof(void*)); */
/* } */



/* int main(void) */
/* { */
		/* int num1 = 2147483648; */
		/* int num2 = 2147483647; */
		/* printf("hello world.\n"); */
		/* if(num1 > num2) */
		/* { */
		/* 		printf("num1(1000) > num2(-1)"); */
		/* } */
		/* else */
		/* { */
		/* 		printf("num1(1000) < num2(-1)"); */
		/* } */
		/* int a = 4; */
		/* int b = 3; */
		/* printf("a = %d , b = %d\n",a,b); */
		/* a = a ^ b; */
		/* b = a ^ b; */
		/* a = a ^ b; */
		/* printf("a = %d , b = %d\n",a,b); */
		/* const char* s = "abcdef"; */
		/* printf("sizeof :"); */
		/* show_bytes((byte_pointer) s,sizeof(s)); */
		/* printf("strlen :"); */
		/* show_bytes((byte_pointer) s,strlen(s)); */
		/* int val = 0x87654321; */
		/* byte_pointer valp = (byte_pointer) &val; */
		/* show_bytes(valp,1); */
		/* printf("\n"); */
		/* show_bytes(valp,2); */
		/* printf("\n"); */
		/* show_bytes(valp,3); */
		/* printf("\n"); */
		/* printf("%p",valp); */
		/* return 0; */
/* } */

















