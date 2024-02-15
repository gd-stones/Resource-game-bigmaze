# Tên đoạn mã: merge_matrices_from_files.py

# Mô tả: Đọc hai ma trận từ hai file txt và ghép chúng lại, chỉ xóa cột 1 ở đầu ma trận 2

# Đoạn mã Python:

def read_matrix_from_file(file_name):
    matrix = []
    with open(file_name, "r") as file:
        for line in file:
            row = list(map(int, line.strip().split()))
            matrix.append(row)
    return matrix


def merge_matrices(matrix1, matrix2):
    merged_matrix = []
    for row1, row2 in zip(matrix1, matrix2):
        merged_row = row1 + row2[1:]
        merged_matrix.append(merged_row)
    return merged_matrix


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

# Ghép hai ma trận, chỉ xóa cột 1 ở đầu ma trận 2
merged_matrix = merge_matrices(matrix1, matrix2)

# In và ghi ma trận ghép
print_matrix(merged_matrix, "Merged Matrix")
output_file_name = "maze_txt/merged_matrix_v2.txt"
write_matrix_to_file(merged_matrix, output_file_name)

print(f"\nMerged Matrix written to: {output_file_name}")
