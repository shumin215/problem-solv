#include <iostream>

int N;
int TARGET;
int min_btn_cnt;

void doDFS(string in_num)
{
    if (in_num.length() )
}

int main()
{
    cin >> TARGET;
    cin >> N;

    for (int i=0; i<N; i++) {
        int num;
        cin >> num;
        button_table[num] = false;
    }

    min_btn_cnt = abs(TARGET - 100);

    doDFS("");

    printf("Hello World\n");

    return 0;
}
