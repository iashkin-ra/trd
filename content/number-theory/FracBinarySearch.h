/**
 * Author: Lucian Bicsi, Simon Lindholm
 * Date: 2017-10-31
 * License: CC0
 * Description: Given $f$ and $N$, finds the smallest fraction $p/q \in [0, 1]$
 * such that $f(p/q)$ is true, and $p, q \le N$.
 * You may want to throw an exception from $f$ if it finds an exact solution,
 * in which case $N$ can be removed.
 * Also a second code by Anton
 * Usage: fracBS([](Frac f) { return f.p>=3*f.q; }, 10); // {1,3}
 * Time: O(\log(N))
 * Status: stress-tested for n <= 300
 */

struct Frac { ll p, q; };

template<class F>
Frac fracBS(F f, ll N) {
	bool dir = 1, A = 1, B = 1;
	Frac lo{0, 1}, hi{1, 1}; // Set hi to 1/0 to search (0, N]
	if (f(lo)) return lo;
	assert(f(hi));
	while (A || B) {
		ll adv = 0, step = 1; // move hi if dir, else lo
		for (int si = 0; step; (step *= 2) >>= si) {
			adv += step;
			Frac mid{lo.p * adv + hi.p, lo.q * adv + hi.q};
			if (abs(mid.p) > N || mid.q > N || dir == !f(mid)) {
				adv -= step; si = 2;
			}
		}
		hi.p += lo.p * adv;
		hi.q += lo.q * adv;
		dir = !dir;
		swap(lo, hi);
		A = B; B = !!adv;
	}
	return dir ? hi : lo;
}

template <class Pred>
pair<ll, ll> rational_bs(ll n, Pred f) {
    ll a = 0, b = 1; // always false
    ll c = 1, d = 0; // always true
    while (a + c <= n && b + d <= n) {
        bool dir = f(a + c, b + d);
        ll low = 1, high = n, step = 0;
        if (dir) {
            if (a > 0) high = min(high, (n - c) / a);
            if (b > 0) high = min(high, (n - d) / b);
            while (low <= high) {
                ll mid = low + (high - low) / 2;
                if (f(c + mid * a, d + mid * b)) {
                    step = mid;
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
            c += step * a;
            d += step * b;
        } else {
            if (c > 0) high = min(high, (n - a) / c);
            if (d > 0) high = min(high, (n - b) / d);
            while (low <= high) {
                ll mid = low + (high - low) / 2;
                if (!f(a + mid * c, b + mid * d)) {
                    step = mid;
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
            a += step * c;
            b += step * d;
        }
    }
    return {c, d};
}

