# **bookstore2021**
#####感谢PaperL同学的帮助，指导我块链的写法，告诉我DEBUG的技巧，感谢憨憨聪老师帮助我凌晨两点配环境，感谢sjm同学后期给予我启发性的帮助，还有libro,Monta,luohaotian同学帮助我解决不小的零碎问题,哦哦还有DE出最后一个BUG的xt哈哈
###许多细节由PaperL启发~
###[github代码](https://github.com/yichuan520030910320/bookstore6.0)
##1.blockchain

###主要组成 1.元素element,2.块block 
###每个块链接成blockchain
***
####1.element is consist of the key ang the offset of the book
```
class element{
public:int offset;
    char key[100];
public:element(const int &offset_=-1,const string &key_=" ");
    bool operator<(const element &a) const;
    element &operator=(const element &right);
};
```
####2.block id consist of the pre,nxt and the number of the element in the block
```
class block{
public:int nxt;
    int pre;
    int numofelment=0;
    element array[MAXN_NUM_OF_BLOCK+5];
public:
    void setnxt(int x){nxt=x;}
    void setpre(int x){pre=x;}
    void setnum(int x){numofelment=x;}
    //block( int pre_=-1,int nxt_=-1, int numofelement_=0);
    block();
    block &operator=(const block &right);
};
```
####3.the private function of blockchain is consisting of mergeblock,splitblock,preblock,nextblock
####the public function is consisting of add delete find
```
the hint in the progress
  f1.open(filename,ios_base::binary|ios::in | ios::out);
    if (!f1){
        f1.open(filename,ios::out|ios::binary);
    }

    f1.close();
    这样的开关文件方式较为合理，可以检查文件目前的开关状态
```

## 2.Bookmanager.cpp
### 1.book类
####存储了书本的基本信息
```
class Book{
public:char ISBN[30];
    char name[60];
    char author[60];
    char keywords[60];
    double price;
    int quantity;
    Book();
};
```
### 2.bookstore类
>包括四个倒排文档的索引块状链表，一个usermanager(inspired by PaperL)
```
class bookstore{
public:
usermanager cmd;
UnrolledLinkedList ISBN_BOOKSTORE,BOOKNAME_BOOKSTORE,KEYWORD_BOOKSTORE,AUTHOR_BOOKSTORE,USERID_BOKKSTORE;
bookstore();
void run(string temp) ;
};
```
>其中usermanager包括用户登录栈以及存储用户信息的文件，主要在下文会提到

##3.Bookstore.h
####用一颗if树实现了对读入指令的切分并且将这些指令丢给不同的子函数执行，将实现写在.h中是我码风太差的原因qwq
##4.Usermanager.cpp/h
###主体部分
###
|名称|功能|细节|
|:---|:---:|---:|
|int usernum|记录当前用户栈的数量便于查找|同下面原因usernum最小是1|
|vector userstack|用户栈，且功能比stack强大|初始化的时候在栈中只有一个权限为零的用户，并且在存储文件中有一个权限为7的BOSS用户|
|  UnrolledLinkedList the_blockchai_of_usermanager;|包含记录用户信息的块状链表，并且与文件相关联|~|
| string filename|文件的名称|~|
***
###部分用户相关的函数
|名称|功能|细节|
|:---|:---:|---:|
|su|登录|要求判断是否是高权限到低权限的登录，这种情况不需要密码，后期debug时遇到的错误|
|useradd|添加用户|权限判断以及该用户在块状链表中是否已经存在|
|logout|退出登录|如果栈中元素数量为一（意思是只有压在栈底的那个不会动的权限为0的用户），则退出登录失效|
|register|注册|不可以直接搬运useradd由于栈中只剩一个元素时也可以注册一个权限为1的用户，与useradd中需要添加权限小于自己的条件矛盾，所以需要单独特判|
|passwd|更改密码|注意分成两种情况|
|checkstring|用来检查string是否格式正确|~|
##5.DEBUG过程中遇到的主要问题
###1.文件流对象fstream经常出现fail的情况，导致读写功能异常，后期解决方法：在每次open之前将这个流对象close();
###2.由于操作系统存在内存自动对齐的情况，原本的指针定位是按照sizeof长度来的，结果会出现长度变化，如int的sizeof在某种诡异的情况下会变成8，解决方法：将结构体作为整体读入，可以防止此类问题的发生
###3.块链DEBUG时经常出现边界考虑错误的情形，解决方法：调就硬调好吧，这边感谢waloltta同学的测试代码用来调块链是否正确
##6.下面是在DEBUG过程中遇到的一些问题记录？？？？（啥玩意
***
###可能过于扯淡，读者自行跳过
```
1.诡异事件，为什么我的f2,f3,f4都可以打开？？？
2.关键字explicit，可以阻止不应该允许的经过转换构造函数进行的隐式转换的发生。
声明为explicit的构造函数不能在隐式转换中使用
3.读取字符数组最好要指定字符数组的长度
4.开完文件之后务必要close,特别是特判时提前返回，很容易自认为最后已经返回了，而没有在特判返回时关掉文件指针
```
```
debug process
1.为什么文件末尾的指针是一个挺大的常数 solved
2.感觉文件指针的BUG好多啊，每个细节都会出错啊啊啊
3.迷惑极了为什么文件删了才能达到我想要的效果?????
4.感觉如果创立文件之后再用指针容易出锅
5.findelement is incorrect!!!!!!!!!!!!!!! attetion please
6.在比较字符数组与字符串的时候，使用了两种不同的方法
```
```
未解决的BUG：
1.su root sjtu之后文件没能关上，目前懒得检查原因了最后再找
2.（目前还没有实现，将来要加上stringcheck函数）鲁棒性测试中要加上对用户名是否满30个字的检验，还有是否是大小写字母，数字组成的一系列检验
3.暂时还没有实现：注意:每次打开程序时默认select空对象，若此时进行import或modify视为Invalid。
4.注意:每次打开程序时默认select空对象，若此时进行import或modify视为Invalid。
5.注意：非管理员输入命令式的界面应该对无参数的show调用进行一定程度的限制(关于前端的一些要求）
6.beyond compare 中输出BOOK为毛线会有差别？？？
```
##7.写完之后的一些感谢反思
###1.代码重复使用过多，封装性极差，导致码风极差，下次希望能做到高内聚低耦合
###2.自己要写测试程序来测试部分单元的功能实现情况
###3..h与.cpp定义与实现分离才能达到比较美观的效果
###4.DEBUG方法效率过低，希望多学习一些比较快捷的DEBUG方法
#END  
##~~1/21~~
######(好像暴露了开发文档是DDL当天写的这个问题（逃)