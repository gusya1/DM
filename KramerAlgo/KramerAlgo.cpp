#include <iostream>
#include <vector>

using namespace std;

const int MAX_SIZE = 100;

// Функция для вычисления определителя матрицы
double determinant(double matrix[MAX_SIZE][MAX_SIZE], int size)
{
  double A[MAX_SIZE][MAX_SIZE] = {};
  memcpy(A, matrix, sizeof(A));
  double det = 1.0;
  for (int k = 0; k < size - 1; k++)
  {
    for (int i = k + 1; i < size; i++)
    {
      double factor = A[i][k] / A[k][k];
      for (int j = k + 1; j < size; j++)
      {
        A[i][j] -= factor * A[k][j];
      }
    }
  }
  // Вычисление определителя
  for (int i = 0; i < size; i++)
  {
    det *= A[i][i];
  }
  return det;
}

int main()
{
  setlocale(LC_ALL, "");

  int n;
  cout << "Введите порядок системы линейных уравнений: ";
  cin >> n;
  double matrix[MAX_SIZE][MAX_SIZE] = {};
  double b[MAX_SIZE]                = {};
  cout << "Введите коэффициенты системы линейных уравнений (по одному на "
          "строку):"
       << endl;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      cin >> matrix[i][j];
    }
  }
  cout << "Введите столбец свободных членов:" << endl;
  ;
  for (int i = 0; i < n; i++)
  {
    cin >> b[i];
  }
  // Вычисление определителя матрицы A
  double det_A = determinant(matrix, n);
  if (det_A == 0)
  {
    cout << "Система линейных уравнений имеет бесконечное число решений или не "
            "имеет решений"
         << endl;
    return 0;
  }
  // Вычисление решения системы линейных уравнений
  cout << "Решение системы линейных уравнений:\n";
  double submatrix[MAX_SIZE][MAX_SIZE];
  for (int i = 0; i < n; i++)
  {
    memcpy(submatrix, matrix, sizeof(submatrix));
    for (int j = 0; j < n; j++)
    {
      submatrix[j][i] = b[j];
    }
    double det_B = determinant(submatrix, n);
    double x     = det_B / det_A;
    cout << "x" << i + 1 << " = " << x << endl;
  }
  return 0;
}