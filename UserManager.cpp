#include "blockchain.h"
#include "UserManager.h"
#include <sys/stat.h>
user::user() {
    priviledge=-1;
    currentbookISBN=-1;

}
inline bool exists_test3 (const std::string& name) {
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}
usermanager::usermanager() :filename(USER_DATA),the_blockchai_of_usermanager(USER_SEARCH){

user temp;
temp.priviledge=7;
strcpy(temp.name," ");
strcpy(temp.id,"root");
strcpy(temp.password,"sjtu");
user basic;
basic.priviledge=0;
user_stack.clear();
user_stack.push_back(basic);
//user_stack.push_back(temp);
usernum=1;//将用户信息写入存储文件中
//cout<<f1.is_open()<<"constructer in usermanager"<<endl;
    if (!(exists_test3(filename))){
        if (!f1.is_open()) {
            //cout<<filename<<endl;

            f1.open(filename, ios_base::binary | ios::in | ios::out);
            if (!f1) {
                f1.open(filename, ios::out | ios::binary);
            }
            //f1.open(filename, ios::binary |  ios::out);
            f1.seekg(0);
            f1.write(reinterpret_cast<char *>(&temp), sizeof(user));
            the_blockchai_of_usermanager.addelement(element(0, "root"));
            //the_blockchai_of_usermanager.debug();
            f1.close();//暴力打开会出锅吗？？？
        } else f1.close();
    }
}