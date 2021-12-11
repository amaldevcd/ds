#include <stdio.h>
int val1,val2,sumcount;
void input(int r1,int c1,int mat[r1][c1])
{
	for(int i=0;i<r1;i++)
	{
		for(int j=0;j<c1;j++)
		{
			scanf("%d",&mat[i][j]);
		}
	}
}


int zerocount(int r1,int c1,int mat[r1][c1])
{
	int count=0;
	for(int i=0;i<r1;i++)
	{
		for(int j=0;j<c1;j++)
		{
			if(mat[i][j]!=0)
				count++;
		}
	}
	return count;
}

struct sparse
{	
	int row,col,val;
}s1[20],s2[20],s1t[20],s2t[20],sum[20];


void sparseconv(int r1, int c1,int mat[r1][c1],struct sparse s1[30],int value)
{
	
	int k=1;
	s1[0].row=r1;
	s1[0].col=c1;
	s1[0].val=value;
	for(int i=0;i<r1;i++)
	{
		for(int j=0;j<c1;j++)
		{
			if(mat[i][j]!=0)
				{
					s1[k].row=i;
					s1[k].col=j;
					s1[k].val=mat[i][j];
					k++;
				}
		}
	}
}


void printsparse(struct sparse s1[30],int value)
{
	for(int i=0;i<=value;i++)
	{
		printf("%d %d %d\n",s1[i].row,s1[i].col,s1[i].val);
	}
}

void sparsetrans(struct sparse s1t[20],struct sparse s1[20],int value,int r1,int c1)
{
	int k=1;
	s1t[0].col=c1;
	s1t[0].row=r1;
	s1t[0].val=value;
	for(int i=0;i<=value;i++)
	{
		for(int j=1;j<=value;j++)
		{
			if(i==s1[j].col)
			{
				s1t[k].row=s1[j].col;
				s1t[k].col=s1[j].row;
				s1t[k].val=s1[j].val;
				k++;
			}
		}
	}
}
void printsparsetrans(struct sparse s1t[20],int value)
{
	for(int i=0;i<=value;i++)
	{
		printf("%d %d %d\n",s1t[i].row,s1t[i].col,s1t[i].val);
	}
}
void sumsp()
{
	int a = 1, b = 1, cnt = 1;
	sum[0].row = s1[0].row;
	sum[0].col = s1[0].col;
	while (a <= s1[0].val && b <= s2[0].val)
	{
		if (s1[a].row < s2[b].row)
		{
			sum[cnt].row = s1[a].row;
			sum[cnt].col = s1[a].col;
			sum[cnt].val = s1[a].val;
			cnt++;
			a++;
		}
		else if (s1[a].row > s2[b].row)
		{
			sum[cnt].row = s2[b].row;
			sum[cnt].col = s2[b].col;
			sum[cnt].val = s2[b].val;
			cnt++;
			b++;
		}

		else if (s1[a].row == s2[b].row)
		{
			if (s1[a].col < s2[b].col)
			{
				sum[cnt].row = s1[a].row;
				sum[cnt].col = s1[a].col;
				sum[cnt].val = s1[a].val;
				cnt++;
				a++;
			}

			else if (s1[a].col > s2[b].col)
			{
				sum[cnt].row = s2[b].row;
				sum[cnt].col = s2[b].col;
				sum[cnt].val = s2[b].val;
				cnt++;
				b++;
			}

			else if (s1[a].col == s2[b].col)
			{
				if (s1[a].val + s2[b].val == 0)
				{
					a++;
					b++;
					continue;
				}
				sum[cnt].row = s1[a].row;
				sum[cnt].col = s1[a].col;
				sum[cnt].val = s1[a].val + s2[b].val;
				cnt++;
				a++;
				b++;
			}
		}
	}
	if(a==s1[0].val)
	{
		sum[cnt].row=s1[a].row;
		sum[cnt].col=s1[a].col;
		sum[cnt].val=s1[a].val;
		a++;
		cnt++;
	}
	if(b==s2[0].val)
	{
		sum[cnt].row=s2[b].row;
		sum[cnt].col=s2[b].col;
		sum[cnt].val=s2[b].val;
		b++;
		cnt++;
	}
	sum[0].val = cnt-1;
	sumcount=cnt;
	
}

void sumprint()
{
	
	for(int i=0;i<sumcount;i++)
	{
		printf("%d %d %d\n",sum[i].row,sum[i].col,sum[i].val);
	}
}
int main()
{
	int r1,c1,r2,c2;
	printf("Enter the row and column of MAT1 :");
	scanf("%d %d",&r1,&c1);
	printf("Enter the row and column of MAT2 :");
	scanf("%d %d",&r2,&c2);
	int mat1[r1][c1],mat2[r2][c2];
	printf("Enter elements into Matrix 1\n");
	input(r1,c1,mat1);
	printf("Enter elements into Matrix 2\n");
	input(r2,c2,mat2);
	val1=zerocount(r1,c1,mat1);
	val2=zerocount(r2,c2,mat2);
	sparseconv(r1,c1,mat1,s1,val1);
	sparseconv(r2,c2,mat2,s2,val2);
	printf("\n\n");
	printf("Tupple form 1\n");
	printsparse(s1,val1);
	printf("\n\n");
	printf("Tupple form 2\n");
	printsparse(s2,val2);
	sparsetrans(s1t,s1,val1,r1,c1);
	sparsetrans(s2t,s2,val2,r2,c2);
	printf("\n\n");
	printf("Transpose Tupple\n");
	printsparsetrans(s1t,val1);
	printf("\n\n");
	printf("Transpose Tupple\n");
	printsparsetrans(s2t,val2);
	printf("\n\n");
	sumsp();
	printf("\n\n");
	printf("Sum Tupple\n");
	sumprint();
	return 0;
}