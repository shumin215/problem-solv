#include <iostream>

int main()
{
    int arr[7] = {0};
    int sum = 0;
    int min = 9999;

    scanf("%d %d %d %d %d %d %d", 
            &arr[0],
            &arr[1],
            &arr[2],
            &arr[3],
            &arr[4],
            &arr[5],
            &arr[6]
            );

    for (auto i=0; i<7; i++) {
        if (arr[i] % 2 == 1) {
            sum += arr[i];
            if (min > arr[i])
                min = arr[i];
        }
    }
    if (sum == 0) {
        printf("-1\n");
        return 0;
    }
    printf("%d\n", sum);
    printf("%d\n", min);

    return 0;
}


