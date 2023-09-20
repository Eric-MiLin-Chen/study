#include <iostream>
#include "../../Lib/UFSets.h"

using namespace std;

int main()
{
    char SetData[11] = "abcdefghij";
    UFSets<char> sets(SetData, 10);
    sets.Display();
    sets.WeightUnion('a', 'b', 1);
    sets.Display();
    sets.WeightUnion('c', 'a', 1);
    sets.Display();
    sets.WeightUnion('d', 'e', 1);
    sets.Display();
    sets.WeightUnion('f', 'g', 1);
    sets.Display();
    sets.WeightUnion('g', 'h', 1);
    sets.Display();
    sets.WeightUnion('j', 'i', 1);
    sets.Display();
    sets.WeightUnion('g', 'c', 1);
    sets.Display();
    // sets.WeightUnion('c', 'a', 1);
    // sets.Display();
    return 0;
}