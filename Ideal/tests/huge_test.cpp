#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>

#include "../ideal.hpp"



std::vector<float> slow_get_page_int(int key)
{
    std::vector<float> V(10, key);

    return V;
}

int main()
{
    std::ifstream data("data/huge_data.txt");
    std::ifstream answers("data/huge_answers.txt");


    int n, m;
    int hits = 0;
    data >> m;
    data >> n;

    std::vector<int> v(n);


    for(size_t i = 0; i < n; i++) {
        data >> v[i];
    }




    cache::ideal_cache_t<std::vector<float>> cache {m, v};

    for(size_t i = 0; i < v.size(); i++) {
        if(cache.loookup_update(v[i], slow_get_page_int)){
            hits++;
        }
    }

    int answ;
    answers >> answ;
    std::cout << answ << " " << hits << std::endl;
    if(answ == hits) {
        std::cout << "Test complete" << std::endl;
    }


}
