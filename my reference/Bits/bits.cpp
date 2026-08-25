// Turn on bit(x)
a = a | (1 << x);
// Turn off bit(x)
a = a & (~(1 << x));
// Flip bit
a = a ^ (1 << x);
// Check bit
((a >> x) & 1);
// Check Power of Two
if (res > 0 and !(res & (res - 1)))
    cout << "YES" << endl;
else
    cout << "NO" << endl;
// ones
__builtin_popcount(a);
// zeros
32 - __builtin_popcount(a);
// number of trailing zeros (RIGHT side)
__builtin_ctz(a);
// number of leading zeros (LEFT side)
__builtin_clz(a);
// index of highest set bit (0-based)
__lg(a);