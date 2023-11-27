#include <iostream>

using namespace std;

int main()
{
    int H, M;
    cin >> H >> M;

    int total_min = H * 60 + M - 45;

    if (total_min < 0) {
        total_min += 24 * 60;
    }

    int hour = total_min / 60;
    int min = total_min % 60;
    
    cout << hour << " " << min << "\n";

    return 0;
}
