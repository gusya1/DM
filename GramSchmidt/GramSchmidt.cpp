#include <cmath>
#include <iostream>

using namespace std;

const int MAX_SIZE = 100;

// Функция для вычисления скалярного произведения двух векторов
double dot_product(double u[MAX_SIZE], double v[MAX_SIZE], int size)
{
  double result = 0;
  for (int i = 0; i < size; i++)
  {
    result += u[i] * v[i];
  }
  return result;
}

int main()
{
  setlocale(LC_ALL, "");

  int n;
  cout << "Введите размерность матрицы: ";
  cin >> n;

  double A[MAX_SIZE][MAX_SIZE] = {};
  cout << "Введите элементы матрицы: " << endl;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      cin >> A[i][j];
    }
  }

  // Инициализируем ортогональную матрицу Q
  double Q[MAX_SIZE][MAX_SIZE] = {};

  // Применяем метод Грама-Шмидта
  for (int j = 0; j < n; j++)
  {
    double v_j[MAX_SIZE];
    memcpy(v_j, A[j], sizeof(v_j));
    for (int i = 0; i < j; i++)
    {
      double proj = dot_product(v_j, Q[i], n) / dot_product(Q[i], Q[i], n);
      for (int k = 0; k < n; k++)
      {
        v_j[k] -= proj * Q[i][k];
      }
    }
    double norm = sqrt(dot_product(v_j, v_j, n));
    for (int k = 0; k < n; k++)
    {
      Q[j][k] = v_j[k] / norm;
    }
  }

  // Выводим ортогональную матрицу Q
  cout << "Ортогональная матрицa Q:" << endl;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      cout << Q[i][j] << " ";
    }
    cout << endl;
  }

  return 0;
}