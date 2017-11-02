#include <iostream>
#include <stack>
#include <functional>
#define SPT_TEMPLATE \
template <typename DataType,\
          typename Less,\
          typename Greater\
          >
#define SPTDLG span_tree<DataType,Less,Greater>
using namespace std;
template <typename DataType,
          typename Less=std::less<DataType>,
          typename Greater=std::greater<DataType>
          >
class span_tree
{
    struct node
    {
        DataType data;
        node* lchild;
        node* rchild;
        node(DataType d, node* l=nullptr, node* r=nullptr):data(d),lchild(l),rchild(r) {}
    };
    Less less;
    Greater greater;
    node *root=nullptr;
    void rotateLeft(node*& n);
    void rotateRight(node*& n);
    void doubleLeft(node*& n);
    void doubleRight(node*& n);
    void handleUp(stack<node*>& st, node* n);
    void clear(node*& n);
    bool remove(DataType data,node*& n);
    bool isBinary(node* n);
public:
    void clear()
    {
        clear(root);
    }
    ~span_tree()
    {
        clear();
    }
    bool insert(DataType data);
    bool remove(DataType data)
    {
        return remove(data,root);
    }
    bool find(DataType data);
    bool del_min();
    bool del_max();
    void print(std::ostream& os,node* n,int k,char c);
    friend std::ostream& operator<<(std::ostream& os, span_tree*& tree)
    {
        tree->print(os,tree->root,0,' ');
        return os;
    }
    bool isBinary()
    {
        return isBinary(root);
    }
    bool empty(){
        return !root;
    }
};
SPT_TEMPLATE
void
SPTDLG::rotateLeft(typename SPTDLG::node*& n)
{
    node* nl=n->lchild;
    node* nll=nl->lchild;
    n->lchild=nl->rchild;
    nl->rchild=n;
    nl->lchild=nll->rchild;
    nll->rchild=nl;
    n=nll;
}
SPT_TEMPLATE
void
SPTDLG::rotateRight(typename SPTDLG::node*& n)
{
    node* nr=n->rchild;
    node* nrr=nr->rchild;
    n->rchild=nr->lchild;
    nr->lchild=n;
    nr->rchild=nrr->lchild;
    nrr->lchild=nr;
    n=nrr;
}
SPT_TEMPLATE
void
SPTDLG::doubleLeft(typename SPTDLG::node*& n)
{
    node* nl=n->lchild;
    node* nlr=nl->rchild;
    n->lchild=nlr->rchild;
    nl->rchild=nlr->lchild;
    nlr->lchild=nl;
    nlr->rchild=n;
    n=nlr;
}
SPT_TEMPLATE
void
SPTDLG::doubleRight(typename SPTDLG::node*& n)
{
    node* nr=n->rchild;
    node* nrl=nr->lchild;
    n->rchild=nrl->lchild;
    nr->lchild=nrl->rchild;
    nrl->lchild=n;
    nrl->rchild=nr;
    n=nrl;
}
SPT_TEMPLATE
void
SPTDLG::clear(typename SPTDLG::node*& n)
{
}
SPT_TEMPLATE
bool
SPTDLG::insert(DataType data)
{
    if (root==nullptr)
    {
        root=new node(data);
        return true;
    }
    node* n=nullptr;
    stack<node*> st;
    node* t=root;
    while (true)
    {
        if (less(data,t->data))
        {
            st.push(t);
            if (t->lchild)
                t=t->lchild;
            else
            {
                n=new node(data);
                t->lchild=n;
                handleUp(st,n);
                return true;
            }
        }
        else if (greater(data, t->data))
        {
            st.push(t);
            if (t->rchild)
                t=t->rchild;
            else
            {
                n=new node(data);
                t->rchild=n;
                handleUp(st,n);
                return true;
            }
        }
        else return false;
    }
}
SPT_TEMPLATE
bool
SPTDLG::find(DataType data)
{
    node* n=root;
    std::stack<node*> st;
    while (n)
    {
        if (!n) return false;
        if (less(data,n->data))
        {
            st.push(n);
            n=n->lchild;
        }
        else if (greater(data,n->data))
        {
            st.push(n);
            n=n->rchild;
        }
        else
        {
            handleUp(st,n);
            return true;
        }
    }
    return false;
}
SPT_TEMPLATE
void
SPTDLG::handleUp(stack<node*>& st, node* n)
{
    while (!st.empty())
    {
        node* np=nullptr;
        node* npp=nullptr;
        node* nppp=nullptr;
        if (!st.empty())
        {
            np=st.top();
            st.pop();
        }
        if (!st.empty())
        {
            npp=st.top();
            st.pop();
        }
        if (!st.empty())nppp=st.top();
        if (!npp)
        {
            if (np)
            {
                if (np->rchild==n)
                {
                    np->rchild=n->lchild;
                    n->lchild=np;
                    root=n;
                }
                else if(np->lchild==n)
                {
                    np->lchild=n->rchild;
                    n->rchild=np;
                    root=n;
                }
            }
        }
        else
        {
            if (npp->lchild==np)
            {
                bool flag=false;
                if (nppp&&nppp->lchild==npp) flag=true;
                if (np->lchild==n) rotateLeft(npp);
                else if (np->rchild==n) doubleLeft(npp);
                if (nppp)
                    if (flag) nppp->lchild=npp;
                    else nppp->rchild=npp;
                else
                    root=npp;
            }
            else if (npp->rchild==np)
            {
                bool flag=false;
                if (nppp&&nppp->lchild==npp) flag=true;
                if (np->rchild==n) rotateRight(npp);
                else if (np->lchild==n) doubleRight(npp);
                if (nppp)
                    if (flag) nppp->lchild=npp;
                    else nppp->rchild=npp;
                else
                    root=npp;
            }
        }
    }
}
SPT_TEMPLATE
bool
SPTDLG::remove(DataType data,typename SPTDLG::node*& n)
{
    if (n==nullptr) return false;
    if (less(data, n->data)) return remove(data, n->lchild);
    else if (greater(data, n->data)) return remove(data, n->lchild);
    if (n->lchild&&n->rchild)
    {
        node* t=n->lchild;
        node* p=n->lchild;
        while (t->rchild)
        {
            p=t;
            t=t->rchild;
        }
        n->data=t->data;
        if (t==n->lchild)
        {
            n->lchild=t->lchild;
            delete t;
        }
        else
        {
            p->rchild=t->lchild;
            delete t;
        }
    }
    else if (n->lchild)
    {
        delete n;
        n=n->lchild;
    }
    else if (n->rchild)
    {
        delete n;
        n=n->rchild;
    }
    else
    {
        delete n;
    }
    return true;
}
SPT_TEMPLATE
bool
SPTDLG::del_min()
{
    if (!root) return false;
    node* p=nullptr;
    node* n=root;
    while (n->lchild)
    {
        p=n;
        n=n->lchild;
    }
    if (p) p->lchild=n->rchild;
    else root=root->rchild;
    delete n;
    n==nullptr;
    return true;
}
SPT_TEMPLATE
bool
SPTDLG::del_max()
{
    if (!root) return false;
    node* p=nullptr;
    node* n=root;
    while (n->rchild)
    {
        p=n;
        n=n->rchild;
    }
    if (p) p->rchild=n->lchild;
    else root=root->lchild;
    delete n;
    n==nullptr;
    return true;
}
SPT_TEMPLATE
void
SPTDLG::print(std::ostream& os,typename SPTDLG::node* n,int k,char c)
{
    if (!n) return ;
    for (int i=0; i<k; ++i)os<<"--";
    os<< n->data << c << std::endl;
    print(os,n->lchild,k+1,'*');
    print(os,n->rchild,k+1,'#');
}
SPT_TEMPLATE
bool
SPTDLG::isBinary(typename SPTDLG::node* n)
{
    if (!n) return true;
    if (n->lchild)
    {
        if (n->data<n->lchild->data) return false;
        if (!isBinary(n->lchild)) return false;
    }
    if (n->rchild)
    {
        if (n->data>n->rchild->data) return false;
        if (!isBinary(n->rchild)) return false;
    }
    return true;
}
