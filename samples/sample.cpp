#pragma once

#include "dheap.h"
#include "dijkstra.h"
#include "vector.h"


int main() {
    setlocale(LC_ALL, "rus");
    int n, m;
    std::cout << "Введите число вершин:\n";
    std::cin >> n;

    std::cout << "Задать граф, с заданным числом вершин ...\n";
    std::cout << "1) матрицей смежности \n2) cписком смежности \n3) Сгенерировать случайный граф\n";

    int op;
    std::cin >> op;
    Graph gr(n);
    do {
        if (op == 1) {
            Vector<Vector<double>> mat(n, Vector<double>(n));
            std::cout << "Введите матрицу " << n << " x " << n << ":\n";
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    std::cin >> mat[i][j];
                    if (mat[i][j] < 0.0) {
                        throw std::exception("Веса не могут быть отрицательными");
                    }
                }
            }
            gr.get_by_matrix(mat);
            if (!gr.check_connect()) {
                throw std::exception("Граф не является связным");
            }
            std::cout << "В графе присуствуют следующие ребра: \n";
            gr.display();
            int v;
            std::cout << "Начать поиск ближайщих путей из вершины ...\n";
            do {
                std::cin >> v;
                if (!(v >= 0 && v < n))
                    std::cout << "Вершины с таким номером в графе нет\n";
            } while (!(v >= 0 && v < n));

            Vector<double> ans = gr.dijkstra(v);
            for (int i = 0; i < n; i++)
                std::cout << "Расстояние до вершины " << i << " = " << ans[i] << '\n';
            
        }
        else if (op == 2) {
            Vector<Vector<int>> a(n);
            Vector<Vector<double>> weight(n);
            std::cout << "Введите список смежности для каждой вершины в формате [номер вершины 1] : [вес ребра 1] \
[номер вершины 2] : [вес ребра 2] ... \n";
            for (int i = 0; i < n; i++) {
                int v; double w;
                char _;
                std::cout << "Степерь вершины " << i << ":\n";
                int n;
                std::cin >> n;
                std::cout << "Введите ребра в указанном выше формате:\n";
                for (int i = 0; i < n; i++) {
                    std::cin >> v >> _ >> w;
                    if (w < 0.0) {
                        throw std::exception("Веса не могут быть отрицательными");
                    }
                    a[i].push_back(v);
                    weight[i].push_back(w);
                }
            }
            gr.get_by_list(a, weight);
            if (!gr.check_connect()) {
                throw std::exception("Граф не является связным");
            }
            std::cout << "В графе присуствуют следующие ребра: \n";
            gr.display();
            int v;
            std::cout << "Начать поиск ближайщих путей из вершины ...\n";
            do {
                std::cin >> v;
                if (!(v >= 0 && v < n))
                    std::cout << "Вершины с таким номером в графе нет\n";
            } while (!(v >= 0 && v < n));
            Vector<double> ans = gr.dijkstra(v);
            for (int i = 0; i < n; i++)
                std::cout << "Расстояние до вершины " << i << " = " << ans[i] << '\n';
        }
        else if (op == 3) {
            std::cout << "Введите число ребер:\n";
            std::cin >> m;
            std::cout << "Тип графа\n";
            std::cout << "1) неориентированный \n2) ориентированный\n";
            int type;
            std::cin >> type;
            type--;
            gr.generate_random(m, type);
            std::cout << "В графе присуствуют следующие ребра: \n";
            gr.display();
            int v;
            std::cout << "Начать поиск ближайщих путей из вершины ...\n";
            do {
                std::cin >> v;
                if (!(v >= 0 && v < n))
                    std::cout << "Вершины с таким номером в графе нет\n";
            } while (!(v >= 0 && v < n));
            Vector<double> ans = gr.dijkstra(v);
            for (int i = 0; i < n; i++)
                std::cout << "Расстояние до вершины " << i << " = " << ans[i] << '\n';
        }
        else {
            std::cout << "Некорректный ввод\n";
        }
    } while (!(op > 0 && op < 4));

}