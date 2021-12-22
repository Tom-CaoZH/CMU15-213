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

#### 一些需要注意的点（本人的nc行为）：

##### 1. 

立即数记得带上$符号（比如赋值内存地址时）

中间十六进制的计算要仔细一点，不然在这种地方出错花很多时间debug很不值得.

##### 2. 

还有一个就是有个地方很神奇：我再把内存赋给我想要的寄存器时，好像不能用指向那个内存的寄存器来代替？

**这里是错误的，是因为你的想法是错误的，你不能把一个整数（比如这里的cookie）拆分成两两一组然后转化成字符串再放进去内存（首先你这样想这个数占的内存都发生了变化，原来是个int后来变成了好多个char）。**

for example:

rsp -------> 0x5561dc78

i need to assign the register rdi to the value 0x5561dc78

it seems that i can not do the operation 

movq $rsp $rdi

我也考虑了函数结束时栈指针rsp增加的情况，但是好像就是不可以，这点比较疑惑

##### 3. input

对于字符串以及整形数的进一步理解：先让我们来回忆一下第二题，第二题是要我们把一个整形数（也就是我们的cookies作为参数传进去），而这一题是把一个字符串当作参数传进去。这两个有什么区别呢？

**整数可以直接赋给寄存器，但是字符串不可以。**

首先我讲一下我的错误思路（来源于第二题，然后在第二题中没注意，又在第三题中犯了）：就是我想比如把参数传进去那么很简单直接把cookies写入我们的要输入的字符串然后把rdi（所需的寄存器）指向那个地址即可，但是我这样想之后发现实现不了，然后呢？我也没有去想为什么，而是想到为什么不直接用一个汇编语句把cookie 的值赋给rdi呢？所以这样就误打误撞的知道了正确解法，但是呢之前产生的错误想法没有得到纠正，所以对于第三题我“延续了”第二题的错误想法，虽然说一个string确实只能使用地址去寻找，不能向整形数一样用立即数直接赋值给寄存器，但是问题在你存在地址里面的值是什么？

**如果你仅仅是把cookie的数字按照小端机器的样式直接输进去，那么你是否有想过电脑读取时是否读到的是这几个数字对应的字符串，结果是当然不是.**

**那么正确的想法是什么呢？应该是把cookie 的每一个数字都转化成对应的字符串。**

##### 4.segament fault

终于找到了一直段错误的原因了--------->原来是在攻击字符串中我把无用的随机的字符串（用00填充）放在了最开始，这就意味着我函数return的时候就会跳到这段00的字符串这里，但是我还没有找到为什么这样就会报错，并且产生了一些新的疑问：

返回值是什么？  经过自己实验一番，大概解决了之前的困惑，是什么呢？就是说返回值是什么呢？总之函数调用的过程是这样的，当被调用的函数快结束的时候，它会把返回值存在rax这个返回值寄存器中，然后return，这个时候return的value是调用函数的下一条语句，然后对于这个返回值，在对rax里面的值进行处理得到，相当与就是数据指令分离.很奇怪的是我好像之前是知道的，但是不知道为什么这个时候又不知道了，可能是理解不深入吧


#### thinkings:

接下来我们正式开始来思考这个题目的解法，这个第三题与第二题相比区别在于两个地方

***1. 输入的参数由一个数变成了一个字符串***

**2. 输入的字符串的位置也有限制，因为你后面要调用函数，所以原来getbuf所占用的buffer会被新调用的函数覆盖一点，那么这个时候字符串输入的位置就需要考虑**

##### 第一个突破点：

这个就直接通过ascii表来一一查找所对应的数，然后通过hex2raw再转化成字符串, 这里还要注意一个问题，就是字符串的结尾要有结束字符('\0')，这个要记得加上去

##### 第二个突破点：

这里我们就要搞清楚调用函数消耗了buffer的多少空间

1. 首先先通过一个跳传字符串（类似第一题）跳传到touch3函数，然后

before : (gdb) p $rsp
$9 = (void *) 0x5561dca8

after : (gdb) p $rsp
$11 = (void *) 0x5561dca0

**减少了8，**

这里其实有一点疑惑就是其实我不太确定只改变了8,为什么呢？因为中间调用了两个函数，中间发生了什么其实是不太知道的，可是当我去check发生了什么的时候，我更疑惑了，因为我好像没发现什么改变rsp的东西，就算改变了也还原了（函数hexmatch)而且这里更诡异的是它改变的值很大，我不知道这意味着什么？然后函数strncmp没有改变rsp的大小

**这里的疑惑是对的，而且这种方法确实不太正确，正确的方法是去观察它调用这个函数后，哪些位置的函数值发生了变化，这样更科学，更有效**





