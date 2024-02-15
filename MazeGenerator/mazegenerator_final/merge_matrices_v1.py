def read_matrix_from_file(file_name):
    matrix = []
    with open(file_name, "r") as file:
        for line in file:
            row = list(map(int, line.strip().split()))
            matrix.append(row)
    return matrix


def merge_matrices(matrix1, matrix2):
    return [row1 + row2 for row1, row2 in zip(matrix1, matrix2)]


def print_matrix(matrix, title="Matrix"):
    print(f"{title}:")
    for row in matrix:
        print(row)


def write_matrix_to_file(matrix, file_name):
    with open(file_name, "w") as file:
        for row in matrix:
            file.write(" ".join(map(str, row)) + "\n")


# Tên file đầu vào
input_file1 = "maze_txt/34.txt"
input_file2 = "maze_txt/34_transposed.txt"

# Đọc hai ma trận từ file
matrix1 = read_matrix_from_file(input_file1)
matrix2 = read_matrix_from_file(input_file2)

# Ghép hai ma trận
merged_matrix = merge_matrices(matrix1, matrix2)

# In và ghi ma trận ghép
print_matrix(merged_matrix, "Merged Matrix")
output_file_name = "maze_txt/merged_matrix.txt"
write_matrix_to_file(merged_matrix, output_file_name)

print(f"\nMerged Matrix written to: {output_file_name}")
