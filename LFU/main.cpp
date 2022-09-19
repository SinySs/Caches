#include <iostream>
#include <assert.h>

#include "LFU.hpp"

int slow_get_page_int(int key) { return key; }

int main()
{
    size_t m;
    int n;
    int hits = 0;

    std::cin >> m >> n;
    assert(std::cin.good());

    cache::lfu_cache_t<int> cache{m};

    for(int i = 0; i < n; i++) {
        int q;
        std::cin >> q;
        assert(std::cin.good());

        if(cache.loookup_update(q, slow_get_page_int)) {
            hits++;
        }
    }

    std::cout << hits << std::endl;

    return 0;
}
