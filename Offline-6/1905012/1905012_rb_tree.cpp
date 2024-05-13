
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<sstream>
#include<string>

using namespace std;

template<typename Key,typename E>
class BSTNode
{
public:
    E data;
    BSTNode* lc;
    BSTNode* rc;
    BSTNode* parent;
    Key key;
    int color;
    int lcnt;
    int rcnt;
    int total;

    BSTNode()
    {
        lcnt=rcnt=0;
    }

    BSTNode(Key k, E d,BSTNode* left, BSTNode* right)
    {
        key=k;
        data=d;
        lc=left;
        rc=right;
    }
    ~BSTNode()
    {

    }
    isNull()
    {
        return key==-1;
    }
    isNotNull()
    {
        return key!=-1;
    }
    void setNil()
    {
        key=-1;
        data=-1;
        color=2;
        lc=NULL;
        rc=NULL;
        lcnt=rcnt=total=0;
    }
};


template<typename Key, typename E> class BST
{
private:
    BSTNode<Key,E>* root;
    int nodeCount;


    void clearhelp(BSTNode<Key,E>* root)
    {
        if(root->isNull())
            return;
        clearhelp(root->lc);
        clearhelp(root->rc);
        delete root;
    }
    BSTNode<Key,E>* getmin(BSTNode<Key,E>* rt)
    {
        if(rt->lc->isNull())
            return rt;
        else return getmin(rt->lc);
    }
    BSTNode<Key,E>* findhelp(BSTNode<Key,E>* root,Key k)
    {
        if(root==NULL){return NULL;}
        if(k<root->key)
            return findhelp(root->lc,k);
        else if(k>root->key)
            return findhelp(root->rc,k);
        else{
             return root;
        }
    }

    int findlesshelp(BSTNode<Key,E>* root,Key k)
    {
        if(root->isNull()){return 0;}
        if(k<root->key)
            return findlesshelp(root->lc,k);
        else if(k>root->key)
            return root->lcnt+1+findlesshelp(root->rc,k);
        else{
             return root->lcnt;
        }
    }



    void printhelp(BSTNode<Key,E>* root)
    {
        if(root==NULL)
            {
                return;
            }
        cout<<"(";
        cout<<root->data<<" color "<<root->color<<" total "<<root->total<<" left "<<root->lcnt<<" right "<<root->rcnt<<endl;
        if(root->lc!=NULL) printhelp(root->lc);
        else{
            if(root->rc!=NULL)
            cout<<"()";
        }
        if(root->rc!=NULL) printhelp(root->rc);
        else{
             if(root->lc!=NULL)
            cout<<"()";
        }
        cout<<")";
    }
public:
    BST()
    {
        root=new BSTNode<Key,E>();
        root->setNil();
        nodeCount=0;
    }
    ~BST()
    {
        clearhelp(root);

    }
    void clear()
    {
        clearhelp(root);
        root=NULL;
        nodeCount=0;
    }
    void propagate(BSTNode<Key,E>* node)
    {
        if(node->parent->isNotNull())
        {
            BSTNode<Key,E>* par=node->parent;
            if(node== par->lc)
            {
                par->lcnt=node->total;
                par->total=1+par->lcnt+par->rcnt;
                node=par;
            }
            else
            {
                par->rcnt=node->total;
                par->total=1+par->lcnt+par->rcnt;
                node=par;
            }
        }
    }
    void insert(Key k,E item)
    {

        BSTNode<Key,E>* pp=findhelp(root,k);
        if(pp!=NULL)
        {
            cout<<"0"<<endl;
            return ;
        }
        else
        {
            cout<<"1"<<endl;
        }


        nodeCount++;

        BSTNode<Key,E>* z = new BSTNode<Key, E>();
        BSTNode<Key,E>* lft = new BSTNode<Key, E>();
        BSTNode<Key,E>* rght = new BSTNode<Key, E>();
        BSTNode<Key,E>* p = new BSTNode<Key, E>();
        lft->setNil();
        rght->setNil();
        p->setNil();


        z->key = k;
        z->data = item;
        z->color = 1;
        z->total=1+z->lcnt+z->rcnt;
        z->lc=lft;
        z->rc=rght;
        z->parent=p;
        lft->parent=z;
        rght->parent=z;

        BSTNode<Key, E>* y=new BSTNode<Key,E>();
        y->setNil();
        BSTNode<Key, E>* x=root;
        //cout<<"before while"<<endl;

        while(x->isNotNull())
        {
            y=x;
            if(z->key < x->key) x=x->lc;
            else x=x->rc;
        }

        z->parent = y;
        if(y->isNull()) root=z;
        else if(z->key < y->key)
        {
            y->lc=z;
            y->lcnt=z->total;
            y->total=1+y->lcnt+y->rcnt;
            propagate(y);
        }
        else
        {
            y->rc=z;
            y->rcnt=z->total;
            y->total=1+y->lcnt+y->rcnt;
            propagate(y);
        }
        if(z==root)
        {
            z->color=2;
        }
        else{
                //print();
            insert_fixup(z);
        }
        //print();
    }

    void leftRotate(BSTNode<Key, E>* b)
    {
        BSTNode<Key,E>* p = b->parent;
        BSTNode<Key,E>* a= b->rc;
        b->rc = a->lc;
        b->rcnt=a->lcnt;
        a->lcnt=0;
        b->total=1+b->lcnt+b->rcnt;
        a->total=1+a->lcnt+a->rcnt;

        a->lc->parent=b;

        a->lc=b;
        a->lcnt=b->total;
        a->total=1+a->lcnt+a->rcnt;
        b->parent=a;
        a->parent=p;
            if(p->rc ==b)
               {
                   p->rc=a;
               }
            else
               {
                   p->lc=a;
               }
        propagate(a);

        if(b==root)
            root=a;
    }
    void rightRotate(BSTNode<Key, E>* b)
    {
        BSTNode<Key,E>* p = b->parent;
        BSTNode<Key,E>* a= b->lc;
        b->lc = a->rc;
        b->lcnt=a->rcnt;
        a->rcnt=0;
        b->total=1+b->lcnt+b->lcnt;
        a->total=1+a->lcnt+a->rcnt;

            a->rc->parent=b;

        a->rc=b;
        a->rcnt=b->total;
        a->total=1+a->lcnt+a->rcnt;

        b->parent=a;
        a->parent=p;

            if(p->lc ==b)
               {
                   p->lc=a;
               }
            else
               {
                   p->rc=a;

               }
        propagate(a);

        if(b==root)
            root=a;
    }

    void insert_fixup(BSTNode<Key,E>* z)
    {
        while(z!=root && z->parent->color==1 )
        {
            if(z->parent == z->parent->parent->lc) // bap jodi dadar left child
            {
                //cout<<"in CATEGORY A"<<endl;
                BSTNode<Key,E>* y= z->parent->parent->rc; // y chacha
                if(y->color==1) // Recoloring
                {
                    z->parent->color=2; // bap black
                    y->color=2; // chacha black
                    z->parent->parent->color=1; // dada red
                    propagate(z);
                    propagate(z->parent);
                    z=z->parent->parent; // dada jhamelay akhon
                    //cout<<"in category A case -1"<<endl;
                }
                else
                {
                    if(z == z->parent->rc) // zigzag condition
                    {
                        z=z->parent;
                        leftRotate(z);
                        //cout<<"in category A case -2"<<endl;
                    }
                    z->parent->color=2;
                    z->parent->parent->color=1;
                    rightRotate(z->parent->parent);
                    //cout<<"in category A case -3"<<endl;
                }
            }

            else // bap jodi dadar left child
            {
                //cout<<"in CATEGORY B"<<endl;
                BSTNode<Key,E>* y= z->parent->parent->lc; // y chacha
                if(y->color==1) // Recoloring
                {
                    //cout<<"in category B case -1"<<endl;
                    z->parent->color=2; // bap black
                    y->color=2; // chacha black
                    z->parent->parent->color=1; // dada red
                    propagate(z);
                    propagate(z->parent);
                    z=z->parent->parent; // dada jhamelay akhon
                }
                else
                {
                    if(z == z->parent->lc) // zigzag condition
                    {
                        z=z->parent;
                        rightRotate(z);
                        //cout<<"in category B case -2"<<endl;
                    }
                    z->parent->color=2;
                    z->parent->parent->color=1;
                    leftRotate(z->parent->parent);
                    //cout<<"in category B case -3"<<endl;
                }
            }
        }
        if(z!=root)
        {
            propagate(z);
            z=z->parent;
        }
        root->color=2;
    }
    void find(Key k)
    {
        BSTNode<Key,E>* ans=findhelp(root,k);
        if(ans==NULL)
            cout<<"0"<<endl;
        else
            cout<<"1"<<endl;
    }
    void findless(Key k)
    {
        int ans=findlesshelp(root,k);
        cout<<ans<<endl;
    }
    int size()
    {
        return nodeCount;
    }
    void print()
    {
        if(root==NULL)
        {
            cout<<"The tree is empty"<<endl;
        }
        else
            {
                cout<<root->data<<" color "<<root->color<<" total "<<root->total<<" left "<<root->lcnt<<" right "<<root->rcnt<<endl;
                if(root->lc!=NULL) printhelp(root->lc);
                else
                {
                    if(root->rc!=NULL)
                    cout<<"()";
                }
                if(root->rc!=NULL) printhelp(root->rc);
                else
                    if(root->lc!=NULL)
                    cout<<"()";
            }
        cout<<endl;
    }


    void delete_fixup(BSTNode<Key,E>* x)
    {
        BSTNode<Key,E>* dummy=x;
        while((x->color == 2) && (x!=root))
        {
            if((x== x->parent->lc))
            {
                //cout<<"In Category A"<<endl;
                BSTNode<Key,E>* w=x->parent->rc;
                if((w->color==1))
                {
                    w->color=2;
                    x->parent->color=1;
                    leftRotate(x->parent);
                    w=x->parent->rc;
                    //cout<<"In Category A if "<<endl;
                }
                if((w->lc->color==2) &&  (w->rc->color==2))
                {
                    w->color=1;
                    x=x->parent;
                    //cout<<"In Category A if 2 "<<endl;
                }
                else
                {
                    if(w->rc->color==2)
                    {
                        w->lc->color=2;
                        w->color=1;
                        rightRotate(w);
                        w=x->parent->rc;
                        //cout<<"In Category A if 3 "<<endl;
                    }
                    w->color=x->parent->color;
                    x->parent->color=2;
                    w->rc->color=2;
                    leftRotate(x->parent);
                    dummy=x;
                    x=root;
                    //cout<<"In Category a if else "<<endl;
                }
            }
            else
            {
                //cout<<"In Category B"<<endl;
                BSTNode<Key,E>* w=x->parent->lc;
                if(w->color==1)
                {
                    w->color=2;
                    x->parent->color=1;
                    rightRotate(x->parent);
                    w=x->parent->lc;
                    //cout<<"In Category B if "<<endl;
                }
                if(w->rc->color==2 && w->lc->color==2)
                {
                    w->color=1;
                    x=x->parent;
                    //cout<<"In Category B if 2 "<<endl;
                }
                else
                {
                    if(w->lc->color==2)
                    {
                        w->rc->color=2;
                        w->color=1;
                        leftRotate(w);
                        w =x->parent->lc;
                        //cout<<"In Category B if 3 "<<endl;
                    }
                    w->color=x->parent->color;
                    x->parent->color=2;
                    w->lc->color=2;
                    rightRotate(x->parent);
                    dummy=x;
                    x=root;
                    //cout<<"In Category B if else "<<endl;
                }
            }
        }
        while(dummy!=root)
        {
            propagate(dummy);
            dummy=dummy->parent;
        }
        x->color=2;
    }


    int rbDelete(Key k)
    {
        BSTNode<Key,E>* ans=findhelp(root,k);
        if(ans==NULL) return 0;
        BSTNode<Key,E>* z=ans;

        BSTNode<Key,E>*y=new BSTNode<Key,E>();
        BSTNode<Key,E>*x=new BSTNode<Key,E>();;
        y->setNil();
        x->setNil();

        if(z->lc->isNull() || z->rc->isNull())
            y=z;
        else
            y = getmin(z->rc);

        if(y->lc->isNotNull()) x=y->lc;
        else x=y->rc;

        x->parent=y->parent;

        if(y->parent->isNull()) root=x;
        else if(y== y->parent->lc)
            {
                y->parent->lc=x;
                y->parent->lcnt=x->total;
                y->parent->total=1+y->parent->lcnt+y->parent->rcnt;
            }
        else{

            y->parent->rc=x;
            y->parent->rcnt=x->total;
            y->parent->total=1+y->parent->lcnt+y->parent->rcnt;
        }

        propagate(y->parent);

        if(y!=z)
           {
               z->key=y->key;
               z->data=y->data;
           }
        if(y->color==2)
           {
               propagate(x);
               delete_fixup(x);
           }
        delete y;
        return 1;
    }



};
int main()
{

    freopen("testrb.txt","r",stdin);
    BST<int,int>b;
    int k,opt=1;
    cin>>k;
    while(k--)
    {
        //cout<<opt<<endl;
        int option,a;
        cin>>option>>a;
        cout<<option<<" "<<a<<" ";
        if(option==1)
        {
            b.insert(a,a);
        }
        else if(option==2)
        {
            b.find(a);
        }
        else if(option==3)
        {
            b.findless(a);
        }
        else
        {
            int ans = b.rbDelete(a);
            cout<<ans<<endl;
        }
    }

    return 0;
}









