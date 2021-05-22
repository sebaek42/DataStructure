// #include <bits/stdc++.h> // window os 용 sort()인듯
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

class Edge {
public:
	int a, b, w; // 노드 a,b 가중치 w
	bool operator < (const Edge& k) const
	{
		return w < k.w;
	}
};

Edge E[1000];
int Use[1000]; // 각각의 엣지를 사용할지말지 결정. 0이면 안씀 1이면 씀

int n, m; // 노드수, 엣지수
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

// 모든 노드마다 살아있는 엣지 다 집어넣어서 트리빌드
vector <pair<int, int> > Ad[1000];

// DFS돌면서 모든 노드를 찍는거로 할거야. 재귀적DFS사용하면서 찍을거임. 살아있는 엣지만 찍는거

void Print(int nd, int depth, int wei, int pr, int LR) // LR? 젤 먼저만 L 나머지는 다 R로 보면됨
{
	int j, cnt;

	if (LR > 0) {
		int i;
		for (i=0; i < depth - 1; i++)
		{
			printf("            ");
		}
		printf("      ");
	}
	if (depth == 0)
		printf("--[%02d]", nd); // 가중치, 노드번호
	else
		printf("--(%02d)--[%02d]", wei, nd); // 가중치, 노드번호
	cnt = 0;
	for (j=0; j < Ad[nd].size(); j++) {
		if (Ad[nd][j].first != pr) {
			Print(Ad[nd][j].first, depth+1, Ad[nd][j].second, nd, cnt);
			cnt++;
		}
	}
	if (cnt == 0)
		printf("\n");
}

int main()
{
	int i, cnt, pr, qr;
	scanf("%d %d", &n, &m);
	for (i=1; i<=m; i++){
		scanf("%d %d %d", &E[i].a, &E[i].b, &E[i].w);
	}
	sort(E+1, E+m+1); // E라는 배열의 1 ~ m 까지 소팅
	// 결과에 넣을까 말까 결정. 0이면 안씀 1이면 씀
	cnt = 0;
	i = 1;
	while (cnt < n-1) { // edge최대 n-1개까지 넣을수있으니까..
		// 사이클이 안만들어지는 그래프라면 탈출조건 만족못하니까 그거 검증하는것도 있어야함
		if (i > m) // i 가 m보다 크다는건 모든 엣지를 다 봤다는것
		{
			printf("Not Connected!\n");
			break ;
		}
		pr = Find(E[i].a); // 지금보고있는 엣지의 a의 루트..속한그룹의대장찾아라
		qr = Find(E[i].b); // b의 대장찾아라
		if (pr == qr)
		{
			; // 같은그룹. 이 엣지는 넘어감
		}
		if (pr != qr)
		{
			cnt++;
			Use[i] = 1; // 이 엣지는 씁니다
			Union(E[i].a, E[i].b);
		}
		i++;
	}
	printf("\nResult\n");
	for (i=1; i<=m; i++)
		if (Use[i] == 1)
			printf("%d %d %d\n", E[i].a, E[i].b, E[i].w);
	printf("\nTree\n");
	for (i = 1; i <=m; i++) {
		if (Use[i]) { // 사용하는 엣지들만 Ad벡터에 넣어줌
			Ad[E[i].a].push_back(make_pair(E[i].b, E[i].w)); // a노드한테 b하고 w넣음
			Ad[E[i].b].push_back(make_pair(E[i].a, E[i].w));
		}
	}
	Print(1, 0, 0,0, 0);
	return 0;
}



/*
3 3 // 노드 3개 엣지 3개
1 2 3 // 1노드 2노드 연결하는 가중치 3짜리 엣지
2 3 2
3 1 4
*/
/*
3 3
1 2 3
2 3 2
3 1 4
*/
/* 강의자료 예시
5 10
1 2 10
2 3 1
2 4 3
4 2 4
3 4 9
1 4 5
1 5 6
4 5 2
3 5 4
3 5 6
*/
/* 연결안된 예시
3 3
1 2 5
1 2 3
1 2 4
*/
