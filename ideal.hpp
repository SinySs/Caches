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
    size_t size_ = 0;
    size_t capacity_ = 0;

    std::unordered_map<T, std::deque<int>> all_calls_;
    std::map<int, T> cache_;
    std::unordered_set<T> elems_in_;

    void fill_calls(const std::vector<T>& v)
    {
        for(auto i = 0; i < v.size(); i++) {
            auto &que = all_calls_.emplace(v[i], std::deque<int> ()).first->second;
            que.push_back(i);
        }
    }

    void upppp(KeyT key)
    {
        auto &que = all_calls_.at(key);
        que.pop_front();
    }

    void insert(KeyT key)
    {

        auto &que = all_calls_.at(key);
        que.pop_front();
        if(que.begin() == que.end())  // dont insert elem that will  no meet
            return;

        if(full()) {
            auto removal_candidate = std::prev(cache_.end());

            if(removal_candidate->first < que.front())
                return;

            elems_in_.erase(removal_candidate->second);
            cache_.erase(prev(cache_.end()));

            size_--;
        }

        cache_.insert({que.front(), key});
        elems_in_.insert(key);
        size_++;


    }



public:
    bool full() { return size_ == capacity_; }

    ideal_cache_t(size_t cache_size, const std::vector<T>& v) : capacity_(cache_size)
    {
        fill_calls(v);
    }

    bool loookup_update(KeyT key)
    {
        auto hit = elems_in_.find(key);
        if(hit == elems_in_.end()) {
            insert(key);
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
            cache_.insert({que.front(), key});
        }

        return true;


    }

};

template <typename T>
int count_ideal_hits(size_t cache_size, const std::vector<T>& v)
{
    int hits = 0;
    ideal_cache_t<T> cache {cache_size, v};

    for(size_t i = 0; i < v.size(); i++) {
        if(cache.loookup_update(v[i])){
            hits++;
        }
    }
    return hits;
}
} // namespace cashe
