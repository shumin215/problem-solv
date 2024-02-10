#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
 
#include  <stdio.h >
 
#define REGISTER_BOOK_INFO  0
#define INPUT_BOOK          1
#define SELL_BOOKS          2
#define PICK_BEST_SELLER    3
#define PICK_BEST_AUTHORS   4
#define OUT_OF_PRINT        5
 
#define AUTHOR_MAX          5
#define RESULT_MAX          3
 
void init(int authorNumber, int genreNumber);
void registerBookInfo(int bookID, int genreID, int price, int number, int authorIDs[]);
void inputBook(int bookID, int cnt);
int sellBooks(int bookID, int cnt);
int pickBestSeller(int genreID, int bookIDs[]);
void pickBestAuthors(int authorIDs[]);
void outOfPrint(int bookID);
 
static int run()
{
    int authorNumber;
    int genreNumber;
    int queryCount;
    bool correct = true;
    int bookID, genreID, price, num, cnt;
    int result[RESULT_MAX + 5], authorIDs[AUTHOR_MAX];
 
    scanf("%d%d%d", &authorNumber, &genreNumber, &queryCount);
    init(authorNumber, genreNumber);
 
    for (int qc = 0; qc < queryCount; qc++) {
        int cmd = 0;
        scanf("%d", &cmd);
        if (cmd == REGISTER_BOOK_INFO) {
            scanf("%d%d%d%d", &bookID, &genreID, &price, &num);
            for (int i = 0; i < num; i++) {
                scanf("%d", &authorIDs[i]);
            }
            registerBookInfo(bookID, genreID, price, num, authorIDs);
        }
        else if (cmd == INPUT_BOOK) {
            scanf("%d%d", &bookID, &cnt);
            inputBook(bookID, cnt);
        }
        else if (cmd == SELL_BOOKS) {
            scanf("%d%d", &bookID, &cnt);
            int ret = sellBooks(bookID, cnt);
            int ans;
            scanf("%d", &ans);
            if (ret != ans)
                correct = false;
        }
        else if (cmd == PICK_BEST_SELLER) {
            scanf("%d", &genreID);
            int ret = pickBestSeller(genreID, result);
            int ans, bid;
            scanf("%d", &ans);
            if (ret != ans) {
                correct = false;
            }
            for (int i = 0; i < ans; i++) {
                scanf("%d", &bid);
                if (result[i] != bid) {
                    correct = false;
                }
            }
        }
        else if (cmd == PICK_BEST_AUTHORS) {
            pickBestAuthors(result);
            int aid;
            for (int i = 0; i < RESULT_MAX; i++) {
                scanf("%d", &aid);
                if (result[i] != aid) {
                    correct = false;
                }
            }
        }
        else if (cmd == OUT_OF_PRINT) {
            scanf("%d", &bookID);
            outOfPrint(bookID);
        }
    }
    return correct;
}
 
int main()
{
    setbuf(stdout, NULL);
    freopen("input.txt", "r", stdin);
 
    int testCase, success;
    scanf("%d %d", &testCase, &success);
    for (int tc = 1; tc <= testCase; tc++) {
        int score = run() ? success : 0;
        printf("#%d %d\n", tc, score);
    }
    return 0;
}