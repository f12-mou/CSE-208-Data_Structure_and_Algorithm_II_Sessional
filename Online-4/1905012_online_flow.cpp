#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=1005;
int arr[N][N];
int mark[N][N];
ll source, destination;
ll visitedToken=1;
ll vis[N];
ll pos_inf=1e18;
ll n,m,k;
ll maxFlow=0;
ll cnt[N];

class Edge
{
public:
    ll from, to, capacity, flow,res_from, res_cap, res_flow, res_to;
    Edge(){}
    Edge(ll f, ll t, ll c, ll f2, ll t2, ll c2)
    {
        from=f;to=t;capacity=c;flow=0;res_from=t2;res_to=f2;res_cap=c2;res_flow=0;
    }
    bool isResidual(){ return capacity==0;}
    ll remCapacity(){return capacity-arr[from][to];}
    void augment(ll bottleneck)
    {
        flow+=bottleneck;
        res_flow-=bottleneck;
        arr[from][to]+=bottleneck;
        arr[to][from]-=bottleneck;
    }
};
Edge adj[N][N];
void addEdge(ll from, ll to, ll cap)
{
    Edge e1(from, to, cap, to, from, 0);
    Edge e2( to, from, 0, from, to, cap);
    adj[from][cnt[from]]=e1;
    cnt[from]++;
    adj[to][cnt[to]]=e2;
    cnt[to]++;
}
ll dfs(ll node, ll flow)
{
    if(node==destination) return flow;
    vis[node]=visitedToken;
    for(ll i=0;i<cnt[node];i++)
    {

        Edge edge=adj[node][i];
        ll bottleneck=0;
        if((edge.remCapacity()>0) && (vis[edge.to]!=visitedToken))
             bottleneck=dfs(edge.to, min(flow, edge.remCapacity()));
        if(bottleneck>0)
        {
            edge.augment(bottleneck);
            adj[node][i]=edge;
            return bottleneck;
        }
    }
    return 0;
}
void solve()
{
    for(ll f=dfs(source, pos_inf); f!=0; f=dfs(source, pos_inf))
    {
        visitedToken++;
        maxFlow+=f;
    }
}
int main()
{
    int t;
    cin>>t;
    int caseNo=1;
    while(t--){
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            arr[i][j]=mark[i][j]=0;
        }
    }
    maxFlow=0;
    cin>>n>>m;// man and woman number.
    ll a,b,c;
    int height[n+1],age[n+1],divorce[n+1];
    int height2[m+1],age2[m+1],divorce2[m+1];
    source=n+m+1;
    destination=source+1;
    /*for(ll i=1;i<=k;i++)
    {
        cin>>a>>b;
        c=1;
        mark[a][b+n]=mark[source][a]=mark[b+n][destination]=1;
    }*/
    for(int i=1;i<=n;i++)
    {
        cin>>height[i]>>age[i]>>divorce[i];
    }
    for(int i=1;i<=m;i++)
    {
        cin>>height2[i]>>age2[i]>>divorce2[i];
    }
    for(int i=1;i<=n;i++)
    {
        int a,b;
        a=i;
        for(int j=1;j<=m;j++)
        {
            if((abs(height[i]-height2[j])<=12) && (abs(age[i]-age2[j]<=5)) && (divorce[i]==divorce2[j]))
            {
                b=j;
                mark[a][b+n]=mark[source][a]=mark[b+n][destination]=1;
            }
        }
    }




    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            if(mark[i][j]!=0)
                addEdge(i,j,mark[i][j]);
    solve();
    cout<<"caseNo "<<caseNo++<<":  "<<maxFlow<<endl;
    for(int i=1;i<=n;i++)
        for(int j=n+1;j<=(n+m);j++)
            if(arr[i][j]!=0) cout<<"man ID: "<<i<<" matched with woman ID: "<<j-n<<endl;
    cout<<endl;
    }
   return 0;
}


