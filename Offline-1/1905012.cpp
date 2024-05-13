#include<bits/stdc++.h>
using namespace std;
#define ll long long

const int N=100005;
int n,m;
vector<pair<int,int>>kruskal_ans_vec;
vector<pair<double,pair<int,int>>>vec;
vector<pair<int,double>>adj[N];
int token[N],parent_in_primsAlgo[N];
int len[N],link[N];

int find(int a)
{
    while(a!=link[a])a=link[a];
    return a;
}

void join(int a,int b)
{
    int x=find(a);
    int y=find(b);
    if(x==y) return ;
    if(len[x]>len[y]) swap(x,y); // worst case time complexity log n.
    len[y]+=len[x];
    link[x]=y;

}

double kruskal()
{
    for(int i=0;i<n;i++){link[i]=i;len[i]=1;}
    sort(vec.begin(),vec.end());
    double sum=0;
	for(auto edge:vec)
    {
        int cost=edge.first;
        int a=edge.second.first;
        int b=edge.second.second;
        if(find(a)==find(b)) continue; // making cycle.
        sum+=cost;
        kruskal_ans_vec.push_back(make_pair(a,b));
        join(a,b);
    }
    int connected_component=0;
    for(int i=0;i<n;i++)
    {
        if(link[i]==i) connected_component++;
    }
    if(connected_component==1)  // checking if the graph is connected.
    {
        return sum;
    }
    else
        return -1;
 }


 double prim()
 {
     for(int i=0;i<n;i++) {token[i]=-1;parent_in_primsAlgo[i]=-1;}
     bool isInMST[n];
     for(int i=0;i<n;i++) isInMST[i]=false;
     priority_queue<pair<double,int>>pq;
     pq.push(make_pair(0.0,0));
     while(!pq.empty())
     {
         pair<double,int>p=pq.top();
         pq.pop();
         int node=p.second;
         int cost=(-1)*p.first;
         if(isInMST[node]==true) continue;
         isInMST[node]=true;
         token[node]=cost;
         for(int i=0;i<adj[node].size();i++)
         {
             pair<int,double>p2=adj[node][i];
             int next=p2.first;
             double edge_weight_now=p2.second;
             if(isInMST[next]==false)
                {
                    token[next]=edge_weight_now;
                    parent_in_primsAlgo[next]=node;
                    pq.push(make_pair((-1)*token[next],next));
                }
         }

     }
     double prim_ans=0.0;
     for(int i=1;i<n;i++)
       {
           if(token[i]==-1)
           {
               prim_ans=-1; break;
           }
           prim_ans+=token[i];
       }
    return prim_ans;
 }

int main()
{
    ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	freopen("mst.txt","r",stdin);
	cin>>n>>m;
	for(int i=0;i<m;i++)
	{
	    int a,b;
	    double c;
	    cin>>a>>b>>c;
	    vec.push_back(make_pair(c,make_pair(a,b))); // Input for Kruskal's algorithm.
	    adj[a].push_back(make_pair(b,c));           // Input for Prim's algorithm.
	    adj[b].push_back(make_pair(a,c));           // Input for Prim's algorithm.
	}

	double sum1=kruskal();
	if(sum1==-1)
        {
            cout<<"NOT POSSIBLE AS THE GRAPH IS NOT CONNECTED."<<endl;
        }
    else{
        cout<<"Cost of the minimum spanning tree: "<<sum1<<endl;
        cout<<"List of edges selected by Prim's: {";
        for(int i=0;i<kruskal_ans_vec.size();i++)
        {
            if(i!=0) cout<<",";
            cout<<"("<<kruskal_ans_vec[i].first<<","<<kruskal_ans_vec[i].second<<")";
        }
        cout<<"}"<<endl;
    }
    double sum2=prim();
    if(sum2==-1)
        {
            cout<<"NOT POSSIBLE AS THE GRAPH IS NOT CONNECTED."<<endl;
        }
    else{
        cout<<"List of edges selected by Kruskal's: {";
        for(int i=1;i<n;i++)
        {
            if(i!=1) cout<<",";
            cout<<"("<<i<<","<<parent_in_primsAlgo[i]<<")";
        }
        cout<<"}"<<endl;
    }
    return 0;
}

