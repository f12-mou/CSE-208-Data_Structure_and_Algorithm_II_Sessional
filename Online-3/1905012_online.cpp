// Based on Dijkstra Algorithm
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1005;

vector<pair<int,int>>adj[N]; // Adjacency List for each node
ll dist[N];                  // Distance array
ll total[N];
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
        total[i]=INT_MAX;
    }
    priority_queue<pair<pair<ll,ll>,ll>>pq;      // -1 * cost  and then to vertex
    dist[source]=0;
    total[source]=0;
    vis[source]=true;
    pq.push(make_pair(make_pair(-1*0,-1*0),source)); // dist number of edges index

    while(!pq.empty())
    {
        pair<pair<ll,ll>,ll>p2 = pq.top();
        pair<ll,ll>p=p2.first;
        ll from = p2.second;
        ll cost_now = (-1) * p.first;
        ll total_now= (-1)*p.second;
         pq.pop();
        vis[from]=true;

        if(cost_now>dist[from])     // Implementing Lazy Dijkstra, avoiding the duplicate key-value pairs
            continue;

        for(auto pp : adj[from])
        {
            ll edge_cost = pp.second;
            ll to = pp.first;
            if(vis[to] == true) continue;
            ll newDistance = edge_cost + cost_now;
            ll newTotal=1+total_now;
            if(newDistance < dist[to])              // Well, got a better option.
            {
                dist[to] = newDistance;             // Edge Relaxation
                total[to]=newTotal;
                parent[to] = from;
                pq.push(make_pair(make_pair((-1)*dist[to], (-1)*total[to]),to));
            }
            else if(newDistance==dist[to])
            {
                dist[to] = newDistance;             // Edge Relaxation
                if(total[to]>newTotal)
                  {total[to]=newTotal;
                parent[to] = from;
                pq.push(make_pair(make_pair((-1)*dist[to], (-1)*total[to]),to));
                  }
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
        adj[d].push_back(make_pair(c,cost));
    }
    cin>>source;

    Dijkstra();

   /* if(parent[destination]==-1)
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
    */
    cout<<"ans here "<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<total[i]<<endl;
    }
    return 0;
}
/*
7 10
0 1 2
0 2 2
0 3 4
1 3 2
2 3 2
3 4 1
3 5 1
3 6 3
4 6 1
5 6 1
0
*/


