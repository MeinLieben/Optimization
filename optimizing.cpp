#include "optimizing.h"

Optimizing::Optimizing(const double& epsilon) : epsilon(epsilon) {}

GROptimizing::GROptimizing(const double& epsilon, const double& lInterval) : epsilon(epsilon), lInterval(lInterval){}

double GROptimizing::optimize(const std::function<double(double)>& f, double l, double r) const {
	stopDiffElem SC(1000, epsilon);
	double ll = r - (r - l) / GOLDEN_RATIO, rr = r + l - ll, fll = f(ll), frr = f(rr);
	for (unsigned int i = 0; (!SC.stop(i, 0, { l }, { r })); ++i) {
		if (fll < frr) {
			r = rr;
			rr = ll;
			ll = r + l - rr;
			frr = fll;
			fll = f(ll);
		}
		else {
			l = ll;
			ll = rr;
			rr = r + l - ll;
			fll = frr;
			frr = f(rr);
		}
	}

	return (r + l) / 2;
}

double GROptimizing::optimize(const double& a, const double& b, const std::function<double(double)>& f) {
	double nInterval = (int)((b - a) / lInterval);
	if (nInterval == 0) {
		this->lInterval = b - a;
		nInterval = 1;
	}
	double argmin = optimize(f, a, a + lInterval);
	double curArgMin;
	for (unsigned int i = 1; i < nInterval; ++i) {
		curArgMin = optimize(f, a + i * lInterval, a + (i + 1.) * lInterval);
		if (f(argmin) > f(curArgMin)) argmin = curArgMin;
	}
	return argmin;
}

GradientOptimizing::GradientOptimizing(const double& epsilon) : Optimizing(epsilon) {}

std::vector<std::vector<double>> GradientOptimizing::optimize(const std::vector<double>& x0, const std::function<double(std::vector<double>)>& f, const Area& area, const std::function<std::vector<double>(std::vector<double>)>& gradf, stopCriterion::State state) {
    std::vector<std::vector<double>> result;
    result.push_back(x0);
    std::vector<double> p = -gradf(x0), xOld = x0, x = x0, xPrevOld = x0;
    p = p * (1 / norm(p));
    GROptimizing GRO;
	stopCriterion* SC;
	switch (state) {
		case stopCriterion::State::grad:
			SC = new stopGrad(100, epsilon);
			break;
		case stopCriterion::State::diffElem:
			SC = new stopDiffElem(100, epsilon);
			break;
		case stopCriterion::State::relDiffFun:
			SC = new stopRelDiffFun(100, epsilon);
			break;
		default: SC = new stopGrad(100, epsilon);
	}
	double maxAlpha = area.distToBorder(x0, p);
	double alpha = GRO.optimize(0, maxAlpha, [f, x0, p](double alpha) {return f(x0 + alpha * p); });
	unsigned int i;
	for (i = 0; !SC->stop(i, 0, x = x + alpha * p, xOld = x, f, gradf); ++i) {
        result.push_back(x);
		if (i % 5 == 4) {
			p = x - xPrevOld;
		}
		else {
			p = -gradf(x);
		}
        p = p * (1 / norm(p));
		maxAlpha = area.distToBorder(x, p);
		alpha = GRO.optimize(0, maxAlpha, [f, x, p](double alpha) {return f(x + alpha * p) ; });
		xPrevOld = xOld;
        //std::cout << x << p << f(x) << "\n";
	}
    result.push_back(x);
	delete SC;
    std::cout << i + 1 << std::endl;
    return result;
}

StochasticOptimizing::StochasticOptimizing(const double& epsilon, const double& delta, const double& prob) : Optimizing(epsilon), delta(delta), prob(prob) {}

std::vector<double>& StochasticOptimizing::xgen(std::vector<double>& x, const std::vector<double>& a, const std::vector<double>& b) {
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0., 1.);
	double alpha;
	for (unsigned int k = 0; k < x.size(); ++k) {
		alpha = dis(gen);
		x[k] = a[k] + alpha * (b[k] - a[k]);
	}
	return x;
}

std::vector<std::vector<double>> StochasticOptimizing::optimize(const std::vector<double>& x0, const std::function<double(std::vector<double>)>& f, const Area& area, const std::function<std::vector<double>(std::vector<double>)>& gradf, stopCriterion::State state) {
    std::vector<std::vector<double>> result;
    result.push_back(x0);
    std::vector<double> argmin = x0, x(x0.size()), a = area.geta(), b = area.getb(), e(x0.size(), 1),
		adelta = x0 - std::min(delta, area.distToBorder(x0, -e)),
		bdelta = x0 + std::min(delta, area.distToBorder(x0, e));
	double min = f(x0), fx;
	std::mt19937 gen(rd());
	std::bernoulli_distribution bd(prob);
	stopStochastic SC(10000, epsilon);
	unsigned int i, count;
	for (i = 0, count = 0; !SC.stop(i, count, {}, {}); ++i, ++count) {
		if (bd(gen)) {
			xgen(x, adelta, bdelta);
		}
		else {
			xgen(x, a, b);
		}
		if ((fx = f(x)) < min) {
			count = 0;
			min = fx;
			argmin = x;
            result.push_back(x);
			adelta = x - std::min(delta, area.distToBorder(x0, -e));
			bdelta = x + std::min(delta, area.distToBorder(x0, e));
		}
	}
	std::cout << i << std::endl;
    return result;
}
