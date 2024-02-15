import os

def remove_border(matrix):
    # Xóa hàng đầu và hàng cuối
    matrix = matrix[1:-1]
    
    # Xóa cột đầu và cột cuối
    matrix = [row[1:-1] for row in matrix]
    print(1)
    
    return matrix

def read_matrix_from_file(file_path):
    with open(file_path, 'r') as file:
        lines = file.readlines()
        matrix = [[int(num) for num in line.strip().split()] for line in lines]
    return matrix

def write_matrix_to_file(matrix, file_path):
    with open(file_path, 'w') as file:
        for row in matrix:
            file.write(' '.join(map(str, row)) + '\n')

# Đường dẫn đến thư mục chứa các tệp
folder_path = 'level'

# Lặp qua các tệp trong thư mục
for file_name in os.listdir(folder_path):
    if file_name.endswith('.txt'):
        file_path = os.path.join(folder_path, file_name)
        
        # Đọc mảng từ tệp
        matrix = read_matrix_from_file(file_path)
        
        # Sửa mảng
        matrix = remove_border(matrix)
        
        # Ghi mảng đã sửa vào tệp
        write_matrix_to_file(matrix, file_path)

# testttttttttttttttt
