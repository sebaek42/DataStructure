#include <iostream>
#include <cstdio>

using namespace std;

class PQ {
public:
	PQ();
	~PQ();
	void Insert(pair<int, int> x);
	pair<int, int> Delete();
	int isEmpty();
	void print(int c, int depth, int lr);

	int s;
	pair<int, int> Arr[1000];
};

PQ::PQ()
{
	s = 0;
}

PQ::~PQ()
{
}

int PQ::isEmpty()
{
	return s == 0;
}

void PQ::Insert(pair <int, int> x)
{
	int i, parent;
	pair <int, int> temp;

	s++;
	Arr[s] = x;
	i = s;
	while (i > 1)
	{
		parent = i / 2;
		if (Arr[parent] > Arr[i])
		{
			temp = Arr[parent];
			Arr[parent] = Arr[i];
			Arr[i] = temp;
			i = parent;
		}
		else
		{
			break ;
		}

	}
}

pair <int, int> PQ::Delete()
{
	int i, j, k, p;
	pair <int, int> rt, temp;
	rt = Arr[1];
	Arr[1] = Arr[s];
	s--;
	i = 1;
	while (1)
	{
		j = i * 2;
		k = i * 2 + 1;
		if (j > s)
			break ;
		if (k > s)
		{
			if (Arr[i] > Arr[j]) {
				temp = Arr[i];
				Arr[i] = Arr[j];
				Arr[j] = temp;
				i = j;
			}
			else {
				break ;
			}
		}
		else {
			if (Arr[i] > Arr[j] || Arr[i] > Arr[k]) {
				if (Arr[j] < Arr[k])
					p = j;
				else
					p = k;
				temp = Arr[i];
				Arr[i] = Arr[p];
				Arr[p] = temp;
				i = p;
			}
			else
				break ;
		}
	}

	return rt;
}

void PQ::print(int C, int depth, int LR)
{
	if (s == 0)
	{
		printf("---\n");
		return ;
	}
	if (depth == 0)
		C = 1;
	if (LR == 1) {
		int i;
		for (i = 0; i < depth; i++)
			printf("           ");
	}
	printf("---%03d, %03d", Arr[C].first, Arr[C].second);
	if (C * 2 <= s)
		print(C*2, depth+1, 0);
	else printf("\n");
	if (C*2 + 1 <= s)
		print(C*2 + 1, depth+1, 1);
	else ;
	return ;
}

int main()
{
	PQ		Q;
	char	com;
	pair <int, int> x;

	while (1)
	{
		Q.print(1, 0, 0);
		scanf(" %c", &com);
		if (com == 'q')
			break ;
		else if (com == 'i')
		{
			scanf("%d %d", &x.first, &x.second);
			Q.Insert(x);
		}
		else if (com == 'd')
		{
			x = Q.Delete();
			printf("Got %d %d\n", x.first, x.second);
		}
		else
			printf("???\n");
	}
	return 0;
}
// 노드 개수 엣지 개수
//1에서 2로 가는 4길이
// 1에서 3로 가는 2길이
// ...
