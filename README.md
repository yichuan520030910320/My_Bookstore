# bookstore2021
#在2.16 ---22：34终于通过了第一个哈哈
##1.blockchain
***
###element,block--->blockchain
***
####1.element is consist of the key ang the offset of the book
####2.block id consist of the pre,nxt and the number of the element in the block
####3.the private function of blockchain is consisting of mergeblock,splitblock,preblock,nextblock
####the public function is consisting of add delete find
```
the hint in the progress
  f1.open(filename,ios_base::binary|ios::in | ios::out);
    if (!f1){
        f1.open(filename,ios::out|ios::binary);
    }

    f1.close();
    这样的开关文件方式较为合理，可以检查文件目前的开关状态——出了几次BUG
```
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
## 2.Bookmanager.cpp
### 1.book类
### 2.bookstore类
>
```
class bookstore{
public:
usermanager cmd;
UnrolledLinkedList ISBN_BOOKSTORE,BOOKNAME_BOOKSTORE,KEYWORD_BOOKSTORE,AUTHOR_BOOKSTORE,USERID_BOKKSTORE;
bookstore();
void run(string temp) ;
};
```

```
the hint in the progress
  f1.open(filename,ios_base::binary|ios::in | ios::out);
    if (!f1){
        f1.open(filename,ios::out|ios::binary);
    }

    f1.close();
    这样的开关文件方式较为合理，可以检查文件目前的开关状态
```
##3.Bookstore.h
import中1定义为支出，0定义为收入
##4.Usermanager.cpp/h
###1.初始化的时候在栈中只有一个权限为零的用户，并且在存储文件中有一个权限为7的BOSS用户
