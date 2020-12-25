#include "area.h"

Area::Area(const std::vector<double>& a, const std::vector<double>& b) : a(a), b(b) {}

bool Area::isInside(const std::vector<double>& x0) const {
	bool res = true;
	for (size_t i = 0; i < x0.size(); ++i) {
		res = res && (x0[i] >= a[i] && x0[i] <= b[i]);
	}
	return res;
}
double Area::distToBorder(const std::vector<double>& x0, const std::vector<double>& p) const {
	if (isInside(x0)) {
		double minDist = std::numeric_limits<double>::max();
		double alpha, beta;
		for (size_t i = 0; i < x0.size(); ++i) {
			alpha = (a[i] - x0[i]) / p[i];
			beta = (b[i] - x0[i]) / p[i];
			minDist = std::min(minDist, std::max(alpha, beta));
		}
		return minDist;
	}
	else return -1;
}
std::vector<double> Area::geta() const {
	return a;
}
std::vector<double> Area::getb() const {
	return b;
}
