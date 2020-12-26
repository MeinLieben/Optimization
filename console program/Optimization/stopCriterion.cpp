#include "stopCriterion.h"

bool stopCriterion::nStop(const unsigned int& i) const {
	return i > maxIteration;
}

stopCriterion::stopCriterion(unsigned int maxIteration, double epsilon) : maxIteration(maxIteration), epsilon(epsilon) {};

stopGrad::stopGrad(unsigned int maxIteration, double epsilon) : stopCriterion(maxIteration, epsilon) {};

bool stopGrad::stop(const unsigned int& i, const unsigned int& count, const std::vector<double>& x, const std::vector<double>& xOld, const std::function<double(std::vector<double>)>& f, const std::function<std::vector<double>(std::vector<double>)>& gradf) const {
	if (nStop(i)) return true;
	return gradf ? norm(gradf(x)) < epsilon : true;
}

stopDiffElem::stopDiffElem(unsigned int maxIteration, double epsilon) : stopCriterion(maxIteration, epsilon) {};

bool stopDiffElem::stop(const unsigned int& i, const unsigned int& count, const std::vector<double>& x, const std::vector<double>& xOld, const std::function<double(std::vector<double>)>& f, const std::function<std::vector<double>(std::vector<double>)>& gradf) const {
	if (nStop(i)) return true;
	return norm(x - xOld) < epsilon;
}

stopRelDiffFun::stopRelDiffFun(unsigned int maxIteration, double epsilon) : stopCriterion(maxIteration, epsilon) {};

bool stopRelDiffFun::stop(const unsigned int& i, const unsigned int& count, const std::vector<double>& x, const std::vector<double>& xOld, const std::function<double(std::vector<double>)>& f, const std::function<std::vector<double>(std::vector<double>)>& gradf) const {
	if (nStop(i)) return true;
	return f ? norm((f(x) - f(xOld)) / f(x)) < epsilon : true;
}

stopStochastic::stopStochastic(unsigned int maxIteration, double epsilon): stopCriterion(maxIteration, epsilon) {};

bool stopStochastic::stop(const unsigned int& i, const unsigned int& count, const std::vector<double>& x, const std::vector<double>& xOld, const std::function<double(std::vector<double>)>& f, const std::function<std::vector<double>(std::vector<double>)>& gradf) const {
	return count > 1. / epsilon || nStop(i);
}

