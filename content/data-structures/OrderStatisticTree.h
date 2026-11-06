/**
 * 
 * Author: AI i think, sent by Anton Borodikhin
 * 
 * Description: Stuff from pbds library
 * 
 */
#pragma once

#include <ext/pb_ds/assoc_container.hpp> /** keep-include */
#include <ext/pb_ds/tree_policy.hpp> /** keep-include */

using namespace __gnu_pbds;

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

template<typename K, typename V>
using fast_map = gp_hash_table<K, V, custom_hash>;

template<typename T>
using pairing_heap = __gnu_pbds::priority_queue<T, std::less<T>, pairing_heap_tag>;
// auto it = pq.push(5);
// pq.modify(it, 10);
