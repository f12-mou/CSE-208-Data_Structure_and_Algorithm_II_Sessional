int isPrime[MAX_SIZE];

void setSieve()
{
    isPrime[0] = isPrime[1] = 1;
    for(long long i = 2; i*i < MAX_SIZE; i++)
        if(isPrime[i] == 0)
        for(long long j = i*i; j < MAX_SIZE; j += i)
            isPrime[j] = 1;
}

class node
{
public:
    string key;
    int val;
    node* lc;
    node* rc;
    node()
    {
        lc=NULL;
        rc=NULL;
    }
    node(string k,int data)
    {
        key=k;
        val=data;
        lc=rc=NULL;
    }

};
ll compute_hash(string s) {
    const int p = 31;
    const int m = 1e9 + 9;
    ll hash_value = 0;
    ll p_pow = 1;
    for (char c : s) {
        hash_value = (hash_value + (c - 'A' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return hash_value;
}
ll P1(ll x)
{
    return 5*x;
}
ll P2(ll x)
{
    return (x+(x*x))/2;
}

class quadHash
{
public:
    int currCapacity;
    float loadFactor;
    int nodeCnt;
    node** p;
    int probe;

    quadHash(int total, float factor)
    {
        currCapacity=total;
        loadFactor=factor;
        nodeCnt=0;
        p=new node*[currCapacity];
        for(int i=0;i<currCapacity;i++)
        {
            p[i]=NULL;
        }
    }
    ~quadHash()
    {
        for(int i=0;i<currCapacity;i++)
            if(p[i]!=NULL)
                delete p[i];
        delete p;
    }
    node* searchHelp(string k)
    {
        ll keyHash=compute_hash(k);
        keyHash=keyHash%currCapacity;
        node* ans=NULL;
        node* temp=p[keyHash];
        ll index=keyHash;
        ll x=1;
        while(temp!=NULL)
        {
            if(temp->key==k)
            {
                ans=temp;
                break;
            }
            index=((keyHash%currCapacity)+(P2(x)%currCapacity))%currCapacity;
            x++;
            temp=p[index];
        }
        probe=x-1;
        return ans;
    }
    int getProbe(){return probe;}

    int searchHash(string k)
    {
        node* found=searchHelp(k);
        if(found==NULL) return 0;
        else {
            if(found->val!=-1)
                return found->val;
            else
                return 0;
        }
    }
    void deleteHash(string k)
    {
        node* found=searchHelp(k);
        if(found==NULL) return ;
        else {
            if(found->val!=-1){
                found->val=-1;
                nodeCnt--;
                return;
            }
        }
    }
    void insertHash(string k, int value)
    {

        node* found=searchHelp(k);
        if(found!=NULL) {
                if(found->val==-1) nodeCnt++;
                found->val=value;
                return;
        }
        else{

        ll keyHash=compute_hash(k);
        keyHash=keyHash%currCapacity;
        node* obj;
        ll index=keyHash;
        ll x=1;
        while(p[index]!=NULL && p[index]->val!=-1)
        {
            index=((keyHash%currCapacity)+(P2(x)%currCapacity))%currCapacity;
            x++;
        }
        if(p[index]==NULL){
            obj=new node(k,value);
            p[index]=obj;
            nodeCnt++;
        }
        else
        {
            nodeCnt++;
            p[index]->key=k;
            p[index]->val=value;
        }
        }

    }
};

class doubleHash
{
public:
    int currCapacity;
    int prime;
    float loadFactor;
    int nodeCnt;
    node** p;
    int probe;

    doubleHash(int total, float factor)
    {
        currCapacity=total;
        loadFactor=factor;
        prime = currCapacity - 1;
        nodeCnt=0;
        while(isPrime[prime] == 1)
            prime--;
        p=new node*[currCapacity];
        for(int i=0;i<currCapacity;i++)
        {
            p[i]=NULL;
        }
    }
    ~doubleHash()
    {
        for(int i=0;i<currCapacity;i++)
        {
            if(p[i]!=NULL)
                delete p[i];
        }
        delete p;
    }
    int hash2(int value){
        return prime - (value%prime);
    }
    node* searchHelp(string k)
    {
        ll keyHash=compute_hash(k);
        ll offset=hash2(keyHash);
        keyHash=keyHash%currCapacity;
        node* ans=NULL;
        node* temp=p[keyHash];
        ll index=keyHash;
        ll x=1;
        while(temp!=NULL)
        {
            if(temp->key==k)
            {
                ans=temp;
                break;
            }
            index=((keyHash%currCapacity)+((x*offset)%currCapacity))%currCapacity;
            x++;
            temp=p[index];
        }
        probe=x-1;
        return ans;
    }
    int getProbe()
    {
        return probe;
    }

    int searchHash(string k)
    {
        node* found=searchHelp(k);
        if(found==NULL) return 0;
        else {
            if(found->val!=-1)
                return found->val;
            else
                return 0;
        }
    }
    void deleteHash(string k)
    {
        node* found=searchHelp(k);
        if(found==NULL) return ;
        else {
            if(found->val!=-1){
                found->val=-1;
                nodeCnt--;
                return;
            }

        }
    }


    void insertHash(string k, int value)
    {

        node* found=searchHelp(k);
        if(found!=NULL) {
                if(found->val==-1) nodeCnt++;
                found->val=value;
                return;
        }
        else{

        ll keyHash=compute_hash(k); // corresponding val of string

        ll offset=hash2(keyHash);

        keyHash=keyHash%currCapacity;

        node* obj;
        ll index=keyHash;
        ll x=1;
        while(p[index]!=NULL && p[index]->val!=-1)
        {
            index=((keyHash%currCapacity)+((x*offset)%currCapacity))%currCapacity;
            x++;
        }
        if(p[index]==NULL){
            obj=new node(k,value);
            p[index]=obj;
            nodeCnt++;
        }
        else
        {
            nodeCnt++;
            p[index]->key=k;
            p[index]->val=value;
        }
        }

    }
};
class chaining
{
public:
    int currCapacity;
    float loadFactor;
    node** p;

    chaining(int total, float factor)
    {
        currCapacity=total;
        loadFactor=factor;
        p=new node*[currCapacity];
        for(int i=0;i<currCapacity;i++)
        {
            p[i]=NULL;
        }
    }
    ~chaining()
    {
        for(int i=0;i<currCapacity;i++)
        {
            node* now=p[i];
            while(now!=NULL)
            {
                node* temp=now;
                now=now->rc;
                delete temp;
            }
        }
        delete p;
    }
    node* searchHelp(string k)
    {
        ll index=compute_hash(k);
        index=index%currCapacity;
        node* temp=p[index];
        while(temp!=NULL)
        {
            if(temp->key==k)
                break;
            temp=temp->rc;
        }
        return temp;
    }
    void deleteHash(string k)
    {
        ll index=compute_hash(k);
        index=index%currCapacity;
        node* found=searchHelp(k);
        if(found==NULL)
        {
            return;
        }
        else

        {
            if(found->lc!=NULL)
            {
                found->lc->rc=found->rc;
            }
            if(found->rc!=NULL)
            {
                found->rc->lc=found->lc;
            }
            if(found->lc==NULL)
            {
                p[index]=found->rc;
            }

            delete found;
        }
    }
    ll searchHash(string k)
    {
        node* found=searchHelp(k);
        if(found==NULL) return 0;
        else
            return found->val;

    }
    void insertHash(string k, int value)
    {
        ll index=compute_hash(k);
        index=index%currCapacity;
        node* obj;
        if(p[index]==NULL)
        {
            obj=new node(k,value);
            p[index]=obj;
            return ;
        }
        else
        {
            int flag=0;
            node* now=p[index];
            while(now->rc!=NULL)
            {
                if(now->key==k)
                {
                    flag=1;
                    break;
                }
                now=now->rc;
            }
            if(flag==0)
            {
                if(now->key==k)
                {
                    // do nothing
                }
                else{
                obj=new node(k,value);
                now->rc=obj;
                obj->lc=now;
                }
            }
        }
    }


};

class linearHash
{
public:
    int currCapacity;
    int nodeCnt;
    float loadFactor;
    int probe;
    node** p;
    linearHash(int total, float factor)
    {
        currCapacity=total;
        loadFactor=factor;
        nodeCnt=0;
        p=new node*[currCapacity];
        for(int i=0;i<currCapacity;i++)
        {
            p[i]=NULL;
        }
    }
    ~linearHash()
    {
        for(int i=0;i<currCapacity;i++)
        {
            if(p[i]!=NULL)
            {
                delete p[i];
            }
        }
        delete p;
    }
    node* searchHelp(string k)
    {
        ll keyHash=compute_hash(k);
        keyHash=keyHash%currCapacity;
        node* ans=NULL;
        node* temp=p[keyHash];
        ll index=keyHash;
        ll x=1;
        while(temp!=NULL)
        {
            if(temp->key==k)
            {
                ans=temp;
                break;
            }
            index=((keyHash%currCapacity)+(P1(x)%currCapacity))%currCapacity;
            x++;
            temp=p[index];
        }
        probe=x-1;
        return ans;
    }

    int searchHash(string k)
    {
        node* found=searchHelp(k);
        if(found==NULL) return 0;
        else {
            if(found->val!=-1)
                return found->val;
            else
                return 0;
        }
    }
    int getProbe()
    {
        return probe;
    }
    void deleteHash(string k)
    {
        node* found=searchHelp(k);
        if(found==NULL) return ;
        else {
            if(found->val!=-1){
                found->val=-1;
                nodeCnt--;
                return;
            }
        }
    }
    void insertHelp(string k, int value)
    {
        node* found=searchHelp(k);
        if(found!=NULL) {
            if(found->val==-1)
            {
                nodeCnt++;
                found->val=value;
            }
            return;
        }
        else{

        ll keyHash=compute_hash(k);
        keyHash=keyHash%currCapacity;
        node* obj;
        ll index=keyHash;
        ll x=1;
        while(p[index]!=NULL && p[index]->val!=-1)
        {
            index=((keyHash%currCapacity)+(P1(x)%currCapacity))%currCapacity;
            x++;
        }
        if(p[index]==NULL){
            obj=new node(k,value);
            p[index]=obj;
            nodeCnt++;
        }
        else
        {
            nodeCnt++;
            p[index]->key=k;
            p[index]->val=value;
        }
        }
    }


    void insertHash(string k, int value)
    {
        insertHelp(k,value);
    }
};
