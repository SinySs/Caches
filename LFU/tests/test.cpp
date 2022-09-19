#include <iostream>
#include <fstream>
#include <assert.h>

#include "../LFU.hpp"

int slow_get_page_int(int key) { return key; }

int main()
{
    std::ifstream data("/tests_data/data.txt");
    std::ifstream answers("/tests_data/answers.txt");

    for(int j = 0; j < 5; j++) {
        int n, m;
        int hits = 0;
        data >> m;
        data >> n;

        cache::lfu_cache_t<int> cache{m};
        for(int i = 0; i < n; i++) {
            int q;
            data >> q;

            if(cache.loookup_update(q, slow_get_page_int)) {
                hits++;
            }
        }

        int answ;

        answers >> answ;

        assert(answ == hits);
        if(answ == hits) {
            std::cout << "Test " << j + 1 << " complete" << std::endl;
        }

    }
}
