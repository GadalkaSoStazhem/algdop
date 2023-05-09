/* 1521
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int *mas = (int*)malloc((n + 1) * sizeof(int));
    for (int i = 1; i < n + 1; i++){
        mas[i] = i;
    }

    k -= 1;
    int unitaz = 0;
    int rest = n;
    while (rest > 0){
        unitaz = (unitaz + k) % rest;
        printf("%d ", mas[unitaz + 1]);
        for (int i = unitaz + 1; i < rest; i++){
            mas[i] = mas[i + 1];
        }
        rest --;
    }
    free(mas);
    return 0;
}
*/




/* 1494
#include <stdlib.h>
#include <stdio.h>
struct stack
{
    int maxsize;
    int top;
    int *items;
};

struct stack* newStack(int capacity)
{
    struct stack *pt = (struct stack*)malloc(sizeof(struct stack));
    pt->maxsize = capacity;
    pt->top = -1;
    pt->items = (int*)malloc(sizeof(int) * capacity);
    return pt;
}

void push(struct stack *pt, int x)
{
    pt->items[++pt->top] = x;
}

int peek(struct stack *pt)
{
    return pt->items[pt->top];
}
int pop(struct stack *pt)
{
    return pt->items[pt->top--];
}
int main(){
    int n;
    int flag = 1;
    scanf("%d", &n);
    struct stack *st = newStack(n);
    int max_number = 0;
    int to_compare = 0;
    for (int i = 0; i < n; i++){
        int cur_number;
        scanf("%d", &cur_number);
        if (cur_number > max_number){
            for (int j = max_number + 1; j <= cur_number - 1; j++)
                push(st, j);
            max_number = cur_number;
        }
        else{
            if (cur_number == peek(st)){
                pop(st);
            }
            else{
                printf("Cheater");
                flag = 0;
                break;
            }
        }
    }
    if (flag == 1)
        printf("Not a proof");
    return 0;
}
*/
//1080 спизженно
/*#include <stdbool.h>
#include <stdio.h>

#define N 100

bool mas[N][N];
int colors[N];
bool flag = true;

void coloring(int country, int color, int n) {
    colors[country] = color;

    for (int sosed = 0; sosed < n; ++sosed) {
        if (mas[country][sosed]) {
            if (colors[sosed] == -1) {
                coloring(sosed, 1 - color, n);
            } else if (colors[sosed] == color) {
                flag = false;
            }
        }
    }
}

int main() {
    int n, sosed;

    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        colors[i] = -1;
        while (scanf("%d", &sosed), sosed != 0) {
            mas[i][sosed - 1] = true;
            mas[sosed - 1][i] = true;
        }
    }
    coloring(0, 0, n);
    if (flag) {
        for (int i = 0; i < n; ++i) {
            printf("%d", colors[i]);
        }
    } else {
        printf("-1");
    }

    return 0;
}
 */
//1162 спизженно
#include <stdbool.h>
#include <stdio.h>

#define MAXN 101
#define MAXM 201

struct comb {
    int a, b;
    double rab, cab, rba, cba;
};

int n, m, s;
double v;
struct comb combs[MAXM];

bool bellman_ford() {
    double cur[MAXN] = {0};
    cur[s] = v;

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int a = combs[j].a;
            int b = combs[j].b;

            if (cur[a] > combs[j].cab) {
                double new_cur = (cur[a] - combs[j].cab) * combs[j].rab;
                if (new_cur > cur[b]) {
                    cur[b] = new_cur;
                }
            }

            if (cur[b] > combs[j].cba) {
                double new_cur = (cur[b] - combs[j].cba) * combs[j].rba;
                if (new_cur > cur[a]) {
                    cur[a] = new_cur;
                }
            }
        }
    }

    for (int j = 0; j < m; ++j) {
        int a = combs[j].a;
        int b = combs[j].b;

        if (cur[a] > combs[j].cab) {
            double new_cur = (cur[a] - combs[j].cab) * combs[j].rab;
            if (new_cur > cur[b]) {
                return true;
            }
        }

        if (cur[b] > combs[j].cba) {
            double new_cur = (cur[b] - combs[j].cba) * combs[j].rba;
            if (new_cur > cur[a]) {
                return true;
            }
        }
    }

    return false;
}

int main() {
    scanf("%d %d %d %lf", &n, &m, &s, &v);

    for (int i = 0; i < m; ++i) {
        scanf("%d %d %lf %lf %lf %lf", &combs[i].a, &combs[i].b,
              &combs[i].rab, &combs[i].cab, &combs[i].rba,
              &combs[i].cba);
    }

    printf("%s\n", bellman_ford() ? "YES" : "NO");

    return 0;
}
