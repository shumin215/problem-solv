#include <iostream>
#define MAX 101

using namespace std;

void makeStar(int n)
{
    int mid = n / 2 + 1;
    for (int i=0; i<mid; i++) {
        for (int j=0; j<i; j++) {
            printf(" ");
        }
        for (int j=0; j<i*2+1; j++) {
            printf("*");
        }
        printf("\n");
    }

    for (int i=0; i<mid-1; i++) {
        for (int j=0; j<mid-1-i-1; j++) {
            printf(" ");
        }
        for (int j=n-2-(i*2); j>0; j--) {
            printf("*");
        }
        printf("\n");
    }
}

int main()
{
    int n;
    cin >> n;

    if (n < 1 || n > 100 || n % 2 == 0) {
        printf("INPUT ERROR!\n");
        return 0;
    }

    makeStar(n);

    return 0;
}
