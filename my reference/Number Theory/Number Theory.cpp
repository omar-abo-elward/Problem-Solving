#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll modpower(ll x, ll n, ll m)
{
   if (n == 0)
      return 1 % m;
   ll u = modpower(x, n / 2, m);
   u = (u * u) % m;
   if (n % 2 != 0)
      u = (u * x) % m;
   return u;
}
// Fermat: works only if mod is prime and gcd(n,mod)=1
ll modInverseFermat(ll n, ll mod) { return modpower(n, mod - 2, mod); }
//   inversemod_2
ll extendedGCD(ll a, ll b, ll &x, ll &y)
{
   if (b == 0)
   {
         x = 1;
         y = 0;
         return a;
   }
   ll x1, y1;
   ll g = extendedGCD(b, a % b, x1, y1);
   x = y1;
   y = x1 - (a / b) * y1;
   return g;
}
// Works if gcd(a,m)=1 (mod not necessarily prime)
ll modInverseEGCD(ll a, ll m)
{
   ll x, y;
   ll g = extendedGCD(a, m, x, y);
   if (g != 1)return -1;
   x = (x % m + m) % m;
   return x;
}

int primes[100001];
void sieveOfEratosthenes(int N)
{

   N += 2;
   primes[1] = 1;
   for (int i = 2; i < N; i++)
      primes[i] = i;
   for (int i = 4; i < N; i += 2)
      primes[i] = 2;
   for (int i = 3; i * i < N; i++)
   {
      if (primes[i] == i)
      {
         for (int j = i * i; j < N; j += i)
            if (primes[j] == j)
               primes[j] = i;
      }
   }
}
vector<ll> findPrimeFactors(int num)
{

   sieveOfEratosthenes(num);
   vector<ll> factors;
   while (num != 1)
   {
      factors.push_back(primes[num]);
      num /= primes[num];
   }
   return factors;
}
vector<ll> getDivisors(ll n)
{
   vector<ll> d;
   for (ll i = 1; i * i <= n; i++)
   {
      if (n % i == 0)
      {
         d.push_back(i);
         if (i != n / i)
            d.push_back(n / i);
      }
   }
   return d;
}