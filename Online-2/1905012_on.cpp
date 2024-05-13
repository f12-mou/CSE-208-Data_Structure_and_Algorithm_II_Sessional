
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
vector<pair<int,int>>del;

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
bool vis[N];
void dfs(int node,int a,int b)
{
    if(vis[node]==true) return;
    vis[node]=true;
    for(int i=0;i<adj[node].size();i++)
    {
        pair<int,double>p=adj[node][i];
        int next=p.first;
        //cout<<next<<endl;
        int flag=1;
        for(int i=0;i<del.size();i++)
        {
            int frst=del[i].first;
            int sec=del[i].second;
            if((next==frst && node==sec ) ||(next==sec && node==frst))
            {
                flag=0;break;
            }
        }
        if((next==a && node==b) ||(next==b && node==a))
            flag=0;
        if(flag==0) continue;
        else
            dfs(next,a,b);
    }

}
bool isConnected(int a, int b)
{
    for(int i=0;i<=n;i++) vis[i]=false;
    dfs(0,a,b);
    int flag=1;
    for(int i=0;i<n;i++)
    {
        if(vis[i]==false)
        {
            flag=0;break;
        }
    }
    if(flag==1) return true;
    else
        return false;
}

double kruskal()
{
    //cout<<"in kruskal "<<" "<<vec.size()<<endl;
    for(int i=0;i<n;i++){link[i]=i;len[i]=1;}
    sort(vec.rbegin(),vec.rend());
    double sum=0;
	for(int i=0;i<vec.size();i++)
    {
        pair<double,pair<int,int>>p=vec[i];
        int cost=p.first;
        int a=p.second.first;
        int b=p.second.second;
        if(isConnected(a,b)==true){del.push_back(make_pair(a,b));}
        else
       {
           cout<<sum<<endl;
           sum+=cost;
        kruskal_ans_vec.push_back(make_pair(a,b));
       }
    }
    return sum;
 }



int main()
{
    ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	//freopen("mst.txt","r",stdin);
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

    return 0;
}

