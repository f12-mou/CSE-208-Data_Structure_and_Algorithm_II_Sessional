#include<bits/stdc++.h>
using namespace std;
const int N=25;
vector<int>adj[N];
int dx[4]={0,1,1};
int dy[4]={1,1,0};

int dx2[4]={-1,-1,0};
int dy2[4]={0,-1,-1};
int found=0;
int grid[4][4];
int vis[4][4];

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        string s1,s2,s3;
        int cnt_unders=0;
        int cnt_first[4]={0,0};
        int cnt_sec[4]={0,0};
        cin>>s1>>s2>>s3;
        for(int i=0;i<3;i++)
        {
            if(s1[i]=='X')
            {
                grid[1][i+1]=1;
            }
            else if(s1[i]=='O')
            {
                grid[1][i+1]=2;
            }
            else
                {grid[1][i+1]=0;cnt_unders++;}
        }
        for(int i=0;i<3;i++)
        {
            if(s2[i]=='X')
            {
                grid[2][i+1]=1;
            }
            else if(s2[i]=='O')
            {
                grid[2][i+1]=2;
            }
            else
                grid[2][i+1]=0;
        }
        for(int i=0;i<3;i++)
        {
            if(s3[i]=='X')
            {
                grid[3][i+1]=1;
            }
            else if(s3[i]=='O')
            {
                grid[3][i+1]=2;
            }
            else
                grid[3][i+1]=0;
        }
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                cout<<grid[i+1][j+1]<<" ";
            }
            cout<<endl;
        }
        queue<pair<int,pair<int,int>>>q;
        vis[1][1]=1;
        q.push(make_pair(1,make_pair(1,1)));
        while(!q.empty())
        {
            pair<int,pair<int,int>>p=q.front();
            q.pop();
            int cnt=p.first;
            int row=p.second.first;
            int col=p.second.second;
            cout<<row<<" "<<col<<endl;
            vis[row][col]=1;
            if(cnt>=3) found++;
            for(int i=0;i<3;i++)
            {
                int r2=row+dx[i];
                int c2=col+dy[i];
                if(r2>3 || c2>3) continue;
                if(vis[r2][c2]==1) continue;
                if(grid[r2][c2]==grid[row][col])
                {
                    q.push(make_pair(cnt+1,make_pair(r2,c2)));
                }
            }
        }
        for(int i=0;i<4;i++) for(int j=0;j<4;j++)
       vis[i][j]=0;

       vis[3][3]=1;
        q.push(make_pair(1,make_pair(3,3)));
        while(!q.empty())
        {
            pair<int,pair<int,int>>p=q.front();
            q.pop();
            int cnt=p.first;
            int row=p.second.first;
            int col=p.second.second;
            vis[row][col]=1;
            if(cnt>=3) found++;
            for(int i=0;i<3;i++)
            {
                int r2=row+dx2[i];
                int c2=col+dy2[i];
                if(r2<1 || c2<1) continue;
                if(vis[r2][c2]==1) continue;

                if(grid[r2][c2]==grid[row][col])
                {
                    q.push(make_pair(cnt+1,make_pair(r2,c2)));
                }
            }
        }
        for(int i=1;i<=3;i++)
        {
            cnt_first[grid[i][2]]++;
            if(cnt_first[grid[i][2]]==3) found++;
        }
        for(int i=1;i<=3;i++)
        {
            cnt_sec[grid[2][i]]++;
            if(cnt_sec[grid[2][i]]==3) found++;
        }
        if(found==0 && cnt_unders>0)
        {
            cout<<2<<endl;

        }
        else if((found==1 || found==0) && cnt_unders==0)
        {
            cout<<1<<endl;
        }
        else if(found>1)
        {
            cout<<3<<endl;
        }
        else
        {
            cout<<3<<endl;
        }


    }
}
/*
Sample Input
3
XOX
XXO
O_O
XXX
OOO
___
XOX
OX_
XO_
*/
