#include<bits/stdc++.h>
using namespace std;
#define ll long long

const int N=105;

ll dp[N][N];
int nxt[N][N];
int n,edges;

void floyd_warshall()
{
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(dp[i][j]!=1e16)
                nxt[i][j]=j;    // Doing this for reconstructing the shortest path.

     for(int k=1;k<=n;k++)
     {
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                if((dp[i][k]==1e16) || (dp[k][j]==1e16)) continue;
                if(dp[i][k]+dp[k][j]<dp[i][j])  // Edge Relaxation Condition
                {
                    dp[i][j]=dp[i][k]+dp[k][j];
                    nxt[i][j]=nxt[i][k];
                }
            }
        }
     }
}
void propagateNegCycle()
{
    // propagate negative cycles
    for(int k=1;k<=n;k++)
    {
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                if(dp[i][k]+dp[k][j]<dp[i][j])
                {
                    dp[i][j]=-1e9;
                    nxt[i][j]=-1;
                }
            }
        }
    }
}
void reconstructShortestPath(int from, int to)
{
    if(dp[from][to]==1e16)
    {
        cout<<"There does not exist any path from "<<from<<" to "<<to<<endl;
    }
    else if(dp[from][to]==-1e9)
    {
        cout<<"The path from from "<<from<<" to "<<to<<" is affected by NEGATIVE CYCLE."<<endl;
    }
    else
    {
        vector<int>path;
        for(int i=from;i!=to;i=nxt[i][to])
        {
            path.push_back(i);
        }
        path.push_back(to);
        cout<<"The Path From "<<from<<" to "<<to<<" is below:"<<endl;
        for(int i=0;i<path.size();i++)
        {
            cout<<path[i]<<" ";
        }
        cout<<endl;
    }
}
int main()
{
    ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);

	cin>>n>>edges;

	for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            dp[i][j]=1e16;  // Distance set to Infinity.
            if(i==j)
                dp[i][j]=0; // Considering no self loops.
        }
    }

	for(int i=0;i<edges;i++)
    {
        ll a,b,c;
        cin>>a>>b>>c;
        ll mini=min(c,dp[a][b]);    // If multiple edges are allowed between no nodes, we consider the minimum one.
        dp[a][b]=mini;
    }
    floyd_warshall();
    //propagateNegCycle();    // Running again the FW algorithm, we can detect nodes affected by Negative Cycle.

    cout<<"Shortest Distance Matrix:"<<endl;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(dp[i][j]==1e16)
                cout<<"INF ";
            else if(dp[i][j]==-1e9)
                cout<<"-INF ";
            else
                cout<<dp[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}


