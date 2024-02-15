def read_matrix_from_file(file_name):
    matrix = []
    with open(file_name, "r") as file:
        for line in file:
            row = list(map(int, line.strip().split()))
            matrix.append(row)
    return matrix


def find_3_position(matrix):
    for index_row, row in enumerate(matrix):
        if 3 in row:
            index_col = row.index(3)
            return index_row, index_col
    return None, None


def merge_matrices(matrix1, matrix2):
    row_3_matrix1, col_3_matrix1 = find_3_position(matrix1)
    row_3_matrix2, col_3_matrix2 = find_3_position(matrix2)
    if col_3_matrix1 > col_3_matrix2:
        front_matrix = matrix1
        row_3_front_matrix = row_3_matrix1
        behind_matrix = matrix2
        row_3_behind_matrix = row_3_matrix2
    else:
        front_matrix = matrix2
        row_3_front_matrix = row_3_matrix2
        behind_matrix = matrix1
        row_3_behind_matrix = row_3_matrix1

    delta_row = row_3_behind_matrix - row_3_front_matrix
    merge_matrix = []
    if delta_row == 0:
        if len(front_matrix) > len(behind_matrix):
            for i in range(0, len(behind_matrix)):
                merge_matrix[i] = front_matrix[i][:-1] + behind_matrix[i]
            for i in range(len(behind_matrix), len(front_matrix)):
                merge_matrix.append(
                    front_matrix[i] + [4] * len(behind_matrix[0][:-1]))
        elif len(front_matrix) < len(behind_matrix):
            for i in range(0, len(front_matrix)):
                merge_matrix[i] = front_matrix[i][:-1] + behind_matrix[i]
            for i in range(len(front_matrix), len(behind_matrix)):
                merge_matrix.append(
                    [4] * len(front_matrix[0][:-1]) + behind_matrix[i])
        else:
            for i in range(0, len(front_matrix)):
                merge_matrix[i] = front_matrix[i][:-1] + behind_matrix[i]
    elif delta_row > 0:
        for i in range(0, delta_row):
            merge_matrix.append(
                [4] * len(front_matrix[0][:-1]) + behind_matrix[i])
        delta = len(behind_matrix) - delta_row - len(front_matrix)
        if delta < 0:
            for i in range(delta_row, len(behind_matrix)):
                merge_matrix.append(
                    front_matrix[i - delta_row][:-1] + behind_matrix[i])
            for i in range(len(behind_matrix) - delta_row, len(front_matrix)):
                merge_matrix.append(
                    front_matrix[i] + [4] * len(behind_matrix[0][:-1]))
        elif delta > 0:
            for i in range(0, len(front_matrix)):
                merge_matrix.append(
                    front_matrix[i][:-1] + behind_matrix[i + delta_row])
            for i in range(len(front_matrix) + delta_row, len(behind_matrix)):
                merge_matrix.append(
                    [4] * len(front_matrix[0][:-1]) + behind_matrix[i])
        else:
            for i in range(0, len(front_matrix)):
                merge_matrix.append(
                    front_matrix[i][:-1] + behind_matrix[i + delta_row])
    elif delta_row < 0:
        for i in range(0, -1 * delta_row):
            merge_matrix.append(
                front_matrix[i] + [4] * len(behind_matrix[0][:-1]))
        delta = len(front_matrix) - (-1 * delta_row) - len(behind_matrix)
        if delta < 0:
            for i in range(-1 * delta_row, len(front_matrix)):
                merge_matrix.append(
                    front_matrix[i][:-1] + behind_matrix[i - (-1 * delta_row)])
            for i in range(len(front_matrix) - (-1 * delta_row), len(behind_matrix)):
                merge_matrix.append(
                    [4] * len(front_matrix[0][:-1]) + behind_matrix[i])
        elif delta > 0:
            for i in range(0, len(behind_matrix)):
                merge_matrix.append(
                    front_matrix[i + (-1 * delta_row)][:-1] + behind_matrix[i])
            for i in range(len(behind_matrix) + (-1 * delta_row), len(front_matrix)):
                merge_matrix.append(
                    front_matrix[i] + [4] * len(behind_matrix[0][:-1]))
        else:
            for i in range(0, len(behind_matrix)):
                merge_matrix.append(
                    front_matrix[i + (-1 * delta_row)][:-1] + behind_matrix[i])
    return merge_matrix


def standardize_matrix(matrix):
    for row in matrix:
        if row[0] == 3 or row[-1] == 3:
            for i in range(len(row)):
                if row[i] == 3:
                    row[i] = 1
        else:
            for i in range(len(row)):
                if row[i] == 3:
                    row[i] = 0
    return matrix


def print_matrix(matrix, title="Matrix"):
    print(f"{title}:")
    for row in matrix:
        print(row)


def write_matrix_to_file(matrix, file_name):
    with open(file_name, "w") as file:
        for row in matrix:
            file.write(" ".join(map(str, row)) + "\n")


# Tên file đầu vào
input_file1 = "maze_txt/1.txt"
input_file2 = "maze_txt/10.txt"

# Đọc hai ma trận từ file
matrix1 = read_matrix_from_file(input_file1)
matrix2 = read_matrix_from_file(input_file2)


# # Ghép hai ma trận
merged_matrix = merge_matrices(matrix1, matrix2)
standardized_matrix = standardize_matrix(merged_matrix)

# # In và ghi ma trận ghép
output_file_name = "maze_txt/1_10_v2.txt"
write_matrix_to_file(standardized_matrix, output_file_name)

print(f"\nMerged Matrix written to: {output_file_name}")


# input_file1 = "maze_txt/1.txt"
# input_file2 = "maze_txt/10.txt"
# output_file_name = "maze_txt/1_10.txt"
