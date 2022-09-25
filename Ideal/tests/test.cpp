#include <iostream>
#include <fstream>
#include <vector>

#include "../ideal.hpp"

int slow_get_page_int(int key) { return key; }

int main()
{
    std::ifstream data("data/data.txt");
    std::ifstream answers("data/answers.txt");

    for(int j = 0; j < 5; j++) {
        int n, m;
        data >> m;
        data >> n;

        std::vector<int> v(n);

        for(size_t i = 0; i < n; i++) {
            data >> v[i];

        }


        cache::ideal_cache_t<int> cache {m, v};
        int hits = 0;

        for(size_t i = 0; i < v.size(); i++) {
            if(cache.loookup_update(v[i], slow_get_page_int)){
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
