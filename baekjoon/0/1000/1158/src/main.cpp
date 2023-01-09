#include <iostream>
#include <list>

using namespace std;

int main()
{
    int n, k;
    list<int> arr;
    scanf("%d %d", &n, &k);

    // Initialize
    for (int i=0; i<n; i++) {
        arr.push_back(i+1);
    }

    printf("<");
    for (int i=0; i<n; i++) {

        for (int j=0; j<k-1; j++) {
            arr.push_back(arr.front());
            arr.pop_front();
        }
        if (i+1 != n) {
            printf("%d, ", arr.front());
        } else {
            printf("%d>", arr.front());
        }

        arr.pop_front();
    }
    printf("\n");

    return 0;
}


