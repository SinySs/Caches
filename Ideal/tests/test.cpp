#include <iostream>
#include <fstream>
#include <vector>

#include "../ideal.hpp"

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

        int answ;
        int hits = cache::count_ideal_hits(m, v);

        answers >> answ;
        assert(answ == hits);
        if(answ == hits) {
            std::cout << "Test " << j + 1 << " complete" << std::endl;
        }

    }
}
