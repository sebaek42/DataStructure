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
	void Zero();
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
	NN->a = x; // 값을 넣고
	NN->n = head; // head의 이전에 넣음. 즉 맨 앞에 넣는다는거.
	head = NN; // 새로 생긴 NN이 이제 곧 head가 됨
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
	return curr->a; // 이게 null이면 다음 Next()는 호출 불가
}

int V[1000]; // 0: unvisited, 1: colorR, 2: colorB
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
	int mycolor; // 노드마다 지금 칠할 색
	int nextcolor; // 다음에 칠할 색
	int changemycolor;
	int fail; // 색 연달아 오면 fail 1로 바뀜
	Node *T;
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
		if (V[i] == 0) // 방문을 안했으면?
		{
			mycolor = 1; // red
			changemycolor = 1;
			fail = 0;
			cur = i;
			V[cur] = mycolor;
			while (1) // 지금보는 노드랑 연결된 노드들중 방문안한애들 전부 스택에 푸쉬
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
					if (V[nn] == 0) // 안가본곳이면 전진
					{
						// stack에 curr노드 푸쉬
						Push(cur);
						PushC(mycolor); // mycolor푸쉬
						cur = nn;
						V[cur] = nextcolor; // 가본곳으로 표시
						mycolor = nextcolor;
						changemycolor = 1;
					}
					else {
						if (V[nn] != nextcolor)
							fail = 1;
					}
				}
				else
				{
					if (isEmpty())
						break ;
					else {
						cur = Pop(); // pop 할때 색도 pop 을 해야해..스택을 고쳐야하는데 너무 귀찮음. 스택을 하나 더 추가하자
						mycolor = PopC();
						changemycolor = 1;
					}
				}
			}
			printf("\n");
		}
	}
	if (fail == 1)
		printf("No\n");
	else
		printf("Yes\n");
	return 0;
}
