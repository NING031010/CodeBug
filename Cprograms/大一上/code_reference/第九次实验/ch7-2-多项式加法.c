/*************************
【问题描述】编写一个程序，实现两个多项式的加法运算。
要求用一个有序的链表表示一个多项式，每一项用一个结点表示。
在链表中按照项的幂数进行排列。
【输入形式】两个多项式，用空格隔开。每个多项式中没有空格。
每项的系数是浮点数，每项的指数是非负整数。每个多项式降幂排序，
已经完全合并同类项。每个多项式字符串的长度小于200。
【输出形式】结果的多项式，同样降幂排序。要求没有多余的正号，
没有多余的1的系数。系数如果不省略，则输出3位小数。
【样例输入】x^3-1.3x^2+2 1.3x^2-1.5x-1
【样例输出】x^3-1.500x+1.000
**************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct node {
	int expn;
	double coef;
	struct node *next;
} node;

// create the linked list to store the polynomial in string input
// the first node (*head) is empty
void create(node *head, char *input) {
	int i = 0, j;
	node *itr = head;
	char coef_now[20], expn_now[20];
	while (input[i] != '\0') {
		node * new_node = (node*)malloc(sizeof(node));
		new_node->next = NULL;
		itr->next = new_node;

		// get coefficient
		// input[i] should be 'x' after this part
		if (input[i] == 'x') {
			new_node->coef = 1.0;
		} else if (input[i] == '+' && input[i+1] == 'x') {
			new_node->coef = 1.0;
			i++;
		} else if (input[i] == '-' && input[i+1] == 'x') {
			new_node->coef = -1.0;
			i++;	// skip character '-'
		} else {
			j = 0;
			while (input[i] != 'x' && input[i] != '\0') {
				coef_now[j++] = input[i++];
			}
			coef_now[j] = '\0';
			new_node->coef = atof(coef_now);
		}

		// get exponent
		if (input[i] == '\0') {
			new_node->expn = 0;
			break;	// constant term must be the last term
		} else if (input[i+1] != '^') {
			new_node->expn = 1;
			i++;	// skip character 'x'
		} else {
			i += 2;	// skip character 'x', '^'
			j = 0;
			while (input[i] != '+' && input[i] != '-' && input[i] != '\0') {
				expn_now[j++] = input[i++];
			}
			expn_now[j] = '\0';
			new_node->expn = atoi(expn_now);
		}
		itr = new_node;	// nove itr for the next loop
	}
}

// res points to the result of poly1 + poly2
// the first node of res (*res) will remain empty
void add_poly(node *res, node *poly1, node *poly2) {
	if (fabs(poly1->coef) < 1e-6) {	// poly1 is 0
		res->next = poly2;
		return;
	} else if (fabs(poly2->coef) < 1e-6) {	// poly2 is 0
		res->next = poly1;
		return;
	}
	node *itr1 = poly1, *itr2 = poly2, *itr_r = res;
	while (itr1 != NULL && itr2 != NULL) {
		if (itr1->expn > itr2->expn) {	// append this term to result
			itr_r->next = itr1;
			itr1 = itr1->next;
			itr_r = itr_r->next;
		} else if (itr1->expn < itr2->expn) {
			itr_r->next = itr2;
			itr2 = itr2->next;
			itr_r = itr_r->next;
		} else {	// add their coefficients
			itr1->coef = itr1->coef + itr2->coef;
			if (fabs(itr1->coef) > 1e-6) {	// the result is not zero
				itr_r->next = itr1;
				itr_r = itr_r->next;
			}
			itr1 = itr1->next;
			itr2 = itr2->next;
		}
	}
	if (itr1 != NULL) // append the terms left in poly1 to result
		itr_r->next = itr1;
	if (itr2 != NULL)
		itr_r->next = itr2;
}

// print a polynomial from the term stored in *head
void print_poly(node *head) {
	if (head == NULL) {	// the polynomial is empty
		printf("0.000");
		return ;
	}
	node *itr = head;
	while (itr != NULL) {
		if (itr->expn == 0) {
			printf("%.3lf", itr->coef);
			break;
		} else if (itr->expn == 1) {
			if (fabs(itr->coef-1) < 1e-6) // coefficient is 1
				printf("x");
			else if (fabs(itr->coef+1) < 1e-6) // coefficient is -1
				printf("-x");
			else
				printf("%.3lfx", itr->coef);
		} else {
			if (fabs(itr->coef-1) < 1e-6) // coefficient is 1
				printf("x^%d", itr->expn);
			else if (fabs(itr->coef+1) < 1e-6) // coefficient is -1
				printf("-x^%d", itr->expn);
			else
				printf("%.3lfx^%d", itr->coef, itr->expn);
		}
		itr = itr->next;
		if (itr != NULL && itr->coef > 0)	// print the sign of the next term
			// needn't print the negative sign
			printf("+");
	}
}

int main() {
	char input1[1000], input2[1000];
	scanf("%s%s", input1, input2);
	node poly1, poly2, res;
	res.next = NULL;
	create(&poly1, input1);
	create(&poly2, input2);
	add_poly(&res, poly1.next, poly2.next);
	print_poly(res.next);
	return 0;
}