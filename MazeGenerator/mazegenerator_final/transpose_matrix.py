input_file_name = "maze_txt/34.txt"

with open(input_file_name, "r") as file:
    # Đọc ma trận từ file
    matrix = [list(map(int, line.split())) for line in file.readlines()]

# Chuyển vị ma trận
transposed_matrix = [list(row) for row in zip(*matrix)]

# In ma trận chuyển vị
print("Original Matrix:")
for row in matrix:
    print(row)

print("\nTransposed Matrix:")
for row in transposed_matrix:
    print(row)

# Ghi ma trận chuyển vị vào file mới
output_file_name = input_file_name.replace(".txt", "_transposed.txt")
with open(output_file_name, "w") as output_file:
    for row in transposed_matrix:
        output_file.write(" ".join(map(str, row)) + "\n")

print(f"\nTransposed Matrix written to: {output_file_name}")
