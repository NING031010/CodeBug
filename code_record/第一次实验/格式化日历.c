#include <stdio.h>

int isLeap(int year) { // leap year ?
    if (year % 400 == 0) {
        return 1;
    }
    if (year % 4 == 0) {
        if (year % 100 != 0) {
            return 1;
        }
    }
    return 0;
}

// 0 -sun, 1-mon, 2-tue, 3-wed, 4-thu, 5-fri, 6-sat
int zeller(int year, int month, int day) {
    if (month <= 2) {
        month += 12;
        year -= 1;
    }
    int c = year / 100;
    int y = year % 100;
    int w = c / 4 - 2 * c + y + y / 4 + 13 * (month + 1) / 5 + day - 1;
    return (w % 7 + 7) % 7;
}

int main() {
    int monthday[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int year, month;
    
    scanf("%d %d", &year, &month);
    printf("Sun   Mon   Tur   Wed   Thu   Fri   Sat   \n");
    int weekday_1 = zeller(year, month, 1);

    int i;
    for (i = 0; i < weekday_1; i++) {
        printf("      ");
    }
    int maxday = monthday[month]; // 一个月的天数
    if (month == 2) {
        maxday += isLeap(year);
    }
    int wd = weekday_1;
    for (i = 1; i <= maxday; i++) {
        printf("%2d    ", i);
        if (wd == 6 && i < maxday) {
            printf("\n");
        }
        wd = (wd + 1) % 7;
    }
    return 0;
}

