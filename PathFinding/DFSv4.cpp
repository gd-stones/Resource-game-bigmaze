#include <iostream>
#include <vector>

const int ROWS = 9;
const int COLS = 6;

struct Point
{
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
};

bool isValid(int x, int y)
{
    return x >= 0 && x < ROWS && y >= 0 && y < COLS;
}

void DFS(std::vector<std::vector<int>> &matrix, Point current, Point destination, std::vector<Point> &path, std::vector<std::vector<bool>> &visited)
{
    if (current.x == destination.x && current.y == destination.y)
    {
        path.push_back(current);
        return;
    }

    visited[current.x][current.y] = true;
    int directions[][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    for (int i = 0; i < ROWS; ++i)
    {
        int newX = current.x + directions[i][0];
        int newY = current.y + directions[i][1];

        if (isValid(newX, newY) && matrix[newX][newY] == 1 && !visited[newX][newY])
        {
            path.push_back(current);
            DFS(matrix, Point(newX, newY), destination, path, visited);

            if (!path.empty() && path.back().x == destination.x && path.back().y == destination.y)
                return;

            path.pop_back();
        }
    }
}

std::vector<Point> findPath(std::vector<std::vector<int>> &matrix, Point start, Point end)
{
    std::vector<Point> path;
    std::vector<std::vector<bool>> visited(ROWS, std::vector<bool>(COLS, false));
    DFS(matrix, start, end, path, visited);

    return path;
}

int main()
{
    std::vector<std::vector<int>> matrix = {
        {1, 1, 1, 1, 1, 0},
        {1, 0, 1, 1, 1, 1},
        {1, 0, 0, 0, 1, 1},
        {1, 0, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1},
        {1, 0, 1, 0, 1, 1},
        {1, 1, 1, 1, 0, 1},
        {1, 1, 1, 0, 1, 1},

    };
    Point start(0, 0);
    Point end(0, 1);

    std::vector<Point> path = findPath(matrix, start, end);
    if (path.empty())
        std::cout << "Khong tim thay duong di.\n";
    else
    {
        std::cout << "Duong di tu (" << start.x << ", " << start.y << ") den (" << end.x << ", " << end.y << "): ";
        for (int i = 0; i < path.size(); ++i)
            std::cout << "(" << path[i].x << ", " << path[i].y << ") ";
        std::cout << "\n";
    }

    system("pause");
    return 0;
}
