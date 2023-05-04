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

