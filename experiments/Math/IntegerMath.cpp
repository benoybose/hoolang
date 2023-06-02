#include <cmath>
#include <cstdint>
#include <iostream>
#include <list>

int main (int argc, char **argv)
{
    std::int64_t max64 = INT64_MAX;
    std::int64_t min64 = INT64_MIN;
    std::list<std::int64_t> divisors = {1, 2, 3, 5, 8, 13, 21, 34, 55, 89};
    std::list<std::int64_t> specimen;

    std::cout << "MAX(i64): " << max64 << std::endl;
    std::cout << "MIN(i64): " << min64 << std::endl;

    specimen.insert(specimen.end(), divisors.begin(), divisors.end());
    for (const std::int64_t& divisor : divisors) {
        auto outcome = max64 / divisor;
        specimen.push_back(outcome);
    }

    std::list<std::int64_t> negative_specimen;
    for (auto item: specimen) {
        negative_specimen.push_back(item * -1);        
    }
    specimen.insert(specimen.end(), negative_specimen.begin(), negative_specimen.end());

    for (auto item: specimen) {
        std::cout << item << std::endl;
    }

    for (auto l: specimen) {
        for (auto r: specimen) {
            std::cout << l << "+" << r << "=" << l + r << std::endl;
        }
    }
    
    return 0;
}
