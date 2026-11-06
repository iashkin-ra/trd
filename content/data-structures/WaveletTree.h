/**
 * Author: Anton
 * Description: Wavelet tree.
 * Time: idk
 */
template<class T = int>
struct WaveletTree {
    struct Node {
        int lo, hi;
        int lc = -1, rc = -1;
        vector<int> pref;

        Node(int lo, int hi) : lo(lo), hi(hi) {
        }
    };

    vector<T> vals;
    vector<Node> tree;

    WaveletTree(const vector<T> &a) : vals(a) {
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());

        vector<int> b(a.size());
        for (int i = 0; i < (int) a.size(); ++i) {
            b[i] = lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin();
        }

        tree.reserve(2 * vals.size() + 1);
        build(b, 0, (int) b.size(), 0, (int) vals.size());
    }

    const T *kth(int l, int r, int k) const {
        if (l >= r || k <= 0 || k > r - l) return nullptr;

        int v = 0;
        while (tree[v].hi - tree[v].lo > 1) {
            const auto &t = tree[v];
            int bl = t.pref[l], br = t.pref[r];
            int cnt = br - bl;

            if (k <= cnt) {
                l = bl;
                r = br;
                v = t.lc;
            } else {
                k -= cnt;
                l -= bl;
                r -= br;
                v = t.rc;
            }
        }
        return &vals[tree[v].lo];
    }

    int less_than(const T &x, int l, int r) const {
        int p = lower_bound(vals.begin(), vals.end(), x) - vals.begin();
        return count_less(0, l, r, p);
    }

    const T *first_ge(const T &x, int l, int r) const {
        return kth(l, r, less_than(x, l, r) + 1);
    }

private:
    int build(vector<int> &a, int l, int r, int lo, int hi) {
        int v = (int) tree.size();
        tree.emplace_back(lo, hi);
        if (l == r || hi - lo <= 1) return v;

        int mid = (lo + hi) / 2;
        tree[v].pref.resize(r - l + 1);
        for (int i = l; i < r; ++i) {
            tree[v].pref[i - l + 1] = tree[v].pref[i - l] + (a[i] < mid);
        }

        int m = stable_partition(a.begin() + l, a.begin() + r, [mid](int x) { return x < mid; }) - a.begin();

        int lc = build(a, l, m, lo, mid);
        int rc = build(a, m, r, mid, hi);
        tree[v].lc = lc;
        tree[v].rc = rc;
        return v;
    }

    int count_less(int v, int l, int r, int p) const {
        const auto &t = tree[v];
        if (l >= r || p <= t.lo) return 0;
        if (t.hi <= p) return r - l;

        int bl = t.pref[l], br = t.pref[r];
        return count_less(t.lc, bl, br, p) + count_less(t.rc, l - bl, r - br, p);
    }
};
