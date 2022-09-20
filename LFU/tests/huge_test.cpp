#include <iostream>
#include <fstream>
#include <assert.h>
#include <vector>

#include "../LFU.hpp"



std::vector<float> slow_get_page_int(int key)
{
    std::vector<float> V(10, key);

    return V;
}

int main()
{
    std::ifstream data("tests_data/huge_data.txt");
    std::ifstream answers("tests_data/huge_answers.txt");


    int n, m;
    int hits = 0;
    data >> m;
    data >> n;

    cache::lfu_cache_t<std::vector<float>> cache{m};
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
        std::cout << "Test complete" << std::endl;
    }


}
