#include <iostream>
using namespace std;

const int MAX_SIZE = 100;

int main()
{
  setlocale(LC_ALL, "");

  int n;                        // Размерность матрицы
  double A[MAX_SIZE][MAX_SIZE]; // Матрица
  double det = 1.0;             // Определитель
  cout << "Введите размерность матрицы: ";
  cin >> n;
  cout << "Введите элементы матрицы: ";
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      cin >> A[i][j];
    }
  }
  // Приведение матрицы к треугольному виду
  for (int k = 0; k < n - 1; k++)
  {
    for (int i = k + 1; i < n; i++)
    {
      double factor = A[i][k] / A[k][k];
      for (int j = k + 1; j < n; j++)
      {
        A[i][j] -= factor * A[k][j];
      }
    }
  }
  // Вычисление определителя
  for (int i = 0; i < n; i++)
  {
    det *= A[i][i];
  }
  cout << "Определитель матрицы равен " << det << endl;
  return 0;
}