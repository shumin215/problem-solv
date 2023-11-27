#include <iostream>
#include <vector>

using namespace std;

long long sum(std::vector<int> &a)
{
    long long ret = 0;

    for (auto i: a) {
        ret += i;
    }

    return ret;
}

int main()
{
    vector<int> list;
    for (int i=0; i<10; i++)
        list.push_back(i);

    cout << sum(list) << "\n";

    return 0;
}
