#include <iostream>
#include <algorithm>
#include <vector>

#define SIZE 20

using namespace std;

vector<int> arr;

void reArrange(int _s, int _e)
{
    auto iter_s = arr.begin() + _s - 1;
    auto iter_e = arr.begin() + _e;
    reverse(iter_s, iter_e);
}

int main()
{
    int num = 10;

    for (int i=0; i<SIZE; i++) {
        arr.push_back(i+1);
    }

    for (int i=0; i<num; i++) {
        int start, end;
        scanf("%d %d", &start, &end);
        reArrange(start, end);
    }
    for (int j=0; j<SIZE; j++) {
        printf("%d ", arr[j]);
    }
    printf("\n");

    return 0;
}


