#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=505;

// Variables
int n,m;
int s,t;
ll init_capacity[N][N];
ll capacity[N][N];
ll arr[N][N];
vector<int>adj[N];
ll wins[N];
ll loss[N];
ll rem[N];
bool vis[N];
int xtra;
string names[N];

ll bfs(int s, int t,int parent[])
{
    for(int i=0;i<=t;i++) parent[i]=-1;
    parent[s]=-2;
    queue<pair<ll,ll>>q;
    q.push(make_pair(s,INT_MAX));
    int idx=0;

    while(!q.empty())
    {
        pair<ll,ll>p=q.front();
        int curr=p.first;
        ll rem_capacity=p.second;
        q.pop();
        for(int next:adj[curr])
        {
            if((parent[next]==-1) && (capacity[curr][next]))
            {
                parent[next]=curr;
                ll new_rem_capacity=min(rem_capacity, capacity[curr][next]);
                if(next==t)
                    return new_rem_capacity;
                q.push(make_pair(next,new_rem_capacity));
            }
        }
    }
    return 0;
}



ll maxflow()
{
    ll flow=0;
    int parent[N];
    ll new_flow=0;
    int ix=0;

    while(new_flow=bfs(0,n+1+xtra,parent))
    {
        flow+=new_flow;
        int curr=n+1+xtra;
        while(curr!=0)
        {
            int prev=parent[curr];
            arr[prev][curr]+=new_flow;
            arr[curr][prev]-=new_flow;
            capacity[prev][curr]-=new_flow;
            capacity[curr][prev]+=new_flow;
            curr=prev;
        }
    }
    return flow;
}
void dfs2(int node)
{
    vis[node]=true;
    for(int i=0;i<=t;i++)
    {
        if((capacity[node][i]!=0) && (vis[i]==false))
            dfs2(i);
    }
}
void mincut(int x)
{
    dfs2(0);
    map<int,int>mp;
    for(int i=1;i<=n;i++)
    {
        if(vis[i]==true)
        {
            mp[i]=1;
        }
    }
    int total_wins=0, total_rem=0;
    vector<int>vec;
    int cnt=0;
    for(int i=1;i<=n;i++)
    {
        if(i==x) continue;
        if(mp[i]==1)
        {
            total_wins+=wins[i];
            vec.push_back(i);
            cout<<names[i]<<" ";
            cnt++;
        }
    }
    for(int i=0;i<vec.size();i++)
    {
        for(int j=i+1;j<vec.size();j++)
        {
            int node1=vec[i];
            int node2=vec[j];
            total_rem+=init_capacity[node1][node2];
        }
    }
    cout<<" have won a total of "<<total_wins<<" games."<<endl;
    cout<<"They play each other "<<total_rem<<" times."<<endl;
    cout<<"On average, each of the teams in this group wins "<<total_wins+total_rem<<"/"<<cnt<<" = "<<float((total_wins+total_rem)/(float)(cnt))<<"games."<<endl;


}
void refresh(int x)
{
    for(int i=0;i<N;i++) adj[i].clear();
    for(int i=0;i<N;i++)
    {
        vis[i]=false;
        for(int j=0;j<N;j++)
        {
            capacity[i][j]=0;arr[i][j]=0;
        }
    }
    int start=n+1;  // Start of Game nodes
    int t=n+1+xtra;
    for(int i=1;i<=n;i++)
    {
        if(i==x) continue;
        for(int j=i+1;j<=n;j++)
        {
            if(j==x) continue;

            adj[0].push_back(start);
            adj[start].push_back(i);
            adj[start].push_back(j);

            adj[start].push_back(0);    // residual edges
            adj[i].push_back(start);    // residual edges
            adj[j].push_back(start);    // residual edges


            capacity[0][start]=init_capacity[i][j];
            capacity[start][i]=INT_MAX; // Doesn't affect our flow graph
            capacity[start][j]=INT_MAX; // Doesn't affect our flow graph
            capacity[i][t]=wins[x]+rem[x]-wins[i];
            capacity[j][t]=wins[x]+rem[x]-wins[j];  // Limiting the number of wins.

            start++;
        }
    }
    for(int i=1;i<=n;i++)
    {
        if(i==x) continue;
        else
           {
                adj[i].push_back(t);
                adj[t].push_back(i); // back edge
           }

    }
    maxflow();
    int flag=1;
    for(int i=0;i<adj[0].size();i++)
    {
        int node=adj[0][i];
        if(capacity[0][node]!=0)
        {
            flag=0;break;
        }
    }
    if(flag==0)
       {
           cout<<endl;
           cout<<names[x]<<" is eliminated."<<endl;
           cout<<"They can win at most "<<wins[x]<<" + "<<rem[x]<<" = "<<wins[x]+rem[x]<<" games."<<endl;
           mincut(x);
       }
}

int main()
{
    cin>>n;
    xtra=((n)*(n-1))/2; // Number Of Additional Game nodes.
    t=n+1+xtra;         // Sink node.
    for(int i=1;i<=n;i++)
    {
        cin>>names[i]>>wins[i]>>loss[i]>>rem[i];
        for(int j=1;j<=n;j++)
        {
            cin>>init_capacity[i][j];
        }
    }
    for(int j=1;j<=n;j++)
    {
        int flag2=0;
        for(int i=1;i<=n;i++)
        {
            if(i==j) continue;
            if(wins[j]+rem[j]<wins[i]) // A team already with more wins.
            {
                flag2=1;
                cout<<endl;
                cout<<names[j]<<" is eliminated."<<endl;
                cout<<"They can win at most "<<wins[j]<<" + "<<rem[j]<<" = "<<wins[j]+rem[j]<<" games."<<endl;
                cout<<names[i]<<" has won a total of "<<wins[i]<<" games"<<endl;
                cout<<"They play each other 0 times."<<endl;
                cout<<"So, on average each of the teams in this group wins "<<wins[i]<<"/1 = "<<wins[i]<<" games."<<endl;
                break;
            }
        }
        if(flag2==0)
            refresh(j); // No clear conclusion, Max Flow algorithm needed.
    }
    return 0;
}
/*
4
Atlanta 83 71 8 0 1 6 1
Philadelphia 80 79 3 1 0 0 2
New_York 78 78 6 6 0 0 0
Montreal 77 82 3 1 2 0 0

5
New_York 75 59 28 0 3 8 7 3
Baltimore 71 63 28 3 0 2 7 4
Boston 69 66 27 8 2 0 0 0
Toronto 63 72 27 7 7 0 0 0
Detroit 49 86 27 3 4 0 0 0
*/



