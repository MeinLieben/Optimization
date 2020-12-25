#include <functional>
#include "ovector.h"
#pragma once

class stopCriterion {
protected:
	unsigned int maxIteration;
	double epsilon;

public:
	enum class State { grad, diffElem, relDiffFun };
	stopCriterion(unsigned int maxIteration, double epsilon);
	bool nStop(const unsigned int& i) const;
	virtual bool stop(const unsigned int& i, const unsigned int& count, const std::vector<double>& x, const std::vector<double>& xOld, const std::function<double(std::vector<double>)> & f = nullptr, const std::function<std::vector<double>(std::vector<double>)> & gradf = nullptr) const = 0;
};

class stopGrad : public stopCriterion {
public:
	stopGrad(unsigned int maxIteration = 100, double epsilon = 0.1);
	bool stop(const unsigned int& i, const unsigned int& count, const std::vector<double>& x, const std::vector<double>& xOld, const std::function<double(std::vector<double>)>& f = nullptr, const std::function<std::vector<double>(std::vector<double>)>& gradf = nullptr) const override;
};

class stopDiffElem : public stopCriterion {
public:
	stopDiffElem(unsigned int maxIteration = 1000, double epsilon = 0.1);
	bool stop(const unsigned int& i, const unsigned int& count, const std::vector<double>& x, const std::vector<double>& xOld, const std::function<double(std::vector<double>)>& f = nullptr, const std::function<std::vector<double>(std::vector<double>)>& gradf = nullptr) const override;
};

class stopRelDiffFun : public stopCriterion {
public:
	stopRelDiffFun(unsigned int maxIteration = 100, double epsilon = 0.1);
	bool stop(const unsigned int& i, const unsigned int& count, const std::vector<double>& x, const std::vector<double>& xOld, const std::function<double(std::vector<double>)>& f = nullptr, const std::function<std::vector<double>(std::vector<double>)>& gradf = nullptr) const override;
};

class stopStochastic : public stopCriterion {
public:
	stopStochastic(unsigned int maxIteration = 10000, double epsilon = 0.01);
	bool stop(const unsigned int& i, const unsigned int& count, const std::vector<double>& x, const std::vector<double>& xOld, const std::function<double(std::vector<double>)>& f = nullptr, const std::function<std::vector<double>(std::vector<double>)>& gradf = nullptr) const override;
};

