#include <iostream>
#include <cstdlib> // For rand() function
#include <ctime>   // For srand() function
#include <vector>

using namespace std;

const int ROWS = 9;
const int COLS = 9;
int position[2] = {1, 1};
//          up left down right
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};

int maze[ROWS][COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 1, 1, 0, 0, 1},
    {1, 0, 0, 1, 1, 1, 0, 0, 1},
    {1, 0, 0, 1, 1, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1}};

vector<pair<int, int>> FindZeroPositions(const int maze[ROWS][COLS])
{
    vector<pair<int, int>> zeroPositions;

    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            if (maze[i][j] == 0)
            {
                zeroPositions.push_back(make_pair(i, j));
            }
        }
    }
    return zeroPositions;
}

void RandomPosition(const vector<pair<int, int>> &vec)
{
    srand(time(0));
    int randomIndex = rand() % vec.size();
    position[0] = vec[randomIndex].first;
    position[1] = vec[randomIndex].second;
}

int main()
{
    char direction = 'd';
    // cout << "Direction: " << endl;
    // cin >> direction;

    vector<pair<int, int>> zeroPositions = FindZeroPositions(maze);
    // cout << "Positions with value 0:" << std::endl;
    // for (const auto &position : zeroPositions)
    // {
    //     cout << "(" << position.first << ", " << position.second << ")" << std::endl;
    // }

    RandomPosition(zeroPositions);
    cout << "Random Position: (" << position[0] << ", " << position[1] << ")" << endl;

    // logic movement
    switch (direction)
    {
    case 'w':
    {
        // Upward
        break;
    }
    case 'a':
        // Leftward
        break;
    case 's':
        // Downward
        break;
    case 'd':
    {
        // Rightward
        int x = position[0];
        int y = position[1];
        while (y < COLS - 1)
        {
            y++;
            if (maze[x][y] == 1)
            {
                y--;
                break;
            }
        }
        position[0] = x;
        position[1] = y;
        break;
    }
    default:
        cout << "Khong biet di huong nao!";
        break;
    }

    system("pause");
    return 0;
}
