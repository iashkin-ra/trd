/**
 * Author: Anton
 * Description: Builds a suffix array and LCP of a string.
 * Time: O(N log N)
 */

template<typename T>
std::vector<std::size_t>  suffix_array(std::size_t n, const T &s) {
    std::vector<std::size_t> sa(n);
    if (n == 0) {
        return sa;
    }
    iota(sa.begin(), sa.end(), 0);
    std::sort(sa.begin(), sa.end(), [&s](std::size_t i, std::size_t j) {
        return s[i] < s[j];
    });
    std::vector<std::size_t> sorted_by_second(n);
    std::vector<std::size_t> group(n), ptr_group(n), new_group(n);
    for (std::size_t i = 1; i < n; ++i) {
        group[sa[i]] = group[sa[i - 1]];
        if (s[sa[i - 1]] != s[sa[i]]) {
            ++group[sa[i]];
        }
    }
    std::size_t cnt = group[sa.back()] + 1;
    std::size_t step = 1;
    while (cnt < n) {
        std::size_t at = 0;
        for (std::size_t i = n - step; i < n; ++i) {
            sorted_by_second[at++] = i;
        }
        for (std::size_t i = 0; i < n; ++i) {
            if (i == 0 || group[sa[i]] != group[sa[i - 1]]) {
                ptr_group[group[sa[i]]] = i;
            }
            if (sa[i] >= step) {
                sorted_by_second[at++] = sa[i] - step;
            }
        }
        for (std::size_t i = 0; i < n; ++i) {
            std::size_t x = sorted_by_second[i];
            sa[ptr_group[group[x]]++] = x;
        }
        new_group[sa[0]] = 0;
        for (std::size_t i = 1; i < n; ++i) {
            if (group[sa[i]] != group[sa[i - 1]]) {
                new_group[sa[i]] = new_group[sa[i - 1]] + 1;
            } else {
                std::size_t prv = sa[i - 1] + step >= n ? n : group[sa[i - 1] + step];
                std::size_t cur = sa[i] + step >= n ? n : group[sa[i] + step];
                new_group[sa[i]] = new_group[sa[i - 1]] + (prv != cur);
            }
        }
        group.swap(new_group);
        cnt = group[sa.back()] + 1;
        step <<= 1;
    }
    return sa;
}

template<typename T>
std::vector<std::size_t> build_lcp(std::size_t n, const T &s, const std::vector<std::size_t> &sa) {
    if (n < 2) {
        return {};
    }
    std::vector<std::size_t> pos(n);
    for (std::size_t i = 0; i < n; ++i) {
        pos[sa[i]] = i;
    }
    std::vector<std::size_t> lcp(n - 1);
    for (std::size_t i = 0, len = 0; i < n; ++i) {
        if (len > 0) {
            --len;
        }
        if (pos[i] == n - 1) {
            len = 0;
            continue;
        }
        std::size_t j = sa[pos[i] + 1];
        while (i + len < n && j + len < n && s[i + len] == s[j + len]) {
            ++len;
        }
        lcp[pos[i]] = len;
    }
    return lcp;
}
