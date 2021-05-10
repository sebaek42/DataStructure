/* ************************************************************************************** */
/*                                                                                        */
/*  스택을 활용하여 DFS방식으로 미로 찾는 알고리즘                                                   */
/* 입력: 맵의 행 열 크기값, '0'과 '1'로 이루어진 맵. '0'은 갈수 있는길, '1'은 갈수 없는길                 */
/* 출력: 맵의 (0,0) 부터 (행-1, 열-1) 인덱스까지 가는 경로 순서대로 출력                               */
/*                                                                                        */
/* 알고리즘                                                                                 */
/* 현재 위치를 경로에 저장해주고 맵도 '*'로 바꿔줌. 그리고 위에서부터 시계방향순서로 8방향 인덱스의 맵을 확인함    */
/* 각 방향의 맵을 탐색하다 '0'인 경우를 만나면 해당 위치로 인덱스 값을 옮김                               */
/* (이때 인덱스 확인과정에서 빈 인덱스를 참조하게되는 경우를 방지하기 위해 맵전체를 1로 둘러쌓아줌)              */
/* 모든 방향에서 탐색한 결과가 '0'이 아닌경우는 곧 벽이거나 이미 지나간 자리라는것이고, 따라서                 */
/* 현재 위치로 이동하기 전의 위치로 다시 이동하여 그 주변의 새로운 길을 찾도록 유도함                        */
/* (이때 현재 위치를 pop하고난 뒤 스택을 봤을때 텅 비어있다면 답이 없다는 뜻이므로 프로그램 종료)              */
/*                                                                                        */
/* ************************************************************************************** */


#include <iostream>
#include <stack>

int main()
{
	// map 관련 변수
	int M;
	int N;
	char **map;

	// 위치 관련 변수
	int i;
	int j;
	std::pair<int, int> tmp;
	// 이동 경로 저장할 스택<i, j>
	std::stack<std::pair<int, int> > path;

	// 정답 경로 저장할 스택<i, j>
	std::stack<std::pair<int, int> > result;

	i = 0;
	j = 0;
	std::cin >> M >> N;
	map = new char*[M + 2];
	for (int k = 0; k < M + 2; ++k)
	{
		map[k] = new char[N + 2];
	}
	for (i = 0; i < M + 2; ++i)
	{
		for (j = 0; j < N + 2; ++j)
		{
			if (i == 0 || i == M + 1 || j == 0 || j == N + 1)
				map[i][j] = '1';
		}
	}
	for (i = 1; i < M + 1; ++i)
	{
		for (j = 1; j < N + 1; ++j)
		{
			std::cin >> map[i][j];
		}
	}
	// 맵 전체 출력
	// for (i = 0; i < M + 2; ++i)
	// {
	// 	for (j = 0; j < N + 2; ++j)
	// 	{
	// 		std::cout << map[i][j] << ' ';
	// 	}
	// 	std::cout << std::endl;
	// }
	// 맵 벽 제외 출력
	// for (i = 1; i < M + 1; ++i)
	// {
	// 	for (j = 1; j < N + 1; ++j)
	// 	{
	// 		std::cout << map[i][j] << ' ';
	// 	}
	// 	std::cout << std::endl;
	// }
	for (i = 0; i < M; ++i)
	{
		for (j = 0; j < N; ++j)
		{
			if (map[i][j] != '0' && map[i][j] != '1')
			{
				std::cout << "error: invalid map content" <<std::endl;
				return (-1);
			}
		}
	}
	i = 1;
	j = 1;
	while (1)
	{
		if (i == M && j == N)
		{
			// TODO: path 스택의 내용을 result스택에 push하고 result스택의 내용을 순서대로 출력해준다
			path.push(std::make_pair(i, j));
			while (!path.empty())
			{
				result.push(path.top());
				path.pop();
			}
			while (!result.empty())
			{
				std::cout << "("<< result.top().first - 1 << ", " << result.top().second - 1 << ")";
				result.pop();
				if (!result.empty())
					std::cout << " -> ";
			}
			std::cout << std::endl;
			break ;
		}
		else
		{
			path.push(std::make_pair(i, j));
			map[i][j] = '*';
			// 위 부터 시계방향으로 방향 탐색
			if (map[i - 1][j] == '0')
			{
				i = i - 1;
			}
			else if (map[i - 1][j + 1] == '0')
			{
				i = i - 1;
				j = j + 1;
			}
			else if (map[i][j + 1] == '0')
			{
				j = j + 1;
			}
			else if (map[i + 1][j + 1] == '0')
			{
				i = i + 1;
				j = j + 1;
			}
			else if (map[i + 1][j] == '0')
			{
				i = i + 1;
			}
			else if (map[i + 1][j - 1] == '0')
			{
				i = i + 1;
				j = j - 1;
			}
			else if (map[i][j - 1] == '0')
			{
				j = j - 1;
			}
			else if (map[i + 1][j - 1] == '0')
			{
				i = i + 1;
				j = j - 1;
			}
			else // 위 모든 경우일때 없으면 뒤로 가야함
			{
				path.pop(); // 뒤로 가고
				if (path.empty()) // 갔는데 없으면 처음위치에서 더이상 찾을게 없다는 뜻
				{
					std::cout << "출구 없음" << std::endl;
					return (0);
				}
				tmp = path.top();
				i = tmp.first;
				j = tmp.second;
				path.pop(); // 같은 i,j를 이미 가지고있는데 다음루프에서 또 push하게 되므로 없애줌
			}
		}
	}
	return (0);
}
