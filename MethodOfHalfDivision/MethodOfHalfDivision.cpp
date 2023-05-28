#include <cmath>
#include <functional>
#include <iostream>

using namespace std;

double f1(double x)
{
  return 2 * pow(x, 3) + pow(x, 2) - 7;
}

double f2(double x)
{
  return 5 * cos(3 * x) + 0.5 * x - 2;
}

double f3(double x)
{
  return pow(x, 5) - 2 * pow(x, 4) + 6 * pow(x, 2) + 2 * x - 4;
}

double f4(double x)
{
  return pow(x, 3) - 0.2 * pow(x, 2) + 0.2 * x - 1.2;
}

double f5(double x)
{
  return log(abs(pow(x, 3)) + 1) + pow(x, 3) - 2;
}

void solve(double a, double b, double eps, std::function<double(double)> f)
{
  cout << "interval[" << a << ", " << b << "]" << endl;
  int iterations = 0;
  double x       = 0;
  while (abs(b - a) > eps)
  {
    x = (a + b) / 2;
    if (f(a) * f(x) < 0)
      b = x;
    else
      a = x;
    iterations++;
  }
  cout << "Number of iterations: " << iterations << endl;
  x = (a + b) / 2;
  cout << "Root: " << x << endl;
  return;
}

int main()
{
  double eps = 0.0001;
  cout << "Function 1" << endl;
  solve(0, 2, eps, f1);
  cout << endl;
  cout << "Function 2" << endl;
  solve(0, 2 * 3.1415926, eps, f2);
  cout << endl;
  cout << "Function 3" << endl;
  solve(0, 2, eps, f3);
  cout << endl;
  cout << "Function 4" << endl;
  solve(0, 2, eps, f4);
  cout << endl;
  cout << "Function 5" << endl;
  solve(0, 2, eps, f5);

  return 0;
}