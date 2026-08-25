#include <bits/stdc++.h>
using namespace std;
#define int long long

struct Node
{
    int sum = 0, mn = 1e18;
};

struct segTree
{
#define Left_node (x * 2 + 1)
#define Right_node (x * 2 + 2)
#define MID ((lx + rx) / 2)
private:
    vector<Node> seg;
    int sz;

    void build(vector<int> &arr, int x, int lx, int rx) // O(4*n)
    {
        if (lx == rx)
        {
            seg[x].mn = arr[lx];
            seg[x].sum = arr[lx];
            return;
        }

        build(arr, Left_node, lx, MID);
        build(arr, Right_node, MID + 1, rx);

        seg[x] = mrg(seg[Left_node], seg[Right_node]);
    }

    Node mrg(Node &lf, Node &rt)
    {
        Node res;
        res.mn = min(lf.mn, rt.mn);
        res.sum = lf.sum + rt.sum;
        return res;
    }

    void update(int i, int val, int x, int lx, int rx)
    {
        if (lx == rx)
        {
            seg[x].mn = val;
            seg[x].sum = val;
            return;
        }
        if (i <= MID)
        {
            update(i, val, Left_node, lx, MID);
        }
        else
        {
            update(i, val, Right_node, MID + 1, rx);
        }
        seg[x] = mrg(seg[Left_node], seg[Right_node]);
    }

    Node query(int lq, int rq, int x, int lx, int rx)
    {
        if (rx < lq or rq < lx)
        {
            return {};
        }
        if (lq <= lx and rx <= rq)
        {
            return seg[x];
        }

        Node left_res = query(lq, rq, Left_node, lx, MID);
        Node right_res = query(lq, rq, Right_node, MID + 1, rx);
        return mrg(left_res, right_res);
    }

public:
    void init(vector<int> &arr)
    {
        sz = arr.size();
        seg.assign(4 * sz, {});
        build(arr, 0, 0, sz - 1);
    }
    void update(int i, int val)
    {
        update(i, val, 0, 0, sz - 1);
    }
    Node query(int l, int r)
    {
        return query(l, r, 0, 0, sz - 1);
    }
};
