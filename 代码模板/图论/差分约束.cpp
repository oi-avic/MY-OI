#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
using namespace std;
vector<pair<int,int>>e[10005];
int dis[10005],bj[10005],cnt[10005];
int n,m;
bool SPFA(int st)
{
	memset(dis,0x3f3f3f3f,(n+3)*sizeof(dis[0]));
	memset(bj,0,(n+3)*sizeof(bj[0]));
	memset(cnt,0,(n+3)*sizeof(cnt[0]));
	dis[st]=0;
	queue<int>q;
	q.push(st);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		bj[u]=0;
		for(auto i:e[u])
		{
			int v=i.first,w=i.second;
			if(dis[v]>dis[u]+w)
			{
				dis[v]=dis[u]+w;
				cnt[v]=cnt[u]+1;
				if(cnt[v]>n+1)
				{
					return false;
				}
				if(bj[v]==0)
				{
					q.push(v);
					bj[v]=1;
				}
			}
		}
	}
	return true;
}
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	int op,a,b,c;
	cin>>n>>m;
	for(int i=1;i<=n;++i)
	{
		e[0].push_back({i,0});
	}
	for(int i=1;i<=m;++i)
	{
		cin>>op;
		if(op==1)
		{
			cin>>a>>b>>c;
			e[a].push_back({b,-c});
		}
		else if(op==2)
		{
			cin>>a>>b>>c;
			e[b].push_back({a,c});
		}
		else
		{
			cin>>a>>b;
			e[a].push_back({b,0});
			e[b].push_back({a,0});
		}
	}
	if(!SPFA(0))
	{
		cout<<"No";
	}
	else
	{
		cout<<"Yes";
	}
	return 0;
}
