#include <iostream>
#define MAX 31

using namespace std;

bool array[MAX];

int main()
{
    for (int i=0; i<28; i++) {
        int num;
        cin >> num;
        array[num] = true;
    }

    for (int i=1; i<MAX; i++) {
        if (!array[i])
            cout << i << "\n";
    }

    return 0;
}
