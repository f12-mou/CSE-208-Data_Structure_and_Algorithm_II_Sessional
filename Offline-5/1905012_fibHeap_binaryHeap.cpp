#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N = 100005;

vector<pair<ll,ll>>adj[N];  // Adjacency List for each node
ll dist[N];                 // Distance array
bool vis[N];                // Marking to be visited or unvisited
int parent[N];              // For constructing the path from source to destination
int n,m;                     // Number of nodes, number of edges
int source, destination;     // Source Node, Destination node
clock_t time1, time2, time3, time4;

int k;
ll destination_distance1, destination_distance2;



template<typename E>
class node
{
public:
    ll idx;
    E key;
    ll degree;
    ll color; // color means mark
    node<E>* left;
    node<E>* right;
    node<E>* parent;
    node<E>* child;
    node(ll id)
    {
        idx=id;
    }

};

template<typename E>
class fHeap
{
public:
    node<E>* mini;
    node<E>* p[100005];
    ll allocaedNodes;
    ll nodeCount;

    fHeap(ll cnt)
    {
        allocaedNodes=cnt;
        nodeCount=0;
        mini=NULL;
        for(ll i=0;i<=allocaedNodes;i++)
           {
               p[i]=new node<E>(i);
           }
    }
    ~fHeap()
    {
        for(ll i=0;i<=allocaedNodes;i++)
            delete p[i];
    }
    void insert(pair<E,int> d)
    {
        E val=d.first;
        ll idx=d.second;
        node<E>* x=p[idx];

        x->key = val;
        x->degree=0;
        x->color=0;
        x->left=x;
        x->right=x;
        x->parent=NULL;
        x->child=NULL;

        if(mini!=NULL)
        {
            (mini->left)->right=x;
            x->right=mini;
            x->left=mini->left;
            mini->left=x;
            if(x->key<mini->key)
                mini=x;
        }
        else
        {
            mini=x;
        }
        nodeCount++;
    }

    void Fibonnaci_link( node<E>* y,node<E>* x )
    {
        (y->left)->right = y->right;
        y->right->left = y->left;
        if (x->right == x)
            mini = x;
        y->left = y;
        y->right = y;
        y->parent = x;
        if (x->child == NULL)
            x->child = y;
        y->right = x->child;
        y->left = (x->child)->left;
        ((x->child)->left)->right = y;
        (x->child)->left = y;
        if (y->key < (x->child)->key)
            x->child = y;
        x->degree++;
        y->color=0;
    }

    void Cut(node<E>* x, node<E>* y)
    {
        if (x == x->right)
            y->child = NULL;

        (x->left)->right = x->right;
        (x->right)->left = x->left;
        if (x == y->child)
            y->child = x->right;

        y->degree = y->degree - 1;
        x->right = x;
        x->left = x;
        (mini->left)->right = x;
        x->right = mini;
        x->left = mini->left;
        mini->left = x;
        x->parent = NULL;
        y->color=1;
    }
    void cascaded_cut(node<E>* y)
    {
        node<E>* z=y->parent;
        if(z!=NULL)
        {
            if(y->color==0)
                y->color=1;
            else
            {
                Cut(y,z);
                cascaded_cut(z);
            }
        }
    }
    void decrease_key(int idx,E val)
    {
        node<E>* x=p[idx];
        if(val>x->key)
        {
            return;
        }
        x->key=val;
        node<E>* y=x->parent;
        if(y!=NULL && x->key<y->key)
        {
            Cut(x,y);
            cascaded_cut(y);
        }
        if(x->key < mini->key)
        {
            mini=x;
        }
    }
    bool empty()
    {
        return nodeCount==0;
    }
    void deleteNode(int idx)
    {
        node<E>* x= p[idx];
        if(x->parent==NULL)
        {
            mini=x;
            extract_min();
        }
        else
        {
            Cut(x, x->parent);
            mini=x;
            extract_min();
        }
    }

    void Consolidate()
    {
        ll temp1;
        float temp2 = (log(nodeCount)/(log(2)));
        ll temp3 = temp2+1;
        node<E>* arr[temp3+1];
        for (ll i = 0; i <= temp3; i++)
            arr[i] = NULL;
        node<E>* ptr1 = mini;
        node<E>* ptr2;
        node<E>* ptr3;
        node<E>* ptr4 = ptr1;
        map<int,int>mp;
        do  {
            ptr4 = ptr1->right;
            temp1 = ptr1->degree;
            if(mp[ptr1->idx]==0)
                mp[ptr1->idx]=1;
            else
                break;
            while (arr[temp1] != NULL) {
                ptr2 = arr[temp1];
                if (ptr1->key > ptr2->key) {
                    ptr3 = ptr1;
                    ptr1 = ptr2;
                    ptr2 = ptr3;
            }
            if (ptr2 == mini)
               mini = ptr1;
            Fibonnaci_link(ptr2, ptr1);
            if (ptr1->right == ptr1)
                mini = ptr1;
            arr[temp1] = NULL;
            temp1++;
        }
        arr[temp1] = ptr1;
        ptr1 = ptr4;
    } while (ptr1 != mini);

    mini = NULL;
    for (ll j = 0; j <= temp3; j++) {
        if (arr[j] != NULL) {
            arr[j]->left = arr[j];
            arr[j]->right = arr[j];
            if (mini != NULL) {
                (mini->left)->right = arr[j];
                arr[j]->right = mini;
                arr[j]->left = mini->left;
                mini->left = arr[j];
                if (arr[j]->key < mini->key)
                    mini = arr[j];
            }
            else {
                mini = arr[j];
            }
            if (mini == NULL)
                mini = arr[j];
            else if (arr[j]->key < mini->key)
                mini = arr[j];
        }
    }
}

        pair<E,int> extract_min()
        {
            node<E>* temp=mini;
            node<E>* pntr;
            pntr=temp;
            node<E>* x=NULL;
            if(temp->child!=NULL)
            {
                x=temp->child;
                do{
                    pntr=x->right;
                    (mini->left)->right=x;
                    x->right=mini;
                    x->left=mini->left;
                    mini->left=x;
                    if(x->key<mini->key)
                        mini=x;
                    x->parent=NULL;
                    x=pntr;
                } while(pntr!=temp->child);
            }
            (temp->left)->right=temp->right;
            temp->right->left=temp->left;
            mini=temp->right;
            if(temp==temp->right && temp->child==NULL)
              {
                  mini=NULL;
              }
            else
            {
                mini=temp->right;
                Consolidate();
            }
            nodeCount--;
            pair<ll,ll>ppp=make_pair(temp->key, temp->idx);
            return ppp;
        }

};


void Dijkstra()
{
    time1=clock();
    for(int i=0;i<n;i++)
    {
        dist[i]=1e18;        // Initialization with positive infinity
        vis[i]=false;           // Marked visited false
        parent[i]=-1;           // Parent to be null
    }
    priority_queue<pair<ll,ll>>pq;      // -1 * cost  and then to vertex
    dist[source]=0;
    vis[source]=true;
    pq.push(make_pair(-1*0,source));

    while(pq.empty()==false)
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
    time2=clock();
}



void Dijkstra_fib_heap()
{
    time3=clock();
    for(ll i=0;i<n;i++)
    {
        dist[i]=1e18;
        vis[i]=false;
    }
    fHeap<ll> pq(n+3);
    for(ll i=0;i<n;i++)
        {
            if(i!=source)
            pq.insert(make_pair(1e18,i));
        }
    dist[source]=0;
    vis[source]=true;
    pq.insert(make_pair(0,source));
    while(!pq.empty())
    {
        pair<ll,ll>p=pq.extract_min();
        ll from=p.second;
        ll cost_now=p.first;
        vis[from]=true;
        if(cost_now>dist[from])
            continue;
        for(auto pp:adj[from])
        {
            ll edge_cost=pp.second;
            ll to=pp.first;
            if(vis[to]==true) continue;
            if(vis[to]==false && dist[from]+edge_cost<dist[to])
            {
                dist[to]=dist[from]+edge_cost;
                pq.decrease_key(to, dist[to]);

            }
        }
    }
    time4=clock();
}

int main()
{
    ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
    freopen("graph_info.txt", "r", stdin);
	cin>>n>>m;
	ll c,d,cost;

	for(ll i=1;i<=m;i++)
    {
        cin>>c>>d>>cost;
        adj[c].push_back(make_pair(d,cost));
        adj[d].push_back(make_pair(c,cost));
    }
    freopen("source_dest_info.txt", "r", stdin);
    cin>>k;
    for(int i=1;i<=k;i++)
    {
        cin>>source>>destination;
        Dijkstra_fib_heap();
        destination_distance1=dist[destination];
        Dijkstra();
        destination_distance2=dist[destination];
        stack<int>path;
        path.push(destination);
        if(parent[destination]!=-1){
            while(destination!=source)
            {
                destination=parent[destination];
                path.push(destination);
            }
        }

        cout<<path.size()-1<<" "<<destination_distance2<<" "<<destination_distance1<<" ";
        cout<<double((time2 - time1) / double((CLOCKS_PER_SEC)))<<" s in binary heap ";
        cout<<double((time4 - time3) / double((CLOCKS_PER_SEC)))<<" s in fib heap "<<endl;

    }
    return 0;
}
