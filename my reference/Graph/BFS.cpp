#include <bits/stdc++.h>
#define ll long long
using namespace std;
//////////////////////////////////////////////////////
vector<vector<int>> adj;
vector<bool> vis;
int n;
auto BFS = [&](int src)
{
    queue<int> q;
    vector<bool> visited(n);
    visited[src] = true;
    q.push(src);
    while (not q.empty())
    {
        int u = q.front();
        q.pop();
        for (int v : adj[u])
        {
            if (!visited[v])
            {
                visited[v] = true;
                q.emplace(v);
            }
        }
    }
};
   auto BFS_Tree = [&](int src){
      queue<pair<int,int>>q;
      q.emplace(src,-1);
      int lvl = 0;
      while(q.size())
      {
         int sz = q.size();
         while (sz--)
         {
            auto [u,par] = q.front();
            q.pop();
            for(int v:adj[u])
            {
               if(v == par)continue;
               q.emplace(v,u);
            }
         }
         lvl++;
      }
};