#include <iostream>
#define MAX 300

using namespace std;

int N;
int array[MAX];

int main()
{
    cin >> N;

    for (int i=0; i<N; i++) {
        int num;
        cin >> num;
        if (num < 0)
            num += 201;
        array[num]++;
    }

    int ans;
    cin >> ans;

    if (ans < 0)
        ans += 201;
    cout << array[ans] << "\n";

    return 0;
}
