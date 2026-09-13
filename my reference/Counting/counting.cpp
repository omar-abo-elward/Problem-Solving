#include <bits/stdc++.h>
#define ll long long
using namespace std;

// ============================================================
//                 COUNTING & COMBINATORICS
// ============================================================
//
// Addition Principle:
//   If cases are disjoint:
//       Answer = case1 + case2 + ...
//
// Multiplication Principle:
//   If choices are independent:
//       Answer = choices1 * choices2 * ...
//
// Permutation:
//   Order matters.
//       P(n,r) = n! / (n-r)!
//
// Combination:
//   Order does NOT matter.
//       C(n,r) = n! / (r! * (n-r)!)
//
// Important identities:
//   C(n,r) = C(n,n-r)
//   C(n,r) = C(n-1,r-1) + C(n-1,r)
//
// Repetition:
//   Ordered + repetition allowed:
//       n^r
//
//   Unordered + repetition allowed (Stars and Bars):
//       C(n+r-1, r)
//       For x1 + x2 + ... + xk = n, xi >= 0:
//           C(n+k-1, k-1)
//
//   For xi > 0:
//       C(n-1, k-1)
//
// Complement Counting:
//   "At least one" -> often easier as:
//       Total - None
//
// Inclusion-Exclusion:
//   |A ∪ B| = |A| + |B| - |A ∩ B|
//
//   Pattern:
//       + singles - pairs + triples - ...
//
// ============================================================
//                  MODULAR COMBINATORICS
// ============================================================
// Precompute:
//   fac[i]  = i!
//   finv[i] = (i!)^(-1)
//
// Then:
//   C(n,r) = fac[n] * finv[r] * finv[n-r]
//   P(n,r) = fac[n] * finv[n-r]
//
// Complexity:
//   init : O(n)
//   nCr  : O(1)
//   nPr  : O(1)
//   power: O(log MOD)
//
// ============================================================

ll MOD = 1e9 + 7;

vector<ll> fac, inv, finv;


// ------------------------------------------------------------
// nCr = Combination
// Choose r objects from n objects.
// Order does NOT matter.
//
// Valid when:
//   0 <= r <= n
//   n <= precomputed size
// ------------------------------------------------------------
ll nCr(ll n, ll r)
{
    if (n < 0 || r > n || r < 0)
        return 0;

    return fac[n] * finv[r] % MOD * finv[n - r] % MOD;
}


// ------------------------------------------------------------
// nPr = Permutation
// Choose r objects from n objects.
// Order MATTERS.
//
// P(n,r) = n! / (n-r)!
// ------------------------------------------------------------
ll nPr(ll n, ll r)
{
    if (n < 0 || r > n || r < 0)
        return 0;

    return fac[n] * finv[n - r] % MOD;
}
// ------------------------------------------------------------
// Binary Exponentiation
// Complexity:
//   O(log n)
// ------------------------------------------------------------
ll power(ll b, ll n)
{
    b %= MOD;

    ll s = 1;

    while (n)
    {
        if (n % 2 == 1)
            s = s * b % MOD;

        b = b * b % MOD;
        n /= 2;
    }

    return s;
}
// ------------------------------------------------------------
// Precompute factorials and inverse factorials.
//
// fac[i]  = i!
// inv[i]  = modular inverse of i
// finv[i] = inverse of i!
//
// Complexity:
//   O(n)
//
// IMPORTANT:
//   This inverse formula requires MOD to be prime
//   and MOD > n.
// ------------------------------------------------------------
void init(int n, ll mod)
{
    MOD = mod;

    fac.resize(n + 1);
    inv.resize(n + 1);
    finv.resize(n + 1);

    fac[0] = 1;
    inv[0] = 1;
    inv[1] = 1;
    finv[0] = 1;
    finv[1] = 1;

    // factorials
    for (ll i = 1; i <= n; ++i)
        fac[i] = fac[i - 1] * i % MOD;

    // modular inverses
    // inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD
    for (ll i = 2; i <= n; ++i)
        inv[i] = MOD - MOD / i * inv[MOD % i] % MOD;

    // inverse factorials
    for (ll i = 2; i <= n; ++i)
        finv[i] = finv[i - 1] * inv[i] % MOD;
}
// -----------------------------------------------------------
ll mul(ll a, ll b)
{
    return ((a % MOD) * (b % MOD)) % MOD;
}
ll add(ll a, ll b)
{
    return ((a % MOD) + (b % MOD)) % MOD;
}
ll sub(ll a, ll b)
{
    return (((a - b) % MOD) + MOD) % MOD;
}
// ------------------------------------------------------------
// Modular Division
// Requires:
//   MOD is prime
//   b is NOT divisible by MOD
// ------------------------------------------------------------
ll divide(ll a, ll b)
{
    return mul(a, power(b, MOD - 2));
}
// ------------------------------------------------------------
// Modular Inverse
// Requires prime MOD and x % MOD != 0.
// ------------------------------------------------------------
ll Inv(int x)
{
    return power(x, MOD - 2);
}
// ------------------------------------------------------------
// Catalan Number
//
// C_n = C(2n,n) / (n+1)
//
// First values:
//   1, 1, 2, 5, 14, 42, ...
//
// Requires:
//   2*n <= precomputed limit
//   MOD is prime
//   n+1 is invertible modulo MOD
// ------------------------------------------------------------
ll catalan(int n)
{
    return nCr(2 * n, n) * Inv(n + 1) % MOD;
}
// ------------------------------------------------------------
// Stars and Bars
//
// Number of non-negative integer solutions:
//
//   x1 + x2 + ... + xk = n
//   xi >= 0
//
// Answer:
//   C(n+k-1, k-1)
//
// Example:
//   x1 + x2 + x3 = 5
//   -> C(7,2)
//
// IMPORTANT:
//   This version is for xi >= 0.
// ------------------------------------------------------------
ll StarsAndBars(ll n, ll k)
{
    if (n < 0 || k <= 0)
        return 0;

    return nCr(n + k - 1, k - 1);
}