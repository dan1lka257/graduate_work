import matplotlib.pyplot as plt
import numpy as np

def read_data(filename):
    x, y = [], []
    with open(filename, 'r') as f:
        for line in f:
            parts = line.strip().split()
            x.append(int(parts[0]))
            y.append(float(parts[1]))
    return np.array(x), np.array(y)

data_path = '../data/'

x_kruskal_1, y_kruskal_1 = read_data(data_path + 'kruskal_file_1.txt')
x_kruskal_2, y_kruskal_2 = read_data(data_path + 'kruskal_file_2.txt')
x_kruskal_3, y_kruskal_3 = read_data(data_path + 'kruskal_file_3.txt')
x_prim_1, y_prim_1 = read_data(data_path + 'prim_file_1.txt')
x_prim_2, y_prim_2 = read_data(data_path + 'prim_file_2.txt')
x_prim_3, y_prim_3 = read_data(data_path + 'prim_file_3.txt')

plt.figure(figsize=(14, 6))

plt.subplot(1, 3, 1)
plt.plot(x_kruskal_1, y_kruskal_1, label='Алгоритм Краскалла')
plt.plot(x_prim_1, y_prim_1, label='Алгоритм Прима')
plt.title('m = n * 2')
plt.xlabel('Количество вершин графа')
plt.ylabel('Время (секунды)')
plt.legend(loc='upper left')

plt.subplot(1, 3, 2)
plt.plot(x_kruskal_2, y_kruskal_2, label='Алгоритм Краскалла')
plt.plot(x_prim_2, y_prim_2, label='Алгоритм Прима')
plt.title('m = n * sqrt(n)')
plt.xlabel('Количество вершин графа')
plt.ylabel('Время (секунды)')
plt.legend(loc='upper left')

plt.subplot(1, 3, 3)
plt.plot(x_kruskal_3, y_kruskal_3, label='Алгоритм Краскалла')
plt.plot(x_prim_3, y_prim_3, label='Алгоритм Прима')
plt.title('m = n * n / 4')
plt.xlabel('Количество вершин графа')
plt.ylabel('Время (секунды)')
plt.legend(loc='upper left')

plt.suptitle('Сравнение алгоритмов Прима и Краскалла')

plt.show()