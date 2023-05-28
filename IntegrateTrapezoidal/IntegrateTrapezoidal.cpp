#include <cmath>
#include <corecrt_math_defines.h>
#include <functional>
#include <iomanip>
#include <iostream>
#include <vector>


double func1(double x)
{
  return x * x;
}

double func2(double x)
{
  using namespace std;
  return pow(sin(x), 2);
}

double func3(double x)
{
  using namespace std;
  return sin(2 * x) + sin(7 * x) + 8;
}

double func4(double x)
{
  using namespace std;
  return 2 * pow(x, 4) + pow(x, 3) + 2 * pow(x, 2) + 3 * x + 24;
}

double func5(double x)
{
  using namespace std;
  return log(x * x + 1) + sin(x / 3) + 17;
}

double func6(double x)
{
  using namespace std;
  return pow(5, x) + sin(x) + x + 11;
}

double func7(double x)
{
  using namespace std;
  return pow(x, 5) + 2 * pow(x, 4) + 3 * pow(x, 3) + 4 * pow(x, 2) + 5 * x + 6;
}

// Метод трапеций для численного интегрирования
double integrateTrapezoidal(double a, double b, int n, const std::function<double(double)>& function)
{
  auto h   = (b - a) / n;
  auto sum = 0.5 * (function(a) + function(b)); // Первый и последний члены
  for (auto i = 1; i < n; i++)
  {
    auto x = a + i * h;
    sum += function(x);
  }
  return h * sum;
}

// Метод прямоугольников для численного интегрирования
double integrateRectangular(double a, double b, int n, const std::function<double(double)>& function)
{
  auto h   = (b - a) / n;
  auto sum = 0.0;
  for (auto i = 0; i < n; i++)
  {
    auto x = a + (i + 0.5) * h;
    sum += function(x);
  }
  return h * sum;
}

// Метод Симпсона для численного интегрирования
double integrateSimpson(double a, double b, int n, const std::function<double(double)>& function)
{
  auto h   = (b - a) / n;
  auto sum = function(a) + function(b);
  for (int i = 1; i < n; i += 2)
  {
    auto x = a + i * h;
    sum += 4 * function(x);
  }
  for (int i = 2; i < n - 1; i += 2)
  {
    auto x = a + i * h;
    sum += 2 * function(x);
  }
  return (h / 3.0) * sum;
}


double calculateTrapezoidalErrorTerm(double a, double b, int n)
{
  auto h  = (b - a) / n;
  auto M2 = 1.0; // Здесь предполагаем, что производная второго порядка ограничена на заданном интервале
  return (M2 * pow(h, 2)) / 12.0 * (b - a);
}


struct FuncForIntegrate
{
  std::function<double(double)> function;
  double a;
  double b;
  double trueValue;
};


int main()
{
  setlocale(LC_ALL, "");

  auto funcsForIntegrate = std::vector<FuncForIntegrate>{
      {func1, -5, 5, -250.0 / 3},
      {func2, -M_PI, M_PI, -M_PI},
      {func3, -M_PI, M_PI, -16.0 * M_PI},
      {func4, -1, 3, -3664.0 / 15},
      {func5, -100, 100, -4.0 * (50.0 * (15.0 + std::log(10001.0)) + 1.0 / std::tan(100))},
      {func6, -M_PI, M_PI, -22.0 * M_PI - (2 * std::sinh(M_PI * std::log(5.0))) / std::log(5.0)},
      {func7, -7, 7, -216664.0 / 15},
  };

  auto a = 0.0; // Начальная точка интервала
  auto b = 5.0; // Конечная точка интервала
  auto n = 50;  // Количество разбиений интервала (шаг сетки)

  std::cout << "номер, реальное_значение, метод_трапеций, метод_прямоугольников, метод_Симпсона, "
               "остаточный_член_МТ"
            << std::endl;
  for (int i = 0; i < funcsForIntegrate.size(); i++)
  {
    const auto& funcForIntegrate = funcsForIntegrate[i];
    std::cout << std::fixed << std::setprecision(8);
    std::cout << i + 1 << '\t' << std::abs(funcForIntegrate.trueValue) << '\t'
              << integrateTrapezoidal(funcForIntegrate.a, funcForIntegrate.b, n, funcForIntegrate.function) << '\t'
              << integrateRectangular(funcForIntegrate.a, funcForIntegrate.b, n, funcForIntegrate.function) << '\t'
              << integrateSimpson(funcForIntegrate.a, funcForIntegrate.b, n, funcForIntegrate.function) << '\t'
              << calculateTrapezoidalErrorTerm(funcForIntegrate.a, funcForIntegrate.b, n) << std::endl;
  }

  return 0;
}