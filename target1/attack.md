# the recording of the attack lab  ------- 21-12-19

## something needs to note:

### 1.when you run the command like :

1. ./ctarget

2. ./rtarget

...etc , please remeber to add the parament "-q" to enable it can be run on your machine

### 2.the function getbuf (see the write-up for more details)

### the tool hex2raw :

我觉得本质上这个工具的作用就是把十六进制（也就是objdump生成的十六进制的数）的数转化成二进制数，并且他生成的文件是不能直接给objdump反汇编回去的。为什么呢？

很好想，因为你这样想，

1. 首先objdump 生成的反汇编文件肯定是他做了一些处理的（是什么处理呢？我现在暂且还不知道）.

2. 然后而且你也不是把整个生成的汇编文件直接拿去hew2raw哪里处理了，而是删去了一些hew2raw不能处理的部分，那么在这里又会有一个损失.

3. 所以最后hex2raw只处理了最核心的部分，所以当然不能吧hex2raw生成的文件给objdump去反汇编虽然它生成的文件确实是二进制文件，但是少了很多东西.

所以可以说hex2raw实现了一个与objdump的一个小功能（当然比较核心或者最核心？）即反汇编相反的功能

## first part : code injection part:

### level1(phase1):

#### description : 

For Phase 1, you will not inject new code. Instead, your exploit string will redirect the program to execute an existing procedure

#### thinkings : 

our mission is just to jump to the function touch1,there is no parameters to pass.

so we just need to find the beginning site of the touch1 function 

#### solutions:

##### firstly : gdb ctarget . the we disas the touch1 function the we get the beginning , the following.

Dump of assembler code for function touch1:


   0x00000000004017c0 <+0>:	sub    $0x8,%rsp

##### then we use hexraw to generate the string --------> the return string

(there is something needs to note : 4017c0---------> c0 17 40)

##### we also need to confirm how many bits the getbuf function reverse for the get function. 

firstly we objdump the ctarget.
the search the getbuf function to find that there is 40 bits(the following),so we need to input another 40 bits before the return string

  4017a8:   48 83 ec 28             sub    $0x28,%rsp

### level2 :

#### description: 

Phase 2 involves injecting a small amount of code as part of your exploit string.

#### thinkings:

##### origion idea(wrong!!!!)

the key to this problem is to find out the input of the function touch2 

then this can be convert into how can we move the value in $rsp to $edi in our string

=> 0x00000000004017fc <+16>:	cmp    0x202ce2(%rip),%edi        # 0x6044e4 <cookie>

edi is our input

the rsp is the input-------->this is for sure

the we need a ststement to assign the rsp to the edi(rdi)

#####为什么上面那个想法是错的呢？

我原来想可以借鉴第一题的想法：就是我可以在前40个bits里面执行

moveq $cookie %edi

这样我再像第一题一样，在return处插入touch2的地址，那么这样就可以实现了

但是但是但是！！！！问题就在你在前40个bits里面输入的东西是存在寄存器里的，不会执行不会执行不会执行！！！！！

##### the right idea:

1. 首先确实应该执行

moveq $cookie %edi

2. 然后再要想我怎么让程序去执行我写入的东西，这里就是用到第一题的想法--------我直接跳转到上面那里

3. 最后就是要跳转到touch2那里去了

### level3




