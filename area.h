#include <vector>
#include <algorithm>
#pragma once

class Area {
	std::vector<double> a;
	std::vector<double> b;

public:
	Area(const std::vector<double>& a, const std::vector<double>& b);
	bool isInside(const std::vector<double>& x0) const;
	double distToBorder(const std::vector<double>& x0, const std::vector<double>& p) const;
	std::vector<double> geta() const;
	std::vector<double> getb() const;
};