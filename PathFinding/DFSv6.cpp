#include <iostream>
#include <vector>
#include <map>
#include <stack>

using namespace std;

class MazePathFinding_v4
{
public:
	const string DOWN = "down";
	const string RIGHT = "right";
	const string UP = "up";
	const string LEFT = "left";
	const string DEADEND = "deadEnd";
	const string BACKTRACK = "backTrack";
	string route = "";
	const char START = 'S';
	const char END = 'E';
	const char BLOCK = 'O';

	vector<vector<char>> maze;
	map<pair<int, int>, bool> visited;

	MazePathFinding_v4(vector<vector<char>> maze)
	{
		this->maze = maze;
	}

	// finding the start index
	pair<int, int> FindStartPoint(vector<vector<char>> &maze)
	{
		pair<int, int> start_index;

		for (int i = 0; i < maze.size(); i++)
		{
			for (int j = 0; j < maze[i].size(); j++)
			{
				if (maze[i][j] == START)
					start_index = {i, j};
			}
		}
		return start_index;
	}

	// Utility Function to check of "O" or "E" ('O' means BLOCK and 'E' means END)
	bool CheckForBlockOrEnd(vector<vector<char>> &maze, string next_move, pair<int, int> current_index)
	{
		if (next_move == DOWN)
		{
			if (maze[current_index.first + 1][current_index.second] == BLOCK || maze[current_index.first + 1][current_index.second] == END)
				return true;
		}
		else if (next_move == RIGHT)
		{
			if (maze[current_index.first][current_index.second + 1] == BLOCK || maze[current_index.first][current_index.second + 1] == END)
				return true;
		}
		else if (next_move == UP)
		{
			if (maze[current_index.first - 1][current_index.second] == BLOCK || maze[current_index.first - 1][current_index.second] == END)
				return true;
		}
		else if (next_move == LEFT)
		{
			if (maze[current_index.first][current_index.second - 1] == BLOCK || maze[current_index.first][current_index.second - 1] == END)
				return true;
		}
		return false;
	}

	// Utility function to check in the hash table if a particular BLOCK is visited or not
	bool IsVisited(pair<int, int> current_index, string next_move)
	{
		if (next_move == DOWN)
		{
			if (visited[{current_index.first + 1, current_index.second}])
				return true;
		}
		else if (next_move == RIGHT)
		{
			if (visited[{current_index.first, current_index.second + 1}])
				return true;
		}
		else if (next_move == UP)
		{
			if (visited[{current_index.first - 1, current_index.second}])
				return true;
		}
		else if (next_move == LEFT)
		{
			if (visited[{current_index.first, current_index.second - 1}])
				return true;
		}
		return false;
	}

	// Utility function for above 2 utility functions (combining above two conditions)
	bool CombinedCheck(vector<vector<char>> &maze, pair<int, int> current_index, string next_move)
	{
		if (next_move == DOWN)
		{
			if (current_index.first + 1 < maze.size() && CheckForBlockOrEnd(maze, DOWN, current_index) && !IsVisited(current_index, DOWN))
				return true;
		}
		else if (next_move == RIGHT)
		{
			if (current_index.second + 1 < maze[0].size() && CheckForBlockOrEnd(maze, RIGHT, current_index) && !IsVisited(current_index, RIGHT))
				return true;
		}
		else if (next_move == UP)
		{
			if (current_index.first - 1 >= 0 && CheckForBlockOrEnd(maze, UP, current_index) && !IsVisited(current_index, UP))
				return true;
		}
		else if (next_move == LEFT)
		{
			if (current_index.second - 1 >= 0 && CheckForBlockOrEnd(maze, LEFT, current_index) && !IsVisited(current_index, LEFT))
				return true;
		}
		return false;
	}

	// Utility Fuction to check if the next move is feasible or not
	void FindRoute(vector<vector<char>> &maze, pair<int, int> current_index)
	{
		if (CombinedCheck(maze, current_index, LEFT))
			route = LEFT;
		else if (CombinedCheck(maze, current_index, UP))
			route = UP;
		else if (CombinedCheck(maze, current_index, RIGHT))
			route = RIGHT;
		else if (CombinedCheck(maze, current_index, DOWN))
			route = DOWN;
		else
			route = BACKTRACK;
	}

	// Moving the current_index to the next feasible Block
	pair<int, int> NextAccessibleMove(vector<vector<char>> &maze, pair<int, int> current_index, string &route)
	{
		if (route == DOWN)
		{
			if (CombinedCheck(maze, current_index, DOWN))
				current_index.first += 1;
			else
				route = DEADEND;
		}
		else if (route == RIGHT)
		{
			if (CombinedCheck(maze, current_index, RIGHT))
				current_index.second += 1;
			else
				route = DEADEND;
		}
		else if (route == UP)
		{
			if (CombinedCheck(maze, current_index, UP))
				current_index.first -= 1;
			else
				route = DEADEND;
		}
		else if (route == LEFT)
		{
			if (CombinedCheck(maze, current_index, LEFT))
				current_index.second -= 1;
			else
				route = DEADEND;
		}
		return current_index;
	}

	// Depth First Search Function combining all the above utility function to return a stack of possible moves
	stack<pair<int, int>> DFS()
	{
		pair<int, int> start_index = FindStartPoint(maze);
		pair<int, int> current_index = start_index;
		stack<pair<int, int>> st;
		st.push(start_index);
		visited[start_index] = true;
		vector<int> path;
		int stepCount = 0;

		while (maze[current_index.first][current_index.second] != 'E')
		{
			bool check = false;
			FindRoute(maze, current_index);
			// go to death in a chosen direction
			while (route != BACKTRACK && route != DEADEND)
			{
				current_index = NextAccessibleMove(maze, current_index, route);
				visited[current_index] = true;
				st.push(current_index);
				if (maze[current_index.first][current_index.second] == 'E')
					break;
				stepCount++;
				check = true;
			}
			if (maze[current_index.first][current_index.second] == 'E')
				break;
			if (check)
			{
				st.pop();
				stepCount--;
				path.push_back(stepCount);
			}

			// backtrack when all 3 directions are blocked
			FindRoute(maze, current_index);
			if (route == BACKTRACK)
			{
				int stepBacktracking = path.back();
				path.pop_back();
				while (stepBacktracking > 0)
				{
					st.pop();
					stepBacktracking--;
				}
				current_index = st.top();
			}
			stepCount = 0;
		}
		return st;
	}

	void PrintPath()
	{
		stack<pair<int, int>> path = DFS();
		vector<pair<int, int>> vt;

		while (!path.empty())
		{
			vt.push_back(path.top());
			path.pop();
		}
		for (int i = vt.size() - 1; i >= 0; i--)
		{
			cout << '(' << vt[i].first << ", " << vt[i].second << ')' << " -> ";
		}
		cout << endl;
	}
};

int main()
{
	// 'O' means empty space (BLOCK)
	// 'X' means barrier
	// 'S' means start point
	// 'E' means end point
	vector<vector<char>> maze =
	{
		{'E', 'O', 'O', 'O'},
		{'X', 'O', 'O', 'O'},
		{'O', 'O', 'O', 'O'},
		{'O', 'O', 'O', 'S'},
	};

	MazePathFinding_v4 mpf(maze);
	mpf.PrintPath();
	system("pause");
	return 0;
}

// vector<vector<char>> maze = {
	// 	{'S', 'X', 'O', 'O', 'O', 'X'},
	// 	{'O', 'X', 'O', 'O', 'O', 'O'},
	// 	{'O', 'X', 'X', 'X', 'O', 'O'},
	// 	{'O', 'X', 'O', 'O', 'O', 'O'},
	// 	{'O', 'O', 'O', 'O', 'O', 'E'},
	// 	{'O', 'X', 'O', 'X', 'O', 'O'},
	// 	{'O', 'O', 'O', 'O', 'X', 'O'},
	// 	{'O', 'O', 'O', 'X', 'O', 'O'},
	// };