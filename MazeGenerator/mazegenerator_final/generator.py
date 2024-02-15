from mazelib import Maze
from mazelib.generate.Prims import Prims
import matplotlib.pyplot as plt
import os

folder_name = "maze_txt"
os.makedirs(folder_name, exist_ok=True)
m = Maze()


def convert_maze_str_to_matrix(maze_str):
    lines = maze_str.strip().split('\n')
    matrix = [[1 if char == '#' else 0 for char in line] for line in lines]
    return matrix


for i in range(1, 99):
    m.generator = Prims(8, 10)
    m.generate()
    maze_matrix = convert_maze_str_to_matrix(m.tostring())

    if i<10:
        file_name = os.path.join(folder_name, f"level_00{i}.txt")
    elif i>=10 and i <100:
        file_name = os.path.join(folder_name, f"level_0{i}.txt")
    else:
        file_name = os.path.join(folder_name, f"level_{i}.txt")
    with open(file_name, 'w') as file:
        for row in maze_matrix:
            file.write(' '.join(map(str, row)) + '\n')

# for row in maze_matrix:
#     print(row)

# print(m.tostring())            # print walls only
# print ("-----------------------------\n")
# print(m.tostring(True))        # print walls and entrances
# print ("-----------------------------\n")
# print(m.tostring(True, True))  # print walls, entrances, and solution
# print ("-----------------------------\n")
# print(str(m))                  # print everything that is available
# print ("-----------------------------\n")
# print(m)                       # print everything that is available

# def showPNG(grid):
#     """Generate a simple image of the maze."""
#     plt.figure(figsize=(10, 5))
#     plt.imshow(grid, cmap=plt.cm.binary, interpolation='nearest')
#     plt.xticks([]), plt.yticks([])
#     plt.show()

# showPNG(m.grid)
