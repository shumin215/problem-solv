#include <iostream>
#include <climits>

using namespace std;

bool isEndNum(int num)
{
    bool ret = false;
    int six_cnt = 0;

    while(num != 0) {
        if (num % 10 == 6) {
            six_cnt++;

            if (six_cnt >= 3) {
                ret = true;
                break;
            }
        } else {
            six_cnt = 0;
        }

        num /= 10;
    }

    return ret;
}

int main()
{
    int N;
    int end_num_cnt = 0;
    cin >> N;

    for (int i=666; i<=INT_MAX; i++) {
        if (isEndNum(i))
            end_num_cnt++;

        if (end_num_cnt == N) {
            printf("%d\n", i);
            return 0;
        }
    }



    return 0;
}
