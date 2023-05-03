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

#include <stdio.h>
#include <stdlib.h>

int main(){
    int m, n, k;
    scanf("%d %d %d", &m, &n, &k);
    char ** life;
    life = (char **) malloc((m + 2) * sizeof (char *));

    for (int i = 0; i < m + 2; i++){
        life[i] = (char *) malloc((n + 2) * sizeof(char ));
        for (int j = 0; j < n + 2; j++){
            if (i == 0 || i == (m + 1) || j == 0 || j == (n + 1)){
                life[i][j] = -1;
            }
            else{
                life[i][j] = 0;
            }
        }
    }
    for (int i = 0; i < k; i++){
        int x, y;
        scanf("%d %d", &x, &y);
        life[x][y] = 1;
    }
    int cnt_str = 0;
    int cnt_single = 0;
    int cnt_stolb = 0;
    for (int i = 1; i < m + 1; i++){
        int ind = 1;
        int max_tmp = 0;
        while (ind < n + 1){
            if (life[i][ind] == 0){
                max_tmp ++;
                if (max_tmp == 1){
                    if (life[i][ind - 1] != 0 && life[i][ind + 1] != 0 && life[i + 1][ind] != 0 && life[i - 1][ind] != 0){
                        cnt_single ++;
                    }
                }
                if (life[i][ind + 1] != 0 && max_tmp > 1)
                    cnt_str++;
            }
            else{
                max_tmp = 0;
            }
            ind++;
        }
    }

    for (int j = 1; j < n + 1; j++){
        int ind = 1;
        int max_tmp = 0;

        while (ind < m + 1){
            if (life[ind][j] == 0){
                max_tmp ++;
                if (life[ind + 1][j] != 0 && max_tmp > 1)
                    cnt_stolb++;
            }
            else{
                max_tmp = 0;
            }
            ind++;
        }

    }
    printf("%d \n", cnt_single+cnt_stolb+cnt_str);
    free(life);
}
