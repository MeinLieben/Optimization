#include <vector>
#include <iostream>
#include <math.h>
#include <algorithm>
#pragma once

const std::vector<double> operator+(const std::vector<double>& x, const std::vector<double>& y);
const std::vector<double> operator+(const std::vector<double>& x, const double& y);
const std::vector<double> operator+(const double& x, const std::vector<double>& y);
const std::vector<double> operator-(const std::vector<double>& x);
const std::vector<double> operator-(const std::vector<double>& x, const double& y);
const std::vector<double> operator-(const double& x, const std::vector<double>& y);
const std::vector<double> operator-(const std::vector<double>& x, const std::vector<double>& y);
const std::vector<double> operator*(const double& x, const std::vector<double>& y);
const std::vector<double> operator*(const std::vector<double>& x, const double& y);
std::ostream& operator<<(std::ostream& os, const std::vector<double>& x);
double norm(const std::vector<double>& x);
double norm(const double& y);