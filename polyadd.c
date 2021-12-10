#include <stdio.h>
#include <stdlib.h>

#define MAX_TERM 100

typedef struct
{
	float coeff;
	int exp;
} polynomial;

polynomial term[MAX_TERM];

int avail = 0;

int COMPARE(int a, int b)
{
	if (a > b)
		return -1;

	if (a == b)
		return 0;

	if (a < b)
		;
	return 1;
}

void attach(float coeff, int exp)
{
	if (avail >= MAX_TERM)
	{
		printf("OVERFLOW");
		exit(0);
	}
	term[avail].coeff = coeff;
	term[avail].exp = exp;
	avail++;
}

void polyIn(int *startA, int *startB, int *finishA, int *finishB)
{
	int n, i;
	float temp;
	*startA = avail;
	printf("How many terms in first polynomial?: ");
	scanf("%d", &n);
	printf("Enter %d terms: \n", n);
	for (i = 0; i < n; i++)
	{
		printf("Term %d Coefficient: ", i + 1);
		scanf("%f", &temp);
		if (temp == 0)
		{
			printf("Power skipped!\n");
			continue;
		}
		else
			term[avail].coeff = temp;
		printf("Term %d Exponent: ", i + 1);
		scanf("%d", &term[avail].exp);
		avail++;
	}

	*finishA = avail - 1;
	*startB = avail;
	printf("How many terms in second polynomial?: ");
	scanf("%d", &n);
	printf("Enter %d terms: \n", n);
	for (i = 0; i < n; i++)
	{
		printf("Term %d Coefficient: ", i + 1);
		scanf("%f", &temp);
		if (temp == 0)
		{
			printf("Power skipped!\n");
			continue;
		}
		else
			term[avail].coeff = temp;
		printf("Term %d Exponent: ", i + 1);
		scanf("%d", &term[avail].exp);
		avail++;
	}
	*finishB = avail - 1;
}

void padd(int startA, int startB, int finishA, int finishB, int *startC, int *finishC)
{

	float coefficient;
	int exponent;
	*startC = avail;
	while (startA <= finishA && startB <= finishB)
	{
		switch (COMPARE(term[startA].exp, term[startB].exp))
		{

		case -1:
			coefficient = term[startA].coeff;
			exponent = term[startA].exp;
			startA++;
			break;
		case 0:
			coefficient = term[startA].coeff + term[startB].coeff;
			exponent = term[startA].exp;
			startA++;
			startB++;
			break;
		case 1:
			coefficient = term[startB].coeff;
			exponent = term[startB].exp;
			startB++;
			break;
		}

		attach(coefficient, exponent);
	}

	for (; startA <= finishA; startA++)
		attach(term[startA].coeff, term[startA].exp);

	for (; startB <= finishB; startB++)
		attach(term[startB].coeff, term[startB].exp);

	*finishC = avail - 1;
}

void disp(int start, int finish)
{
	while (start <= finish)
	{
		printf("%.1fx^%d", term[start].coeff, term[start].exp);
		start++;
		if (start <= finish)
			printf(" + ");
	}
	printf("\n");
}

int main()
{
	int startA, startB, startC, finishA, finishB, finishC;

	polyIn(&startA, &startB, &finishA, &finishB);
	padd(startA, startB, finishA, finishB, &startC, &finishC);
	disp(startC, finishC);

	return 0;
}
