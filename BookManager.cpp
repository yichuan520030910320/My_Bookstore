#include "BookStore.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctime>
void color(int x) //设置字体颜色
{
    if(x>=0 && x<=15)
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
    else
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
ostream &operator<<(ostream &os,const reportfinance&obj){
    srand((double)clock());
    int temp=rand()%15;
    color(temp);
    //cout<<obj.input_or_output<<endl;
    //cout<<obj.input_or_output<<endl;
    if (obj.input_or_output){
        os<<obj.tempuser.id<<": "<<obj.tempuser.name<<"   import   "<<obj.num<<"  "<<obj.ISBN<<"  in  "<<obj.price1<<"  at  "<<obj.time<<endl;
    }
    else{
        os<<obj.tempuser.id<<": "<<obj.tempuser.name<<"   buy   "<<obj.num<<"  "<<obj.ISBN<<"  in  "<<obj.price1<<"  at  "<<obj.time<<endl;
    }
    return os;
}
void init(){

}
class logemployee{
public: friend ostream &operator<<(ostream &os,const logemployee&obj);
    user temp;
    char command[160];
};
void bookstore::report_finance()
{
    fa.close();
    fa.open(CLI_FINANCE_DETAILED,ios_base::binary|ios::in | ios::out);
    if (!fa){
        fa.open(CLI_FINANCE_DETAILED,ios::out|ios::binary);
    }
    fa.seekg(0,ios::end);
    while (fa.tellg()>0) {
        fa.seekg(-sizeof(reportfinance), ios::cur);
        reportfinance temp;
        fa.read(reinterpret_cast<char *>(&temp), sizeof(temp));
        cout << temp;
        fa.seekg(-sizeof(reportfinance), ios::cur);
    }
}
void bookstore::report_employee(string name)
{vector<int>tempvec(cmd.the_blockchai_of_usermanager.findelement(name));
    if (tempvec.empty()){cout<<"GO FUCK  FW"<<endl;
        return;}
    fa.close();
    fa.open(CLI_EMPLOYEE_DETAILED,ios_base::binary|ios::in | ios::out);
    if (!fa){fa.open(CLI_EMPLOYEE_DETAILED,ios::out|ios::binary);}
    fa.seekg(0,ios::end);
    while (fa.tellg()>0) {
        fa.seekg(-sizeof(logemployee), ios::cur);
        logemployee temp;
        fa.read(reinterpret_cast<char *>(&temp), sizeof(temp));
        if (strcmp(name.c_str(),temp.temp.id)==0) { cout << temp; }
        fa.seekg(-sizeof(logemployee), ios::cur);
    }
}
void bookstore::log()
{
    fa.close();
    fa.open(CLI_EMPLOYEE_DETAILED,ios_base::binary|ios::in | ios::out);
    if (!fa){fa.open(CLI_EMPLOYEE_DETAILED,ios::out|ios::binary);}
    fa.seekg(0,ios::end);
    while (fa.tellg()>0) {
        fa.seekg(-sizeof(logemployee), ios::cur);
        logemployee temp;
        fa.read(reinterpret_cast<char *>(&temp), sizeof(temp));
        cout << temp;
        fa.seekg(-sizeof(logemployee), ios::cur);
    }
}
void bookstore::reportme()
{
user tempuser;
tempuser=cmd.user_stack[cmd.usernum-1];
char tempid[40];
strcpy(tempid,tempuser.id);
    fa.close();
    fa.open(CLI_EMPLOYEE_DETAILED,ios_base::binary|ios::in | ios::out);
    if (!fa){fa.open(CLI_EMPLOYEE_DETAILED,ios::out|ios::binary);}
    fa.seekg(0,ios::end);
    while (fa.tellg()>0) {
        fa.seekg(-sizeof(logemployee), ios::cur);
        logemployee temp;
        fa.read(reinterpret_cast<char *>(&temp), sizeof(temp));
        if (strcmp(tempid,temp.temp.id)==0) { cout << temp; }
        fa.seekg(-sizeof(logemployee), ios::cur);
    }

}
bool isDegital(string str) {
    for (int i = 0;i < str.size();i++) {
        if (str.at(i) == '-' && str.size() > 1)  // 有可能出现负数
            continue;
        if (str.at(i) > '9' || str.at(i) < '0')
            return false;
    }
    return true;
}
void error(){
    cout<<"Invalid"<<endl;
}
void the_fuction_in_modify(string temp){

}

ostream &operator<<(ostream &os,const logemployee&obj){
    srand((double)clock());
    int temp=rand()%15;
    color(temp);
    os<<obj.temp.id<<"  :  "<<obj.temp.name<<"      do   "<<obj.command<<endl;
    return os;
}
void bookstore::run(string temp){
//cout<<"&&&"<<endl;
//
    fa.close();
    fa.open(CLI_EMPLOYEE_DETAILED,ios_base::binary|ios::in | ios::out);
    if (!fa){fa.open(CLI_EMPLOYEE_DETAILED,ios::out|ios::binary);}
    fa.seekg(0,ios::end);
    logemployee templog;
    templog.temp=cmd.user_stack[cmd.usernum-1];
    strcpy(templog.command,temp.c_str());
    fa.write(reinterpret_cast<char*>(&templog),sizeof (templog));
    if (temp.empty()){return;}
int len=temp.length();
string temp1;int i;
    for (i = 0; i <len&&temp[i]!=' ' ; ++i) {
        temp1+=temp[i];
    }
   // if (temp1=="modify"){ISBN_BOOKSTORE_blocklist.debug();}
    if (temp1=="su"){
      // cout<<" in run su"<<endl;
       //cout<<temp<<"    in su "<<endl;
        string user_id,pass;
        for (i++; i <len&&temp[i]!=' ' ; ++i) {
            user_id+=temp[i];
        }
        for (i++; (i <len&&temp[i]!=' ') ; ++i) {
            pass+=temp[i];
        }
        for (; i < len && temp[i] == ' '; ++i);
       // cout<<user_id<<" "<<pass<<endl;
        //cout<<i<<  "  len"<<len<<endl;
        //cout<<i<<  "  len"<<len<<endl;
        if (i<len) { error();
        //cout<<"****"<<endl;
       // cout<<"su 0"<<endl;
            return;}
        else{
                if (user_id.empty()){error();
               // cout<<"su 1"<<endl;
                return;}
            if (pass.empty()){
                cmd.su(user_id,"@q@");
            }
           // cout<<user_id<<" "<<pass<<endl;
            else   { cmd.su(user_id, pass); }
        }
    } else if(temp1=="report_finance"){
        report_finance();
    }
        else if(temp1=="log"){log();}
    else if (temp1=="report_me"){
      reportme();
    } else if (temp1=="report_employee"){
        string user_id;
        for (i++; i <len&&temp[i]!=' ' ; ++i) {user_id+=temp[i];}
      report_employee(user_id);
    }
    else if (temp1=="useradd"){
        string user_id,pass,privilege,username;
        for (i++; i <len&&temp[i]!=' ' ; ++i) {user_id+=temp[i];}
        for (i++; i <len&&temp[i]!=' ' ; ++i) {pass+=temp[i];}
        for (i++; i <len&&temp[i]!=' ' ; ++i) {privilege+=temp[i];}
        for (i++; i <len&&temp[i]!=' ' ; ++i) {username+=temp[i];}
        if (i!=len) { error();
            return;}
        else{
            if (privilege.empty()||username.empty()||pass.empty()||username.empty()) {
              //  cout<<"error in useradd"<<endl;
                error();
                return;}
            cmd.adduser(user_id,pass,username,atoi(privilege.c_str()));
        }
    }
    else if (temp1=="delete"){
        string userid;
        for (i++; i <len&&temp[i]!=' ' ; ++i) {userid+=temp[i];}
        if (i!=len) { error(); return;}
        else{ cmd.deleteid(userid); }
    }
    else if (temp1=="select"){
string ISBN;for (i++; i <len&&temp[i]!=' ' ; ++i) {ISBN+=temp[i];}
        if (i!=len) error();
        else{select(ISBN);}
    } else if (temp1=="passwd"){
        string userid,oldpass,newpass;
        for (i++; i <len&&temp[i]!=' ' ; ++i) {userid+=temp[i];}
        for (i++; i <len&&temp[i]!=' ' ; ++i) {oldpass+=temp[i];}
        //cout<<i<<"   "<<len<<endl;
        if (i==len){
           // cout<<oldpass<<"  passwd"<<endl;
            cmd.replace_the_password(userid,"@",oldpass);
        } else { for (i++; i < len && temp[i] != ' '; ++i) { newpass += temp[i]; }
            if (i==len) { cmd.replace_the_password(userid, oldpass, newpass); }
            else{cout<<"Invalid"<<endl;}
        }
    }
    else if (temp1=="modify"){
       // cout<<cmd.user_stack[cmd.usernum-1].priviledge<<"&&&&&&&&&"<<endl;
       // cout<<cmd.user_stack[cmd.usernum-1].currentbookISBN<<endl;
        if ((cmd.user_stack[cmd.usernum-1].priviledge)<3||cmd.user_stack[cmd.usernum-1].currentbookISBN==-1) {
           // cout<<"first invalid in modify fuction"<<endl;
            cout<<"Invalid"<<endl;
            return;}
string modify1,modify2,modify3,modify4,modify5,modify6;
        for (i++; i <len&&temp[i]!=' ' ; ++i) {modify1+=temp[i];}
        for (i++; i <len&&temp[i]!=' ' ; ++i) {modify2+=temp[i];}
        for (i++; i <len&&temp[i]!=' ' ; ++i) {modify3+=temp[i];}
        for (i++; i <len&&temp[i]!=' ' ; ++i) {modify4+=temp[i];}
        for (i++; i <len&&temp[i]!=' ' ; ++i) {modify5+=temp[i];}
        for (i++; i <len&&temp[i]!=' ' ; ++i) {modify6+=temp[i];}
        //cout<<modify1<<" "<<modify2<<" "<<modify3<<" "<<modify4<<" "<<modify5<<" "<<modify6<<endl;
        //cout<<len<<" "<<i<<endl;
        if (!modify1.empty()){
           // cout<<"in run fuction brhin in modify1"<<endl;
            string keycharacter;
            string index;
            int lentemp=modify1.length();
            int j;
            if (modify1[0]!='-'){
                error();
                return;
            }
            for ( j = 1; j <lentemp&&modify1[j]!='=' ; ++j) {
                keycharacter+=modify1[j];
            }

            for (j+=1; j <lentemp; ++j) {
                index+=modify1[j];
            }

            //to build the conection between the user and the book
            int bookisbn=(--cmd.user_stack.end())->currentbookISBN;
           // cout<<"in modify 1 in run fuction  keycharacter:  "<<keycharacter<<"    index:  "<<index<<"   isbnoffset:"<<bookisbn<<endl;
            if (keycharacter=="keyword"){modify("keyword",index,bookisbn); }
            else if (keycharacter=="author"){ modify("author",index,bookisbn);}
            else if (keycharacter=="name"){ modify("name",index,bookisbn);}
            else if (keycharacter=="ISBN"){ modify("ISBN",index,bookisbn);}
            else if (keycharacter=="price"){ modify("price",index,bookisbn);}
        }
        if (!modify2.empty()){ string keycharacter;
            string index;
            int lentemp=modify2.length();
            int j;
            if (modify2[0]!='-'){
                error();
                return;
            }
            for ( j = 1; j <lentemp&&modify2[j]!='=' ; ++j) {
                keycharacter+=modify2[j];
            }

            for (j+=1; j <lentemp; ++j) {
                index+=modify2[j];
            }

            //to build the conection between the user and the book
            int bookisbn=(--cmd.user_stack.end())->currentbookISBN;
            if (keycharacter=="keyword"){modify("keyword",index,bookisbn); }
            else if (keycharacter=="author"){ modify("author",index,bookisbn);}
            else if (keycharacter=="name"){ modify("name",index,bookisbn);}
            else if (keycharacter=="ISBN"){ modify("ISBN",index,bookisbn);}
            else if (keycharacter=="price"){ modify("price",index,bookisbn);}}
        if (!modify3.empty()){  string keycharacter;
            string index;
            int lentemp=modify3.length();
            int j;
            if (modify3[0]!='-'){
                error();
                return;
            }
            for ( j = 1; j <lentemp&&modify3[j]!='=' ; ++j) {
                keycharacter+=modify3[j];
            }

            for (j+=1; j <lentemp; ++j) {
                index+=modify3[j];
            }
            //to build the conection between the user and the book
            int bookisbn=(--cmd.user_stack.end())->currentbookISBN;
            if (keycharacter=="keyword"){modify("keyword",index,bookisbn); }
            else if (keycharacter=="author"){ modify("author",index,bookisbn);}
            else if (keycharacter=="name"){ modify("name",index,bookisbn);}
            else if (keycharacter=="ISBN"){ modify("ISBN",index,bookisbn);}
            else if (keycharacter=="price"){ modify("price",index,bookisbn);}}
        if (!modify4.empty()){ string keycharacter;
            string index;
            int lentemp=modify4.length();
            int j;
            if (modify4[0]!='-'){
                error();
                return;
            }
            for ( j = 1; j <lentemp&&modify4[j]!='=' ; ++j) {
                keycharacter+=modify4[j];
            }

            for (j+=1; j <lentemp; ++j) {
                index+=modify4[j];
            }
            //to build the conection between the user and the book
            int bookisbn=(--cmd.user_stack.end())->currentbookISBN;
            if (keycharacter=="keyword"){modify("keyword",index,bookisbn); }
            else if (keycharacter=="author"){ modify("author",index,bookisbn);}
            else if (keycharacter=="name"){ modify("name",index,bookisbn);}
            else if (keycharacter=="ISBN"){ modify("ISBN",index,bookisbn);}
            else if (keycharacter=="price"){ modify("price",index,bookisbn);}}
        if (!modify5.empty()){ string keycharacter;
            string index;
            int lentemp=modify5.length();
            int j;
            if (modify5[0]!='-'){
                error();
                return;
            }
            for ( j = 1; j <lentemp&&modify5[j]!='=' ; ++j) {
                keycharacter+=modify5[j];
            }

            for (j+=1; j <lentemp; ++j) {
                index+=modify5[j];
            }
            int bookisbn=(--cmd.user_stack.end())->currentbookISBN;
            if (keycharacter=="keyword"){modify("keyword",index,bookisbn); }
            else if (keycharacter=="author"){ modify("author",index,bookisbn);}
            else if (keycharacter=="name"){ modify("name",index,bookisbn);}
            else if (keycharacter=="ISBN"){ modify("ISBN",index,bookisbn);}
            else if (keycharacter=="price"){ modify("price",index,bookisbn);}
        }
        if (!modify6.empty()){ string keycharacter;
            string index;
            int lentemp=modify6.length();
            int j;
            if (modify6[0]!='-'){
                error();
                return;
            }
            for ( j = 1; j <lentemp&&modify6[j]!='=' ; ++j) {
                keycharacter+=modify6[j];
            }

            for (j+=1; j <lentemp; ++j) {
                index+=modify6[j];
            }
            int bookisbn=(--cmd.user_stack.end())->currentbookISBN;
            if (keycharacter=="keyword"){modify("keyword",index,bookisbn); }
            else if (keycharacter=="author"){ modify("author",index,bookisbn);}
            else if (keycharacter=="name"){ modify("name",index,bookisbn);}
            else if (keycharacter=="ISBN"){ modify("ISBN",index,bookisbn);}
            else if (keycharacter=="price"){ modify("price",index,bookisbn);}
        }
    } else if (temp1=="logout"){
        if (i!=len) error();
        else{
cmd.logout();
        }
    } else if (temp1=="register"){
        string user_id,pass,username;
        for (i++; i <len&&temp[i]!=' ' ; ++i) {user_id+=temp[i];}
        for (i++; i <len&&temp[i]!=' ' ; ++i) {pass+=temp[i];}
        for (i++; i <len&&temp[i]!=' ' ; ++i) {username+=temp[i];}
        if (i!=len) error();
        else{
            if (user_id.empty()||pass.empty()||username.empty()){
                error();return;
            }
          // cout<<" in run register"<<endl;
cmd.registeruser(user_id,pass,username);
        }
    } else if (temp1=="show"){//todo work in steps
        show(temp);
    }
    else if (temp1=="import"){
        string totalnum,totalmoney;
        for (i++; i <len&&temp[i]!=' ' ; ++i) {totalnum+=temp[i];}
        for (i++; i <len&&temp[i]!=' ' ; ++i) {totalmoney+=temp[i];}
        if (i!=len) error();
        else{
            if (!isDegital(totalnum)){
                cout<<"Invalid"<<endl;
                return;
            }
import(atoi(totalnum.c_str()),atof(totalmoney.c_str()));
        }
    } else if (temp1=="buy"){
        string ISBN_,quantity_;
        for (i++; i <len&&temp[i]!=' ' ; ++i) {ISBN_+=temp[i];}
        for (i++; i <len&&temp[i]!=' ' ; ++i) {quantity_+=temp[i];}
        if (i!=len) error();
        else{
            if (ISBN_.empty()||quantity_.empty()){error();return;}
            buy(ISBN_,quantity_);
        }

    }
    else{
        cout<<"Invalid"<<endl;
    }
}
bookstore::bookstore():ISBN_BOOKSTORE_blocklist(ISBN_SEARCH),AUTHOR_BOOKSTORE(AUTHOR_SEARCH),BOOKNAME_BOOKSTORE_blocklist(BOOK_NAME_SEARCH),KEYWORD_BOOKSTORE(KEYWORD_SEARCH) {
totaiinput=0,totoaloutput=0,tradetimes=0;
}
Book::Book() {
    price=-1;
    quantity=0;
    memset(ISBN,0,30);
    memset(name,0,60);
    memset(author,0,60);
    memset(keywords,0,60);
}