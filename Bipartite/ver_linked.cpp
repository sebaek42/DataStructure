#include <iostream>
#include <cstdio>

// insert만하고 순서대로만. 소팅x
using namespace std;

class Node
{
public:
	int a;
	Node *n;
};

class List
{
public:
	void Zero(); // 처음으로 돌아감
	int Next();
	Node *head;
	Node *curr;
	int Z;
	List();
	int Insert(int x);
};

List::List()
{
	head = NULL;
	curr = head;
}

int List::Insert(int x)
{
	Node *NN;
	NN = new Node;
	NN->a = x;	  // 값을 넣고
	NN->n = head; // head의 이전에 넣음. 즉 맨 앞에 넣는다는거.
	head = NN;	  // 새로 생긴 NN이 이제 곧 head가 됨
	return 1;
}

void List::Zero()
{
	Z = 1;
}

int List::Next() // 이걸 호출할때 curr가 null인 상태면 안됨
{
	if (Z == 1)
	{
		Z = 0;
		curr = head;
	}
	else
		curr = curr->n;
	if (curr == NULL)
		return 0;
	return curr->a; // 이게 null이면 다음 Next()는 호출 불가. 노드번호 리턴. 노드번호가 0이면 없는거니까 있는동안 계속가게될거임!
}

int V[1000]; // 0: 방문안함  1: 빨강  2: 파랑  => bipartite 보려고 색칠하는거임. 인접한게 같은 색이면 안돼니까
List LK[1000];
int SK[1000];
int SP; // stack pointer

void Push(int x)
{
	SK[SP] = x;
	SP++;
}

int Pop()
{
	SP--;
	return SK[SP];
}

bool isEmpty()
{
	return SP == 0;
}

int SKC[1000];
int SPC; // stack pointer

void PushC(int x)
{
	SKC[SPC] = x;
	SPC++;
}

int PopC()
{
	SPC--;
	return SKC[SPC];
}

bool isEmptyC()
{
	return SPC == 0;
}

int main()
{
	int n, m, i, cur, x, y, nn;
	Node *T;

	int mycolor, nextcolor, changemycolor;
	int fail;

	scanf("%d%d", &n, &m);
	for (i = 0; i < m; i++)
	{
		scanf("%d %d", &x, &y);
		LK[x].Insert(y);
		LK[y].Insert(x);
	}
	for (i = 1; i <= n; i++)
		LK[i].Zero();
	for (i = 1; i <= n; i++)
	{
		if (V[i] == 0) // 방문을 안했으면.
		{
			mycolor = 1;
			fail = 0;
			changemycolor = 1;

			cur = i;
			V[cur] = mycolor;
			printf("%d  ", cur);
			while (1)
			{
				if (changemycolor == 1) {
					changemycolor = 0;
					V[cur] = mycolor;
					if (mycolor == 1)
						nextcolor = 2;
					else
						nextcolor = 1;
				}
				if ((nn = LK[cur].Next()) != 0)
				{
					if (V[nn] == 0) // 안가본곳이면
					{
						// stack에 curr노드 푸쉬
						Push(cur);
						PushC(mycolor);
						cur = nn;
						V[cur] = nextcolor;
						mycolor = nextcolor;
						changemycolor = 1;
						printf("%d  ", cur);
					}
					else {
						if (V[nn] != nextcolor){
							fail = 1;
							printf("??? node %d color %d next node %d color %d\n", cur, V[cur], nn, V[nn]);
						}
					}
					//  가본곳이면 무시
				}
				else
				{
					if (isEmpty())
						break;
					else
					{
						cur = Pop();
						mycolor = PopC();
						changemycolor = 1;
						printf("node %d\n", cur);
					}
				}
				printf("\n");
			}
		}
		if (fail == 1)
			printf("NO\n");
		else
			printf("YES\n");
		return 0;
	}
}
