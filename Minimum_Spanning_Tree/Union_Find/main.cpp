#include <iostream>
#include <cstdio>

using namespace std;

int n; // 전체 n은 얼만지
int A[1000]; // union find를 위한 노드담을배열. 글로벌변수니까 첨엔 다 0으로 초기화되어있을거고



int Find(int p)
{
	//path compression 안 된 버젼
	int r;
	r = p;
	while (A[r] != 0) {
		r = A[r]; // 0이 아니면 부모로 가야죠. 부모로 가는게 이거죠
	}
	// 여기까지 하고 return r하면 끝.
	/* path compression 한 버젼*/
	// root 찾았음 한번더해
	int tmp, r2;
	r2 = r; // root 기억
	r = p; // 다시 r 초기화
	while (A[r] != 0) {
		tmp = r; // 현재 노드 기억
		r = A[r]; // 부모노드로 올라감
		A[tmp] = r2; // 지나가는 모든 노드가 루트를 가르키게됨
	}
	return r;
}


void Union(int p, int q)
{
	int pr, qr;
	pr = Find(p);
	qr = Find(q);
	A[qr] = pr; // p가 루트가된거임. 루트면 그자리에 0이 써져있음
	return ;
}

int main()
{
	int i, p, q;
	printf("Size? : ");
	scanf("%d", &n);
	while (1) {
		for (i=1; i<=n; i++)
			printf("%4d", A[i]);
		printf("\n");
		char com;
		scanf(" %c", &com);
		if (com == 'q')
			break ;
		else if (com == 'u') { // cmd = union
			scanf("%d %d", &p, &q);
			Union(p, q);
		}
		else if (com == 'f') { // cmd = find
			scanf("%d", &p);
			q = Find(p);
			printf("Result = %d\n", q);
		}
		else {
			printf("???\n");
		}
	}
	return 0;
}
