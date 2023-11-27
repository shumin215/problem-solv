#include <iostream>

using namespace std;

int main()
{
    int H, M, F;
    cin >> H >> M;
    cin >> F;

    int total_min = H * 60 + M + F;

    if (total_min < 0) {
        total_min += 24 * 60;
    }

    int hour = total_min / 60;
    if (hour >= 24) {
        hour -= 24;
    }
    int min = total_min % 60;
    
    cout << hour << " " << min << "\n";

    return 0;
}
