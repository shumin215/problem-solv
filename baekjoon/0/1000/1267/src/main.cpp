#include <iostream>
int main()
{
    int num;
    int fee[20] = {0};
    int ys_fee = 0;
    int ms_fee = 0;
    scanf("%d", &num);
    
    for (int i=0; i<num; i++) {
        scanf("%d", &fee[i]);

        int half_min = (fee[i] + 1) / 30;
        int remainder = (fee[i] + 1)  % 30;

        ys_fee += half_min * 10;
        ys_fee += (remainder > 0) ? 10 : 0;

        int first = (fee[i] + 1) / 60;
        int first_o = (fee[i] + 1) % 60;

        ms_fee += first * 15;
        ms_fee += (first_o > 0) ? 15 : 0;
    }

    if (ys_fee < ms_fee) {
        printf("Y %d\n", ys_fee);
    } else if (ys_fee > ms_fee) {
        printf("M %d\n", ms_fee);
    } else {
        printf("Y M %d\n", ys_fee);
    }

    return 0;
}

