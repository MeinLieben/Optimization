#include "ovector.h"

double norm(const double& y) {
	return fabs(y);
}

const std::vector<double> operator+(const std::vector<double>& x, const std::vector<double>& y) {
	size_t n = std::min(x.size(), y.size());
	std::vector<double> z(n);
	for (size_t i = 0; i < n; ++i) z[i] = x[i] + y[i];
	return z;
}

const std::vector<double> operator+(const std::vector<double>& x, const double& y) {
	std::vector<double> z(x);
	for (size_t i = 0; i < z.size(); ++i) z[i] += y;
	return z;
}

const std::vector<double> operator+(const double& x, const std::vector<double>& y) {
	return y + x;
}

const std::vector<double> operator-(const std::vector<double>& x) {
	std::vector<double> z(x);
	for (size_t i = 0; i < z.size(); ++i) z[i] = -z[i];
	return z;
}

const std::vector<double> operator-(const std::vector<double>& x, const double& y) {
	std::vector<double> z(x);
	for (size_t i = 0; i < z.size(); ++i) z[i] -= y;
	return z;
}

const std::vector<double> operator-(const double& x, const std::vector<double>& y) {
	std::vector<double> z(y.size(), x);
	for (size_t i = 0; i < z.size(); ++i) z[i] -= y[i];
	return z;
}

const std::vector<double> operator-(const std::vector<double>& x, const std::vector<double>& y) {
	size_t n = std::min(x.size(), y.size());
	std::vector<double> z(n);
	for (size_t i = 0; i < n; ++i) z[i] = x[i] - y[i];
	return z;
}

const std::vector<double> operator*(const double& x, const std::vector<double>& y) {
	std::vector<double> z(y);
	for (size_t i = 0; i < z.size(); ++i) z[i] *= x;
	return z;
}

const std::vector<double> operator*(const std::vector<double>& x, const double& y) {
	return y * x;
}

std::ostream& operator<<(std::ostream& os, const std::vector<double>& x) {
	if (size_t n = x.size()) {
		std::cout << "(";
		for (size_t i = 0; i < n - 1; ++i) std::cout << x[i] << ", ";
		std::cout << x[n - 1] << ")";
	}
	return os;
}

double norm(const std::vector<double>& x) {
	double res = 0;
	for (size_t i = 0; i < x.size(); ++i) res += x[i] * x[i];
	return pow(res, 0.5);
}