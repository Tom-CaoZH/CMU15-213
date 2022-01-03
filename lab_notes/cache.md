# the recording of the cache lab --- 22-01-02 ---

## the ge


## the problem 

### the given address,i have no idea how to convert it to the target

在这里这个题目我没有办法的主要原因就是我不知道怎么去把给定的地址去转化，也就是对cache的理解不够深刻。

在这里我大概知道一点点，就是这个地址的分布也就是（tag，index，offset）的分布取决与给定的地址位数（比如这里是64bits），如果是我了解的，那么这里就应该是低6位是tag，再低6位是index，剩下的40位是offset
``````
|----------------------------64------------------------------------|
------+------+----------------------------------------+------------+
      | (6)  |                                        |            |(add)
tar(6)|index |       offset(40)                       |            |
------+------+----------------------------------------+------------+	 
(12)         |           PPO(40)                      |            |
PPN	         |                                        |            |(PPM)
------+------+------------------------------------+---+------------+	 
(12)         |           VPO(36)                  |                |
VPN	         |                                    |                |(PPM)
------+------+------------------------------------+---+------------+
``````
如果是像上面所画的那样，那么这个题目好像就不太符合，所以这里我有点疑惑

对于上面那个应该是给定了四元组(S,E,B,m(the bits of addr)),那么就可以的出来

其实书上面给出来各部分的计算方法，虽然没有明说但是也可以翻到，简略来说就是：
 
1. first ,the the companent of addr :

|-----tag-----|-------set_index-----|-------offset_of_block----------|

那么如果我们想求tag，那么就可以得到addr的高地址的tag的位数，那么tag的位数（要就是sizeof(addr) - sizeof(set_index) - sizeof(offset_of_block)),那么这个地方其实也很好想，这里

set_index = s(the number of set'bits)

offset_of_block = b(the number of blocks) 

(ps:the size of the block is the 2^b);

这点也很好想，这其实就是配套嘛，你想你的set_index 要等于the number of sets,而b表示b的offset（即偏离的block数），那么这个时候就正如上面等式所言

这点我疑惑了好久，唉，还是没认真看书呀！！


### the S , M , L ,tags

i have no idea what is the difference between them.so i can not modify something before i fingure it out.

怎么说呢，这里其实不用管这分别的东西，因为S和L的差别在这题里面根本体现不出来，所以这里都是一样的

### 终极无敌大BUG

说到这个我真的又高兴又落泪呀，我debug花了半天多，下午开始到晚上，就是因为这个bebug，先上代码
```

				if(temp.valid != 0 && temp.tag == addr_tag){
						temp.counter = 0;
						hits++;
						if(flag){
								printf(" hit");
						}
						return;
				}
``````
###### 怎么说呢，如上面所示,这里的情况就是，我用的是计数的方式来实现lru策略的（本人小白，比较菜hhh），这里我是在hit以后更新counter值（我是取最大的为victim），这里我用了个局部变量temp然后更新值，恰恰问题就在这里呀，这个局部变量是分配在栈上面的呀！！！根本没有更新到heap上面，所以就这个问题，我找了半天！！！！c，狗都不学！！！（bushi）---来自菜狗的咆哮---22-01-03-23：45.
``````

				if(temp.valid != 0 && temp.tag == addr_tag){
						temp.counter = 0;
						cache[begin+i] = temp;
						hits++;
						if(flag){
								printf(" hit");
						}
						return;
				}
``````
###### 上面就是改进后的结果






