// recursive function with memory
#include <stdio.h>
#include <stdlib.h>
#define N 101

int input[N];
int memory[N][N][3];

void second_turn(int, int, int *);

// the first player take his turn,
// and left numbers are input[begin]-input[end]
// local_res is actually the return value,
// which stores each player's socre gained during selecting input[begin]-input[end]
void first_turn(int begin, int end, int *local_res) {
    if (memory[begin][end][2] == 1) {
        local_res[0] = memory[begin][end][0];
        local_res[1] = memory[begin][end][1];
        return;
    }
    if (begin == end) {
        local_res[0] = input[begin];
        local_res[1] = 0;
        return;
    }
    int next_res1[2];
    second_turn(begin+1, end, next_res1);
    int next_res2[2];
    second_turn(begin, end-1, next_res2);
    int t1 = next_res1[0] + input[begin];
    int t2 = next_res2[0] + input[end];
    if (t1 >= t2) { // select input[begin]
        local_res[0] = t1;
        local_res[1] = next_res1[1];
    } else {        // select input[end]
        local_res[0] = t2;
        local_res[1] = next_res2[1];
    }
    memory[begin][end][0] = local_res[0];
    memory[begin][end][1] = local_res[1];
    memory[begin][end][2] = 1;
}

void second_turn(int begin, int end, int *local_res){
    if (memory[begin][end][2] == 1) {
        local_res[0] = memory[begin][end][0];
        local_res[1] = memory[begin][end][1];
        return;
    }
    if (begin == end) {
        local_res[1] = input[begin];
        local_res[0] = 0;
        return;
    }
    int next_res1[2];
    first_turn(begin+1, end, next_res1);
    int next_res2[2];
    first_turn(begin, end-1, next_res2);
    int t1 = next_res1[1] + input[begin];
    int t2 = next_res2[1] + input[end];
    if (t1 >= t2) {
        local_res[1] = t1;
        local_res[0] = next_res1[0];
    } else {
        local_res[1] = t2;
        local_res[0] = next_res2[0];
    }
    memory[begin][end][0] = local_res[0];
    memory[begin][end][1] = local_res[1];
    memory[begin][end][2] = 1;
}

int main(){
    int n, i;
    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        scanf("%d", &input[i]);
    }
    int res[2];
    first_turn(1, n, res);
    printf("%d %d\n", res[0], res[1]);
    return 0;
}