#include<bits/stdc++.h>
using namespace std;
#define ll long long

const int N=105;

int n,m;
ll W[N][N]; // Weight Matrix
ll L[N][N]; // L is an intermediate matrix
ll D[N][N]; // Distance Matrix.

void extend_shortest_path()
{
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            L[i][j]=1e16;
            for(int k=1;k<=n;k++)
            {
                L[i][j]=min(L[i][j], D[i][k]+W[k][j]);
            }
        }
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            D[i][j]=L[i][j];
}

void matrix_multi()
{
    int cnt=2;
    while(cnt<=n-1)
    {
        extend_shortest_path();
        cnt++;
    }
}
int main()
{
    for(int i=1;i<N;i++)
    {
        for(int j=1;j<N;j++)
        {
            D[i][j]=W[i][j]=1e16;
            if(i==j)
                D[i][j]=W[i][j]=0;
        }
    }
    cin>>n>>m;
    ll source,destination,weight;
    for(int i=1;i<=m;i++)
    {
        cin>>source>>destination>>weight;
        ll mini=min(weight, D[source][destination]);
        D[source][destination]=W[source][destination]=mini;
    }
    matrix_multi();
    cout<<"Shortest Distance Matrix:"<<endl;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(D[i][j]==1e16) cout<<"INF ";
            else cout<<D[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}



