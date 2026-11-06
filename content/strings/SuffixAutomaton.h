/**
 * Author: Might be AI, sent by Anton Borodikhin
 * Description: Suffix automaton algorithm.
 * Time: $O(26N)$
 * Status: stress-tested a bit
 */

struct Node {
    int suf, par;
    array<int, 26> link;

    Node() = default;

    Node(int suf, int par, const array<int, 26>& link) : suf(suf), par(par), link(link) {
    }
};

vector<Node> sa(2);
int last = 1;

// 0 <= nc < 26
void add_char(int nc) {
    int b = sa.size();
    sa.emplace_back();
    sa[b].par = last;
    sa[b].suf = 1;
    for (; last; last = sa[last].suf) {
        if (!sa[last].link[nc]) {
            sa[last].link[nc] = b;
            continue;
        }
        int c = sa[last].link[nc];
        if (sa[c].par == last) {
            sa[b].suf = c;
            break;
        }
        int d = sa.size();
        sa.emplace_back(sa[c].suf, last, sa[c].link);
        sa[b].suf = sa[c].suf = d;
        for (; last && sa[last].link[nc] == c; last = sa[last].suf) {
            sa[last].link[nc] = d;
        }
        break;
    }
    last = b;
}
