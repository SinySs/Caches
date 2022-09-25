#include <iostream>
#include <vector>
#include <cassert>
#include <iterator>

#include "ideal.hpp"

int slow_get_page_int(int key) { return key; }


int main()
{
    size_t n, m;
    int hits = 0;

    std::cin >> m >> n;
    assert(std::cin.good());

    std::vector<int> v(n);


    for(size_t i = 0; i < n; i++) {
        std::cin >> v[i];
        assert(std::cin.good());


    }

    cache::ideal_cache_t<int> cache {m, v};

    for(size_t i = 0; i < v.size(); i++) {
        if(cache.loookup_update(v[i], slow_get_page_int)){
            hits++;
        }
    }

    std::cout << hits;

}
