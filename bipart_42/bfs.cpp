#include <iostream>
#include <cstdio>

using namespace std;

class PQ {
public:
	PQ();
	~PQ();
	void Insert(pair<int, pair<int, int> > x);
	pair<int, pair<int, int> > Delete();
	int isEmpty();

	int s;
	pair<int, pair<int, int> > Arr[1000];
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

void PQ::Insert(pair <int, pair<int, int> > x)
{
	int i, parent;
	pair <int, pair<int, int> > temp;

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

pair <int, pair<int, int> > PQ::Delete()
{
	int i, j, k, p;
	pair <int, pair<int, int> > rt, temp;
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

pair <int, int> LK[100][100]; // from to
int S[100]; // number of link from node
int D[100];
int R[100]; // 0: not visited, 1: red, 2: blue

int n, m;

int main()
{
	char c;
	int		i;
	int		p, q, r, color;
	PQ		Q;
	pair <int, pair<int, int> > t, pkt; // weight, nodenum, nodecolor
	// pair <int, int> t, pkt; // weight, nodenum
	int mycolor;
	int nextcolor;
	int changemycolor;
	int fail;

	r = 1; // bfs처럼쓰기위해 가중치 1로 통일
	scanf("%d %d", &n, &m);
	for (i = 1; i < n; i++)
		S[i] = 0;
	for (i = 1; i <= m; i++)
	{
		scanf("%d %d", &p, &q);
		S[p]++;
		LK[p][S[p]].first = q;
		LK[p][S[p]].second = r;
	}
	for (i = 1; i <= n; i++)
	{
		D[i] = 10000;
		R[i] = 0;
	}
	mycolor = 1;
	pkt.first = 0; // weight 0
	pkt.second.first = 1; // 1 node
	pkt.second.second = mycolor;
	fail = 0;
	Q.Insert(pkt);
	while (Q.isEmpty() == 0)
	{
		t = Q.Delete();
		r = t.first;
		q = t.second.first;
		color = t.second.second;
		if (color == 1)
			mycolor = 2;
		else
			mycolor = 1;
		if (R[q] == 1 || R[q] == 2)
		{
			if (R[q] != mycolor) {
				fail = 1;
			}
		}
		else {
			R[q] = mycolor;
			D[q] = r;
			for (i = 1; i <= S[q]; i++)
			{
				pkt.first = D[q] + LK[q][i].second; //distance + weight
				pkt.second.first = LK[q][i].first; //node number
				pkt.second.second = mycolor;
				Q.Insert(pkt); // 추가할때 니 색을 뭐다라는거만 추가해줘
			}
		}
	}
	if (fail == 1)
		printf("No\n");
	else
		printf("Yes\n");
	return 0;
}

