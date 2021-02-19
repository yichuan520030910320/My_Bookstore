
#include <iostream>
#include "BookStore.h"
using namespace std;
extern int booknum;
bookstore commandbookstore;//缺少构造函数
int main() {
    init();
    string command;
    int cnt=1;
fstream fo;

    while (getline(cin,command)){
        if (command=="quit"||command=="exit") break;
        //cout<<command<<endl;

        commandbookstore.run(command);

//        cout<<command<<":"<<endl;
//        fo.open(BOOK_DATA,ios_base::binary|ios::in | ios::out);
//        if (!fo){
//            fo.open(BOOK_DATA,ios::out|ios::binary);
//        }
//        cout<<fo.fail()<<"  f1.fail in main"<<endl;
//        fo.seekg(0);
//        Book tempbook;
//        fo.read(reinterpret_cast<char*>(&tempbook),232);
//        cout<<tempbook.ISBN<<" "<<tempbook.name<<" "<<tempbook.author<<" "<<tempbook.keywords<<" "<<setiosflags(ios::fixed) << setprecision(2)<<tempbook.price<<" "<<tempbook.quantity<<endl;
//        //commandbookstore.cmd.the_blockchai_of_usermanager.debug();//todo
//       // cout<<"one round finish"<<cnt++<<endl;
//       cout<<endl;
//       fo.close();
    }
   // std::cout << "Hello, World!fffffffffffffffuckLL" << std::endl;
    return 0;
}
