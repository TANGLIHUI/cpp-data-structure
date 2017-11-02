#include <iostream>
#include "SPT.hpp"
using namespace std;

int main()
{
    span_tree<int>* tree=new span_tree<int>;
    tree->insert(1);
    int m=20000;
    for (int i=2; i<m; i+=2)
    {
        //tree->insert(i+1);//cout<<123<<endl;
        int j=rand()%m;
        tree->insert(j);
        j=rand()%m;//cout<<tree<<endl;
        if (tree->remove(j))
        {
            cout<<i<<"&&&&"<<endl;
            //cout<<tree<<endl;
            //cout<<boolalpha<<tree->find(j)<<endl;
        }
        //cout<<tree->isBinary()<<endl;
    }
    cout<<tree<<endl;
    while (!tree->empty())
    {
        cout<<boolalpha<<tree->del_min()<<endl;
        tree->del_max();
    }
    cout<<tree<<endl;
    return 0;
}
