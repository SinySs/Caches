#pragma once

#include <iterator>
#include <iostream>
#include <vector>
#include <cassert>
#include <unordered_map>
#include <map>
#include <list>
#include <deque>
#include <unordered_set>

namespace cache
{

template <typename T, typename KeyT = int> class ideal_cache_t
{
    struct data
    {
        T data_;
        KeyT key_;
    };

    size_t size_ = 0;
    size_t capacity_ = 0;

    std::unordered_map<KeyT, std::deque<int>> all_calls_;
    std::map<int, data> cache_;
    std::unordered_set<KeyT> elems_in_;

    void fill_calls(const std::vector<int>& v)
    {
        for(auto i = 0; i < v.size(); i++) {
            auto &que = all_calls_.emplace(v[i], std::deque<int> ()).first->second;
            que.push_back(i);
        }
    }

    template <typename F> void insert(KeyT key, F slow_get_page_int)
    {

        auto &que = all_calls_.at(key);
        que.pop_front();
        if(que.begin() == que.end())  // dont insert elem that will  no meet
            return;

        if(full()) {
            auto removal_candidate = std::prev(cache_.end());

            if(removal_candidate->first < que.front())
                return;

            elems_in_.erase(removal_candidate->second.key_);
            cache_.erase(prev(cache_.end()));

            size_--;
        }
        data new_elem;
        new_elem.key_ = key;
        new_elem.data_ = slow_get_page_int(key);

        cache_.insert({que.front(), new_elem});
        elems_in_.insert(key);
        size_++;


    }



public:
    bool full() const { return size_ == capacity_; }

    ideal_cache_t(size_t cache_size, const std::vector<int>& v) : capacity_(cache_size)
    {
        fill_calls(v);
    }

    template <typename F> bool loookup_update(KeyT key, F slow_get_page_int)
    {
        auto hit = elems_in_.find(key);
        if(hit == elems_in_.end()) {
            insert(key, slow_get_page_int);
            return false;
        }

        auto &que = all_calls_.at(key);
        int past_time = que.front();
        que.pop_front();

        if(que.begin() == que.end()) { //del elem that never meet
            cache_.erase(past_time);
            elems_in_.erase(key);
            size_--;
        } else {
            cache_.erase(past_time);
            data new_elem;
            new_elem.key_ = key;
            new_elem.data_ = slow_get_page_int(key);
            cache_.insert({que.front(), new_elem});
        }

        return true;
    }

};
} // namespace cashe



