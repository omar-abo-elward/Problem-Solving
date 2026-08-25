#include <bits/stdc++.h>
#define ll long long
using namespace std;
//////////////////////////////////////////////////////
vector<vector<int>> adj;
vector<bool> vis;
void dfs(int u)
{
   vis[u] = true;
   for (int v : adj[u])
   {
        if (not vis[v])dfs(v);
   }
}
void dfsTree(int u, int parent)
{
   for (auto v : adj[u])
   {
      if (v != parent)dfsTree(v, u);
   }
}
int main()
{
    int n, m;
    // adj matrix
    vector<vector<int>> adj(n + 1, vector<int>(n + 1, -1));
    for (int i = 1, u, v, w; i <= m; i++)
    {
        cin >> u >> v >> w;
        adj[u][v] = w;
        adj[v][u] = w;
    }

    // adj list
    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 1, u, v, w; i <= m; i++)
    {
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    // edge list
    vector<array<int, 3>> edgeList(m);
    for (auto &[u, v, w] : edgeList)
    {
        cin >> u >> v >> w;
    }
}