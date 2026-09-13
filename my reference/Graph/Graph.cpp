// ============================================================
//                  GRAPH REPRESENTATIONS
// ============================================================
//
// 1) ADJACENCY LIST -> DEFAULT
//
// vector<vector<int>> adj(n + 1);
//
// Use for:
//   - DFS / BFS
//   - Most graph problems
//   - Sparse graphs
//
// Memory: O(V + E)
// Traversal: O(V + E)
//
// ------------------------------------------------------------
//
// 2) WEIGHTED ADJACENCY LIST
//
// vector<vector<pair<int,int>>> adj(n + 1);
//
// adj[u].push_back({v, w});
//
// Use for:
//   - Weighted graphs
//   - Dijkstra / 0-1 BFS / Prim
//
// ------------------------------------------------------------
//
// 3) ADJACENCY MATRIX
//
// vector<vector<int>> adj(n + 1, vector<int>(n + 1));
//
// Use when:
//   - V is small
//   - Need to check edge(u,v) in O(1)
//   - Dense graph / Floyd-Warshall
//
// Memory: O(V^2)
//
// ------------------------------------------------------------
//
// 4) EDGE LIST
//
// struct Edge
// {
//     int u, v, w;
// };
//
// vector<Edge> edges;
//
// Use when:
//   - Working with edges directly
//   - Kruskal
//   - Bellman-Ford
//
// ------------------------------------------------------------
//
// 5) GRID
//
// vector<string> grid(n);
//
// Treat each cell as a node.
// Neighbors using dx / dy.
//
// Use for:
//   - Islands
//   - Maze
//   - Flood Fill
//   - Shortest path in grid
//
// ============================================================
// RULE:
//
// Adjacency List = DEFAULT
// Matrix        = Small V + O(1) edge check
// Edge List     = Processing edges
// Grid          = Graph represented as cells
//
// ============================================================
//                  DFS / BFS REFERENCE
// ============================================================
//
// DFS:
//   - Explore as deep as possible.
//   - Reachability / Components / Trees / DP / Cycles
//
// BFS:
//   - Explore level by level.
//   - Shortest path in unweighted graphs
//
// Graph:
//   Undirected:
//       adj[u].push_back(v);
//       adj[v].push_back(u);
//
//   Directed:
//       adj[u].push_back(v);
//
// Complexity:
//   DFS / BFS -> O(V + E)
//
// ============================================================
// QUICK PATTERNS
// ============================================================
//
// Components       -> DFS / BFS
// Grid / Islands   -> DFS / BFS
// Reachability     -> DFS / BFS
// Shortest path    -> BFS (unweighted)
// Path              -> BFS + parent
// Tree / Subtree   -> DFS
// Bipartite        -> DFS/BFS + 2-coloring
// Undirected Cycle -> DFS + parent
// Directed Cycle   -> DFS + 3 states
// Dependencies     -> Topological Sort
//
// ============================================================


#include <bits/stdc++.h>
using namespace std;

#define ll long long

vector<vector<int>> adj;
vector<bool> vis;


// ======================== DFS ===============================

void dfs(int u)
{
    vis[u] = true;

    // process u

    for (int v : adj[u])
    {
        if (vis[v]) continue;

        dfs(v);
    }

    // process u after children if needed
}


// ======================== BFS ===============================

void bfs(int start)
{
    queue<int> q;

    vis[start] = true;
    q.push(start);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        // process u

        for (int v : adj[u])
        {
            if (vis[v]) continue;

            vis[v] = true;
            q.push(v);
        }
    }
}


// ================= BFS Shortest Path =======================
//
// Works for unweighted / equal-weight edges.
//
// dist[v] = shortest number of edges from start.

vector<int> dist, parent;

void bfsShortest(int start, int n)
{
    dist.assign(n + 1, -1);
    parent.assign(n + 1, -1);

    queue<int> q;

    dist[start] = 0;
    q.push(start);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v : adj[u])
        {
            if (dist[v] != -1) continue;

            dist[v] = dist[u] + 1;
            parent[v] = u;

            q.push(v);
        }
    }
}


// Recover path:
// for (int cur = target; cur != -1; cur = parent[cur])
//     path.push_back(cur);
// reverse(path.begin(), path.end());


// ===================== Tree DFS =============================

void treeDFS(int u, int p)
{
    // process u

    for (int v : adj[u])
    {
        if (v == p) continue;

        treeDFS(v, u);

        // process child after DFS if needed
    }
}


// ==================== Subtree Size ==========================

vector<int> sub;

void dfsSubtree(int u, int p)
{
    sub[u] = 1;

    for (int v : adj[u])
    {
        if (v == p) continue;

        dfsSubtree(v, u);

        sub[u] += sub[v];
    }
}


// ====================== Bipartite ===========================

vector<int> color;

bool dfsBipartite(int u, int c)
{
    color[u] = c;

    for (int v : adj[u])
    {
        if (color[v] == -1)
        {
            if (!dfsBipartite(v, c ^ 1))
                return false;
        }
        else if (color[v] == color[u])
            return false;
    }
    return true;
}


// ================= Undirected Cycle =========================

bool dfsCycle(int u, int p)
{
    vis[u] = true;

    for (int v : adj[u])
    {
        if (!vis[v])
        {
            if (dfsCycle(v, u))
                return true;
        }
        else if (v != p)
            return true;
    }

    return false;
}


// ================== Directed Cycle ==========================
//
// state:
// 0 = unvisited
// 1 = currently in recursion stack
// 2 = finished

vector<int> state;

bool dfsCycleDirected(int u)
{
    state[u] = 1;

    for (int v : adj[u])
    {
        if (state[v] == 1)
            return true;

        if (state[v] == 0 && dfsCycleDirected(v))
            return true;
    }

    state[u] = 2;
    return false;
}


// ================== Topological Sort ========================
//
// DFS:
//   push after children, then reverse.
//
// Kahn:
//   Start with indegree = 0 nodes.

vector<int> topo;

void dfsTopo(int u)
{
    vis[u] = true;

    for (int v : adj[u])
        if (!vis[v])
            dfsTopo(v);

    topo.push_back(u);
}
// After:
// reverse(topo.begin(), topo.end());

// ======================== GRID ===============================
// Grid = Graph
// 4 directions:
//   dx = {1,-1,0,0}
//   dy = {0,0,1,-1}
//
// 8 directions:
//   dx = {1,1,1,-1,-1,-1,0,0}
//   dy = {1,-1,0,1,-1,0,1,-1}

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
// ============================================================