//
// Created by lenovo on 2021/1/19.
//
#ifndef CODE_BOOKSTORE_H
#define CODE_BOOKSTORE_H
#pragma once
#include "blockchain.h"
#include "UserManager.h"
#include <iomanip>
#include <set>
#include <map>
//vector<string>splitkey(string index){
//    vector<string> returnvec;
//    int len=index.length();
//    string a1,a2,a3,a4,a5,a6,a7,a8;
//    int i;
//    for ( i = 0; i <len&&index[i]!='|' ; ++i) {a1+=index[i];}
//    returnvec.push_back(a1);
//    for (i++;i<len&&index[i]!='|';++i) {a2+=index[i];}
//    if (!a2.empty())returnvec.push_back(a2);
//    for (i++;i<len&&index[i]!='|';++i) {a3+=index[i];}
//    for (i++;i<len&&index[i]!='|';++i) {a4+=index[i];}
//    for (i++;i<len&&index[i]!='|';++i) {a5+=index[i];}
//    for (i++;i<len&&index[i]!='|';++i) {a6+=index[i];}
//    for (i++;i<len&&index[i]!='|';++i) {a7+=index[i];}
//    for (i++;i<len&&index[i]!='|';++i) {a8+=index[i];}
//    if (!a3.empty())returnvec.push_back(a3);
//    if (!a4.empty())returnvec.push_back(a4);
//    if (!a5.empty())returnvec.push_back(a5);
//    if (!a6.empty())returnvec.push_back(a6);
//    if (!a7.empty())returnvec.push_back(a7);
//    if (!a8.empty())returnvec.push_back(a8);
//    return returnvec;
//}
void init() ;
class Book{
public:char ISBN[30];
    char name[60];
    char author[60];
    char keywords[60];
    double price;
    int quantity;
    Book();
//缺少构造函数
};
enum bookinfo{
    ISBN,NAME,AUTHOR,KETWORDS
};
class bookstore{
public:
    int tradetimes;
    int booknum;
    double totaiinput,totoaloutput;
    usermanager cmd;
    UnrolledLinkedList ISBN_BOOKSTORE_blocklist,BOOKNAME_BOOKSTORE_blocklist,KEYWORD_BOOKSTORE,AUTHOR_BOOKSTORE;//the region of the four output
fstream f1,f2,f3,f4,f5,f6;
    bookstore();
    vector<string>splitkey(string index){
        vector<string> returnvec;
        if (index.empty()){return returnvec;}
        int len=index.length();
        string a1,a2,a3,a4,a5,a6,a7,a8;
        int i;
        for ( i = 0; i <len&&index[i]!='|' ; ++i) {a1+=index[i];}
        returnvec.push_back(a1);
        for (i++;i<len&&index[i]!='|';++i) {a2+=index[i];}
        if (!a2.empty())returnvec.push_back(a2);
        for (i++;i<len&&index[i]!='|';++i) {a3+=index[i];}
        for (i++;i<len&&index[i]!='|';++i) {a4+=index[i];}
        for (i++;i<len&&index[i]!='|';++i) {a5+=index[i];}
        for (i++;i<len&&index[i]!='|';++i) {a6+=index[i];}
        for (i++;i<len&&index[i]!='|';++i) {a7+=index[i];}
        for (i++;i<len&&index[i]!='|';++i) {a8+=index[i];}
        if (!a3.empty())returnvec.push_back(a3);
        if (!a4.empty())returnvec.push_back(a4);
        if (!a5.empty())returnvec.push_back(a5);
        if (!a6.empty())returnvec.push_back(a6);
        if (!a7.empty())returnvec.push_back(a7);
        if (!a8.empty())returnvec.push_back(a8);
        return returnvec;
    }
    void run(string temp);
    void select(string ISBN_){//modify the stack
       // cout<<cmd.usernum<<"   in select"<<endl;
        //cout<<cmd.user_stack[cmd.usernum-1].id<<"(((((in select"<<endl;
       // cout<<cmd.user_stack[cmd.usernum-1].priviledge<<"^^^^^^^ in select"<<endl;//random
        if (ISBN_.empty()||(cmd.user_stack[cmd.usernum-1].priviledge)<3) {
           //cout<<"^^ in selelct"<<endl;//todo
            cout<<"Invalid"<<endl;
            return;}
        //cout<<"&&&&&&&&&"<<endl;
        //(--cmd.user_stack.end())->currentbookISBN=atoi(ISBN_.c_str());
       // cout<<(--cmd.user_stack.end())->currentbookISBN<<"&&&&&&&"<<endl;
       vector<int>tempsearch (ISBN_BOOKSTORE_blocklist.findelement(ISBN_));
        if (tempsearch.empty()){
           //cout<<"is empty in select"<<endl;
            f1.open(BOOK_DATA,ios_base::binary|ios::in | ios::out);
            if (!f1){
                f1.open(BOOK_DATA,ios::out|ios::binary);
            }
//            f2.open(BOOK_DATA,ios_base::binary|ios::in | ios::out);
//            if (!f2){
//                f2.open(BOOK_DATA,ios::out|ios::binary);
//            }
//            f2.seekg(0);
//            char tempnam[30];
//            f2.read(reinterpret_cast<char*>(&tempnam),30);
//            cout<<"f2.fail:  "<<f2.fail()<<endl;
//            cout<<tempnam<<"test in select in tempnam"<<endl;
            f1.seekg(0,ios::end);
            int tempoffset=f1.tellg();//must be incorrect
           // cout<<tempoffset<<"***************in name selsect"<<endl;//todo
            Book tempbook;
            strcpy(tempbook.ISBN,ISBN_.c_str());
            f1.write(reinterpret_cast<char*>(&tempbook),sizeof (Book));
            element tempele;
            tempele.offset=tempoffset;
            strcpy(tempele.key,ISBN_.c_str());
            //cout<<ISBN_.c_str()<<" in select"<<endl;
            ISBN_BOOKSTORE_blocklist.addelement(element(tempoffset,ISBN_.c_str()));//todo
           // cout<<"select fuction:"<<endl;
           // ISBN_BOOKSTORE_blocklist.debug();
          //  cout<<"select fuc"<<endl;
            (--cmd.user_stack.end())->currentbookISBN=tempoffset;
            //ISBN_BOOKSTORE_blocklist.debug();
            f1.close();
        } else{
            (--cmd.user_stack.end())->currentbookISBN=tempsearch[0];
//    vector<int> temp(ISBN_BOOKSTORE_blocklist.findelement(ISBN_));
//    int tempoffset=temp[0];
//            f1.open(BOOK_DATA,ios_base::binary|ios::in | ios::out);
//            if (!f1){
//                f1.open(BOOK_DATA,ios::out|ios::binary);
//            }
//            f1.seekg(tempoffset);
//            f1.write(reinterpret_cast<char*>(&ISBN_),40);
//            element tempelement;
//            strcpy(tempelement.key,ISBN_.c_str());
//            tempelement.offset=tempoffset;
//            ISBN_BOOKSTORE_blocklist.deleteelment(tempelement);
//            ISBN_BOOKSTORE_blocklist.addelement(tempelement);
        }
    }
    void import(int tempquantity,double allcost){
        if ((cmd.user_stack[cmd.usernum-1].priviledge)<3||cmd.user_stack[cmd.usernum-1].currentbookISBN==-1) {
            cout<<"Invalid"<<endl;
            return;}
int tempisbn=cmd.user_stack[cmd.usernum-1].currentbookISBN;
        f6.open(BOOK_DATA,ios_base::binary|ios::in | ios::out);
        if (!f6){
            f6.open(BOOK_DATA,ios::out|ios::binary);
        }
        f6.seekg(tempisbn);
        Book tempbook;
        f6.read(reinterpret_cast<char*>(&tempbook),sizeof (Book));
        char ss[30];
        strcpy(ss,tempbook.ISBN);
        //cout<<ss<<"   import"<<endl;
        string s=ss;
        f6.close();
        //std::string s = std::to_string(tempisbn) ;
        vector<int>tempsearch (ISBN_BOOKSTORE_blocklist.findelement(s));
        int tempoffset=tempsearch[0];
        f1.open(BOOK_DATA,ios_base::binary|ios::in | ios::out);
        if (!f1){
            f1.open(BOOK_DATA,ios::out|ios::binary);
        }
        f1.seekg(tempoffset);
        Book tempbook2;
        int prenum;
        f1.read(reinterpret_cast<char*>(&tempbook),sizeof (Book));
        tempbook.quantity+=tempquantity;
        f1.seekg(tempoffset);
        f1.write(reinterpret_cast<char*>(&tempbook),sizeof (Book));
        f2.open(TOTAL_FINANCE_DATA,ios_base::binary|ios::in | ios::out);
        if (!f2){
            f2.open(TOTAL_FINANCE_DATA,ios::out|ios::binary);
        }
        totoaloutput+=allcost;
        booknum+=tempquantity;
        tradetimes++;
        //写入顺序，总收入，总支出，书本数量，交易次数
        f2.seekg(0);
        f2.write(reinterpret_cast<char*>(&totaiinput),8);
        f2.write(reinterpret_cast<char*>(&totoaloutput),8);
        f2.write(reinterpret_cast<char*>(&booknum),4);
        f2.write(reinterpret_cast<char*>(&tradetimes),4);
        f2.close();
        f2.open(EVERT_FINANCE_DATA,ios_base::binary|ios::in | ios::out);
        if (!f2){
            f2.open(EVERT_FINANCE_DATA,ios::out|ios::binary);
        }
        f2.seekg(0,ios::end);
        bool output=1;//1定义为支出，0定义为收入
        f2.write(reinterpret_cast<char*>(&output),sizeof (bool));
        f2.write(reinterpret_cast<char*>(&allcost),sizeof (double ));
        f1.close(),f2.close();
    }
    void modify(string keycharacter,string index,int offset){
      // cout<<"?????????begin in modify"<<endl;
      //cout<<"index  :"<<index<<"       in modify"<<endl;
        if (index.empty()||(cmd.user_stack[cmd.usernum-1].priviledge)<3||cmd.user_stack[cmd.usernum-1].currentbookISBN==-1) {
           //cout<<"first invalid in modify fuction"<<endl;
            cout<<"Invalid"<<endl;
            return;}
        f1.open(BOOK_DATA,ios_base::binary|ios::in | ios::out);
        if (!f1){
            f1.open(BOOK_DATA,ios::out|ios::binary);
        }
        f1.seekg(offset);

        char isbnstring_[30];
        f1.read(reinterpret_cast<char*>(&isbnstring_),30);
        string isbnstring=isbnstring_;
      //  cout<<isbnstring<<"   isbnstring in modify fuction"<<endl;
        //cout<<f1.fail()<<"  in the modify begin f1.fail"<<endl;

        if (keycharacter=="author"){
            vector<int>tempsearch (ISBN_BOOKSTORE_blocklist.findelement(isbnstring));
            if (tempsearch.empty()){
               // cout<<"   find result empty in modify"<<endl;
                cout<<"Invalid"<<endl;
                return;}
            int tempoffset=tempsearch[0];
            f6.open(BOOK_DATA,ios_base::binary|ios::in | ios::out);
            if (!f6){
                f6.open(BOOK_DATA,ios::out|ios::binary);
            }
            //cout<<f6.fail()<<" f1.fail"<<" in modify_ISBN"<<endl;
            f6.seekg(tempoffset+90);
            char pre_author[60];
            f6.read(reinterpret_cast<char*>(&pre_author),60);
            //modify
            // cout<<pre_author<<"debug in preauthor in modify-ISBN branch"<<endl;
            //cout<<index<<" index in modify-ISBN branch"<<endl;
//            vector<int>tempsearch2 (ISBN_BOOKSTORE_blocklist.findelement(index));
//            // ISBN_BOOKSTORE_blocklist.debug();
//            //cout<<tempsearch2[0]<<"debug in modify_ISBN"<<endl;
//            if (!tempsearch2.empty()){cout<<"Invalid"<<endl;
//                //cout<<"the isbn is exist yet in modify ISBN"<<endl;
//                f1.close();
//                f6.close();
//                return;}
            f6.seekg(tempoffset+90);

            //modify__
            char index_[60];
            string tempput;
            strcpy(index_,index.c_str());
            for (int i = 1; index_[i] !='"' ; ++i) {
                tempput+=index_[i];
            }
            char writein[60];
            strcpy(writein,tempput.c_str());
            //cout<<index_<<"author in modify"<<endl;
            f6.write(reinterpret_cast<char*>(&writein),60);//modify__
            //cout<<index_<<" debug in index_ in modify in ISBN"<<endl;
            AUTHOR_BOOKSTORE.deleteelment(element(tempoffset,pre_author));
            //ISBN_BOOKSTORE_blocklist.debug();
            AUTHOR_BOOKSTORE.addelement(element(tempoffset,writein));
            //ISBN_BOOKSTORE_blocklist.debug();
            f1.close();
            f6.close();

        }
        else if (keycharacter=="name"){
           // ISBN_BOOKSTORE_blocklist.debug();
            vector<int>tempsearch (ISBN_BOOKSTORE_blocklist.findelement(isbnstring));
            if (tempsearch.empty()){
               // cout<<"   tempsearch empty!!! in modify_name"<<endl;
                cout<<"Invalid"<<endl;
                f1.close();
                return;}
            int tempoffset=tempsearch[0];
            f6.open(BOOK_DATA,ios_base::binary|ios::in | ios::out);
            if (!f6){
                f6.open(BOOK_DATA,ios::out|ios::binary);
            }
            //cout<<f6.fail()<<" f1.fail"<<" in modify_ISBN"<<endl;
            f6.seekg(tempoffset+30);
            char pre_author[60];
            f6.read(reinterpret_cast<char*>(&pre_author),60);
            //modify
            // cout<<pre_author<<"debug in preauthor in modify-ISBN branch"<<endl;
            //cout<<index<<" index in modify-ISBN branch"<<endl;
//            vector<int>tempsearch2 (ISBN_BOOKSTORE_blocklist.findelement(index));
//            // ISBN_BOOKSTORE_blocklist.debug();
//            //cout<<tempsearch2[0]<<"debug in modify_ISBN"<<endl;
//            if (!tempsearch2.empty()){cout<<"Invalid"<<endl;
//                //cout<<"the isbn is exist yet in modify ISBN"<<endl;
//                f1.close();
//                f6.close();
//                return;}
            f6.seekg(tempoffset+30);

            //modify__
            char index_[60];
            string tempput;
            strcpy(index_,index.c_str());
            for (int i = 1; index_[i] !='"' ; ++i) {
                tempput+=index_[i];
            }
            char writein[60];
            strcpy(writein,tempput.c_str());


            f6.write(reinterpret_cast<char*>(&writein),60);//modify__
            //cout<<index_<<" debug in index_ in modify in ISBN"<<endl;
            BOOKNAME_BOOKSTORE_blocklist.deleteelment(element(tempoffset,pre_author));
            //ISBN_BOOKSTORE_blocklist.debug();
             BOOKNAME_BOOKSTORE_blocklist.addelement(element(tempoffset,writein));
            //ISBN_BOOKSTORE_blocklist.debug();
            f1.close();
            f6.close();


        }
        else if (keycharacter=="ISBN"){
            //cout<<"go into in modify_ISBN fuction"<<endl;
            vector<int>tempsearch (ISBN_BOOKSTORE_blocklist.findelement(isbnstring));
            if (tempsearch.empty()){
                //cout<<"finresult is empty  in modify"<<endl;
                cout<<"Invalid"<<endl;
                f1.close();
                return;}
            int tempoffset=tempsearch[0];
            //cout<<tempoffset<<"  tempoffset in ISBN in modify"<<endl;

            //modify
            f6.open(BOOK_DATA,ios_base::binary|ios::in | ios::out);
            if (!f6){
                f6.open(BOOK_DATA,ios::out|ios::binary);
            }
            //cout<<f6.fail()<<" f1.fail"<<" in modify_ISBN"<<endl;
            f6.seekg(tempoffset);
            char pre_author[30];
            f6.read(reinterpret_cast<char*>(&pre_author),30);
            //modify
           // cout<<pre_author<<"debug in preauthor in modify-ISBN branch"<<endl;
            //cout<<index<<" index in modify-ISBN branch"<<endl;
            vector<int>tempsearch2 (ISBN_BOOKSTORE_blocklist.findelement(index));
           // ISBN_BOOKSTORE_blocklist.debug();
            //cout<<tempsearch2[0]<<"debug in modify_ISBN"<<endl;
            if (!tempsearch2.empty()){cout<<"Invalid"<<endl;
            //cout<<"the isbn is exist yet in modify ISBN"<<endl;
            f1.close();
            f6.close();
                return;}
            f6.seekg(tempoffset);

            //modify__
            char index_[30];
            strcpy(index_,index.c_str());
            f6.write(reinterpret_cast<char*>(&index_),30);//modify__
            //cout<<index_<<" debug in index_ in modify in ISBN"<<endl;
            ISBN_BOOKSTORE_blocklist.deleteelment(element(tempoffset,pre_author));
            //ISBN_BOOKSTORE_blocklist.debug();
          ISBN_BOOKSTORE_blocklist.addelement(element(tempoffset,index));
            //ISBN_BOOKSTORE_blocklist.debug();
           // cout<<"in modify ISBN"<<endl;
            f1.close();
            f6.close();

        }
        else if (keycharacter=="keyword"){//注意这里不同于上面，关键词要求一个一个添加到块状链表中
            vector<int>tempsearch (ISBN_BOOKSTORE_blocklist.findelement(isbnstring));
            if (tempsearch.empty()){
                cout<<"Invalid"<<endl;
                f1.close();
                return;}
            int tempoffset=tempsearch[0];
            f6.open(BOOK_DATA,ios_base::binary|ios::in | ios::out);
            if (!f6){
                f6.open(BOOK_DATA,ios::out|ios::binary);
            }
            //cout<<f6.fail()<<" f1.fail"<<" in modify_ISBN"<<endl;
            f6.seekg(tempoffset+150);
            char pre_author[60];
            f6.read(reinterpret_cast<char*>(&pre_author),60);
            //modify
            // cout<<pre_author<<"debug in preauthor in modify-ISBN branch"<<endl;
            //cout<<index<<" index in modify-ISBN branch"<<endl;
//            vector<int>tempsearch2 (ISBN_BOOKSTORE_blocklist.findelement(index));
//            // ISBN_BOOKSTORE_blocklist.debug();
//            //cout<<tempsearch2[0]<<"debug in modify_ISBN"<<endl;
//            if (!tempsearch2.empty()){cout<<"Invalid"<<endl;
//                //cout<<"the isbn is exist yet in modify ISBN"<<endl;
//                f1.close();
//                f6.close();
//                return;}
            f6.seekg(tempoffset+150);

            char index_[60];
            string tempput;
            strcpy(index_,index.c_str());
            for (int i = 1; index_[i] !='"' ; ++i) {
                tempput+=index_[i];
            }
            char writein[60];
            strcpy(writein,tempput.c_str());


            f6.write(reinterpret_cast<char*>(&writein),60);//modify__
            //cout<<index_<<" debug in index_ in modify in ISBN"<<endl;
            vector<string>tempvec(splitkey(tempput));
            string str(pre_author);
            vector<string>tempbefore(splitkey(str));
            //todo
            map<string,int> tempmap;
            set<string>s;
            for (int i = 0; i<tempvec.size() ; ++i) {
            s.insert(tempvec[i]);
            }
            if (s.size()!=tempvec.size()){
                cout<<"Invalid"<<endl;
                f1.close(),f6.close();
                return;
            }
            for (int i = 0; i <tempbefore.size() ; ++i) {
                KEYWORD_BOOKSTORE.deleteelment(element(tempoffset,tempbefore[i]));
            }
            for (int i = 0; i < tempvec.size(); ++i) {
                KEYWORD_BOOKSTORE.addelement(element(tempoffset,tempvec[i]));
            }
            //ISBN_BOOKSTORE_blocklist.debug();

            //ISBN_BOOKSTORE_blocklist.debug();
            f1.close();
            f6.close();

        }
        else if(keycharacter=="price"){
            vector<int>tempsearch (ISBN_BOOKSTORE_blocklist.findelement(isbnstring));
            if (tempsearch.empty()){
                cout<<"Invalid"<<endl;
                f1.close();
                return;}
            int tempoffset=tempsearch[0];
            f6.open(BOOK_DATA,ios_base::binary|ios::in | ios::out);
            if (!f6){
                f6.open(BOOK_DATA,ios::out|ios::binary);
            }
            f6.seekg(tempoffset);
           // cout<<f6.fail()<<"    f1.fail() in modify in price"<<endl;
            double d = atof((index.c_str()));
            Book tempbook;
            f6.read(reinterpret_cast<char*>(&tempbook),sizeof (Book));
            tempbook.price=d;
          //  cout<<tempbook.ISBN<<" "<<tempbook.name<<" "<<tempbook.author<<" "<<tempbook.keywords<<" "<<setiosflags(ios::fixed) << setprecision(2)<<tempbook.price<<" "<<tempbook.quantity<<"debug in modify_price"<<endl;
            f6.seekg(tempoffset);
            f6.write(reinterpret_cast<char*>(&tempbook),sizeof (Book));
            {
//            f1.seekg(tempoffset+210);
//            cout<<index<<"  modify price "<<endl;
//            double d = atof((index.c_str()));
//            cout<<d<<"    double modify price"<<endl;
//            cout<<sizeof (d)<< "size of d"<<endl;
//            cout<<sizeof (Book)<<"size of book"<<endl;
//
//            f1.write(reinterpret_cast<char*>(&d),8);
        }
            f1.close();
            f6.close();
        }}
    void show(string command){
    //分成两个部分丢给两个子函数执行吧！
    int len=command.length();
    string head,body1,body2,body3,body4;
    int i;
        for (i = 0; i <len&&command[i]!=' ' ; ++i) {
            head+=command[i];
        }
        if (i==len){
            showall();
        } else{
            int temp=i;
            for (++i; i <len&&command[i]!=' ' ; ++i) {
                body1+=command[i];
            }
            //cout<<body1<<endl;
            if (body1=="finance"){
                if (i==len){
                    showfinance(-1);
                } else{
                    for (++i; i <len&&command[i]!=' ' ; ++i) {
                        body2+=command[i];
                    }
                    if (atoi(body2.c_str())<0){cout<<"Invalid"<<endl;return;}
                    showfinance(atoi(body2.c_str()));
                }
            }
            else{
               // cout<<head<<endl;
                for (temp+=2; command[temp]!='=' ; ++temp) {body3+=command[temp];}
                for (temp++; temp<len ; ++temp) {body4+=command[temp];}
                //cout<<body3<<"    "<<body4<<endl;
                show_part_withrestrict(body3,body4);
            }
        }
    }
    void buy(string ISBN_,string quantity){
        //cout<<"in buy"<<endl;
        int tempquantity=atoi(quantity.c_str());

        vector<int>tempsearch (ISBN_BOOKSTORE_blocklist.findelement(ISBN_));
        if (tempsearch.empty()){
            cout<<"Invalid"<<endl;
            return;}
        if (tempquantity==0){
            cout<<"0.00"<<endl;
            return;}
        int tempoffset=tempsearch[0];
       // cout<<tempoffset<<"   in buy tempoffset"<<"  ISBN:"<<ISBN_<<endl;
        f1.open(BOOK_DATA,ios_base::binary|ios::in | ios::out);
        if (!f1){
            f1.open(BOOK_DATA,ios::out|ios::binary);
        }
        Book tempbook;
        f1.seekg(tempoffset);
        double nowprice;
        int booknum_for_storage;
        f1.read(reinterpret_cast<char*>(&tempbook),sizeof (Book ));
        if (tempbook.quantity<tempquantity){
            cout<<"Invalid"<<endl;
        f1.close();
            return;}
        tempbook.quantity-=tempquantity;
        double bookprice=tempbook.price;
       // cout<<bookprice<<"   bookprice"<<endl;
        f1.seekg(tempoffset);
        f1.write(reinterpret_cast<char*>(&tempbook),sizeof (Book));
       // f1.read(reinterpret_cast<char*>(&booknum_for_storage),sizeof (int));
       // booknum_for_storage+=tempquantity;
       // f1.seekg(tempoffset+218);
        //f1.write(reinterpret_cast<char*>(&booknum_for_storage),sizeof (int));
        f2.open(TOTAL_FINANCE_DATA,ios_base::binary|ios::in | ios::out);
        if (!f2){
            f2.open(TOTAL_FINANCE_DATA,ios::out|ios::binary);
        }
       totaiinput+=(tempquantity*bookprice);
        booknum-=tempquantity;
        tradetimes++;
        //写入顺序，总收入，总支出，书本数量，交易次数
        f2.seekg(0);
        f2.write(reinterpret_cast<char*>(&totaiinput),8);
        f2.write(reinterpret_cast<char*>(&totoaloutput),8);
        f2.write(reinterpret_cast<char*>(&booknum),4);
        f2.write(reinterpret_cast<char*>(&tradetimes),4);
        f2.close();
        f2.open(EVERT_FINANCE_DATA,ios_base::binary|ios::in | ios::out);
        if (!f2){
            f2.open(EVERT_FINANCE_DATA,ios::out|ios::binary);
        }
        f2.seekg(0,ios::end);
        bool output=0;//1定义为支出，0定义为收入
        double allcost=bookprice*tempquantity;
        //cout<<allcost<<"    buy "<<endl;
        f2.write(reinterpret_cast<char*>(&output),sizeof (bool));
        f2.write(reinterpret_cast<char*>(&allcost),sizeof (double ));
        f1.close(),f2.close();
        cout<<setiosflags(ios::fixed) << setprecision(2)<<allcost<<endl;
       // cout<<" the end in buy"<<endl;
    }
    void showall(){
        //ISBN_BOOKSTORE_blocklist.debug();
        //cout<<"above is showall in bookstore.h"<<endl;
        if (cmd.user_stack[cmd.usernum-1].priviledge<1){
            cout<<"Invalid"<<endl;
            return;
        }
vector<int >shoe_vec(ISBN_BOOKSTORE_blocklist.return_all_offset());
        if (shoe_vec.empty()){cout<<endl;
            return;}
        //cout<<shoe_vec[0]<<"  "<<sh
        for (int i = 0; i <shoe_vec.size() ; ++i) {
            //cout<<shoe_vec[i]<<endl;
            f1.open(BOOK_DATA,ios_base::binary|ios::in | ios::out);
            if (!f1){
                f1.open(BOOK_DATA,ios::out|ios::binary);
            }
            f1.seekg(shoe_vec[i]);
            Book tempbook;
            f1.read(reinterpret_cast<char*>(&tempbook),sizeof (Book));
           // cout<<tempbook.price<<"   price"<<endl;
            double output=0;
            if (tempbook.price==-1){  printf("%s\t%s\t%s\t%s\t%.2lf\t%d\n", tempbook.ISBN, tempbook.name, tempbook.author, tempbook.keywords, output, tempbook.quantity);
            } else printf("%s\t%s\t%s\t%s\t%.2lf\t%d\n", tempbook.ISBN, tempbook.name, tempbook.author, tempbook.keywords, tempbook.price, tempbook.quantity);
f1.close();
        }
//        cout<<"in show all"<<endl;
//        vector<int>::iterator it = shoe_vec.begin();
//
//        for(; it != shoe_vec.end(); ++it)
//        {
//            f1.open(BOOK_DATA,ios_base::binary|ios::in | ios::out);
//            if (!f1){
//                f1.open(BOOK_DATA,ios::out|ios::binary);
//            }
//            f1.seekg(*it);
//            char ISBN_[30];
//            char name_[60];
//            char author_[60];
//            char keywords_[60];
//            double price_;
//            int quantity_;
//            f1.read(reinterpret_cast<char*>(&ISBN_),30);
//            f1.read(reinterpret_cast<char*>(&name_),60);
//            f1.read(reinterpret_cast<char*>(&author_),60);
//            f1.read(reinterpret_cast<char*>(&keywords_),60);
//            f1.read(reinterpret_cast<char*>(&price_),8);//两位小数输出
//            f1.read(reinterpret_cast<char*>(&quantity_),4);
//            cout<<ISBN_<<" "<<name_<<" "<<author_<<" "<<keywords_<<" "<<setiosflags(ios::fixed) << setprecision(2)<<price_<<" "<<quantity_<<endl;
//            //cout<<(*it)<<" ";
//        }
//        f1.close();
    }
    void  show_part_withrestrict(string type,string keyword){
       // cout<<cmd.user_stack[cmd.usernum-1].priviledge<<"show with restrict"<<endl;
        if (cmd.user_stack[cmd.usernum-1].priviledge<1||keyword.empty()){
            cout<<"Invalid"<<endl;
            return;
        }
        struct pair_ISBN_offset{
            int offset;
            string ISBN;
            pair_ISBN_offset(string s,int a):ISBN(s),offset(a){}
            pair_ISBN_offset() {}
            bool operator <(const  pair_ISBN_offset &s) const {
                return ISBN<s.ISBN;
            }
        };
        if (type=="ISBN") {
            vector<int > tempans(ISBN_BOOKSTORE_blocklist.findelement(keyword));
            if (tempans.empty()){cout<<endl;
                return;}
            int tempooffset=tempans[0];
            f1.open(BOOK_DATA,ios_base::binary|ios::in | ios::out);
            if (!f1){
                f1.open(BOOK_DATA,ios::out|ios::binary);
            }
            f6.open(BOOK_DATA,ios_base::binary|ios::in | ios::out);
            if (!f6){
                f6.open(BOOK_DATA,ios::out|ios::binary);
            }
            f6.seekg(tempooffset);
           // cout<<tempooffset<<" debug in modify tempoffset"<<endl;

            Book tempbook;
            f6.read(reinterpret_cast<char*>(&tempbook),sizeof(Book));
           // cout<<tempbook.price<<"   book.price "<<endl;
             double output=0;
            if (tempbook.price==-1){  printf("%s\t%s\t%s\t%s\t%.2lf\t%d\n", tempbook.ISBN, tempbook.name, tempbook.author, tempbook.keywords, output, tempbook.quantity);
            } else printf("%s\t%s\t%s\t%s\t%.2lf\t%d\n", tempbook.ISBN, tempbook.name, tempbook.author, tempbook.keywords, tempbook.price, tempbook.quantity);

            //printf("%s\t%s\t%s\t%s\t%.2lf\t%d\n", tempbook.ISBN, tempbook.name, tempbook.author, tempbook.keywords, tempbook.price, tempbook.quantity);
            f1.seekg(tempooffset);
            char ISBN_[30];
            char name_[60];
            char author_[60];
            char keywords_[60];
            double price_;
            int quantity_;
            f1.read(reinterpret_cast<char*>(&ISBN_),30);
            f1.read(reinterpret_cast<char*>(&name_),60);
            f1.read(reinterpret_cast<char*>(&author_),60);
            f1.read(reinterpret_cast<char*>(&keywords_),60);
            f1.read(reinterpret_cast<char*>(&price_),8);//两位小数输出
            f1.read(reinterpret_cast<char*>(&quantity_),4);
            //cout<<price_<<" price in show with restrict"<<endl;
            //cout<<ISBN_<<" "<<name_<<" "<<author_<<" "<<keywords_<<" "<<setiosflags(ios::fixed) << setprecision(2)<<price_<<" "<<quantity_<<endl;
        f6.close();
        }
        if (type=="author"){
            int len=keyword.length();
            string beyong_master;
            for (int i = 1; i <len-1 ; ++i) {
                beyong_master+=keyword[i];
            }
            vector<int > tempans(AUTHOR_BOOKSTORE.findelement(beyong_master));
            if (tempans.empty()){cout<<endl;
                return;}
            f1.open(BOOK_DATA,ios_base::binary|ios::in | ios::out);
            if (!f1){
                f1.open(BOOK_DATA,ios::out|ios::binary);
            }
            set<pair_ISBN_offset> s;
            for (vector<int>::const_iterator iter = tempans.cbegin();iter !=tempans.cend(); iter++) {
                //cout << (*iter) << endl;
                f1.seekg(*iter);
                char ISBN_[30];
                char name_[60];
                char author_[60];
                char keywords_[60];
                double price_;
                int quantity_;
                f1.read(reinterpret_cast<char*>(&ISBN_),30);
                f1.read(reinterpret_cast<char*>(&name_),60);
                f1.read(reinterpret_cast<char*>(&author_),60);
                f1.read(reinterpret_cast<char*>(&keywords_),60);
                f1.read(reinterpret_cast<char*>(&price_),8);//两位小数输出
                f1.read(reinterpret_cast<char*>(&quantity_),4);
                string name1;
                name1 = ISBN_;
                s.insert(pair_ISBN_offset(name1,*iter));
                //cout<<ISBN_<<" "<<name_<<" "<<author_<<" "<<keywords_<<" "<<setiosflags(ios::fixed) << setprecision(2)<<price_<<" "<<quantity_<<endl;
            }
            set<pair_ISBN_offset>::iterator it;
            for(it=s.begin ();it!=s.end ();it++)
            {f6.open(BOOK_DATA,ios_base::binary|ios::in | ios::out);
                if (!f6){
                    f6.open(BOOK_DATA,ios::out|ios::binary);
                }
                f6.seekg(it->offset);
              //  cout<<it->offset<<" debug in modify tempoffset"<<endl;

                Book tempbook;
                f6.read(reinterpret_cast<char*>(&tempbook),sizeof(Book));
               // cout<<tempbook.price<<"   book.price "<<endl;
                 double output=0;
            if (tempbook.price==-1){  printf("%s\t%s\t%s\t%s\t%.2lf\t%d\n", tempbook.ISBN, tempbook.name, tempbook.author, tempbook.keywords, output, tempbook.quantity);
            } else printf("%s\t%s\t%s\t%s\t%.2lf\t%d\n", tempbook.ISBN, tempbook.name, tempbook.author, tempbook.keywords, tempbook.price, tempbook.quantity);

f6.close();





                f1.seekg(it->offset);




                char ISBN_[30];
                char name_[60];
                char author_[60];
                char keywords_[60];
                double price_;
                int quantity_;
                f1.read(reinterpret_cast<char*>(&ISBN_),30);
                f1.read(reinterpret_cast<char*>(&name_),60);
                f1.read(reinterpret_cast<char*>(&author_),60);
                f1.read(reinterpret_cast<char*>(&keywords_),60);
                f1.read(reinterpret_cast<char*>(&price_),8);//两位小数输出
                f1.read(reinterpret_cast<char*>(&quantity_),4);
               // cout<<ISBN_<<" "<<name_<<" "<<author_<<" "<<keywords_<<" "<<setiosflags(ios::fixed) << setprecision(2)<<price_<<" "<<quantity_<<endl;
            }
        }
        if (type=="keyword"){
            //KEYWORD_BOOKSTORE.debug();
            //cout<<" aboye is in the bookstore.h showwithrestrict keyword"<<endl;
            int len=keyword.length();
            string beyong_master;
            for (int i = 1; i <len-1 ; ++i) {
                beyong_master+=keyword[i];
            }
            vector<int > tempans(KEYWORD_BOOKSTORE.findelement(beyong_master));
            if (tempans.empty()){cout<<endl;
                return;}
            f1.open(BOOK_DATA,ios_base::binary|ios::in | ios::out);
            if (!f1){
                f1.open(BOOK_DATA,ios::out|ios::binary);
            }
            set<pair_ISBN_offset> s;
            for (vector<int>::const_iterator iter = tempans.cbegin();iter !=tempans.cend(); iter++) {
                //cout << (*iter) << endl;
                f1.seekg(*iter);
                char ISBN_[30];
                char name_[60];
                char author_[60];
                char keywords_[60];
                double price_;
                int quantity_;
                f1.read(reinterpret_cast<char*>(&ISBN_),30);
                f1.read(reinterpret_cast<char*>(&name_),60);
                f1.read(reinterpret_cast<char*>(&author_),60);
                f1.read(reinterpret_cast<char*>(&keywords_),60);
                f1.read(reinterpret_cast<char*>(&price_),8);//两位小数输出
                f1.read(reinterpret_cast<char*>(&quantity_),4);
                string name1;
                name1 = ISBN_;
                s.insert(pair_ISBN_offset(name1,*iter));
                //cout<<ISBN_<<" "<<name_<<" "<<author_<<" "<<keywords_<<" "<<setiosflags(ios::fixed) << setprecision(2)<<price_<<" "<<quantity_<<endl;
            }
            set<pair_ISBN_offset>::iterator it;
            for(it=s.begin ();it!=s.end ();it++)
            {
                f6.open(BOOK_DATA,ios_base::binary|ios::in | ios::out);
                if (!f6){
                    f6.open(BOOK_DATA,ios::out|ios::binary);
                }
                f6.seekg(it->offset);
              //  cout<<it->offset<<" debug in modify tempoffset"<<endl;

                Book tempbook;
                f6.read(reinterpret_cast<char*>(&tempbook),sizeof(Book));
               // cout<<tempbook.price<<"   book.price "<<endl;
                printf("%s\t%s\t%s\t%s\t%.2lf\t%d\n", tempbook.ISBN, tempbook.name, tempbook.author, tempbook.keywords, tempbook.price, tempbook.quantity);
                f6.close();

                f1.seekg(it->offset);
                char ISBN_[30];
                char name_[60];
                char author_[60];
                char keywords_[60];
                double price_;
                int quantity_;
                f1.read(reinterpret_cast<char*>(&ISBN_),30);
                f1.read(reinterpret_cast<char*>(&name_),60);
                f1.read(reinterpret_cast<char*>(&author_),60);
                f1.read(reinterpret_cast<char*>(&keywords_),60);
                f1.read(reinterpret_cast<char*>(&price_),8);//两位小数输出
                f1.read(reinterpret_cast<char*>(&quantity_),4);
              //  cout<<ISBN_<<" "<<name_<<" "<<author_<<" "<<keywords_<<" "<<setiosflags(ios::fixed) << setprecision(2)<<price_<<" "<<quantity_<<endl;
            }
        }
        if (type=="name"){
            int len=keyword.length();
            string beyong_master;
            for (int i = 1; i <len-1 ; ++i) {
                beyong_master+=keyword[i];
            }
            vector<int > tempans(BOOKNAME_BOOKSTORE_blocklist.findelement(beyong_master));
            if (tempans.empty()){cout<<endl;
                return;}
            f1.open(BOOK_DATA,ios_base::binary|ios::in | ios::out);
            if (!f1){
                f1.open(BOOK_DATA,ios::out|ios::binary);
            }
            set<pair_ISBN_offset> s;
            for (vector<int>::const_iterator iter = tempans.cbegin();iter !=tempans.cend(); iter++) {
                //cout << (*iter) << endl;
                f1.seekg(*iter);
                char ISBN_[30];
                char name_[60];
                char author_[60];
                char keywords_[60];
                double price_;
                int quantity_;
                f1.read(reinterpret_cast<char*>(&ISBN_),30);
                f1.read(reinterpret_cast<char*>(&name_),60);
                f1.read(reinterpret_cast<char*>(&author_),60);
                f1.read(reinterpret_cast<char*>(&keywords_),60);
                f1.read(reinterpret_cast<char*>(&price_),8);//两位小数输出
                f1.read(reinterpret_cast<char*>(&quantity_),4);
                string name1;
                name1 = ISBN_;
                s.insert(pair_ISBN_offset(name1,*iter));
                //cout<<ISBN_<<" "<<name_<<" "<<author_<<" "<<keywords_<<" "<<setiosflags(ios::fixed) << setprecision(2)<<price_<<" "<<quantity_<<endl;
            }
            set<pair_ISBN_offset>::iterator it;
            for(it=s.begin ();it!=s.end ();it++)
            {
                f6.open(BOOK_DATA,ios_base::binary|ios::in | ios::out);
                if (!f6){
                    f6.open(BOOK_DATA,ios::out|ios::binary);
                }
                f6.seekg(it->offset);
                //cout<<it->offset<<" debug in modify tempoffset"<<endl;

                Book tempbook;
                f6.read(reinterpret_cast<char*>(&tempbook),sizeof(Book));
                //cout<<tempbook.price<<"   book.price "<<endl;
                 double output=0;
            if (tempbook.price==-1){  printf("%s\t%s\t%s\t%s\t%.2lf\t%d\n", tempbook.ISBN, tempbook.name, tempbook.author, tempbook.keywords, output, tempbook.quantity);
            } else printf("%s\t%s\t%s\t%s\t%.2lf\t%d\n", tempbook.ISBN, tempbook.name, tempbook.author, tempbook.keywords, tempbook.price, tempbook.quantity);

                f6.close();

                f1.seekg(it->offset);
                char ISBN_[30];
                char name_[60];
                char author_[60];
                char keywords_[60];
                double price_;
                int quantity_;
                f1.read(reinterpret_cast<char*>(&ISBN_),30);
                f1.read(reinterpret_cast<char*>(&name_),60);
                f1.read(reinterpret_cast<char*>(&author_),60);
                f1.read(reinterpret_cast<char*>(&keywords_),60);
                f1.read(reinterpret_cast<char*>(&price_),8);//两位小数输出
                f1.read(reinterpret_cast<char*>(&quantity_),4);
              //  cout<<ISBN_<<" "<<name_<<" "<<author_<<" "<<keywords_<<" "<<setiosflags(ios::fixed) << setprecision(2)<<price_<<" "<<quantity_<<endl;
            }
        }
        f1.close();
    }
    void showfinance(int time){
        if (cmd.user_stack[cmd.usernum-1].priviledge<7){
            cout<<"Invalid"<<endl;
            return;
        }
        if (time==-1){
            f1.open(EVERT_FINANCE_DATA,ios_base::binary|ios::in | ios::out);
            if (!f1){
                f1.open(EVERT_FINANCE_DATA,ios::out|ios::binary);
            }
            f2.open(EVERT_FINANCE_DATA,ios_base::binary|ios::in | ios::out);
            if (!f2){
                f2.open(EVERT_FINANCE_DATA,ios::out|ios::binary);
            }
            f2.seekg(0,ios::end);
            int end=f2.tellg();
            f1.seekg(0);
            double alloutput=0,allinput=0;
            while (f1.tellg()!=end){
                bool tempflag;
                double tempfinance;
                f1.read(reinterpret_cast<char*>(&tempflag),sizeof (bool ));
                f1.read(reinterpret_cast<char*>(&tempfinance),sizeof (double ));
//cout<<tempflag<<"   "<<tempfinance<<" in show finance -1"<<endl;
                if (tempflag){alloutput+=tempfinance;}
                else{allinput+=tempfinance;}
                //if (tempflag){cout<<"((((((((((((("<<'-'<<setiosflags(ios::fixed) << setprecision(2)<<tempfinance;}
                //else{cout<<'+'<<setiosflags(ios::fixed) << setprecision(2)<<tempfinance;}
            }
            cout<<'+'<<" "<<setiosflags(ios::fixed) << setprecision(2)<<allinput<<" "<<'-'<<" "<<setiosflags(ios::fixed) << setprecision(2)<<alloutput;
            cout<<endl;
            f1.close(),f2.close();
        } else{
            f1.open(EVERT_FINANCE_DATA,ios_base::binary|ios::in | ios::out);
            if (!f1){
                f1.open(EVERT_FINANCE_DATA,ios::out|ios::binary);
            }
            f2.open(EVERT_FINANCE_DATA,ios_base::binary|ios::in | ios::out);
            if (!f2){
                f2.open(EVERT_FINANCE_DATA,ios::out|ios::binary);
            }
            double alloutput=0,allinput=0;
            f2.seekg(0,ios::end);
            int end=f2.tellg();
            if (time*(sizeof (bool )+sizeof (double ))>end){
                f1.close(),f2.close();
                cout<<"Invalid"<<endl;return;
            }
            f1.seekg(-(sizeof (bool )+sizeof (double )),ios::end);
            while (time--){
                bool tempflag;
                double tempfinance;
                f1.read(reinterpret_cast<char*>(&tempflag),sizeof (bool ));
                f1.read(reinterpret_cast<char*>(&tempfinance),sizeof (double ));
               // cout<<tempflag<<"   "<<tempfinance<<endl;
//                if (tempflag){cout<<'-'<<setiosflags(ios::fixed) << setprecision(2)<<tempfinance;}
//                else{cout<<'+'<<setiosflags(ios::fixed) << setprecision(2)<<tempfinance;}
                if (tempflag){alloutput+=tempfinance;}
                else{allinput+=tempfinance;}
               f1.seekg(-(2*sizeof (bool )+2*sizeof (double )),ios::cur);
            }
            cout<<'+'<<" "<<setiosflags(ios::fixed) << setprecision(2)<<allinput<<" "<<'-'<<" "<<setiosflags(ios::fixed) << setprecision(2)<<alloutput;
            cout<<endl;
            f1.close(),f2.close();
        }
    }
};
#endif //CODE_BOOKSTORE_H
