#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define ld long double
#define null_string string::npos
#define all(X) X.begin(), X.end()
#define allr(X) X.rbegin(), X.rend()
using namespace std;
const int oo = 0x3f3f3f3f;
const int MOD = 1e9 + 7;
//////////////////////////////////////////////////////////////////////////////

void solution()
{
    ll n;cin>>n;
    vector<ll>v(n);
    for (int i = 0; i < n; i++)
    {
        cin>>v[i];
    }
    ld temp1=0;
    for (int i = 0; i < n; i++)
    {
        temp1+=(log(v[i]));
    }
    ld ans = floor(exp(temp1/n));
    ans++;
    cout<<ans<<'\n';
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    // freopen("moocast.in", "r", stdin);
    // freopen("moocast.out", "w", stdout);
    int test = 1;
    // cin >> test;
    while (test--)
        solution();
}