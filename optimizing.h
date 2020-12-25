#include <random>
#include <algorithm>
#include "area.h"
#include "stopCriterion.h"
#pragma once

class Optimizing {
protected:
	double epsilon;

public:
	Optimizing(const double& epsilon = 0.001);
    virtual std::vector<std::vector<double>> optimize(const std::vector<double>& x0, const std::function<double(std::vector<double>)>& f, const Area& area, const std::function<std::vector<double>(std::vector<double>)>& gradf, stopCriterion::State state = stopCriterion::State::grad) = 0;
};


class GROptimizing {
	double epsilon;
	const double GOLDEN_RATIO = (pow(5, 0.5) + 1) / 2;
	double lInterval;

    double optimize(const std::function<double(double)>& f, double l, double r) const;

public:
	GROptimizing( const double& epsilon = 0.001, const double& lInterval = 0.1);

	double optimize(const double& a, const double& b, const std::function<double(double)>& f);
};



class GradientOptimizing : public Optimizing{

public:
	GradientOptimizing(const double& epsilon = 0.01);

    std::vector<std::vector<double>> optimize(const std::vector<double>& x0, const std::function<double(std::vector<double>)>& f, const Area& area, const std::function<std::vector<double>(std::vector<double>)>& gradf, stopCriterion::State state = stopCriterion::State::grad) override;
};

class StochasticOptimizing : public Optimizing{
	double delta;
	double prob;
	std::random_device rd;

	std::vector<double>& xgen(std::vector<double>& x, const std::vector<double>& a, const std::vector<double>& b);

public:
	StochasticOptimizing(const double& epsilon = 0.001, const double& delta = 0.1, const double& prob = 0.8);
    std::vector<std::vector<double>> optimize(const std::vector<double>& x0, const std::function<double(std::vector<double>)>& f, const Area& area, const std::function<std::vector<double>(std::vector<double>)>& gradf = nullptr, stopCriterion::State state = stopCriterion::State::grad) override;
};
