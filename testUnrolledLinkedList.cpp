//
// Created by Rainy Memory on 2021/1/12.
//


#define testUnrolledLinkedList
#ifdef testUnrolledLinkedList
#include "blockchain.h"
#include <cstdlib>
#include <map>

using namespace std;

#define TEST_SIZE 10000

fstream fs_test;

void initialize_() {
    fs_test.open("test.dat", ios::out | ios::binary);
    fs_test.close();
}

int main() {
    initialize_();
    map<string, vector<int>> save;
    UnrolledLinkedList ull("test.dat");
    vector<string> test_vec;
    srand(233);
    for (int i = 0; i < TEST_SIZE; i++) {
        int temp = rand();
        string str = to_string(temp);
        test_vec.push_back(str);
       element temp_ele(i, test_vec[i]);
        ull.addelement(temp_ele);
       cout<<i<<" "<<test_vec[i]<<endl;
        if (i % (TEST_SIZE/100) == 0) cout << i << " " << test_vec[i] << endl;
    }
    ull.debug();

//    for (int i = 0; i < TEST_SIZE; i += 1) {
//        save[test_vec[i]].push_back(i);
//        if (i % (TEST_SIZE/100) == 0)cout << i << endl;
//    }






    for (int i = 0; i < TEST_SIZE; i += 2) {
        save[test_vec[i]].push_back(i);
        if (i % (TEST_SIZE/100) == 0)cout << i << endl;
    }
    
    //ull.printList();

    for (int i = 1; i < TEST_SIZE; i += 2) {
        element temp_ele(i, test_vec[i]);
        ull.deleteelment(temp_ele);
        //ull.printList();
        if (i % (TEST_SIZE/100) == 1)cout << i << endl;
    }

    for (int i = 0; i < TEST_SIZE; i++) {
        vector<int> res(ull.findelement(test_vec[i])), answer = save[test_vec[i]];
      //  ull.findelement(test_vec[i], res);
        for (int j = 0; j < res.size(); j++) {
            if (res[j] != answer[j]) {
                cerr << "key: " << test_vec[i] << " offset: " << answer[j] << endl;
                cerr << "your offset: " << res[j] << endl;
            }
        }
        if (i % (TEST_SIZE/100) == 0)cout << i << endl;
    }
    
    return 0;
}
#endif //testUnrolledLinkedList
