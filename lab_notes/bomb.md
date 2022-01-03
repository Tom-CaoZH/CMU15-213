# bomblab


## phase_6

### overview:

   0x00000000004010f4 <+0>:	push   %r14

   0x00000000004010f6 <+2>:	push   %r13

   0x00000000004010f8 <+4>:	push   %r12

   0x00000000004010fa <+6>:	push   %rbp

   0x00000000004010fb <+7>:	push   %rbx

   0x00000000004010fc <+8>:	sub    $0x50,%rsp

   0x0000000000401100 <+12>:	mov    %rsp,%r13

   0x0000000000401103 <+15>:	mov    %rsp,%rsi

   0x0000000000401106 <+18>:	call   0x40145c <read_six_numbers>

#### **above are the first part**

#### **this remind us that there are six numbers to input**

   0x000000000040110b <+23>:	mov    %rsp,%r14

   0x000000000040110e <+26>:	mov    $0x0,%r12d

   0x0000000000401114 <+32>:	mov    %r13,%rbp

   0x0000000000401117 <+35>:	mov    0x0(%r13),%eax

   0x000000000040111b <+39>:	sub    $0x1,%eax

   0x000000000040111e <+42>:	cmp    $0x5,%eax

   0x0000000000401121 <+45>:	jbe    0x401128 <phase_6+52>

   0x0000000000401123 <+47>:	call   0x40143a <explode_bomb>

   0x0000000000401128 <+52>:	add    $0x1,%r12d

   0x000000000040112c <+56>:	cmp    $0x6,%r12d

   0x0000000000401130 <+60>:	je     0x401153 <phase_6+95>

   0x0000000000401132 <+62>:	mov    %r12d,%ebx

   0x0000000000401135 <+65>:	movslq %ebx,%rax

   0x0000000000401138 <+68>:	mov    (%rsp,%rax,4),%eax

   0x000000000040113b <+71>:	cmp    %eax,0x0(%rbp)

   0x000000000040113e <+74>:	jne    0x401145 <phase_6+81>

   0x0000000000401140 <+76>:	call   0x40143a <explode_bomb>

   0x0000000000401145 <+81>:	add    $0x1,%ebx

   0x0000000000401148 <+84>:	cmp    $0x5,%ebx

   0x000000000040114b <+87>:	jle    0x401135 <phase_6+65>

   0x000000000040114d <+89>:	add    $0x4,%r13

   0x0000000000401151 <+93>:	jmp    0x401114 <phase_6+32>


#### **the above is the part two : this is a loop**

#### **the function of it is to enable the former numbers is all not equal  to each other  and enable the six number is all different and less than or equal to six**

   0x0000000000401153 <+95>:	lea    0x18(%rsp),%rsi

   0x0000000000401158 <+100>:	mov    %r14,%rax

   0x000000000040115b <+103>:	mov    $0x7,%ecx

   0x0000000000401160 <+108>:	mov    %ecx,%edx

   0x0000000000401162 <+110>:	sub    (%rax),%edx

   0x0000000000401164 <+112>:	mov    %edx,(%rax)

   0x0000000000401166 <+114>:	add    $0x4,%rax

   0x000000000040116a <+118>:	cmp    %rsi,%rax

   0x000000000040116d <+121>:	jne    0x401160 <phase_6+108>

#### this place i think is also a loop , the effect of it is to use 7 to sub the every number.

#### for example:

#### nums : 1 2 3 4 5 6

#### then reverse into 

#### nums : 6 5 4 3 2 1

   0x000000000040116f <+123>:	mov    $0x0,%esi

   0x0000000000401174 <+128>:	jmp    0x401197 <phase_6+163>

   0x0000000000401176 <+130>:	mov    0x8(%rdx),%rdx

   0x000000000040117a <+134>:	add    $0x1,%eax

   0x000000000040117d <+137>:	cmp    %ecx,%eax

   0x000000000040117f <+139>:	jne    0x401176 <phase_6+130>

   0x0000000000401181 <+141>:	jmp    0x401188 <phase_6+148>

   0x0000000000401183 <+143>:	mov    $0x6032d0,%edx

   0x0000000000401188 <+148>:	mov    %rdx,0x20(%rsp,%rsi,2)

   0x000000000040118d <+153>:	add    $0x4,%rsi

   0x0000000000401191 <+157>:	cmp    $0x18,%rsi

   0x0000000000401195 <+161>:	je     0x4011ab <phase_6+183>

   0x0000000000401197 <+163>:	mov    (%rsp,%rsi,1),%ecx

   0x000000000040119a <+166>:	cmp    $0x1,%ecx

   0x000000000040119d <+169>:	jle    0x401183 <phase_6+143>

   0x000000000040119f <+171>:	mov    $0x1,%eax

   0x00000000004011a4 <+176>:	mov    $0x6032d0,%edx

   0x00000000004011a9 <+181>:	jmp    0x401176 <phase_6+130>


#### **the above is the part three**

#### **this part is also a loop , i am a bit of confused because i think it is nothing against the numbers i input , i think the function of it is to  add numbers to the end which we input-numbers, but i have no idea what is the effect of it .**


#### **now i know that what is the real effect . it is to permutate the nums in linklist according to the nums we input

   0x00000000004011ab <+183>:	mov    0x20(%rsp),%rbx  **rbx = node1**

   0x00000000004011b0 <+188>:	lea    0x28(%rsp),%rax  **rax = node2**

   0x00000000004011b5 <+193>:	lea    0x50(%rsp),%rsi  **rsi is a end , the exit of this loop**

   0x00000000004011ba <+198>:	mov    %rbx,%rcx  **rcx = node1**

   0x00000000004011bd <+201>:	mov    (%rax),%rdx  **rdx = rax** // 2: **rdx = node3**

   0x00000000004011c0 <+204>:	mov    %rdx,0x8(%rcx)  **(rcx + 0x8)==node2**

   0x00000000004011c4 <+208>:	add    $0x8,%rax    **rax = node3**

   0x00000000004011c8 <+212>:	cmp    %rsi,%rax  **the standard**

   0x00000000004011cb <+215>:	je     0x4011d2 <phase_6+222>

   0x00000000004011cd <+217>:	mov    %rdx,%rcx

   0x00000000004011d0 <+220>:	jmp    0x4011bd <phase_6+201>

#### the above one is a another loop . the effect of it is to change the value in the linklist

   0x00000000004011d2 <+222>:	movq   $0x0,0x8(%rdx)   **origion  : rdx  = node6  and (rdx + 0x8) = 0x0// now : is 0x0 as usual

   0x00000000004011da <+230>:	mov    $0x5,%ebp

   0x00000000004011df <+235>:	mov    0x8(%rbx),%rax

   0x00000000004011e3 <+239>:	mov    (%rax),%eax

   0x00000000004011e5 <+241>:	cmp    %eax,(%rbx)

   0x00000000004011e7 <+243>:	jge    0x4011ee <phase_6+250>

   0x00000000004011e9 <+245>:	call   0x40143a <explode_bomb>

   0x00000000004011ee <+250>:	mov    0x8(%rbx),%rbx

   0x00000000004011f2 <+254>:	sub    $0x1,%ebp

   0x00000000004011f5 <+257>:	jne    0x4011df <phase_6+235>

#### **the above one is a loop , the effect of it is to check that the nums in the linklist are  decreasing

   0x00000000004011f7 <+259>:	add    $0x50,%rsp

   0x00000000004011fb <+263>:	pop    %rbx

   0x00000000004011fc <+264>:	pop    %rbp

   0x00000000004011fd <+265>:	pop    %r12

   0x00000000004011ff <+267>:	pop    %r13

   0x0000000000401201 <+269>:	pop    %r14

   0x0000000000401203 <+271>:	ret



#### **this part is the last part**


   End of assembler dump.








### part1



0x6032d0 <node1>:       332     1       6304480 0

0x6032e0 <node2>:       168     2       6304496 0

0x6032f0 <node3>:       924     3       6304512 0

0x603300 <node4>:       691     4       6304528 0

0x603310 <node5>:       477     5       6304544 0

0x603320 <node6>:       443     6       0       0

0x603330:       0       0       0       0

0x603340 <host_table>:  4204073 0       4204099 0

0x603350 <host_table+16>:       4204125 0       0       0

0x603360 <host_table+32>:       0       0       0       0






0x7fffffffde00: 0x006032d0      0x00000000      0x006032e0      0x00000000

0x7fffffffde10: 0x006032f0      0x00000000      0x00603300      0x00000000

0x7fffffffde20: 0x00603310      0x00000000      0x00603320      0x00000000

0x7fffffffde30: 0x00402210      0x00000000      0x00000000      0x00000000

0x7fffffffde40: 0x00400c90      0x00000000      0xffffdf50      0x00007fff

0x7fffffffde50: 0x00000000      0x00000000      0x00400ecb      0x00000000

0x7fffffffde60: 0x00402210      0x00000000      0xf7de90b3      0x00007fff

0x7fffffffde70: 0xf7ffc620      0x00007fff      0xffffdf58      0x00007fff

0x7fffffffde80: 0x00000000      0x00000001      0x00400da0      0x00000000

0x7fffffffde90: 0x00402210      0x00000000      0x1ec4ad1c      0x1654d80d



### changed1:

0x7fffffffdde0: 0x00000001      0x00000002      0x00000003      0x00000004

0x7fffffffddf0: 0x00000005      0x00000006      0x00000000      0x00000000

0x7fffffffde00: 0x006032d0      0x00000000      0x006032e0      0x00000000

0x7fffffffde10: 0x006032f0      0x00000000      0x00603300      0x00000000

0x7fffffffde20: 0x00603310      0x00000000      0x00603320      0x00000000

0x7fffffffde30: 0x00402210      0x00000000      0x00000000      0x00000000

0x7fffffffde40: 0x00400c90      0x00000000      0xffffdf50      0x00007fff

0x7fffffffde50: 0x00000000      0x00000000      0x00400ecb      0x00000000

0x7fffffffde60: 0x00402210      0x00000000      0xf7de90b3      0x00007fff

0x7fffffffde70: 0xf7ffc620      0x00007fff      0xffffdf58      0x00007fff

0x7fffffffde80: 0x00000000      0x00000001      0x00400da0      0x00000000

0x7fffffffde90: 0x00402210      0x00000000      0x1ec4ad1c      0x1654d80d





#### the correct answer i suppose

this index : 2 1 6 5 4 3

this is wrong : 447 443 322 168 924 691



0x7fffffffdde0: 5       6       1       2

0x7fffffffddf0: 3       4       0       0

0x7fffffffde00: 6304528 0       6304544 0

0x7fffffffde10: 6304464 0       6304480 0

0x7fffffffde20: 6304496 0       6304512 0

0x7fffffffde30: 4203024 0       0       0

0x7fffffffde40: 4197520 0       -8368   32767

0x7fffffffde50: 0       0       4198091 0

0x7fffffffde60: 4203024 0       -136408909      32767

0x7fffffffde70: -134232544      32767   -8360   32767

0x7fffffffde80: 0       1       4197792 0

0x7fffffffde90: 4203024 0       -2123758324     10538296



#### another try
0x7fffffffdde0: 3       4       5       6

0x7fffffffddf0: 1       2       0       0

0x7fffffffde00: 6304496 0       6304512 0

0x7fffffffde10: 6304528 0       6304544 0

0x7fffffffde20: 6304464 0       6304480 0

0x7fffffffde30: 4203024 0       0       0

0x7fffffffde40: 4197520 0       -8368   32767

0x7fffffffde50: 0       0       4198091 0

0x7fffffffde60: 4203024 0       -136408909      32767

0x7fffffffde70: -134232544      32767   -8360   32767

0x7fffffffde80: 0       1       4197792 0

0x7fffffffde90: 4203024 0       1758047995      -441666524

## secret_phase

### firstly, we should find the way entering it 

#### my method is to objdump the bomb and then search for secret_phase then i find it in the phase_defused function


### overiew

0x00000000004015c4 <+0>:	sub    $0x78,%rsp

0x00000000004015c8 <+4>:	mov    %fs:0x28,%rax

0x00000000004015d1 <+13>:	mov    %rax,0x68(%rsp)

0x00000000004015d6 <+18>:	xor    %eax,%eax

0x00000000004015d8 <+20>:	cmpl   $0x6,0x202181(%rip)        # 0x603760 <num_input_strings>

0x00000000004015df <+27>:	jne    0x40163f <phase_defused+123>

0x00000000004015e1 <+29>:	lea    0x10(%rsp),%r8

0x00000000004015e6 <+34>:	lea    0xc(%rsp),%rcx

0x00000000004015eb <+39>:	lea    0x8(%rsp),%rdx

0x00000000004015f0 <+44>:	mov    $0x402619,%esi  // this -----> (%d %d %s)

0x00000000004015f5 <+49>:	mov    $0x603870,%edi

0x00000000004015fa <+54>:	call   0x400bf0 <__isoc99_sscanf@plt>

0x00000000004015ff <+59>:	cmp    $0x3,%eax

0x0000000000401602 <+62>:	jne    0x401635 <phase_defused+113>

0x0000000000401604 <+64>:	mov    $0x402622,%esi  // this place is the DrEvil  // the key

0x0000000000401609 <+69>:	lea    0x10(%rsp),%rdi

0x000000000040160e <+74>:	call   0x401338 <strings_not_equal>

0x0000000000401613 <+79>:	test   %eax,%eax

0x0000000000401615 <+81>:	jne    0x401635 <phase_defused+113>

0x0000000000401617 <+83>:	mov    $0x4024f8,%edi

0x000000000040161c <+88>:	call   0x400b10 <puts@plt>

0x0000000000401621 <+93>:	mov    $0x402520,%edi

0x0000000000401626 <+98>:	call   0x400b10 <puts@plt>

0x000000000040162b <+103>:	mov    $0x0,%eax

0x0000000000401630 <+108>:	call   0x401242 <secret_phase>

0x0000000000401635 <+113>:	mov    $0x402558,%edi

0x000000000040163a <+118>:	call   0x400b10 <puts@plt>

0x000000000040163f <+123>:	mov    0x68(%rsp),%rax

0x0000000000401644 <+128>:	xor    %fs:0x28,%rax

0x000000000040164d <+137>:	je     0x401654 <phase_defused+144>

0x000000000040164f <+139>:	call   0x400b30 <__stack_chk_fail@plt>

0x0000000000401654 <+144>:	add    $0x78,%rsp

0x0000000000401658 <+148>:	ret    

#### the secret_phase

0x0000000000401242 <+0>:	push   %rbx

0x0000000000401243 <+1>:	call   0x40149e <read_line>

0x0000000000401248 <+6>:	mov    $0xa,%edx

0x000000000040124d <+11>:	mov    $0x0,%esi

0x0000000000401252 <+16>:	mov    %rax,%rdi

0x0000000000401255 <+19>:	call   0x400bd0 <strtol@plt>  //  the role of the function strtol is to transform the str to a long integer

##### for eample :  "12h23y3" ----- through strtol -------->  $rax = 12

0x000000000040125a <+24>:	mov    %rax,%rbx    //  **rbx(ebx) = rax = 11 -------> the input**

0x000000000040125d <+27>:	lea    -0x1(%rax),%eax   // **$eax = ($rax----->value) - 1**

0x0000000000401260 <+30>:	cmp    $0x3e8,%eax   // **0x3e8 = 1000**

0x0000000000401265 <+35>:	jbe    0x40126c <secret_phase+42>

0x0000000000401267 <+37>:	call   0x40143a <explode_bomb>

0x000000000040126c <+42>:	mov    %ebx,%esi  // **esi = ebx** = 11 --------> the input

0x000000000040126e <+44>:	mov    $0x6030f0,%edi   // **edi = 36($)**

0x0000000000401273 <+49>:	call   0x401204 <fun7>

0x0000000000401278 <+54>:	cmp    $0x2,%eax   

###### this is the output : eax(rax) = 2  // the result after fun7 

#### the answer is 22

0x000000000040127b <+57>:	je     0x401282 <secret_phase+64>

0x000000000040127d <+59>:	call   0x40143a <explode_bomb>

0x0000000000401282 <+64>:	mov    $0x402438,%edi

0x0000000000401287 <+69>:	call   0x400b10 <puts@plt>

0x000000000040128c <+74>:	call   0x4015c4 <phase_defused>

0x0000000000401291 <+79>:	pop    %rbx

0x0000000000401292 <+80>:	ret    


#### function7


0x0000000000401204 <+0>:	sub    $0x8,%rsp

0x0000000000401208 <+4>:	test   %rdi,%rdi

0x000000000040120b <+7>:	je     0x401238 <fun7+52>

0x000000000040120d <+9>:	mov    (%rdi),%edx  // **edx = 36**

0x000000000040120f <+11>:	cmp    %esi,%edx                                                              

##### the example:the role of the function7

rdi ----> linklist

edx = (rdi)

esi = input

if(edx <= esi)
{
		eax = 0;

		jump  [fun7 + 28]

		if(edx == esi)

		{

				return eax

		}

		else

		{

				fun7(rdi + 2)		

				0x0000000000401232 <+46>:	lea    0x1(%rax,%rax,1),%eax

				return eax

		}

}

else

{

		fun7(rdi + 1)		// this one should be : eax = 1

		0x000000000040121c <+24>:	add    %eax,%eax

		return eax

}

0x0000000000401211 <+13>:	jle    0x401220 <fun7+28>                                                       

0x0000000000401213 <+15>:	mov    0x8(%rdi),%rdi

0x0000000000401217 <+19>:	call   0x401204 <fun7>

0x000000000040121c <+24>:	add    %eax,%eax

0x000000000040121e <+26>:	jmp    0x40123d <fun7+57>

0x0000000000401220 <+28>:	mov    $0x0,%eax

0x0000000000401225 <+33>:	cmp    %esi,%edx

0x0000000000401227 <+35>:	je     0x40123d <fun7+57>

0x0000000000401229 <+37>:	mov    0x10(%rdi),%rdi

0x000000000040122d <+41>:	call   0x401204 <fun7>

0x0000000000401232 <+46>:	lea    0x1(%rax,%rax,1),%eax

0x0000000000401236 <+50>:	jmp    0x40123d <fun7+57>

0x0000000000401238 <+52>:	mov    $0xffffffff,%eax

0x000000000040123d <+57>:	add    $0x8,%rsp

0x0000000000401241 <+61>:	ret


#### another mystery: numbers around $rdi

$rdi     ------> 36 

$rdi + 1 ------> 8 

$rdi + 2 ------> 50

$rdi + 3 ------> 22

$rdi + 4 ------> 45

$rdi + 5 ------> 6

$rdi + 6 ------> 107

$rdi + 7 ------> 40



##### the linklist behind $rdi

0x6030f0 <n1>:	0x00000024	0x00000000	0x00603110	0x00000000

0x603100 <n1+16>:	0x00603130	0x00000000	0x00000000	0x00000000

0x603110 <n21>:	0x00000008	0x00000000	0x00603190	0x00000000

0x603120 <n21+16>:	0x00603150	0x00000000	0x00000000	0x00000000

0x603130 <n22>:	0x00000032	0x00000000	0x00603170	0x00000000

0x603140 <n22+16>:	0x006031b0	0x00000000	0x00000000	0x00000000

0x603150 <n32>:	0x00000016	0x00000000	0x00603270	0x00000000

0x603160 <n32+16>:	0x00603230	0x00000000	0x00000000	0x00000000

0x603170 <n33>:	0x0000002d	0x00000000	0x006031d0	0x00000000

0x603180 <n33+16>:	0x00603290	0x00000000	0x00000000	0x00000000

0x603190 <n31>:	0x00000006	0x00000000	0x006031f0	0x00000000

0x6031a0 <n31+16>:	0x00603250	0x00000000	0x00000000	0x00000000

0x6031b0 <n34>:	0x0000006b	0x00000000	0x00603210	0x00000000

0x6031c0 <n34+16>:	0x006032b0	0x00000000	0x00000000	0x00000000

0x6031d0 <n45>:	0x00000028	0x00000000	0x00000000	0x00000000








