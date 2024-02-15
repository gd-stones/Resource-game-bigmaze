#include <iostream>
#include <vector>
#include <map>
#include <stack>

using namespace std;

int MAZE_01[9][11] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

class MazePathFinding_v5
{
public:
	const string DOWN = "down";
	const string RIGHT = "right";
	const string UP = "up";
	const string LEFT = "left";
	const string DEADEND = "deadEnd";
	const string BACKTRACK = "backTrack";
	string route = "";

	pair<int, int> startCell;
	pair<int, int> endCell;

	vector<pair<int, int>> blockCells;
	vector<pair<int, int>> currentKeyCells; // Saves the cells currently under review and not yet completed
	vector<pair<int, int>> visitedKeyCells; // Checked all 4 directions
	stack<pair<int, int>> path;				// Saves the cells currently under review and not yet completed

public:
	MazePathFinding_v5() {}
	~MazePathFinding_v5() {}

	void DetectObstacles()
	{
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 11; j++)
				if (MAZE_01[i][j] == 1)
					blockCells.push_back(make_pair(i, j));
	}

	void Init(pair<int, int> startCell, pair<int, int> endCell)
	{
		this->startCell = startCell;
		this->endCell = endCell;
		path.push(startCell);
	}

	bool IsVisited(pair<int, int> checkCell)
	{
		for (int i = 0; i < visitedKeyCells.size(); i++)
		{
			if (visitedKeyCells[i] == checkCell)
				return true;
		}
		for (int i = 0; i < currentKeyCells.size(); i++)
		{
			if (currentKeyCells[i] == checkCell)
				return true;
		}
		return false;
	}
	bool CanMoveUp(pair<int, int> currentCell)
	{
		pair<int, int> nearestBlockCell = make_pair(0, currentCell.second);
		for (int i = 0; i < blockCells.size(); i++)
		{
			if (blockCells[i].second == currentCell.second)
			{
				if (currentCell.first > blockCells[i].first && blockCells[i].first > nearestBlockCell.first)
				{
					nearestBlockCell = blockCells[i];
				}
			}
		}
		
		pair<int, int> nearestKeyCell = make_pair(nearestBlockCell.first + 1, nearestBlockCell.second);
		if (nearestBlockCell.first - currentCell.first - 1 == 0 || IsVisited(nearestKeyCell))
		{
			// Khong di theo huong nay
			return false;
		}
		return true; // Di theo huong nay
	}
	bool CanMoveDown(pair<int, int> currentCell)
	{
		return false;
	}
	bool CanMoveLeft(pair<int, int> currentCell)
	{
		return false;
	}
	bool CanMoveRight(pair<int, int> currentCell)
	{
		return false;
	}

	void CalculateNextMove() {}

	void PathFinding() // add parameters
	{
		int numCheckedDirections = 0;
		if (CanMoveUp(startCell))
		{
			numCheckedDirections++;
		}
	}
};

int main()
{
	MazePathFinding_v5 mpf_v5;

	system("pause");
	return 0;
}