#include <random>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <limits>
#include <chrono>

#include "SkipList.h"
// #include "SkipList_muster.h"

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "wrong number of arguments!" << std::endl;
        return 0;
    }

    std::vector<double> times;
    //prepare data to be inserted
    const size_t numElems = atoi(argv[1]);
    std::mt19937 g1(0);
    std::uniform_int_distribution<unsigned> distribution(0, 20 * numElems);

    std::vector<bool> added(20 * numElems, false);
    std::vector<unsigned> numbers(3 * numElems, 0);

    unsigned inserted = 0;

    while (inserted < 3 * numElems)
    {
        unsigned cand = distribution(g1);
        if (!added[cand])
        {
            added[cand] = true;
            numbers[inserted] = cand;
            ++inserted;
        }
    }

    std::vector<int64_t> init(numbers.begin(), numbers.begin() + numElems);
    std::vector<int64_t> numbers1(numbers.begin() + numElems, numbers.begin() + 2 * numElems);
    std::vector<int64_t> numbers2(numbers.begin() + 2 * numElems, numbers.end());
    numbers.clear();

    SkipList map(init);
    bool success = true;

    std::cout << "start inserting" << std::endl;

    //-----------------------------------------------------
    //--------check successful insertion-------------------
    //-----------------------------------------------------

    auto start = std::chrono::system_clock::now();

    for (size_t i = 0; i < numbers1.size(); ++i)
    {
        success = success && map.insert(numbers1[i]);
    }

    auto end = std::chrono::system_clock::now();

    if (success)
        std::cout << "insert ok" << std::endl;
    else
        std::cout << "insert broken" << std::endl;

    std::cout << "took " << (end - start).count() << " nanoseconds" << std::endl;

    //-----------------------------------------------------
    //------check unsuccessful insertion-------------------
    //-----------------------------------------------------

    start = std::chrono::system_clock::now();
    success = true;
    for (size_t i = 0; i < numbers1.size(); ++i)
    {
        success = success && !map.insert(numbers1[i]);
    }

    end = std::chrono::system_clock::now();

    if (success)
        std::cout << "duplicate insert ok" << std::endl;
    else
        std::cout << "duplicate insert broken" << std::endl;

    std::cout << "took " << (end - start).count() << " nanoseconds" << std::endl;

    //-----------------------------------------------------
    //--------check successful search----------------------
    //-----------------------------------------------------

    start = std::chrono::system_clock::now();
    success = true;

    for (size_t i = 0; i < numbers1.size(); ++i)
    {
        success = success && map.find(numbers1[i]);
    }
    end = std::chrono::system_clock::now();

    if (success)
        std::cout << "successful search ok" << std::endl;
    else
        std::cout << "successful search broken" << std::endl;

    std::cout << "took " << (end - start).count() << " nanoseconds" << std::endl;

    //-----------------------------------------------------
    //--------check unsuccessful search--------------------
    //-----------------------------------------------------

    start = std::chrono::system_clock::now();
    success = true;

    for (size_t i = 0; i < numbers2.size(); ++i)
    {
        success = success && !map.find(numbers2[i]);
    }

    end = std::chrono::system_clock::now();

    if(success)
        std::cout << "unsuccessful search ok" << std::endl;
    else
        std::cout << "unsuccessful search broken" << std::endl;

    std::cout << "took " << (end - start).count() << " nanoseconds" << std::endl;

    //-----------------------------------------------------
    //-------------check remove----------------------------
    //-----------------------------------------------------

    start = std::chrono::system_clock::now();
    success = true;
    for (size_t i = 0; i < numbers1.size(); ++i)
    {
        success = success && map.remove(numbers1[i]);
        success = success && !map.remove(numbers1[i]); //try to remove again
        success = success && !map.find(numbers1[i]); // try to find removed
    }
    end = std::chrono::system_clock::now();

    if (success)
        std::cout << "remove ok" << std::endl;
    else
        std::cout << "remove broken" << std::endl;

    std::cout << "took " << (end - start).count() << " nanoseconds" << std::endl;

    return 0;
}
