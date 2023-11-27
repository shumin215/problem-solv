#include <iostream>
#define MAX 101

using namespace std;

void funcType1(int n)
{
    int mid = n / 2 + 1;
    for (int i=0; i<mid; i++) {
        for (int j=0; j<i+1; j++) {
            printf("*");
        }
        printf("\n");
    }

    for (int i=0; i<mid-1; i++) {
        for (int j=0; j<mid-1-i; j++) {
            printf("*");
        }
        printf("\n");
    }
}

void funcType2(int n)
{
    int mid = n / 2 + 1;
    for (int i=0; i<mid; i++) {
        for (int j=0; j<mid-i-1; j++) {
            printf(" ");
        }
        for (int j=0; j<i+1; j++) {
            printf("*");
        }
        printf("\n");
    }

    for (int i=0; i<mid-1; i++) {
        for (int j=0; j<i+1; j++) {
            printf(" ");
        }
        for (int j=0; j<mid-1-i; j++) {
            printf("*");
        }
        printf("\n");
    }
}

void funcType3(int n)
{
    int mid = n / 2 + 1;

    for (int i=0; i<mid-1; i++) {
        for (int j=0; j<i; j++) {
            printf(" ");
        }
        for (int j=0; j<n-(i*2); j++) {
            printf("*");
        }
        printf("\n");
    }

    for (int i=0; i<mid; i++) {
        for (int j=0; j<mid-i-1; j++) {
            printf(" ");
        }
        for (int j=0; j<i*2+1; j++) {
            printf("*");
        }
        printf("\n");
    }
}

void funcType4(int n)
{
    int mid = n / 2 + 1;

    for (int i=0; i<mid-1; i++) {
        for (int j=0; j<i; j++) {
            printf(" ");
        }
        for (int j=0; j<mid-i; j++) {
            printf("*");
        }
        printf("\n");
    }

    for (int i=0; i<mid; i++) {
        for (int j=0; j<mid-1; j++) {
            printf(" ");
        }

        for (int j=0; j<i+1; j++) {
            printf("*");
        }

        printf("\n");
    }
}

int main()
{
    int n, type;
    cin >> n >> type;

    if (n < 1 || n > 100 || type < 1 || type > 4 || n % 2 == 0) {
        printf("INPUT ERROR!\n");
        return 0;
    }

    if (type == 1)
        funcType1(n);
    else if (type == 2)
        funcType2(n);
    else if (type == 3)
        funcType3(n);
    else if (type == 4)
        funcType4(n);

    return 0;
}
