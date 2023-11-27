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
                for (int j=1; j<10; j++) {
                    for (int i=a; i>=b; i--) {
                        printf("%d * %d = %2d", i, j, i*j);
                        printf("   ");
                    }
                    printf("\n");
                }
            } else {
                for (int j=1; j<10; j++) {
                    for (int i=a; i<=b; i++) {
                        printf("%d * %d = %2d", i, j, i*j);
                        printf("   ");
                    }
                    printf("\n");
                }
            }

            break;
        }
    }

    return 0;
}
