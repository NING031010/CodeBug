#include <stdio.h>
#include <stdlib.h>

char cards_str[20];
char suit[5];
int cards[5] = {0};

// 按等级排序
void sort()
{
    int temp;
    for (int i = 0; i < 4; i++)
    {
        for (int j = i + 1; j < 5; j++)
        {
            if (cards[j] < cards[i])
            {
                temp = cards[i];
                cards[i] = cards[j];
                cards[j] = temp;
            }
        }
    }
}

// 判断牌型
void judge()
{
    for (int i = 0; i < 5; i++)
    {
        if (cards[i] == 0)
        {
            printf("Invalid\n");
            return;
        }
        if (suit[i] != 'D' && suit[i] != 'C' && suit[i] != 'H' && suit[i] != 'S')
        {
            printf("Invalid\n");
            return;
        }
        for (int j = i + 1; j < 5; j++)
        {
            if (cards[i] == cards[j] && suit[i] == suit[j])
            {
                printf("Invalid\n");
                return;
            }
        }
    }
    sort();
    bool flush = false;
    bool straight = false;
    if (suit[0] == suit[1] && suit[0] == suit[2] && suit[0] == suit[3] && suit[0] == suit[4])
    {
        flush = true;
    }

    if ((cards[0] == cards[1] - 1) &&
        (cards[1] == cards[2] - 1) &&
        (cards[2] == cards[3] - 1) &&
        (cards[3] == cards[4] - 1))
    {
        straight = true;
    }

    if (flush && straight)
    {
        printf("Straight Flush\n");
        return;
    }
    else if (cards[0] == cards[3] || cards[1] == cards[4])
    {
        printf("Four of A Kind\n");
    }
    else if ((cards[0] == cards[2] && cards[3] == cards[4]) || (cards[0] == cards[1] && cards[2] == cards[4]))
    {
        printf("Full House\n");
    }
    else if (flush)
    {
        printf("Flush\n");
    }
    else if (straight)
    {
        printf("Straight\n");
    }

    else if (cards[0] == cards[2] || cards[1] == cards[3] || cards[2] == cards[4])
    {
        printf("Three of A Kind\n");
    }

    else if ((cards[0] == cards[1] && cards[2] == cards[3]) || (cards[0] == cards[1] && cards[3] == cards[4]) || (cards[1] == cards[2] && cards[3] == cards[4]))
    {
        printf("Two Pairs\n");
    }
    else if (cards[0] == cards[1] || cards[1] == cards[2] || cards[2] == cards[3] || cards[3] == cards[4])
    {
        printf("Pair\n");
    }
    else
    {
        printf("Other\n");
    }
    return;
}

int main()
{
    while (1)
    {
        gets(cards_str);
        if (cards_str[0] == '0')
        {
            break;
        }
        for (int i = 0; i < 5; i++)
        {
            suit[i] = cards_str[3 * i];
            cards[i] = 0;
            switch (cards_str[3 * i + 1]) // 将等级转换为数字
            {
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                cards[i] += cards_str[3 * i + 1] - '0';
                break;
            case 'T':
                cards[i] += 10;
                break;
            case 'J':
                cards[i] += 11;
                break;
            case 'Q':
                cards[i] += 12;
                break;
            case 'K':
                cards[i] += 13;
                break;
            case 'A':
                cards[i] += 1;
                break;
            default:
                break;
            }
        }
        judge();
    }

    system("pause");
}