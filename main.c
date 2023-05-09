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
/*#include <stdbool.h>
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
*/

//1806 частично спизженно
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


#define N 50010


typedef struct {
    int v, w, next;
}edge;

typedef struct {
    int d, prev;
}mpa;

typedef struct{
    long long val;
    int num;
}vertex;

typedef struct {
    int d, v;
} ve;
//heap
bool b[N];
ve h[N*200]; int hn;
int dp[N];
mpa d[N];
edge e[N*200];
int cost[10], n, head[N], m, t[N], nt;
vertex v[N];

int find(long long vx) {
    int p1 = 1, p2 = n, pm;

    while ( p1 <= p2 ) {
        pm = (p1 + p2)/2;
        if ( v[pm].val > vx )
            p2 = pm-1;
        else if ( v[pm].val < vx )
            p1 = pm+1;
        else
            return pm;
    }

    return 0;
}

void add(int v1, int v2) {
    long long t = 1000000000;
    int k = 0;
    while (((v[v1].val/t)%10) == ((v[v2].val/t)%10)) {
        k++;
        t /= 10;
    }

    m++;
    e[m].v = v2;
    e[m].next = head[v1];
    e[m].w = cost[k];
    head[v1] = m;

    m++;
    e[m].v = v1;
    e[m].next = head[v2];
    e[m].w = cost[k];
    head[v2] = m;
}
void swap(vertex* xp, vertex* yp)
{
    vertex temp = *xp;
    *xp = *yp;
    *yp = temp;
}


void hup(int p) {
    int v = h[p].v;

    dp[v] = 1;
    while ( p > 1 ) {
        if ( h[p].d < h[p/2].d ) {
            dp[h[p/2].v] = p;
            int c = h[p].v;
            h[p].v = h[p/2].v;
            h[p/2].v = c;

            c = h[p].d;
            h[p].d = h[p/2].d;
            h[p/2].d = c;

            p /= 2;

        } else {
            dp[v] = p;
            break;
        }
    }
    return;
}

void hdown() {
    int p = 1;
    int v = h[p].v;
    //dp[v] = hn;
    while (p <= hn) {
        if ((p*2 <= hn) && (( h[p*2].d <= h[p*2+1].d ) || (p*2 == hn)) && ( h[p*2].d < h[p].d)) {
            dp[h[p*2].v] = p;
            int c = h[p].v;
            h[p].v = h[p*2].v;
            h[p*2].v = c;
            c = h[p].d;
            h[p].d = h[p*2].d;
            h[p*2].d = c;

            p = p*2;
        } else if ((p*2+1 <= hn) && (h[p*2+1].d <= h[p*2].d) && (h[p*2+1].d < h[p].d)){
            dp[h[p*2+1].v] = p;
            int c = h[p].v;
            h[p].v = h[p*2+1].v;
            h[p*2+1].v = c;
            c = h[p].d;
            h[p].d = h[p*2+1].d;
            h[p*2+1].d = c;

            p = p*2 + 1;
        } else {
            dp[v] = p;
            break;
        }

    }

    return;
}

int comparator(const void* v1, const void* v2){
    vertex *k = (vertex *)v1;
    vertex *m = (vertex *)v2;
    if (k->val < m->val)
        return -1;
    else if(k->val > m->val)
        return 1;
    else
        return 0;

}
//spizhenny algoritm
void SwampPebbleSort(vertex *arr, int size)
{
    for (int j = 0; j < size - 1; j++)
    {
        if (arr[j].val > arr[j + 1].val)
        {
            vertex t = arr[j + 1];
            arr[j + 1] = arr[j];
            arr[j] = t;
            for (int v = j; v > 0; v--)
            {
                if (arr[v].val < arr[v - 1].val)
                {
                    t = arr[v - 1];
                    arr[v - 1] = arr[v];
                    arr[v] = t;
                }
                else break;
            }
        }
    }

}

int main() {
    scanf("%d", &n);
    for ( int i = 0; i <= 9; i++ )
        scanf("%d", &cost[i]);

    for ( int i = 1; i <= n; i++ ) {
        scanf("%lld", &v[i].val);
        v[i].num = i;
    }

    SwampPebbleSort(v, n+1);

    for ( int i = 1; i <= n; i++ ) {
        long long base = 1;
        for ( int j = 0; j <= 9; j++ ) {

            long long digit = (v[i].val/base)%10;

            long long base2 = 1;

            for ( int k = 0; k <= 9; k++ ) {
                long long vx;
                if ( k != digit ) {

                    vx = v[i].val - base*digit + base*k;

                    int p = find(vx);
                    if ( p > 0 )
                        add(p, i);

                }

                long long digit2 = (v[i].val/base2)%10;
                if (( k > j ) && (digit != digit2)) {
                    vx = v[i].val - base*digit + base*digit2 - base2*digit2 + base2*digit ;

                    int p = find(vx);
                    if (p > 0)
                        add(p, i);

                }

                base2 *= 10;
            }

            base *= 10;
        }

    }

    for ( int i = 1; i <= n; i++ ) {
        d[i].d = 1000000000;
        if ( v[i].num == 1 ) {
            h[1].v = i;
            h[1].d = 0;
            d[i].d = 0;
            dp[i] = 1;
        }
    }

    hn = 1;
    for ( int k = 1; k <= n; k++ ) {
        int v = h[1].v;
        if (( v > 0 ) && (hn >= 1)) {
            int j = head[v];
            while ( j > 0 ) {
                if ( d[v].d + e[j].w < d[e[j].v].d ) {
                    d[e[j].v].d = d[v].d + e[j].w;
                    d[e[j].v].prev = v;
                    if (dp[e[j].v] == 0 ) {
                        hn++;
                        h[hn].v = e[j].v;
                        h[hn].d = d[e[j].v].d;
                        hup(hn);
                    } else {
                        h[dp[e[j].v]].d = d[e[j].v].d;
                        hup(dp[e[j].v]);
                    }
                }
                j = e[j].next;
            }
            h[1].v = h[hn].v;
            h[1].d = h[hn].d;
            hn--;
            hdown();
        } else
            break;
    }

    int p = 0;
    for ( int i = 1; i <= n; i++ )
        if ( v[i].num == n ) {
            p = i;
            break;
        }

    int ans = -1;
    nt = 0;
    if ( d[p].d != 1000000000 ) {
        ans = d[p].d;
        int j = p;
        while (j > 0 ) {
            nt++;
            t[nt] = v[j].num;
            j = d[j].prev;
        }
    }

    printf("%d\n", ans);
    if ( ans != -1 ) {
        printf("%d\n", nt);
        for ( int i = nt; i >= 1; i-- )
            printf("%d ", t[i]);
    }
    return 0;
}
