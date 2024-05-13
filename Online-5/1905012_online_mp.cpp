#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX_SIZE 1000005

int isPrime[MAX_SIZE];

void setSieve()
{
    isPrime[0] = isPrime[1] = 1;
    for(long long i = 2; i*i < MAX_SIZE; i++)
        if(isPrime[i] == 0)
        for(long long j = i*i; j < MAX_SIZE; j += i)
            isPrime[j] = 1;
 }
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
class node
{
public:
    string key;
    int val;
    node()
    {
    }
    node(string k,int data)
    {
        key=k;
        val=data;
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

    void reAllocate()
    {
        vector<pair<string,int>>vec;
        for(int i=0;i<currCapacity;i++)
        {
            if(p[i]!=NULL)
            {
                vec.push_back(make_pair(p[i]->key, p[i]->val));
                delete p[i];
            }
        }
        delete p;
        currCapacity=2*currCapacity;
        while(isPrime[currCapacity]==1)
            currCapacity++;
        prime=currCapacity-1;
        while(isPrime[prime] == 1)
            prime--;
        nodeCnt=0;
        probe=0;
        p=new node*[currCapacity];
        for(int i=0;i<currCapacity;i++)
        {
            p[i]=NULL;
        }
        for(int i=0;i<vec.size();i++)
        {
            if(vec[i].second!=-1)
                insertHash(vec[i].first, vec[i].second);
        }
        cout<<"in reallocate func currCapacity and prime is  "<<currCapacity<<" "<<prime<<endl;
    }


    void reAllocate2()
    {
        vector<pair<string,int>>vec;
        for(int i=0;i<currCapacity;i++)
        {
            if(p[i]!=NULL)
            {
                vec.push_back(make_pair(p[i]->key, p[i]->val));
                delete p[i];
            }
        }
        delete p;
        currCapacity=currCapacity/2;
        while(isPrime[currCapacity]==1)
            currCapacity++;
        prime=currCapacity-1;
        while(isPrime[prime] == 1)
            prime--;
        nodeCnt=0;
        probe=0;
        p=new node*[currCapacity];
        for(int i=0;i<currCapacity;i++)
        {
            p[i]=NULL;
        }
        for(int i=0;i<vec.size();i++)
        {
            if(vec[i].second!=-1)
                insertHash(vec[i].first, vec[i].second);
        }
        cout<<"in reallocate2 func currCapacity and prime is  "<<currCapacity<<" "<<prime<<endl;
    }



    doubleHash(int total, float factor=0.4)
    {
        probe=0;
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
        probe+=(x-1);
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
        if((double)nodeCnt/(1.0*currCapacity)<0.4)
            reAllocate2();
    }


    void insertHash(string k, int value)
    {
        if(nodeCnt!=0){
        if(((probe)/nodeCnt)>2)
            reAllocate();
        }
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
        //probe=x-1;

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
 int main()
{
    setSieve();
    int n;
    cin>>n;
    string input_arr[1000];
    for(int i=0;i<1000;i++)
    {
        string a="";
        for(int j=0;j<7;j++)
        {
            int r=(rand()%(90-65))+65;
            char c=(char)(r);
            int r2=(rand()%(122-97))+97;
            char c2=(char)(r2);
           if(rand()%2)
                a+=c;
            else
                a+=c2;
        }
        input_arr[i]=a;
    }
    for(int i=0;i<n;i++)
    {
        cout<<input_arr[i]<<endl;
    }
    double load[6]={0.4,0.5,0.6,0.7,0.8,0.9};
    doubleHash arr[6]={doubleHash(n,0.4),doubleHash(n,0.5),doubleHash(n,0.6),doubleHash(n,0.7),doubleHash(n,0.8),doubleHash(n,0.9)};
    for(int i=0;i<6;i++)
    {
        int allowed_insert_cnt=(int)(load[i]*n);
        for(int j=0;j<allowed_insert_cnt;j++)
        {
            arr[i].insertHash(input_arr[j],j+1);
        }
    }
    for(int i=0;i<6;i++)
    {
        for(int j=0;j<100;j++)
        {
            int h=arr[i].searchHash(input_arr[j]);
        }
    }
    for(int i=0;i<6;i++){
    cout<<"avg number of probes in search "<<arr[i].getProbe()/100<<endl;
    }
    for(int i=0;i<6;i++)
    {
        int allowed_insert_cnt=(int)(load[i]*n);
        for(int j=0;j<allowed_insert_cnt;j++)
        {
            arr[i].insertHash(input_arr[j],j+1);
        }
    }
    for(int i=0;i<6;i++)
    {
        chrono::steady_clock::time_point chaining_search_begin = chrono::steady_clock::now();
        for(int j=0;j<100;j++)
        {
            int h=arr[i].searchHash(input_arr[rand()%1000]);
        }
        chrono::steady_clock::time_point chaining_search_end = chrono::steady_clock::now();
        //before_del1[i]=chrono::duration_cast<chrono::nanoseconds>(chaining_search_end-chaining_search_begin).count();
        //before_del1[i]=before_del1[i]/(double)search_cnt;
        cout<<"after reallocating avg time "<<chrono::duration_cast<chrono::nanoseconds>(chaining_search_end-chaining_search_begin).count()/100<<" nanoseconds and "<<endl;
    }
    for(int i=0;i<6;i++){
    cout<<"avg number of probes in search "<<arr[i].getProbe()/100<<endl;
    }
    for(int i=0;i<6;i++)
    {
        int allowed_insert_cnt=(int)(load[i]*n);
        for(int j=0;j<(int)(0.1*allowed_insert_cnt);j++)
        {
            arr[i].deleteHash(input_arr[((rand())%allowed_insert_cnt)]);
        }
    }
    for(int i=0;i<6;i++)
    {
        chrono::steady_clock::time_point chaining_search_begin = chrono::steady_clock::now();
        for(int j=0;j<100;j++)
        {
            int h=arr[i].searchHash(input_arr[(rand()%1000)]);
        }
        chrono::steady_clock::time_point chaining_search_end = chrono::steady_clock::now();
        //before_del1[i]=chrono::duration_cast<chrono::nanoseconds>(chaining_search_end-chaining_search_begin).count();
        //before_del1[i]=before_del1[i]/(double)search_cnt;
        cout<<"after reallocating2 function avg time "<<chrono::duration_cast<chrono::nanoseconds>(chaining_search_end-chaining_search_begin).count()/100<<" nanoseconds and "<<endl;
    }
    for(int i=0;i<6;i++){
    cout<<"avg number of probes in search "<<arr[i].getProbe()/100<<endl;
    }










    return 0;
}


