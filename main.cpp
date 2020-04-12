/*
same solution as in ur tutorial
*/
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,m,o;
long long a[N],sz[N],ans[N];
vector <pair<int,int> > v[N];
queue<int> q;
bool vis[N];
long long sum (int x)
{
    vis[x]=true;
    long long here=0;
    bool yes=false;
    for (int i=0;i<v[x].size();i++)
    {
        if (!vis[v[x][i].first])
        {
            yes=true;
            here=sum(v[x][i].first);
            break;
        }
    }
    vis[x]=false;
    return here+a[x];
}
long long dfs1 (int x,long long last)
{
    vis[x]=true;
    bool yes=false;
    long long here=0;
    for (int i=0;i<v[x].size();i++)
    {
        if (!vis[v[x][i].first])
        {
            here=dfs1(v[x][i].first,a[v[x][i].first]-last);
            yes=true;
            break;
        }
    }
    vis[x]=false;
    return here+last;
}
void dfs2 (int x)
{
    vis[x]=true;
    bool yes=false;
    for (int i=0;i<v[x].size();i++)
    {
        if (!vis[v[x][i].first])
        {
            a[v[x][i].first]-=a[x];
            ans[v[x][i].second]=a[x];
            dfs2(v[x][i].first);
            yes=true;
            break;
        }
    }
    if (!yes)
    {
        for (int i=0;i<v[x].size();i++)
        {
            if (v[x][i].first==o)
            {
                ans[v[x][i].second]=a[x];
                break;
            }
        }
    }
    vis[x]=false;
}
int main()
{
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++)
    {
        scanf("%lld",&a[i]);
    }
    for (int i=0;i<m;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        v[a].push_back({b,i});
        v[b].push_back({a,i});
    }
    if (m>n)
    {
        cout <<0;
        return 0;
    }
    for (int i=1;i<=n;i++)
    {
        sz[i]=v[i].size();
        if (v[i].size()==1)
        {
            q.push(i);
        }
    }
    int cnt=n;
    while (!q.empty())
    {
        int x= q.front();
        q.pop();
        cnt--;
        vis[x]=true;
        for (int i=0;i<v[x].size();i++)
        {
            int nxt=v[x][i].first;
            int idx=v[x][i].second;
            if (!vis[nxt])
            {
                ans[idx]=a[x];
                a[nxt]-=a[x];
                sz[nxt]--;
                if (sz[nxt]==1)
                    q.push(nxt);
            }
        }
    }
    if (cnt%2==0&&cnt)
    {
        cout <<0;
        return 0;
    }
    for (int i=1;i<=n;i++)
    {
        if (!vis[i])
        {
            o=i;
            long long x=sum(i);
            x/=2;
            long long y=dfs1(i,0);
            a[i]= x-y;
            dfs2(i);
            break;
        }
    }
    for (int i=0;i<m;i++)
        printf("%lld\n",ans[i]*2ll);
    return 0;
}
/*
4 3
-1
1
-3
1
1 2
1 3
1 4

4 5
1
2
1
2
1 2
2 3
3 4
4 1
1 3

3 3
1
15
-4
1 2
2 3
3 1
*/
