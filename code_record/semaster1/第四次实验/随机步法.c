#include <stdio.h>
#include <stdlib.h>

/*
0 1 2 3
u r d l
*/
int di[4] = {-1, 0, 1, 0};
int dj[4] = {0, 1, 0, -1};

#define N 10


int isUnvalid(char map[N][N], int posi, int posj, int dir) {
	// if a direction cannot walk
	posi += di[dir];
	posj += dj[dir];
	if (posi < 0 || posi >= N || posj < 0 || posj >= N) {
		return 1;
	}
	if (map[posi][posj] == '.') {
		return 0;
	}
	else {
		return 1;
	}
}

int step(char map[N][N], int posi, int posj, char label, int dir) {
	// 返回最终走的方向，走失败则返回-1 
	int fail = 0;
	while (isUnvalid(map, posi, posj, dir)) {
		
		fail++;
		if (fail >= 4) {
			return -1; // no directions can walk
		}
		dir = (dir + 1) % 4;
	}
	posi += di[dir];
	posj += dj[dir];
	map[posi][posj] = label;
	return dir;
}

int main() {
	char map[N][N];
	int i, j;
	// 初始化
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			map[i][j] = '.';
		}
	}
	int posi, posj;
	scanf("%d %d", &posi, &posj);
	int seed = posi + 10 * posj;
	srand(seed);
	char cur = 'A';
	map[posi][posj] = 'A';
	for (i = 1; i < 26; i++) {
		cur++;
		int dir = rand() % 4;
		int success = step(map, posi, posj, cur, dir);
		if (success < 0) {
			break;
		}
		posi += di[success];
		posj += dj[success];
	}
	
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			printf("%c ", map[i][j]);
		}
		printf("\n");
	}
	return 0;
}




