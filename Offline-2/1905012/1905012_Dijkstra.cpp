// Based on Dijkstra Algorithm
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1005;

vector<pair<int,int>>adj[N]; // Adjacency List for each node
ll dist[N];                  // Distance array
int parent[N];               // For constructing the path from source to destination
bool vis[N];                 // Marking to be visited or unvisited
int n,m;                     // Number of nodes, number of edges
int source, destination;     // Source Node, Destination node

void Dijkstra()
{
    for(int i=0;i<n;i++)
    {
        dist[i]=INT_MAX;        // Initialization with positive infinity
        vis[i]=false;           // Marked visited false
        parent[i]=-1;           // Parent to be null
    }
    priority_queue<pair<ll,ll>>pq;      // -1 * cost  and then to vertex
    dist[source]=0;
    vis[source]=true;
    pq.push(make_pair(-1*0,source));

    while(!pq.empty())
    {
        pair<ll,ll>p = pq.top();
        pq.pop();
        ll from = p.second;
        ll cost_now = (-1) * p.first;
        vis[from]=true;

        if(cost_now>dist[from])     // Implementing Lazy Dijkstra, avoiding the duplicate key-value pairs
            continue;

        for(auto pp : adj[from])
        {
            ll edge_cost = pp.second;
            ll to = pp.first;
            if(vis[to] == true) continue;
            ll newDistance = edge_cost + cost_now;
            if(newDistance < dist[to])              // Well, got a better option.
            {
                dist[to] = newDistance;             // Edge Relaxation
                parent[to] = from;
                pq.push(make_pair((-1)*dist[to], to));
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);

	cin>>n>>m;
	int c,d,cost;
	for(int i=0;i<m;i++)
    {
        cin>>c>>d>>cost;
        adj[c].push_back(make_pair(d,cost));
        //adj[d].push_back(make_pair(c,cost));
    }
    cin>>source>>destination;

    Dijkstra();

    if(parent[destination]==-1)
    {
        cout<<"THE DESTINATION CAN NOT BE REACHED."<<endl;
    }
    else
    {
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


