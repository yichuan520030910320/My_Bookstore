//
// Created by lenovo on 2021/1/19.
//

#include "blockchain.h"
#include <cstring>
element::element(const int &offset_, const string &key_) {
    offset=offset_;
    strcpy(key,key_.c_str());
}
bool element::operator<(const element &a) const {
    return strcmp(key,a.key)<0;

    //return key<a.key;
}
element & element::operator=(const element &right) {
    if (this==&right) { return *this; }
    offset=right.offset;
    string temp=right.key;
    strcpy(key,temp.c_str());
    return *this;
}

//block::block(int pre_,  int nxt_,  int numofelement_) {
//    pre=pre_,nxt=nxt_,numofelment=numofelement_;
//
//}
block::block() {
    pre=-1;
    nxt=-1;
    numofelment=0;
}
block & block::operator=(const block &right) {
    if (this==&right) return *this;
    pre=right.pre;
    nxt=right.nxt;
    numofelment=right.numofelment;
    for (int i = 0; i <right.numofelment ; ++i) {
        array[i]=right.array[i];
    }
    for (int i = right.numofelment; i < MAXN_NUM_OF_BLOCK; ++i) {
        array[i]=element();
    }
    return *this;
}
UnrolledLinkedList::UnrolledLinkedList(const string &name): filename(name){
    //cout<<"constructer in blocklist"<<endl;
    f1.open(filename,ios_base::binary|ios::in | ios::out);
    if (!f1){
        //cout<<"8888"<<endl;
        f1.open(filename,ios::out|ios::binary);
       // f1.seekg(0,ios::end);
        //cout<<"constructer tellg end"<<" "<<f1.tellg()<<endl;//输出为-1????
    }
    f2.open(filename,ios_base::binary|ios::in | ios::out);
    if (!f2){
        f2.open(filename,ios::out|ios::binary);
    }
    f3.open(filename,ios_base::binary|ios::in | ios::out);
    if (!f3){
        f3.open(filename,ios::out|ios::binary);
    }
    f4.open(filename,ios_base::binary|ios::in | ios::out);
    if (!f4){
        f4.open(filename,ios::out|ios::binary);
    }
    f5.open(filename,ios_base::binary|ios::in | ios::out);
    if (!f5){f5.open(filename,ios::out|ios::binary);}
    f6.open(filename,ios_base::binary|ios::in | ios::out);
    if (!f6){f6.open(filename,ios::out|ios::binary);}
   // cout<<f1.fail()<<"  "<<f2.fail()<<"in blocklist constructer"<<endl;
    f1.close(),f2.close(),f3.close(),f4.close(),f5.close(),f6.close();
}
UnrolledLinkedList::~UnrolledLinkedList() {
    f1.close(),f2.close(),f3.close();
    f4.close(),f5.close(),f6.close();
}
void UnrolledLinkedList::splitblock(const int offset)//this offset means the location in the file(倒排文档的绝对位置）
{f1.clear(),f2.clear(),f3.clear(),f4.clear(),f5.clear(),f6.clear();
    block tempblock;
    f1.open(filename,ios_base::binary|ios::in | ios::out);

    if (!f1){
        f1.open(filename,ios::out|ios::binary);
    }
    f2.open(filename,ios_base::binary|ios::in | ios::out);
    if (!f2){f2.open(filename,ios::out|ios::binary);}
    f3.open(filename,ios_base::binary|ios::in | ios::out);
    if (!f3){f3.open(filename,ios::out|ios::binary);}
    f4.open(filename,ios_base::binary|ios::in | ios::out);
    if (!f4){f4.open(filename,ios::out|ios::binary);}
    f5.open(filename,ios_base::binary|ios::in | ios::out);
    if (!f5){f5.open(filename,ios::out|ios::binary);}
    f6.open(filename,ios_base::binary|ios::in | ios::out);
    if (!f6){f6.open(filename,ios::out|ios::binary);}
    //cout<<f1.fail()<<" "<<f2.fail()<<" "<<f3.fail()<<" "<<f4.fail()<<" "<<f5.fail()<<" "<<f6.fail()<<endl;
    f1.seekg(offset);
    f1.read(reinterpret_cast<char*>(&tempblock),sizeof (block));
//        tempblock
//        tempblock.setnum()
    tempblock.setpre(offset);
   // tempblock.nxt=-1;
    f1.close();
    f2.seekg(offset+8);
    int temp;
    f2.read(reinterpret_cast<char*>(&temp),4);
    f2.close();
    f3.seekg(0,ios::end);
   // cout<<f3.fail()<<" debug in split"<<endl;
    int endlocation=f3.tellg();
f3.close();
    for (int i = 0; i <temp-SPLIT_NUM; ++i) {
        tempblock.array[i]=tempblock.array[i+MAXN_NUM_OF_BLOCK];
    }
    for (int i = temp-SPLIT_NUM; i <MAXN_NUM_OF_BLOCK ; ++i) {
        tempblock.array[i]=element();
    }
    tempblock.numofelment-=SPLIT_NUM;//SPLIT_NUM意思是剩下的元素数量
    f6.seekg(offset);
    f6.write(reinterpret_cast<char*>(&endlocation),4);
    f6.close();
    f5.seekg(offset+8);
    int num=SPLIT_NUM;
    f5.write(reinterpret_cast<char*>(&num),4);
    f5.seekg(endlocation);
    f5.write(reinterpret_cast<char*>(&tempblock),sizeof (block));
    f1.close(),f2.close(),f3.close();
    f4.close(),f5.close(),f6.close();
}
void UnrolledLinkedList::mergeblock(int offset1, int offset2)
{
    f1.open(filename,ios::in | ios::out|ios::binary);
    f2.open(filename,ios::in | ios::out|ios::binary);
    f3.open(filename,ios::in | ios::out|ios::binary);
    f4.open(filename,ios::in | ios::out|ios::binary);
    block tempblock1,tempblock2;
    f1.seekg(offset1);
    f1.read(reinterpret_cast<char*>(&tempblock1),sizeof (block));
    f1.seekg(offset2);
    f1.read(reinterpret_cast<char*>(&tempblock2),sizeof (block));
    tempblock1.nxt=tempblock2.nxt;
    tempblock1.numofelment+=tempblock2.numofelment;
    for (int i = tempblock1.numofelment-tempblock2.numofelment; i <tempblock1.numofelment ; ++i) {
        tempblock1.array[i]=tempblock2.array[i-(tempblock1.numofelment-tempblock2.numofelment)];
    }
    f3.seekg(offset1);
    f3.write(reinterpret_cast<char*>(&tempblock1),sizeof (block));
    f1.close(),f2.close(),f3.close(),f4.close();

}




