//
// Created by lenovo on 2021/1/19.
//

#ifndef CODE_UNROLLEDLINKEDLIST_H
#define CODE_UNROLLEDLINKEDLIST_H
#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <vector>
#include <fstream>
#define MAXN_NUM_OF_BLOCK 300
#define SPLIT_NUM 300//设置成一样可以避免列快失败
#define MERGENUM 50


using std::string;
using namespace std;

class element{//pherhaps node
public:int offset;//thie offset means the locatiion ih the file of the book(sorted by the add time )
    char key[100];
public:element(const int &offset_=-1,const string &key_=" ");
    bool operator<(const element &a) const;
    element &operator=(const element &right);
};
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
class UnrolledLinkedList {
private:string filename;
    fstream f1,f2,f3,f4,f5,f6;
int nxtblock(int offset){
f6.open(filename,ios::in | ios::out|ios::binary);
//cout<<offset<<"&&&&&&&"<<endl;
f6.seekg(offset);
int temp;
    f6.read(reinterpret_cast<char*>(&temp),sizeof (int));
    int temp1;
    f6.read(reinterpret_cast<char*>(&temp1),sizeof (int));
    //cout<<temp1<<"^^^^^^^"<<endl;
    f6.read(reinterpret_cast<char*>(&temp1),sizeof (int));
   // cout<<temp1<<"%%%%%%%%%"<<endl;
    f6.close();
//cout<<temp<<"       nxtblock"<<endl;
    return temp;
}
int preblock(int offset){
    f1.open(filename,ios::in | ios::out|ios::binary);
    f1.seekg(offset+4);
    int temp;
    f1.read(reinterpret_cast<char*>(&temp),4);
    f1.close();
    return temp;
}
   void splitblock(const int offset);//this offset means the location in the file(倒排文档的绝对位置）
    void mergeblock(int offset1,int offset2);
public:
    void debug_print_the_filenode(){
        cout<<f1.is_open()<<" "<<f2.is_open()<<" "<<f3.is_open()<<" "<<f4.is_open()<<endl;
    }
     UnrolledLinkedList(const string &name=" ");
    ~UnrolledLinkedList();
void  addelement(const element&index){
        string temp=index.key;
  //  cout<<f1.fail()<<"&&&&in debug addelement  in the addelement begin"<<f2.fail()<<endl;
    f1.open(filename,ios_base::binary|ios::in | ios::out);
    if (!f1){f1.open(filename,ios::out|ios::binary);}
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
   // cout<<f1.fail()<<"&&&&in debug addelement"<<f2.fail()<<endl;

   // cout<<f1.is_open()<<" "<<f2.is_open()<<" "<<f3.is_open()<<" "<<f4.is_open()<<" "<<f5.is_open()<<" "<<f6.is_open()<<"  debug in addelement"<<endl;
        f1.seekg(16);
        //cout<<f1.fail()<<"&&&&"<<endl;
        //f1.seekg(0,ios::end),cout<<f1.tellg()<<endl;
        char headname[100];
        f2.seekg(0,ios::end);
   // cout<<f1.fail()<<"&&&&in debug addelement"<<f2.fail()<<endl;
      // cout<<f1.tellg()<<" "<<f2.tellg()<<"debug in addelement"<<endl;
    if (f1.tellg()>f2.tellg()){
        block tempblock;
        //cout<<tempblock.nxt<<" addelemeny"<<endl;
        tempblock.numofelment=1;
        tempblock.array[0]=index;
        f3.seekg(0);
        f3.write(reinterpret_cast<char*>(&tempblock),sizeof (block));
        f3.seekg(16);
        f3.seekg(0);
        int num;
        f3.read(reinterpret_cast<char*>(&num),sizeof (int));
        f3.clear();
        //cout<<"select   *********in addelement"<<endl;
        //cout<<num<<"&&&&&&^^^^^^(((("<<endl;
       // cout<<tempblock.nxt<<"%$$$$$$$$$^^^^^"<<endl;
//        char temp1[100];
//        f3.read(reinterpret_cast<char*>(&temp1),100);
//        cout<<temp1<<" debug in findnode"<<endl;
    } else{
        int headoffset=0,lastoffset_in_the_block;
        f1.read(reinterpret_cast<char*>(&headname),100);
//        f1.seekg(0);
//        int num;
//        f1.read(reinterpret_cast<char *>(&num),4);
       // cout<<num<<"^%%%%%%%%%%"<<endl;
      // cout<<headname<<" "<<temp<<" addelement"<<endl;
        int controloffset=0;
        string str(headname);
        while (temp>str)//endless loop
        {
            //cout<<"********"<<endl;
       // cout<<headoffset<<"pre  &&&&"<<endl;
        f1.seekg(headoffset);
        controloffset=headoffset;
        int tempoff;
        f1.read(reinterpret_cast<char*>(&tempoff),4);
        headoffset=tempoff;
            //headoffset=nxtblock(headoffset);
           // cout<<headoffset<<"&&&&&&"<<endl;
            if (headoffset==-1) break;
            f1.seekg(headoffset+16);
            f1.read(reinterpret_cast<char*>(&headname),100);//logic may need to be rewrite
            str=headname;
        }
        //this headoffset means the block of the node and now to search the block
       //cout<<headoffset<<"debug in addelement"<<endl;
        f4.seekg(controloffset);
        block tempblock;
        f4.read(reinterpret_cast<char*>(&tempblock),sizeof (block));
        int location=upper_bound(tempblock.array,tempblock.array+tempblock.numofelment,index)-tempblock.array;//todo
        //tempblock.numofelment++;
        for (int i = tempblock.numofelment; i >=location ; --i) {
            tempblock.array[i+1]=tempblock.array[i];
        }
        tempblock.array[location]=index;
 tempblock.numofelment++;
 //cout<<tempblock.array[0].key<<" mmm"<<tempblock.array[1].key<<endl;
 f5.seekg(controloffset);
        f5.write(reinterpret_cast<char*>(&tempblock),sizeof (block));
        if (tempblock.numofelment>SPLIT_NUM)
        {f1.close(),f2.close(),f3.close(),f4.close(),f5.close(),f6.close();
            splitblock(controloffset);
            return;
        }
    }
    f1.close(),f2.close(),f3.close(),f4.close(),f5.close(),f6.close();
}
void deleteelment(const element&index){
    //cout<<"deleteelement in begin"<<endl;
    f1.open(filename,ios::in | ios::out|ios::binary);
    f2.open(filename,ios::in | ios::out|ios::binary);
    f3.open(filename,ios::in | ios::out|ios::binary);
    f4.open(filename,ios::in | ios::out|ios::binary);
    f5.open(filename,ios::in | ios::out|ios::binary);
    //cout<<f1.fail()<<" in deleteelement begin f1.fail"<<endl;
    f1.seekg(0,ios::end);
   // cout<<f1.tellg()<<"in delete element f1.tellg"<<endl;//todo
    if (f1.tellg()==0) {
        f1.close(),f2.close(),f3.close(),f4.close();
        f5.close();
        return; }
    char temp1[100];
    strcpy(temp1,index.key);
   // string temp1=index.key;
    f1.seekg(16);
    int headoffset=0,lastoffset_in_the_block;
    char headname[100];
    int tempheadoffsey=0;
    f1.read(reinterpret_cast<char*>(&headname),100);
    if (strcmp(temp1,headname)<0) {
        f1.close(),f2.close(),f3.close(),f4.close();
        f5.close();
        return; }
    //cout<<temp1<<"   in deleteele"<<headname<<endl;
    while (strcmp(temp1,headname)>0)
    {    tempheadoffsey=headoffset;
        headoffset=nxtblock(headoffset);
        if (headoffset==-1) break;
        f3.seekg(headoffset+16);
        f3.read(reinterpret_cast<char*>(&headname),100);
    }
    f2.seekg(tempheadoffsey);
    block tempblock;
    f2.read(reinterpret_cast<char*>(&tempblock),sizeof (block));
    int location=lower_bound(tempblock.array,tempblock.array+tempblock.numofelment,index)-tempblock.array;
    int pos=location;
    //cout<<"pos:"<<pos<<"delete element"<<endl;
    //cout<<tempblock.numofelment<<"     numofelement in element"<<endl;
    while (pos!=tempblock.numofelment){
        //cout<<tempblock.array[pos].key<<"  "<<temp1<<"  delete"<<endl;
        //cout<<tempblock.array[pos].offset<<"  "<<index.offset<<"  delete"<<endl;
        if ((strcmp(temp1,tempblock.array[pos].key)==0)&&tempblock.array[pos].offset==index.offset) {
            //cout<<"succeed break in delete"<<endl;
            break; }
        pos++;
    }
//cout<<" run out od the first while in deleteelement"<<endl;
    //search in the next block
    //below is not check
    if (pos==tempblock.numofelment){
        while (nxtblock(tempheadoffsey)!=-1&&pos==tempblock.numofelment){
            tempheadoffsey=nxtblock(tempheadoffsey);
            f2.seekg(tempheadoffsey);
            f2.read(reinterpret_cast<char*>(&tempblock),sizeof (block));
             location=lower_bound(tempblock.array,tempblock.array+tempblock.numofelment,index)-tempblock.array;
             pos=location;
            while (pos!=tempblock.numofelment){
                if ((strcmp(temp1,tempblock.array[pos].key)==0)&&tempblock.array[pos].offset==index.offset) break;
                pos++;
            }
        }
    }
    if (pos!=tempblock.numofelment){
        //cout<<"in deleteelement pos!=tempblock"<<endl;
        tempblock.numofelment--;
        element tempele;
        tempblock.array[pos]=tempele;
        for (int i = pos; i <tempblock.numofelment ; ++i) {
            tempblock.array[i]=tempblock.array[i+1];
        }
        f4.seekg(tempheadoffsey);
        f4.write(reinterpret_cast<char*>(&tempblock),sizeof (block));
    }
    //below is not check
    if (nxtblock(tempheadoffsey)!=-1){
        f5.seekg(nxtblock(tempheadoffsey)+8);
        int nxtnum;
        f5.read(reinterpret_cast<char*>(&nxtnum),4);
        if (nxtnum+tempblock.numofelment<MERGENUM) mergeblock(tempheadoffsey,nxtblock(tempheadoffsey));

    }
    f1.close(),f2.close(),f3.close(),f4.close();
    f5.close();
}
vector<int> findelement(const string key_name) {

    f1.open(filename,ios::in | ios::out|ios::binary);
    //cout<<"f1 check"<<f1.is_open()<<endl;
    f2.open(filename,ios::in | ios::out|ios::binary);
    f3.open(filename,ios::in | ios::out|ios::binary);
    f4.open(filename,ios::in | ios::out|ios::binary);
   // cout<<f2.is_open()<<endl;
    vector<int> return_ans;
    return_ans.clear();
    f1.seekg(16);
    f2.seekg(0,ios::end);
    //cout<<f1.tellg()<<"*****"<<endl;
    //cout<<f1.tellg()<<" "<<f2.tellg()<<"in find element"<<endl;
    if (f1.tellg()>f2.tellg()) {
        f1.close(),f2.close(),f3.close(),f4.close();
        return return_ans; }
    char temp[100];

    f1.read(reinterpret_cast<char*>(&temp),100);
//cout<<temp<<" "<<key_name<<" the keyname and the head tempdebug in find element"<<endl;//todo
    if (strcmp(temp,key_name.c_str())>0) {
        f1.close(),f2.close(),f3.close(),f4.close();
        return return_ans;}
    if (strcmp(temp,key_name.c_str())==0) {
        f1.seekg(-104,ios::cur);
        int ans;
        f1.read(reinterpret_cast<char*>(&ans),4);
        return_ans.push_back(ans);
        f1.close(),f2.close(),f3.close(),f4.close();
        return return_ans;
    }
    int headoffset=0;
int controloffset=0;
    while (temp<key_name)
    {f1.seekg(controloffset);
    int temp;
    f1.read(reinterpret_cast<char*>(&temp),4);
    headoffset=temp;
        //headoffset=nxtblock(headoffset);
        if (headoffset==-1) break;
        controloffset=headoffset;
        f3.seekg(headoffset+16);
        f3.read(reinterpret_cast<char*>(&temp),100);
    }
    f4.seekg(controloffset);
    block tempblock;
    //cout<<controloffset<<"&&&&& control offset in findelement"<<endl;
    f4.read(reinterpret_cast<char*>(&tempblock),sizeof (block));
    element tempelement;
    strcpy(tempelement.key,key_name.c_str());
    //cout<<tempelement.key<<" in find ele  temp.key"<<endl;
    //cout<<key_name<<"findelement"<<endl;
    //cout<<tempblock.array[0].key<<" 8888888"<<tempblock.array[1].key<<"debug in findelement"<<endl;
    //cout<<tempblock.numofelment<<"debug in tempblock.num in findelement"<<endl;
    int location=lower_bound(tempblock.array,tempblock.array+tempblock.numofelment,tempelement)-tempblock.array;//todo
    int nowlocation=location;//todo what's the fuuuck
    //cout<<location<<"location  debug in findnode"<<endl;

    //above is right
    while (nowlocation!=(tempblock.numofelment)&&key_name==tempblock.array[nowlocation].key){
        return_ans.push_back(tempblock.array[nowlocation].offset);
        nowlocation++;
    }
    if (nowlocation!=(tempblock.numofelment)){
        f1.close(),f2.close(),f3.close(),f4.close();
        return return_ans;
    } else//below may have bug
        {
        int the_beginofblock_offset;
        the_beginofblock_offset=nxtblock(controloffset);
        while (the_beginofblock_offset!=-1){
            f4.seekg(the_beginofblock_offset);
            f4.read(reinterpret_cast<char*>(&tempblock),sizeof (block));
            strcpy(tempelement.key,key_name.c_str());
            location=lower_bound(tempblock.array,tempblock.array+tempblock.numofelment,tempelement)-tempblock.array;
            nowlocation=location;

            while (nowlocation!=tempblock.numofelment&&key_name==tempblock.array[nowlocation].key){
                return_ans.push_back(tempblock.array[nowlocation].offset);
                nowlocation++;
            }
            if (nowlocation!=tempblock.numofelment) break;

            the_beginofblock_offset=nxtblock(the_beginofblock_offset);
        }
    }
    f1.close(),f2.close(),f3.close(),f4.close();
    return return_ans;
}
void deleteblock(int offset){//may be useless
    f1.open(filename,ios::in | ios::out|ios::binary);
    f2.open(filename,ios::in | ios::out|ios::binary);
    f3.open(filename,ios::in | ios::out|ios::binary);
    f4.open(filename,ios::in | ios::out|ios::binary);
    f1.seekg(offset);
    int pre,nxt;
    f1.read(reinterpret_cast<char*>(&nxt),4);
    f1.read(reinterpret_cast<char*>(&pre),4);
    if (pre==-1){
    block tempblock;
    f4.seekg(0);
        f4.write(reinterpret_cast<char*>(&tempblock),sizeof (block));
    } else{
        f2.seekg(pre);
        f2.write(reinterpret_cast<char*>(&nxt),4);
    }
    if (nxt!=-1){
        f3.seekg(nxt+4);
        f3.write(reinterpret_cast<char*>(&pre),4);
    }
    f1.close(),f2.close(),f3.close(),f4.close();
}
vector<int> return_all_offset(){
    vector<int >return_ans;
    f1.open(filename,ios::in | ios::out|ios::binary);
    f2.open(filename,ios::in | ios::out|ios::binary);
    f3.open(filename,ios::in | ios::out|ios::binary);
    f4.open(filename,ios::in | ios::out|ios::binary);
    //cout<<"DEBUG"<<endl;
    //debug_print_the_filenode();
    f1.seekg(0);
    int nxt;
    f1.read(reinterpret_cast<char*>(&nxt),4);
    //cout<<nxt<<"debug in the nxt output"<<endl;
    f2.seekg(0);
    block tempblock;
    f2.read(reinterpret_cast<char*>(&tempblock),sizeof (tempblock));
    //cout<<tempblock.numofelment<<"blocklist debug the numofelement"<<endl;
    for (int i = 0; i <tempblock.numofelment ; ++i) {
        //cout<<tempblock.array[i].key<<"___________*************____________"<<tempblock.array[i].offset<<endl;
    return_ans.push_back(tempblock.array[i].offset);
    }
    while (nxt!=-1)
    {
        f3.seekg(nxt);
        f3.read(reinterpret_cast<char*>(&tempblock),sizeof (tempblock));
        for (int i = 0; i <tempblock.numofelment ; ++i) {
            return_ans.push_back(tempblock.array[i].offset);
        }
        nxt=nxtblock(nxt);
    }
    f1.close(),f2.close(),f3.close(),f4.close();
    return return_ans;
}//用于show操作无参数的情况
void debug(){
    cout<<"____________________________________________________"<<endl;
    f1.open(filename,ios::in | ios::out|ios::binary);
    f2.open(filename,ios::in | ios::out|ios::binary);
    f3.open(filename,ios::in | ios::out|ios::binary);
    f4.open(filename,ios::in | ios::out|ios::binary);
    cout<<"DEBUG"<<endl;
    //debug_print_the_filenode();
    f1.seekg(0);
    int nxt;
    f1.read(reinterpret_cast<char*>(&nxt),4);
    cout<<nxt<<"debug in the nxt output"<<endl;
    f2.seekg(0);
    block tempblock;
    f2.read(reinterpret_cast<char*>(&tempblock),sizeof (tempblock));
    cout<<tempblock.numofelment<<"blocklist debug the numofelement"<<endl;
    for (int i = 0; i <tempblock.numofelment ; ++i) {
        cout<<tempblock.array[i].key<<"___________*************____________"<<tempblock.array[i].offset<<endl;
    }
    while (nxt!=-1)
    {
        f3.seekg(nxt);
        f3.read(reinterpret_cast<char*>(&tempblock),sizeof (tempblock));
        for (int i = 0; i <tempblock.numofelment ; ++i) {
            cout<<tempblock.array[i].key<<"&&&&& ---------**********    &&&&"<<tempblock.array[i].offset<<endl;
        }
        nxt=nxtblock(nxt);
    }
    f1.close(),f2.close(),f3.close(),f4.close();
    cout<<"the end of the blocklist debug"<<endl;
    cout<<"_________________________________________________"<<endl;
}
};


#endif //CODE_UNROLLEDLINKEDLIST_H
