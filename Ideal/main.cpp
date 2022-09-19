#include <iostream>
#include <vector>
#include <cassert>
#include <iterator>

#include "ideal.hpp"


int main()
{
    size_t n, m;

    std::cin >> m >> n;
    assert(std::cin.good());

    std::vector<int> v(n);


    for(size_t i = 0; i < n; i++) {
        std::cin >> v[i];
        assert(std::cin.good());
    }

    std::cout << cache::count_ideal_hits(m, v);

}
