#ifndef IncludeGenerator
#define IncludeGenerator
#include "field/WinBox.hpp"
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <memory>

using namespace std;

long long comb(int n, int k);
double roundNice(double x);
vector<double> create_multipliers(int rows, std::string risk, double rtp);
vector<unique_ptr<WinBox>> create_win_boxes(int rows, std::string risk);
vector<unique_ptr<Circle>> create_field(int rows);

#endif