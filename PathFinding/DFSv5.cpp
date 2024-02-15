#include <iostream>
#include <vector>
#include <map>
#include <stack>

using namespace std;

class MazePathFinding_v3
{
public:
	const string DOWN = "down";
	const string RIGHT = "right";
	const string UP = "up";
	const string LEFT = "left";
	const char START = 'S';
	const char END = 'E';
	const char BLOCK = 'O';

	vector<vector<char>> maze;
	map<pair<int, int>, bool> visited;

	MazePathFinding_v3(vector<vector<char>> maze)
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
		bool isPossible = false;

		if (next_move == DOWN)
		{
			if (maze[current_index.first + 1][current_index.second] == BLOCK || maze[current_index.first + 1][current_index.second] == END)
				isPossible = true;
		}
		else if (next_move == RIGHT)
		{
			if (maze[current_index.first][current_index.second + 1] == BLOCK || maze[current_index.first][current_index.second + 1] == END)
				isPossible = true;
		}
		else if (next_move == UP)
		{
			if (maze[current_index.first - 1][current_index.second] == BLOCK || maze[current_index.first - 1][current_index.second] == END)
				isPossible = true;
		}
		else if (next_move == LEFT)
		{
			if (maze[current_index.first][current_index.second - 1] == BLOCK || maze[current_index.first][current_index.second - 1] == END)
				isPossible = true;
		}
		return isPossible;
	}

	// Utility function to check in the hash table if a particular BLOCK is visited or not
	bool IsVisited(pair<int, int> current_index, string next_move)
	{
		bool isPossible = false;

		if (next_move == DOWN)
		{
			if (visited[{current_index.first + 1, current_index.second}])
				isPossible = true;
		}
		else if (next_move == RIGHT)
		{
			if (visited[{current_index.first, current_index.second + 1}])
				isPossible = true;
		}
		else if (next_move == UP)
		{
			if (visited[{current_index.first - 1, current_index.second}])
				isPossible = true;
		}
		else if (next_move == LEFT)
		{
			if (visited[{current_index.first, current_index.second - 1}])
				isPossible = true;
		}
		return isPossible;
	}

	// Utility function for above 2 utility functions (combining above two conditions)
	bool CombinedCheck(vector<vector<char>> &maze, pair<int, int> current_index, string next_move)
	{
		bool isPossible = false;

		if (next_move == DOWN)
		{
			if (current_index.first + 1 < maze.size() && CheckForBlockOrEnd(maze, DOWN, current_index) && !IsVisited(current_index, DOWN))
				isPossible = true;
		}
		else if (next_move == RIGHT)
		{
			if (current_index.second + 1 < maze[0].size() && CheckForBlockOrEnd(maze, RIGHT, current_index) && !IsVisited(current_index, RIGHT))
				isPossible = true;
		}
		else if (next_move == UP)
		{
			if (current_index.first - 1 >= 0 && CheckForBlockOrEnd(maze, UP, current_index) && !IsVisited(current_index, UP))
				isPossible = true;
		}
		else if (next_move == LEFT)
		{
			if (current_index.second - 1 >= 0 && CheckForBlockOrEnd(maze, LEFT, current_index) && !IsVisited(current_index, LEFT))
				isPossible = true;
		}
		return isPossible;
	}

	// Utility Fuction to check if the next move is feasible or not
	bool IsNextMovePossible(vector<vector<char>> &maze, pair<int, int> current_index)
	{
		bool is_feasible = false;

		if (CombinedCheck(maze, current_index, DOWN))
		{
			is_feasible = true;
		}
		else if (CombinedCheck(maze, current_index, RIGHT))
		{
			is_feasible = true;
		}
		else if (CombinedCheck(maze, current_index, UP))
		{
			is_feasible = true;
		}
		else if (CombinedCheck(maze, current_index, LEFT))
		{
			is_feasible = true;
		}
		else
			is_feasible = false;
		return is_feasible;
	}

	// Moving the current_index to the next feasible Block
	pair<int, int> NextAccessibleMove(vector<vector<char>> &maze, pair<int, int> current_index)
	{
		if (CombinedCheck(maze, current_index, DOWN))
		{
			current_index.first += 1;
		}
		else if (CombinedCheck(maze, current_index, RIGHT))
		{
			current_index.second += 1;
		}
		else if (CombinedCheck(maze, current_index, UP))
		{
			current_index.first -= 1;
		}
		else if (CombinedCheck(maze, current_index, LEFT))
		{
			current_index.second -= 1;
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

		while (maze[current_index.first][current_index.second] != 'E')
		{
			// if Next move is possible then move the current_index to next feasible block
			// and update the stack and hashtable accordingly
			if (IsNextMovePossible(maze, current_index))
			{
				current_index = NextAccessibleMove(maze, current_index);
				visited[current_index] = true;
				st.push(current_index);
			}
			// If there is on feasible move, then backtrack to the last last index
			// and set it to the current_index
			else if (!IsNextMovePossible(maze, current_index))
			{
				st.pop();
				current_index = st.top();
			}
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
	vector<vector<char>> maze = {
		{'S', 'E', 'O', 'O', 'O', 'X'},
		{'O', 'X', 'O', 'O', 'O', 'O'},
		{'O', 'X', 'X', 'X', 'O', 'O'},
		{'O', 'X', 'O', 'O', 'O', 'O'},
		{'O', 'O', 'O', 'O', 'O', 'O'},
		{'O', 'O', 'O', 'O', 'O', 'O'},
		{'O', 'X', 'O', 'X', 'O', 'O'},
		{'O', 'O', 'O', 'O', 'X', 'O'},
		{'O', 'O', 'O', 'X', 'O', 'O'},
	};

	MazePathFinding_v3 mpf(maze);
	mpf.PrintPath();
}