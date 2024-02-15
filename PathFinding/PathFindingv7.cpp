#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <utility>
#include <algorithm>

using namespace std;

// int MAZE_01[9][11] = {
//	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1} };

int MAZE_01[7][7] = {
	{1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1}};

class MazePathFinding_v6
{
public:
	pair<int, int> startCell;
	pair<int, int> endCell;
	vector<pair<int, int>> blockCells;
	vector<pair<int, int>> currentKeyCells; // Saves the cells currently under review and not yet completed
	vector<pair<int, int>> visitedKeyCells; // Checked all 4 directions
	stack<pair<int, int>> path;				// Saves the cells currently under review and not yet completed

	vector<stack<pair<int, int>>> pathList;
	vector<stack<string>> directionList;
	vector<int> totalStepList;

public:
	MazePathFinding_v6() {}
	~MazePathFinding_v6() {}

	void DetectObstacles()
	{
		for (int i = 0; i < 7; i++)
			for (int j = 0; j < 7; j++)
				if (MAZE_01[i][j] == 1)
					blockCells.push_back(make_pair(i, j));
	}

	void Init(pair<int, int> startCell, pair<int, int> endCell)
	{
		this->startCell = startCell;
		this->endCell = endCell;
		path.push(startCell);
		currentKeyCells.push_back(startCell);
		DetectObstacles();
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

	bool isPathFound = false;
	void PathFound()
	{
		pathList.push_back(path);
		stack<pair<int, int>> tmp = path;
		tmp.push(endCell);

		// Clean path
		vector<pair<int, int>> elements;
		while (!tmp.empty())
		{
			elements.push_back(tmp.top());
			tmp.pop();
		}
		reverse(elements.begin(), elements.end());
		// for (int i = 0; i < elements.size(); i++)
		// 	cout << "(" << elements[i].first << ", " << elements[i].second << ")"
		// 		 << ", ";
		// cout << endl;

		for (int i = 0; i < elements.size() - 2; i++)
		{
			if (elements[i].first == elements[i + 1].first && elements[i + 1].first == elements[i + 2].first || elements[i].second == elements[i + 1].second && elements[i + 1].second == elements[i + 2].second)
			{
				elements.erase(elements.begin() + i + 1);
				i--;
			}
		}

		for (int i = 0; i < elements.size(); i++)
		{
			tmp.push(elements[i]);
		}

		stack<string> reverseDirections;
		int totalSteps = 0;
		pair<int, int> f = tmp.top(); // endCell;
		tmp.pop();
		while (!tmp.empty())
		{
			pair<int, int> s = tmp.top();
			// up
			if (f.second == s.second && s.first > f.first)
			{
				totalSteps += (s.first - f.first);
				reverseDirections.push("up");
			}
			// left
			else if (f.first == s.first && s.second > f.second)
			{
				totalSteps += (s.second - f.second);
				reverseDirections.push("left");
			}
			// down
			else if (f.second == s.second && s.first < f.first)
			{
				totalSteps += (f.first - s.first);
				reverseDirections.push("down");
			}
			// right
			else if (f.first == s.first && s.second < f.second)
			{
				totalSteps += (f.second - s.second);
				reverseDirections.push("right");
			}
			f = s;
			tmp.pop();
		}

		totalStepList.push_back(totalSteps);
		directionList.push_back(reverseDirections);
		isPathFound = false;
	}

	bool CanMoveUp(pair<int, int> currentCell)
	{
		if (currentCell.second == endCell.second && currentCell.first >= endCell.first)
		{
			isPathFound = true;
			return true;
		}

		pair<int, int> nearestBlockCell = make_pair(0, currentCell.second);
		for (int i = 0; i < blockCells.size(); i++)
		{
			if (blockCells[i].second == currentCell.second && currentCell.first > blockCells[i].first && blockCells[i].first > nearestBlockCell.first)
				nearestBlockCell = blockCells[i];
		}

		pair<int, int> nearestKeyCell = make_pair(nearestBlockCell.first + 1, nearestBlockCell.second);
		if (currentCell.first - nearestKeyCell.first == 0 || IsVisited(nearestKeyCell))
			return false;

		path.push(nearestKeyCell);
		currentKeyCells.push_back(nearestKeyCell);
		return true;
	}

	bool CanMoveDown(pair<int, int> currentCell)
	{
		if (currentCell.second == endCell.second && currentCell.first <= endCell.first)
		{
			isPathFound = true;
			return true;
		}

		pair<int, int> nearestBlockCell = make_pair(sizeof(MAZE_01) / sizeof(MAZE_01[0]) - 1, currentCell.second);
		for (int i = 0; i < blockCells.size(); i++)
		{
			if (blockCells[i].second == currentCell.second && currentCell.first < blockCells[i].first && blockCells[i].first < nearestBlockCell.first)
				nearestBlockCell = blockCells[i];
		}

		pair<int, int> nearestKeyCell = make_pair(nearestBlockCell.first - 1, nearestBlockCell.second);
		if (nearestKeyCell.first - currentCell.first == 0 || IsVisited(nearestKeyCell))
			return false;

		path.push(nearestKeyCell);
		currentKeyCells.push_back(nearestKeyCell);
		return true;
	}

	bool CanMoveLeft(pair<int, int> currentCell)
	{
		if (currentCell.first == endCell.first && currentCell.second >= endCell.second)
		{
			isPathFound = true;
			return true;
		}

		pair<int, int> nearestBlockCell = make_pair(currentCell.first, 0);
		for (int i = 0; i < blockCells.size(); i++)
		{
			if (blockCells[i].first == currentCell.first && currentCell.second > blockCells[i].second && blockCells[i].second > nearestBlockCell.second)
				nearestBlockCell = blockCells[i];
		}

		pair<int, int> nearestKeyCell = make_pair(nearestBlockCell.first, nearestBlockCell.second + 1);
		if (currentCell.second - nearestKeyCell.second == 0 || IsVisited(nearestKeyCell))
			return false;

		path.push(nearestKeyCell);
		currentKeyCells.push_back(nearestKeyCell);
		return true;
	}

	bool CanMoveRight(pair<int, int> currentCell)
	{
		if (currentCell.first == endCell.first && currentCell.second <= endCell.second)
		{
			isPathFound = true;
			return true;
		}

		pair<int, int> nearestBlockCell = make_pair(currentCell.first, sizeof(MAZE_01[0]) - 1);
		for (int i = 0; i < blockCells.size(); i++)
		{
			if (blockCells[i].first == currentCell.first && currentCell.second < blockCells[i].second && blockCells[i].second < nearestBlockCell.second)
				nearestBlockCell = blockCells[i];
		}

		pair<int, int> nearestKeyCell = make_pair(nearestBlockCell.first, nearestBlockCell.second - 1);
		if (nearestKeyCell.second - currentCell.second == 0 || IsVisited(nearestKeyCell))
			return false;

		path.push(nearestKeyCell);
		currentKeyCells.push_back(nearestKeyCell);
		return true;
	}

	void PathFinding()
	{
		if (CanMoveUp(path.top()))
		{
			if (isPathFound)
				PathFound();
			else
				PathFinding();
		}
		if (CanMoveLeft(path.top()))
		{
			if (isPathFound)
				PathFound();
			else
				PathFinding();
		}
		if (CanMoveDown(path.top()))
		{
			if (isPathFound)
				PathFound();
			else
				PathFinding();
		}
		if (CanMoveRight(path.top()))
		{
			if (isPathFound)
				PathFound();
			else
				PathFinding();
		}

		pair<int, int> tmp = path.top();
		if (tmp == startCell)
			return;
		path.pop();
		visitedKeyCells.push_back(currentKeyCells.back());
		currentKeyCells.pop_back();
	}

	void Print()
	{
		for (int i = 0; i < directionList.size(); i++)
		{
			while (!directionList[i].empty())
			{
				cout << directionList[i].top() << "-";
				directionList[i].pop();
			}
			cout << endl;
		}
	}
};

int main()
{
	MazePathFinding_v6 mpf_v6;
	mpf_v6.Init(make_pair(4, 5), make_pair(3, 2));
	mpf_v6.PathFinding();
	mpf_v6.Print();

	system("pause");
	return 0;
}