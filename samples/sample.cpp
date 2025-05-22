#pragma once

#include "dheap.h"
#include "dijkstra.h"
#include "vector.h"


int main() {
    setlocale(LC_ALL, "rus");
    int n, m;
    std::cout << "������� ����� ������:\n";
    std::cin >> n;

    std::cout << "������ ����, � �������� ������ ������ ...\n";
    std::cout << "1) �������� ��������� \n2) c������ ��������� \n3) ������������� ��������� ����\n";

    int op;
    std::cin >> op;
    Graph gr(n);
    do {
        if (op == 1) {
            Vector<Vector<double>> mat(n, Vector<double>(n));
            std::cout << "������� ������� " << n << " x " << n << ":\n";
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    std::cin >> mat[i][j];
                    if (mat[i][j] < 0.0) {
                        throw std::exception("���� �� ����� ���� ��������������");
                    }
                }
            }
            gr.get_by_matrix(mat);
            if (!gr.check_connect()) {
                throw std::exception("���� �� �������� �������");
            }
            std::cout << "� ����� ����������� ��������� �����: \n";
            gr.display();
            int v;
            std::cout << "������ ����� ��������� ����� �� ������� ...\n";
            do {
                std::cin >> v;
                if (!(v >= 0 && v < n))
                    std::cout << "������� � ����� ������� � ����� ���\n";
            } while (!(v >= 0 && v < n));

            Vector<double> ans = gr.dijkstra(v);
            for (int i = 0; i < n; i++)
                std::cout << "���������� �� ������� " << i << " = " << ans[i] << '\n';
            
        }
        else if (op == 2) {
            Vector<Vector<int>> a(n);
            Vector<Vector<double>> weight(n);
            std::cout << "������� ������ ��������� ��� ������ ������� � ������� [����� ������� 1] : [��� ����� 1] \
[����� ������� 2] : [��� ����� 2] ... \n";
            for (int i = 0; i < n; i++) {
                int v; double w;
                char _;
                std::cout << "������� ������� " << i << ":\n";
                int n;
                std::cin >> n;
                std::cout << "������� ����� � ��������� ���� �������:\n";
                for (int i = 0; i < n; i++) {
                    std::cin >> v >> _ >> w;
                    if (w < 0.0) {
                        throw std::exception("���� �� ����� ���� ��������������");
                    }
                    a[i].push_back(v);
                    weight[i].push_back(w);
                }
            }
            gr.get_by_list(a, weight);
            if (!gr.check_connect()) {
                throw std::exception("���� �� �������� �������");
            }
            std::cout << "� ����� ����������� ��������� �����: \n";
            gr.display();
            int v;
            std::cout << "������ ����� ��������� ����� �� ������� ...\n";
            do {
                std::cin >> v;
                if (!(v >= 0 && v < n))
                    std::cout << "������� � ����� ������� � ����� ���\n";
            } while (!(v >= 0 && v < n));
            Vector<double> ans = gr.dijkstra(v);
            for (int i = 0; i < n; i++)
                std::cout << "���������� �� ������� " << i << " = " << ans[i] << '\n';
        }
        else if (op == 3) {
            std::cout << "������� ����� �����:\n";
            std::cin >> m;
            std::cout << "��� �����\n";
            std::cout << "1) ����������������� \n2) ���������������\n";
            int type;
            std::cin >> type;
            type--;
            gr.generate_random(m, type);
            std::cout << "� ����� ����������� ��������� �����: \n";
            gr.display();
            int v;
            std::cout << "������ ����� ��������� ����� �� ������� ...\n";
            do {
                std::cin >> v;
                if (!(v >= 0 && v < n))
                    std::cout << "������� � ����� ������� � ����� ���\n";
            } while (!(v >= 0 && v < n));
            Vector<double> ans = gr.dijkstra(v);
            for (int i = 0; i < n; i++)
                std::cout << "���������� �� ������� " << i << " = " << ans[i] << '\n';
        }
        else {
            std::cout << "������������ ����\n";
        }
    } while (!(op > 0 && op < 4));

}