#include <iostream>
#include <functional>
#include <stack>
#include <algorithm>
#include <cmath>
#include <set>
#define AVL_TEMPLATE \
template <typename Datatype,\
          typename Less,\
          typename Greater\
          >
#define AVLDLG AVL<Datatype,Less,Greater>
template <typename Datatype,
          typename Less=std::less<Datatype>,
          typename Greater=std::greater<Datatype>
          >
class AVL
{
    Less less;
    Greater greater;
    struct node //avl tree node data structure
    {
        Datatype data;
        node* lchild;
        node* rchild;
        int height;
        node(Datatype da,node* l=nullptr,node* r=nullptr,int h=0)
            :data(da),lchild(l),rchild(r),height(h) {}
        friend std::ostream& operator<<(std::ostream& os, node* n)
        {
            return os<<n->data;
        }
    };
    node* root=nullptr;
    node* findMin(node*& n);
    node* findMax(node*& n);
    static int height(node*& n);
    node* rotateLeft(node*& n);  //rotate LL
    node* rotateRight(node*& n);  //rotate RR
    node* doubleLeft(node*& n);  //rotate LR
    node* doubleRight(node*& n);  //rotate RL
    void insert(node*& n, Datatype& data);
    std::ostream& print(std::ostream& os, node* n, int k, char c);
    bool balance(node*& n);
public:
    Datatype findMin()
    {
        return findMin(root)->data;
    }
    Datatype findMax()
    {
        return findMax(root)->data;
    }
    void insert(Datatype data)
    {
        insert(root, data);
    }
    friend std::ostream& operator<<(std::ostream& os, AVL& tree)
    {
        return tree.print(os, tree.root, 0, ' ');
    }
    bool remove(Datatype data);
    void clear(node*& n);
    void clear()
    {
        clear(root);
    }
    ~AVL()
    {
        clear();
    }
    bool balance()
    {
        balance(root);
    }
    bool find(Datatype data);
};
AVL_TEMPLATE
typename AVLDLG::node*
AVLDLG::findMin(typename AVLDLG::node*& n)
{
    if (!n || n->lchild==nullptr) return n;
    return findMin(n->lchild);
}

AVL_TEMPLATE
typename AVLDLG::node*
AVLDLG::findMax(typename AVLDLG::node*& n)
{
    if (!n || n->rchild==nullptr) return n;
    return findMax(n->rchild);
}

AVL_TEMPLATE
int
AVLDLG::height (typename AVLDLG::node*& n)
{
    return n==nullptr ? -1 : n->height;
}
AVL_TEMPLATE
typename AVLDLG::node*
AVLDLG::rotateLeft(typename AVLDLG::node*& n)
{
    node* newRoot = n->lchild;
    n->lchild = newRoot->rchild;
    newRoot->rchild = n;
    n->height=std::max(height(n->lchild), height(n->rchild))+1;
    newRoot->height=std::max(height(newRoot->lchild), height(newRoot->rchild))+1;
    n = newRoot;
    return newRoot;
}
AVL_TEMPLATE
typename AVLDLG::node*
AVLDLG::rotateRight(typename AVLDLG::node*& n)
{
    node* newRoot = n->rchild;
    n->rchild = newRoot->lchild;
    newRoot->lchild = n;
    n->height=std::max(height(n->lchild), height(n->rchild))+1;
    newRoot->height=std::max(height(newRoot->lchild), height(newRoot->rchild))+1;
    n = newRoot;
    return newRoot;
}
AVL_TEMPLATE
typename AVLDLG::node*
AVLDLG::doubleLeft(typename AVLDLG::node*& n)
{
    node* newLeft = n->lchild;
    node* newRoot = newLeft->rchild;
    n->lchild = newRoot->rchild;
    newLeft->rchild = newRoot->lchild;
    newRoot->lchild = newLeft;
    newRoot->rchild = n;
    n->height=std::max(height(n->lchild), height(n->rchild))+1;
    newLeft->height=std::max(height(newLeft->lchild), height(newLeft->rchild))+1;
    newRoot->height=std::max(height(newRoot->lchild), height(newRoot->rchild))+1;
    n = newRoot;
    return newRoot;
}
AVL_TEMPLATE
typename AVLDLG::node*
AVLDLG::doubleRight(typename AVLDLG::node*& n)
{
    node* newRight = n->rchild;
    node* newRoot = newRight->lchild;
    n->rchild = newRoot->lchild;
    newRight->lchild = newRoot->rchild;
    newRoot->lchild = n;
    newRoot->rchild = newRight;
    n->height=std::max(height(n->lchild), height(n->rchild))+1;
    newRight->height=std::max(height(newRight->lchild), height(newRight->rchild))+1;
    newRoot->height=std::max(height(newRoot->lchild), height(newRoot->rchild))+1;
    n = newRoot;
    return newRoot;
}

AVL_TEMPLATE
void
AVLDLG::insert(typename AVLDLG::node*& n, Datatype& data)
{
    if (n==nullptr)
    {
        n=new node(data);
        return;
    }
    else if (less(data, n->data))
    {
        insert(n->lchild, data);
        if (height(n->lchild) - height(n->rchild) == 2)
        {
            if (data < n->lchild->data) rotateLeft(n);
            else doubleLeft(n);
        }
    }
    else if (greater(data, n->data))
    {
        insert(n->rchild, data);
        if (height(n->rchild) - height(n->lchild) == 2)
        {
            if (data > n->rchild->data) rotateRight(n);
            else doubleRight(n);
        }
    }
    n->height = std::max(height(n->lchild), height(n->rchild))+1;
}

AVL_TEMPLATE
std::ostream&
AVLDLG::print(std::ostream& os,typename AVLDLG::node* n, int k, char c)
{
    if (n==nullptr) return os;
    for (int i=0; i<k; ++i)
    {
        if (i==k-2)
        {
            os<<'|';
            continue;
        }
        os<<'_';
    }
    os<<n<<c<<std::endl;
    print(os, n->lchild, k+2, '*');
    print(os, n->rchild, k+2, '#');
    return os;
}
AVL_TEMPLATE
bool
AVLDLG::remove(Datatype data)
{
    node* n=root;
    std::stack<std::pair<node*,bool>> st;
    while (n)
    {
        if (less(data, n->data))
        {
            st.push({n,true});
            n=n->lchild;
        }
        else if (greater(data, n->data))
        {
            st.push({n,false});
            n=n->rchild;
        }
        else break;
    }
    if (!n) return false;
    if (n->lchild&&n->rchild)
    {
        st.push({n,true});
        node* temp=n->lchild;
        while (temp->rchild)
        {
            st.push({temp,false});
            temp=temp->rchild;
        }
        n->data=temp->data;
        node * t=st.top().first;
        if (t==n) t->lchild=temp->lchild;
        else t->rchild=temp->lchild;
    }
    else if (n->lchild)
    {
        if (st.top().second) st.top().first->lchild = n->lchild;
        else st.top().first->rchild = n->lchild;
        delete n;
    }
    else if (n->rchild)
    {
        if (st.top().second) st.top().first->lchild = n->rchild;
        else st.top().first->rchild = n->rchild;
        delete n;
    }
    else
    {
        if (st.top().second) st.top().first->lchild = nullptr;
        else st.top().first->rchild = nullptr;
        delete n;
        n=nullptr;
    }
    while (!st.empty())
    {
        node* t=st.top().first;
        st.pop();
        if (height(t->lchild) - height(t->rchild) >= 2)
        {
            if (height(t->lchild->lchild) >= height(t->lchild->rchild))
            {
                t=rotateLeft(t);
                if (!st.empty())
                {
                    if (st.top().second) st.top().first->lchild=t;
                    else st.top().first->rchild=t;
                }
            }
            else if (height(t->lchild->rchild) > height(t->lchild->lchild))
            {
                t=doubleLeft(t);
                if (!st.empty())
                {
                    if (st.top().second) st.top().first->lchild=t;
                    else st.top().first->rchild=t;
                }
            }
        }
        else if (height(t->rchild) - height(t->lchild) >= 2)
        {
            if (height(t->rchild->rchild) >= height(t->rchild->lchild))
            {
                t=rotateRight(t);
                if (!st.empty())
                {
                    if (st.top().second) st.top().first->lchild=t;
                    else st.top().first->rchild=t;
                }
            }
            else if (height(t->rchild->lchild) > height(t->rchild->rchild))
            {
                t=doubleRight(t);
                if (!st.empty())
                {
                    if (st.top().second) st.top().first->lchild=t;
                    else st.top().first->rchild=t;
                }
            }
        }
        t->height=std::max(height(t->lchild), height(t->rchild))+1;
        root=t;
    }
    return true;
}
AVL_TEMPLATE
void
AVLDLG::clear(typename AVLDLG::node*& n)
{
    if (!n) return;
    clear(n->lchild);
    clear(n->rchild);
    delete n;
    n=nullptr;
}
AVL_TEMPLATE
bool
AVLDLG::balance(typename AVLDLG::node*& n)
{
    if (!n) return true;
    int lh=height(n->lchild);
    int rh=height(n->rchild);
    bool bl=balance(n->lchild),br=balance(n->rchild);
    if (bl && br && abs(lh - rh) < 2) return true;
    else return false;
}
AVL_TEMPLATE
bool
AVLDLG::find(Datatype data){
    node* n=root;
    while (n){
        if (less(data, n->data)) n=n->lchild;
        else if (greater(data, n->data)) n=n->rchild;
        else return true;
    }
    return false;
}
