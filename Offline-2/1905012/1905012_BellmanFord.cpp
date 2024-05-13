// Based on BellmanFord Algorithm
#include<bits/stdc++.h>
using namespace std;
#define ll long long

const ll N=1005;
const ll mod=1e9+7;
ll positive_infinity = 1e8+5;
ll negative_infinity = -(1e8+5);

vector<int>adj[N];
ll dist[N];
bool vis[N];
int parent[N];
ll n,m;
int source, destination;
int flag_for_neg_cycle;

class Edge
{
public:
    ll to,from,cost;
    Edge()
    {
    }
};
void dfs(int node)
{
    vis[node]=true;
    for(auto child:adj[node])
    {
        if(vis[child]==false)
            dfs(child);
    }
}
int main()
{
    ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);

	cin>>n>>m;
	Edge edges[m];
	ll c,d,cost;
	for(ll i=0;i<m;i++)
    {
        cin>>c>>d>>cost;
        edges[i].from=c;
        edges[i].to = d;
        edges[i].cost = cost;
        adj[c].push_back(d);
    }
    cin>>source>>destination;

    for(ll i=0;i<n;i++)
    {
        dist[i]=positive_infinity;      // Initial Distance to be Positive Infinity
        vis[i]=false;                   // Marked visited to be false
        parent[i]=-1;                   // Parent set to be null, needed to reconstruct the path
    }

    dist[source]=0;
    dfs(source); // Indeed useful, edges are relaxed randomly, what about the case
                 // when are even unable to reach destination from source
    for(ll i=1;i<=n-1;i++)
    {
        for(auto edge:edges)
        {
            if(vis[edge.from]==false)
                continue;
            if(dist[edge.from]+edge.cost<dist[edge.to])
            {
                dist[edge.to]=dist[edge.from]+edge.cost; // Edge Relaxation
                parent[edge.to]=edge.from;
            }
        }
    }
    for(ll i=1;i<=n-1;i++)
    {
        for(auto edge:edges)
        {
            if(vis[edge.from]==false)
                continue;
            if(dist[edge.from]+edge.cost<dist[edge.to])
            {
                dist[edge.to]=negative_infinity; // !!! DETECTED NEGATIVE CYCLE
                flag_for_neg_cycle=1;
            }
        }
    }
    if(flag_for_neg_cycle==1)
        cout<<"The graph contains a negative cycle"<<endl;
    else if(dist[destination]==positive_infinity)
        cout<<"No Connection from source to destination"<<endl;
    else
    {
        cout<<"The graph does not contain a negative cycle"<<endl;
        cout<<"Shortest Path Cost: "<<dist[destination]<<endl;
        stack<int>path;
        path.push(destination);
        while(destination!=source)
        {
            destination=parent[destination];
            path.push(destination);
        }
        cout<<path.top();
        path.pop();
        while(!path.empty())
        {
            cout<<" -> ";
            int idx=path.top();
            path.pop();
            cout<<idx<<" ";
        }
    }
    return 0;
}

