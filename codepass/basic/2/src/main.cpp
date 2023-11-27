#include <iostream>

using namespace std;

int main()
{
    int a, b;
    
    while (true) {
        cin >> a >> b;

        if (a < 2 || a > 9 || b < 2 || b > 9) {
            printf("INPUT ERROR!\n");
            continue;
        } else {

            if (a > b) {
                for (int i=a; i>=b; i--) {
                    for (int j=1; j<=9; j+=3) {
                        printf("%d * %d = %2d   %d * %d = %2d   %d * %d = %2d\n",
                                i, j, i*j, i, j+1, i*(j+1), i, j+2, i*(j+2));
                    }
                    printf("\n");
                }
            } else {
                for (int i=a; i<=b; i++) {
                    for (int j=1; j<=9; j+=3) {
                        printf("%d * %d = %2d   %d * %d = %2d   %d * %d = %2d\n",
                                i, j, i*j, i, j+1, i*(j+1), i, j+2, i*(j+2));
                    }
                    printf("\n");
                }
            }

            break;
        }
    }

    return 0;
}
