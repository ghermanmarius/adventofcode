//https://adventofcode.com/2020/day/15
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

std::array<int, 6> input = {15,5,1,4,7,0};

int solve(std::array<int, 6>& seed, int cycles)
{
    std::vector<int> game(cycles);
    int turn{ 1 };
    int last{ 0 };
    auto play = [&](int val)
    {
        if (game[val] == 0) 
            return 0;
        return turn - game[val];
    };
    
    std::for_each(seed.begin(), std::prev(seed.end()), [&](auto v)
        {
            game[v] = turn;
            ++turn;
        });
    last = seed.back();
    while (turn != cycles)
    {
        auto next = play(last);
        game[last] = turn;
        last = next;
        ++turn;
    }
    return last;
}



int main()
{
    auto p1 = solve(input, 2020);
    auto p2 = solve(input, 30'000'000);
    std::cout << "p1    " << p1 << '\n';
    std::cout << "p2    " << p2 << '\n';
}