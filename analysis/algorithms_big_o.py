import matplotlib.pyplot as plt
import numpy as np

def complexity_prim_binary_heap(vertex_count, edges_count):
    """
    Алгоритм Прима с бинарной кучей
    Сложность: O((V + E) log V)
    """
    vertex_count = float(vertex_count)
    edges_count = float(edges_count)
    return (vertex_count + edges_count) * np.log2(vertex_count)

def complexity_prim_fibonacci_heap(vertex_count, edges_count):
    """
    Алгоритм Прима с фибоначчиевой кучей
    Сложность: O(E + V log V)
    """
    vertex_count = float(vertex_count)
    edges_count = float(edges_count)
    return edges_count + vertex_count * np.log2(vertex_count)

def complexity_prim_vector(vertex_count, edges_count):
    """
    Алгоритм Прима с векторной реализацией (простой поиск минимума)
    Сложность: O(V^2 + E)
    """
    vertex_count = float(vertex_count)
    edges_count = float(edges_count)
    return vertex_count * vertex_count + edges_count

def complexity_kruskal(vertex_count, edges_count):
    """
    Алгоритм Краскалла с сортировкой рёбер
    Сложность: O(E log E)
    """
    vertex_count = float(vertex_count)
    edges_count = float(edges_count)
    return edges_count * np.log2(edges_count)

def read_data(filename, complexity_func):
    x, y = [], []
    with open(filename, 'r') as f:
        for line in f:
            line = line.strip()
            if not line or line.startswith('#'):
                continue
            parts = line.split()
            vertex_count = int(parts[0])
            edges_count = int(parts[1])
            time = float(parts[2])
            x.append(vertex_count)
            y.append(time / complexity_func(vertex_count, edges_count))
    return np.array(x), np.array(y)

data_path = './data/'

x_kruskal_1, y_kruskal_1 = read_data(data_path + 'kruskal_file_1.txt', complexity_kruskal)
x_kruskal_2, y_kruskal_2 = read_data(data_path + 'kruskal_file_2.txt', complexity_kruskal)
x_kruskal_3, y_kruskal_3 = read_data(data_path + 'kruskal_file_3.txt', complexity_kruskal)

x_prim_bin_1, y_prim_bin_1 = read_data(data_path + 'prim_bin_file_1.txt', complexity_prim_binary_heap)
x_prim_bin_2, y_prim_bin_2 = read_data(data_path + 'prim_bin_file_2.txt', complexity_prim_binary_heap)
x_prim_bin_3, y_prim_bin_3 = read_data(data_path + 'prim_bin_file_3.txt', complexity_prim_binary_heap)

x_prim_fib_1, y_prim_fib_1 = read_data(data_path + 'prim_fib_file_1.txt', complexity_prim_fibonacci_heap)
x_prim_fib_2, y_prim_fib_2 = read_data(data_path + 'prim_fib_file_2.txt', complexity_prim_fibonacci_heap)
x_prim_fib_3, y_prim_fib_3 = read_data(data_path + 'prim_fib_file_3.txt', complexity_prim_fibonacci_heap)

x_prim_vec_1, y_prim_vec_1 = read_data(data_path + 'prim_vec_file_1.txt', complexity_prim_vector)
x_prim_vec_2, y_prim_vec_2 = read_data(data_path + 'prim_vec_file_2.txt', complexity_prim_vector)
x_prim_vec_3, y_prim_vec_3 = read_data(data_path + 'prim_vec_file_3.txt', complexity_prim_vector)

plt.figure(figsize=(16, 12))

plt.subplot(2, 2, 1)
plt.plot(x_kruskal_1, y_kruskal_1, label='m = n * 2')
plt.plot(x_kruskal_2, y_kruskal_2, label='m = n * sqrt(n)')
plt.plot(x_kruskal_3, y_kruskal_3, label='m = n * n / 4')
plt.title('Алгоритм Краскалла', fontsize=12)
plt.xlabel('Количество вершин графа')
plt.ylabel('Отношение к оценке сложности')
plt.legend(loc='upper left')
plt.grid(True, alpha=0.3)

plt.subplot(2, 2, 2)
plt.plot(x_prim_bin_1, y_prim_bin_1, label='m = n * 2')
plt.plot(x_prim_bin_2, y_prim_bin_2, label='m = n * sqrt(n)')
plt.plot(x_prim_bin_3, y_prim_bin_3, label='m = n * n / 4')
plt.title('Алгоритм Прима (бинарная куча)', fontsize=12)
plt.xlabel('Количество вершин графа')
plt.ylabel('Отношение к оценке сложности')
plt.legend(loc='upper left')
plt.grid(True, alpha=0.3)

plt.subplot(2, 2, 3)
plt.plot(x_prim_fib_1, y_prim_fib_1, label='m = n * 2')
plt.plot(x_prim_fib_2, y_prim_fib_2, label='m = n * sqrt(n)')
plt.plot(x_prim_fib_3, y_prim_fib_3, label='m = n * n / 4')
plt.title('Алгоритм Прима (фибоначчиева куча)', fontsize=12)
plt.xlabel('Количество вершин графа')
plt.ylabel('Отношение к оценке сложности')
plt.legend(loc='upper left')
plt.grid(True, alpha=0.3)

plt.subplot(2, 2, 4)
plt.plot(x_prim_vec_1, y_prim_vec_1, label='m = n * 2')
plt.plot(x_prim_vec_2, y_prim_vec_2, label='m = n * sqrt(n)')
plt.plot(x_prim_vec_3, y_prim_vec_3, label='m = n * n / 4')
plt.title('Алгоритм Прима (вектор)', fontsize=12)
plt.xlabel('Количество вершин графа')
plt.ylabel('Отношение к оценке сложности')
plt.legend(loc='upper left')
plt.grid(True, alpha=0.3)

plt.suptitle('Сравнение времени выполнения алгоритмов MST с теоретической оценкой сложности', fontsize=14)
plt.show()