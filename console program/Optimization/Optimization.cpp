#include "optimizing.h"

double getValueInBounders(double left, double right)
{
	double value;
	while (true) {
		std::cout << "Enter a value between " << left << " and " << right << ": ";
		std::cin >> value;
		if (std::cin.fail() || (!std::cin.fail() && (value < left || value > right)))
		{
			std::cin.clear();
			std::cin.ignore(2048, '\n');
			std::cout << "Input is invalid. Please try again.\n";
		}
		else
		{
			std::cin.ignore(2048, '\n');
			return value;
		}
	}
}

int getValue() {
	int value;
	while (true) {
		std::cout << "> ";
		std::cin.clear();
		std::cin >> value;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(2048, '\n');
			std::cout << "Input is invalid. Please try again.\n";
		}
		else
		{
			std::cin.ignore(2048, '\n');
			return value;
		}
	}
}

double f1(const std::vector<double>& x) {
	return (x[0] - 1) * (x[0] - 1) + (x[1] - 2) * (x[1] - 2);
}

std::vector<double> gradf1(const std::vector<double>& x) {
	return { 2 * (x[0] - 1), 2 * (x[1] - 2) };
}

double f2(const std::vector<double>& x) {
	return (1 - x[0]) * (1 - x[0]) + 100 * (x[1] - x[0] * x[0]) * (x[1] - x[0] * x[0]);
}

std::vector<double> gradf2(const std::vector<double>& x) {
	return { 2 * (x[0] - 1) - 400 * x[0] * (x[1] - x[0] * x[0]), 200 * (x[1] - x[0] * x[0]) };
}

double f3(const std::vector<double>& x) {
	return (x[0] + 2 * x[1] - 7) * (x[0] + 2 * x[1] - 7) + (2 * x[0] + x[1] - 5) * (2 * x[0] + x[1] - 5);
}

std::vector<double> gradf3(std::vector<double> x) {
	return { 2 * (x[0] + 2 * x[1] - 7) + 4 * (2 * x[0] + x[1] - 5), 4 * (x[0] + 2 * x[1] - 7) + 2 * (2 * x[0] + x[1] - 5) };
}

double f4(const std::vector<double>& x) {
	double res = 0;
	for (size_t i = 0; i < x.size(); ++i) {
		res += x[i] * x[i];
	}
	return res;
}

std::vector<double> gradf4(const std::vector<double>& x) {
	std::vector<double> res;
	for (size_t i = 0; i < x.size(); ++i) {
		res.push_back(2 * x[i]);
	}
	return res;
}


int main()
{

	int regulator = 1;
	double value;
	Optimizing* opt;
	stopCriterion::State stop = stopCriterion::State::grad;
	std::function<double(std::vector<double>)> f;
	std::function<std::vector<double>(std::vector<double>)> gradf;
	std::vector<double> a, b, x0;
	std::vector<std::vector<double>> result;

	while (regulator) {

		std::cout << "Set accuracy (epsilon). Epsilon is [1 / (number iteration after last improvement)] for stochastic optimization.\n";
		value = getValueInBounders(0.001, 1);

		system("cls");
		std::cout << "Choose method optimization:\n1. Gradient optimization\n2. Stochastic optimization\n";
		regulator = getValue();
		system("cls");
		if (regulator == 1) {
			opt = new GradientOptimizing(value);
			std::cout << "Choose stop criterion:\n1. Norm of gradient\n2. Norm of difference between element\n3. Norm of relation different between value of function\n";
			switch (regulator = getValue()) {
			default:
				stop = stopCriterion::State::grad;
				break;
			case 2:
				stop = stopCriterion::State::diffElem;
				break;
			case 3:
				stop = stopCriterion::State::relDiffFun;
			}

			system("cls");
		}
		else opt = new StochasticOptimizing(value);

		std::cout << "Choose function:\n1. f(x, y) = (x - 1)^2 + (y - 2)^2\n2. f(x, y) = (x - 1)^2 + 100(y - x^2)^2\n3. f(x, y) = (x + 2y - 7)^2 + (2x + y - 5)^2\n4. f(x1,..,xn) = x1^2 + ... + xn^2\n";
		switch (regulator = getValue()) {
		default:
			f = f1;
			gradf = gradf1;
			break;
		case 2:
			f = f2;
			gradf = gradf2;
			break;
		case 3:
			f = f3;
			gradf = gradf3;
			break;
		case 4:
			f = f4;
			gradf = gradf4;
		}
		system("cls");
		if (regulator == 4) {
			std::cout << "Set dimension: ";
			regulator =  getValue();
			regulator = __max(1, regulator);
			for (unsigned int i = 0; i < regulator; ++i) {
				std::cout << "Set min x" << i + 1 << "\n";
				a.push_back(value = getValueInBounders(-99, 99));
				std::cout << "Set max x" << i + 1 << "\n";
				b.push_back(value = getValueInBounders(value + 1, 101));
			}
			system("cls");
			std::cout << "Choose starting point\n";
			for (unsigned int i = 0; i < regulator; ++i) {
				std::cout << "Set x" << i + 1 << "\n";
				x0.push_back(value = getValueInBounders(a[i], b[i]));
			}
		}
		else {
			std::cout << "Set min x\n";
			a.push_back(value = getValueInBounders(-99, 99));
			std::cout << "Set max x\n";
			b.push_back(value = getValueInBounders(value + 1, 101));
			std::cout << "Set min y\n";
			a.push_back(value = getValueInBounders(-99, 99));
			std::cout << "Set max y\n";
			b.push_back(value = getValueInBounders(value + 1, 101));
			system("cls");
			std::cout << "Choose starting point\n";
			std::cout << "Set x0\n";
			x0.push_back(value = getValueInBounders(a[0], b[0]));
			std::cout << "Set y0\n";
			x0.push_back(value = getValueInBounders(a[1], b[1]));
		}
		system("cls");
		result = opt->optimize(x0, f, Area(a, b), gradf, stop);
		std::cout << result[result.size() - 1] << "\n" << f(result[result.size() - 1]) << "\nDo you want start again? Enter 0, if you don't.\n";
		regulator = getValue();
		system("cls");
	}

	delete opt;
}