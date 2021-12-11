#include <stdio.h>
#include <stdlib.h>
#define MAX_TERM 100

typedef struct
{
	int exp;
	float coef;
}poly;
int StartA,StartB,StartD,FinishA,FinishB,FinishD;
poly term[MAX_TERM];
int avail=0;
int compare(int a,int b)
{
	if(a<b)
		return -1;
	else if(b>a)
		return 1;
	else if(a==b)
		return 0;
}
void attach(float coef,int exp)
{
	if(avail>=MAX_TERM)
	{
		printf("Too many terms");
		exit(0);
	}
	else
	{
		term[avail].coef=coef;
		term[avail].exp=exp;
		avail++;
	}

}
void padd(int StartA,int FinishA,int StartB,int FinishB)
{
	int coefficient;
	while(StartA<=FinishA && StartB<=FinishB)
	{
		switch(compare(term[StartA].exp,term[StartB].exp))
		{
			case -1:
				attach(term[StartB].coef,term[StartB].exp);
				StartB++;
				break;
			case 1:
				attach(term[StartA].coef,term[StartA].exp);
				StartA++;
				break;
			case 0:
				coefficient=term[StartA].coef + term[StartB].coef;
				attach(coefficient,term[StartB].exp);
				StartB++;
				StartA++;
				break;
		}

	}
	for(;StartA<=FinishA;StartA++)
		attach(term[StartA].coef,term[StartA].exp);
	for(;StartB<=FinishB;StartB++)
		attach(term[StartB].coef,term[StartB].exp);
	FinishD=avail-1;
}
void printpoly(int StartA,int FinishA,int StartB,int FinishB)
{
	printf("\nPoly 1\n\n");
	for(StartA;StartA<=FinishA;StartA++)
	{
		printf("%.1fx^%d",term[StartA].coef,term[StartA].exp);
		if(StartA!=FinishA)
			printf(" + ");
	}
	printf("\n\n\nPoly 2\n\n");
	for(StartB;StartB<=FinishB;StartB++)
	{
		printf("%.1fx^%d",term[StartB].coef,term[StartB].exp);
		if(StartB!=FinishB)
			printf(" + ");
	}
}
void printpolysum(int StartD,int FinishD)
{
	printf("\nSum Poly\n\n");
	for(StartD;StartD<=FinishD;StartD++)
	{
		printf("%.1fx^%d",term[StartD].coef,term[StartD].exp);
		if(StartD!=FinishD)
			printf(" + ");
	}
}
int main()
{

	int t1,t2,i,j;
	StartA=avail;
	printf("Enter the number of terms of poly 1:");
	scanf("%d",&t1);
	printf("Enter the number of terms of poly 2:");
	scanf("%d",&t2);
	printf("Enter coefficient and exponents of each term");
	for(i=0;i<t1;i++)
	{
		scanf("%f %d",&term[i].coef,&term[i].exp);
	}
	FinishA=i-1;
	StartB=i;
	printf("Enter coefficient and exponents of each term");
	for(j=0;j<t2;j++)
	{
		scanf("%f %d",&term[i+j].coef,&term[i+j].exp);
	}
	FinishB=i+j-1;
	StartD=i+j;
	avail=StartD;
	padd(StartA,FinishA,StartB,FinishB);
	printpoly(StartA,FinishA,StartB,FinishB);
	printf("\n\n");
	printpolysum(StartD,FinishD);
	printf("\n\n");
	return 0;
}