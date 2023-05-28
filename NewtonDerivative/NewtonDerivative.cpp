#include <cassert>
#include <cmath>
#include <corecrt_math_defines.h>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <ranges>
#include <vector>


// Функция для вычисления производной с помощью метода правых конечных разностей
double ComputeRightDifference(const std::vector<double>& x, const std::vector<double>& y, double point)
{
  const auto n = x.size();
  auto index   = 0;
  auto h       = 0.0;

  // Нахождение ближайшего значения x, меньшего или равного точке
  for (auto i = 0; i < n - 1; ++i)
  {
    if (x[i] < point)
    {
      index = i;
      h     = x[i + 1] - x[i];
    }
    else
      break;
  }
  if (index == n - 1)
    return NAN;

  return (y[index + 1] - y[index]) / h;
}

// Функция для вычисления производной с помощью метода левых конечных разностей
double ComputeLeftDifference(const std::vector<double>& x, const std::vector<double>& y, double point)
{
  const auto n = x.size();
  auto index   = 0;
  auto h       = 0.0;

  // Нахождение ближайшего значения x, большего или равного точке
  for (auto i = 1; i < n; ++i)
  {
    if (x[i] >= point)
    {
      index = i;
      h     = x[i] - x[i - 1];
      break;
    }
  }
  if (index == 0)
    return NAN;

  return (y[index] - y[index - 1]) / h;
  ;
}


void printTable(const std::vector<std::vector<double>>& table)
{
  for (const auto& row : table)
  {
    for (const auto& value : row)
      std::cout << std::fixed << std::setprecision(4) << value << ", ";
    std::cout << std::endl;
  }
}

int factorial(int x)
{
  if (x == 0)
    return 1;
  return x * factorial(x - 1);
}

double ComputeDerivative(const std::vector<double>& x, const std::vector<double>& y, double point)
{
  constexpr auto N = 5;
  // product (t-i)
  static const auto diffFuncs = std::vector<std::function<double(double)>>{
      [](double) { return 1.0; },
      [](double t) { return 2 * t - 1; },
      [](double t) { return 3 * t * t - 6 * t + 2; },
      [](double t) { return 4 * t * t * t - 18 * t * t + 22 * t - 6; },
      [](double t) { return 5 * t * t * t * t - 40 * t * t * t + 105 * t * t - 100 * t + 24; }};

  const auto n = x.size();
  assert(n > N);

  auto differences = std::vector<std::vector<double>>(n, std::vector<double>(N + 1));
  for (int i = 0; i < n; i++)
  {
    differences[i][0] = y[i];
    for (int k = 1; k <= std::min(N, i); k++)
      differences[i][k] = differences[i][k - 1] - differences[i - 1][k - 1];
  }

  //printTable(differences);

  auto i0_iter = std::ranges::find_if(x, [&](auto val) { return point < val; });
  if (i0_iter == x.end())
    return NAN;

  auto i0 = std::distance(x.begin(), i0_iter);

  auto h = x[i0 + 1] - x[i0];
  auto t = (point - x[i0]) / h;

  auto dy = 0.0;
  for (auto i = 0; i < std::min<size_t>(N, n - i0 - 1); i++)
    dy += differences[i0 + i + 1][i + 1] * (diffFuncs[i](t) / static_cast<double>(factorial(i + 1)));

  return 1 / h * dy;
}

double func(double x)
{
  return x * x * x - 6 * x * x + 4 * x + 12 + std::sin(x);
}

double trueDerivative(double x)
{
  return 3 * x * x - 12 * x + 4 + std::cos(x);
}


std::map<double, double> getFuncFoints(const std::function<double(double)> f, double begin, double end, double eps)
{
  auto result = std::map<double, double>{};
  for (double i = begin; i < end; i += eps)
    result[i] = f(i);
  return result;
}

int main()
{
  setlocale(LC_ALL, "");
  // Входные данные - последовательность точек (x, y)

  const auto begin  = 0.0;
  const auto end    = 5.0;
  const auto points = getFuncFoints(func, begin, end, 0.5);
  auto xs           = std::vector<double>{};
  auto ys           = std::vector<double>{};
  for (const auto& [x, y] : points)
  {
    xs.push_back(x);
    ys.push_back(y);
  }

  std::cout << "x\tИстинная_производная\tНьютон\tправые_разности\tлевые_разности" << std::endl;
  std::cout << std::fixed << std::setprecision(8);
  for (auto i = begin; i < end; i += 0.1)
    std::cout << i << '\t' << trueDerivative(i) << '\t' << ComputeDerivative(xs, ys, i) << '\t'
              << ComputeRightDifference(xs, ys, i) << '\t' << ComputeLeftDifference(xs, ys, i) << '\t' << std::endl;

  return 0;
}
