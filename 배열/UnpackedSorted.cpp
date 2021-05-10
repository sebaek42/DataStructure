#include <iostream>
#include <cstdio>

using namespace std;

int lef, rig;
// l ~ r 까지 이진탐색. 내려가는 로직은 같음. 못찾으면 -1 리턴 맞고. 찾았을때 1을 리턴하는데
int Search(int a[], int b[], int n, int x)
{
	int l, r, m;

	l = 0;
	r = n - 1;
	while (l <= r)
	{
		m = (l + r) / 2;
		if (a[m] == x)
			if (b[m] == 0) // 찾았는데 안쓰는자리면 -1 리턴
			{
				lef = m;
				rig = m + 1;
				return -1;
			}
			else
				return m;
		else if (a[m] < x)
		{
			l = m + 1;
		}
		else
		{
			r = m - 1;
		}
	}
	lef = r;
	rig = l;
	return -1;
}

int Insert(int a[], int b[], int &n, int x) // case가 좀 많음.
{
	int i;
	if (Search(a, b, n, x) == -1) // 탐색실패..기존에 없거나 brr에 0으로 안쓴다고 표기된경우
	{
		if (lef >= 0 && a[lef] == x)
		{
			b[lef] = 1;
			return 0; // 있는데 안쓴다고 표기된경우 0리턴
		}
		else
		{
			if (rig == n)
			{
				a[rig] = x;
				b[rig] = 1;
				n++;
				return 1;
			}
			else if (b[rig] == 1)
			{
				for (i = n - 1; i >= rig; i--)
				{
					a[i + 1] = a[i];
					b[i + 1] = b[i];
				}
				a[rig] = x;
				b[rig] = 1;
				n++;
				return 1;
			}
			else
			{
				a[rig] = x;
				b[rig] = 1;
				return 0;
			}
		}
	}
	return 0;
}

int Delete(int a[], int b[], int &n, int x)
{
	int i, j;

	i = Search(a, b, n, x);
	if (i == -1)
		return -1;
	else
	{
		b[i] = 0; // 그냥 안쓰는걸로 표시하면 끝나지
		return 0;
	}
	return 0;
}

int main()
{
	int arr[100], brr[100];
	int n = 0;
	int S = 100;
	int i, in, x;
	char com;
	for (i = 0; i < S; i++)
		arr[i] = -1;
	for (i = 0; i < S; i++)
		brr[i] = 0;
	arr[0] = 1; arr[1] = 5; arr[2] = 8; n = 3; // 몇 번 칸까지 썼었다
	brr[0] = 1; brr[1] = 0; brr[2] = 1; // 1이면 사용하는칸 0이면 사용안하는칸
	while (1)
	{
		for (i = 0; i <= n; i++)
		{
			printf("|%4d", i);
		}
		printf("|\n");
		for (i = 0; i <= n; i++)
		{
			printf("|%4d", arr[i]);
		}
		printf("|\n");
		for (i = 0; i <= n; i++)
		{
			printf("|%4d", brr[i]);
		}
		printf("|\n\n");
		scanf(" %c", &com);
		if (com == 'q')
			break;
		else if (com == 's')
		{
			scanf("%d", &x);
			in = Search(arr, brr, n, x);
			if (in == -1)
				printf("Not Found. left = %d, right = %d\n\n", lef, rig);
			else
				printf("Found at index %d\n\n", in);
		}
		else if (com == 'i')
		{
			scanf("%d", &x);
			Insert(arr, brr, n, x);
		}
		else if (com == 'd')
		{
			scanf("%d", &x);
			Delete(arr, brr, n, x);
		}
		else
		{
			printf("???\n");
		}
	}
	return 0;
}
