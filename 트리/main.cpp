#include <iostream>
#include <cstdio>

using namespace std;

class Node {
	public:
	int a;
	Node *L, *R;
};

class BST {
	public:
	BST();
	int Search(int x, Node **P, Node **L);
	int Insert(int x);
	int Delete(int x);
	int Print(Node *C, int depth, int LR);
	Node *root;
};


// dummy node
BST::BST()
{
	root = new Node; // 루트에 새로운 노드를 하나 할당했음.
	root->a = 999; // 999보다 작은 값만 사용한다
	root->L = NULL;
	root->R = NULL;
	// 이제 이진트리 생성시 루트 노드는 항상 있는거임!
}

int BST::Search(int x, Node **P, Node **D)
{
	*D = root; // 첫번째 보는 노드는 루트
	*P = NULL; // 직전에 본 노드
	while (*D != NULL)
	{
		if ((*D)->a == x)
		{
			return 1; // 찾은거지. 지금상태 L과 P가 맞춰진 상태에서 리턴하면됨
		}
		else if ((*D)->a < x)
		{
			// 찾는 x가 현재 노드의 데이터보다 더 크니까 오른쪽 차일드로 가야지
			*P = *D; // 직전에 본 노드는 지금의 노드를 담고
			*D = (*D)->R; // 지금의 노드는 왼쪽 차일드로 바꿈
		}
		else
		{
			// 왼쪽 차일드로 감
			*P = *D;
			*D = (*D)->L;
		}
	}
	return 0;
}

int BST::Insert(int x)
{
	Node *P, *D, *NN;
	if (Search(x, &P, &D) == 0)
	{
		NN = new Node;
		NN->a = x;
		NN->L = NULL;
		NN->R = NULL;
		if (P->a < x)
			P->R = NN;
		else
			P->L = NN;
		return 1;
	}
	else
		return 0;
}

int BST::Delete(int x)
{
	Node *P, *D;
	if (Search(x, &P, &D) == 1)
	{
		// case 4개를 따져봐야지. 자식 양쪽 없을때 한쪽 자식 없을때 양쪽 자식 모두 있을때
		if (D->L == NULL && D->R == NULL)
		{
			if (D == P->L)
				P->L = NULL;
			else
				P->R = NULL;
			delete D;
		}
		else if (D->L == NULL && D->R != NULL)
		{
			if (D == P->L)
				P->L = D->R;
			else
				P->R = D->R;
			delete D;
		}
		else if (D->L != NULL && D->R == NULL)
		{
			if (D == P->L)
				P->L = D->L;
			else
				P->R = D->L;
			delete D;
		}
		else
		{
			Node *RLL, *RLLP;
			RLL = D->R;
			RLLP = D;
			while (RLL->L != NULL)
			{
				RLLP = RLL;
				RLL = RLL->L;
			}
			D->a = RLL->a;
			if (RLL->L == NULL && RLL->R == NULL)
			{
				if (RLL == RLLP->L)
					RLLP->L = NULL;
				else
					RLLP->R = NULL;
				delete RLL;
			}
			else if (RLL->L == NULL && RLL->R != NULL)
			{
				if (RLL == RLLP->L)
					RLLP->L = RLL->R;
				else
					RLLP->R = RLL->R;
				delete RLL;
			}
		}
		return 1;
	}
	return 0;
}

int BST::Print(Node *C, int depth, int LR)
{
	if (depth == 0) // root인경우
	{
		C = root; // C는 current node
	}
	if (LR == 1)
	{
		int i;
		for(i = 0; i < depth; i++)
			printf("      ");
	}
	printf("---%03d", C->a);
	if (C->L != NULL)
	{
		Print(C->L, depth + 1, 0);
	}
	else
		printf("\n");
	if (C->R != NULL)
	{
		Print(C->R, depth + 1, 1);
	}
	return 0;
}

int main()
{
	char com;
	int x, in;
	Node *P, *D;
	BST TT;

	while (1)
	{
		TT.Print(NULL, 0, 0);
		scanf(" %c", &com);
		if (com == 'q')
			break ;
		else if (com == 's')
		{
			scanf("%d", &x);
			in = TT.Search(x, &P, &D);
			if (in == 0)
				printf("Not Found.\n\n");
			else
				printf("Found at address %p\n\n", D);
		}
		else if (com == 'i')
		{
			scanf("%d", &x);
			if (TT.Insert(x) == 1)
				printf("Insert Successful.\n");
			else
				printf("Insert Failed.\n");
		}
		else if (com == 'd')
		{
			scanf("%d", &x);
			if (TT.Delete(x) == 1)
				printf("Delete Successful.\n");
			else
				printf("Delete Failed.\n");
		}
		else
			printf("???\n");
	}
	return 0;
}
