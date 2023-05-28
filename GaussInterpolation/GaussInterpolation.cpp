#include <iostream>
#include <vector>

using namespace std;

const int MAX_SIZE = 100;

double divided_difference(const vector<double>& x, const vector<double>& y, int i, int j)
{
  if (i == j)
  {
    return y[i];
  }
  else
  {
    return (divided_difference(x, y, i + 1, j) - divided_difference(x, y, i, j - 1)) / (x[j] - x[i]);
  }
}

vector<double> compute_gauss_weights(const vector<double>& x)
{
  const auto n = x.size();
  auto w       = vector<double>(n);

  for (int i = 0; i < n; i++)
    w[i] = 1.;

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      if (i != j)
      {
        w[i] *= x[i] - x[j];
      }
    }
    w[i] = 1.0 / w[i];
  }

  return w;
}

vector<double> compute_gauss_coefficients(const vector<double>& x, const vector<double>& y)
{
  auto n = x.size();
  vector<double> a(n);
  for (int i = 0; i < n; i++)
  {
    a[i] = divided_difference(x, y, 0, i);
  }

  return a;
}

double interpolate_gauss_first(const vector<double>& x, const vector<double>& y, double t)
{
  auto n   = x.size();
  double s = y[0];
  for (int i = 1; i < n; i++)
  {
    double p = 1.0;
    for (int j = 0; j < i; j++)
    {
      p *= (t - x[j]);
    }
    s += p * compute_gauss_coefficients(x, y)[i];
  }

  return s;
}

double interpolate_gauss_second(const vector<double>& x, const vector<double>& y, const vector<double>& w, double t)
{
  auto n   = x.size();
  double s = 0.0;
  for (int i = 0; i < n; i++)
  {
    s += w[i] * y[i] / (t - x[i]);
  }

  return s;
}

int main()
{
  int n;
  cout << "Enter the number of data points: ";
  cin >> n;
  auto x = vector<double>(MAX_SIZE);
  auto y = vector<double>(MAX_SIZE);
  cout << "Enter the data points:" << endl;
  for (int i = 0; i < n; i++)
  {
    cin >> x[i] >> y[i];
  }
  auto w = compute_gauss_weights(x);

  while (true)
  {
    double t;
    cout << "Enter a point to interpolate (or a negative number to quit): ";
    cin >> t;
    if (t < 0)
    {
      break;
    }

    cout << "Interpolated value (using first Gauss formula): " << interpolate_gauss_first(x, y, t) << endl;
    cout << "Interpolated value (using second Gauss formula): " << interpolate_gauss_second(x, y, w, t) << endl;
  }

  return 0;
}