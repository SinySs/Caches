#pragma once

#include <iterator>
#include <unordered_map>
#include <map>

namespace cache
{
const size_t START_TIME = 1;

template <typename T, typename KeyT = int> class lfu_cache_t
{
    struct data
    {
        T data_;
        KeyT key_;
    };

    size_t size_ = 0;
    size_t capacity_ = 0;
    using lfu_iterator = typename std::multimap<size_t, data>::iterator;


    std::multimap<size_t, data> freq_map_;
    std::unordered_map<KeyT, lfu_iterator> hash_;

    void erase()
    {
        KeyT rem_key = freq_map_.begin()->second.key_;
        freq_map_.erase(hash_[rem_key]);
        hash_.erase(rem_key);
        size_--;
    }

    template <typename F> void insert(KeyT key, F slow_get_page_int)
    {
        data new_elem;
        new_elem.data_ = slow_get_page_int(key);
        new_elem.key_ = key;
        if(full()) {
            erase();
        }

        hash_[key] = freq_map_.emplace(START_TIME, new_elem);
        size_++;
    }

    void update(KeyT key, lfu_iterator hit)
    {
        freq_map_.erase(hit);
        hash_[key] = freq_map_.emplace(hit->first + 1, hit->second);
    }

public:
    lfu_cache_t(size_t cache_size) : capacity_(cache_size) {}

    bool full() { return size_ == capacity_; }

    template <typename F> bool loookup_update(KeyT key, F slow_get_page_int)
    {
        auto hit = hash_.find(key);

        if(hit == hash_.end()) {
            insert(key, slow_get_page_int);
            return false;
        }

        update(key, hit->second);

        return true;
    }

};
} // namespace cache
