import matplotlib.pyplot as plt
import numpy as np

def read_data(filename):
    x, y = [], []
    with open(filename, 'r') as f:
        for line in f:
            line = line.strip()
            if not line or line.startswith('#'):
                continue
            parts = line.split()
            x.append(int(parts[0]))
            y.append(float(parts[2]))
    return np.array(x), np.array(y)

data_path = './data/'

x_kruskal_1, y_kruskal_1 = read_data(data_path + 'kruskal_file_1.txt')
x_kruskal_2, y_kruskal_2 = read_data(data_path + 'kruskal_file_2.txt')
x_kruskal_3, y_kruskal_3 = read_data(data_path + 'kruskal_file_3.txt')

x_prim_bin_1, y_prim_bin_1 = read_data(data_path + 'prim_bin_file_1.txt')
x_prim_bin_2, y_prim_bin_2 = read_data(data_path + 'prim_bin_file_2.txt')
x_prim_bin_3, y_prim_bin_3 = read_data(data_path + 'prim_bin_file_3.txt')

x_prim_fib_1, y_prim_fib_1 = read_data(data_path + 'prim_fib_file_1.txt')
x_prim_fib_2, y_prim_fib_2 = read_data(data_path + 'prim_fib_file_2.txt')
x_prim_fib_3, y_prim_fib_3 = read_data(data_path + 'prim_fib_file_3.txt')

x_prim_vec_1, y_prim_vec_1 = read_data(data_path + 'prim_vec_file_1.txt')
x_prim_vec_2, y_prim_vec_2 = read_data(data_path + 'prim_vec_file_2.txt')
x_prim_vec_3, y_prim_vec_3 = read_data(data_path + 'prim_vec_file_3.txt')

plt.figure(figsize=(14, 6))

plt.subplot(1, 3, 1)
plt.plot(x_kruskal_1, y_kruskal_1, label='Алг. Краскалла')
plt.plot(x_prim_vec_1, y_prim_vec_1, label='Алг. Прима (вектор)')
plt.plot(x_prim_bin_1, y_prim_bin_1, label='Алг. Прима (бинарная куча)')
plt.plot(x_prim_fib_1, y_prim_fib_1, label='Алг. Прима (фибоначчиева куча)')
plt.title('m = n * 2')
plt.xlabel('Количество вершин графа')
plt.ylabel('Время (секунды)')
plt.legend(loc='upper left')
plt.grid(True, alpha=0.3)

plt.subplot(1, 3, 2)
plt.plot(x_kruskal_2, y_kruskal_2, label='Алг. Краскалла')
plt.plot(x_prim_vec_2, y_prim_vec_2, label='Алг. Прима (вектор)')
plt.plot(x_prim_bin_2, y_prim_bin_2, label='Алг. Прима (бинарная куча)')
plt.plot(x_prim_fib_2, y_prim_fib_2, label='Алг. Прима (фибоначчиева куча)')
plt.title('m = n * sqrt(n)')
plt.xlabel('Количество вершин графа')
plt.ylabel('Время (секунды)')
plt.legend(loc='upper left')
plt.grid(True, alpha=0.3)

plt.subplot(1, 3, 3)
plt.plot(x_kruskal_3, y_kruskal_3, label='Алг. Краскалла')
plt.plot(x_prim_vec_3, y_prim_vec_3, label='Алг. Прима (вектор)')
plt.plot(x_prim_bin_3, y_prim_bin_3, label='Алг. Прима (бинарная куча)')
plt.plot(x_prim_fib_3, y_prim_fib_3, label='Алг. Прима (фибоначчиева куча)')
plt.title('m = n * n / 4')
plt.xlabel('Количество вершин графа')
plt.ylabel('Время (секунды)')
plt.legend(loc='upper left')
plt.grid(True, alpha=0.3)

plt.suptitle('Сравнение алгоритмов Прима и Краскалла')

plt.show()