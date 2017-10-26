#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <functional>
#include "AVL.hpp"
using namespace std;
int main(){
    AVL<double>* tree=new AVL<double>();
    cout<<boolalpha<<"insert elements"<<endl;
    int cnt=100000;
    for (int i=0; i<cnt; ++i){
        int j=rand()%cnt;
        tree->insert(j);
        //cout<<tree->balance()<<' '<<j<<endl;
    }
    //cout<<*tree<<endl;
    cout<<"remove elements"<<endl;
    for (int i=0; i<cnt; ++i){
        //cout<<*tree<<endl;
        int j=rand()%cnt;
        //cout<<j<<' ';
        tree->remove(j);
        if (i%10000==0) cout<<j<<ends;
        //cout<<tree->balance()<<endl;
        if (!tree->balance()){
            cout<<"#############"<<j<<"###########"<<endl;
            cout<<*tree<<endl;
            cout<<"#############"<<j<<"###########"<<endl;
        }
    }
    return 0;
}
