/**
 * @file
 * @author  Олег Чемокос
 * @version 1.0
 *
 * @section LICENSE
 *
 * Это бесплатное програмное обеспечение. Эта и последующие версии
 * не предполагают лицензии и могут распространяться свободно
 *
 * Этот пакет дает возможность проводить многомерную оптимизацию
 * стохастическим методом и методом градиентного спуска, а также
 * одномерную оптимизацию методом золотого сечения, на котором
 * основан градиентный спуск в части сведения задачи одномерной оптимизации
 */

#include <random>
#include <algorithm>
#include "area.h"
#include "stopCriterion.h"
#pragma once



/**
* @section DESCRIPTION
*
* Базовый класс оптимизации
* @param epsilon точность оптимизации
*/
class Optimizing {
protected:
	double epsilon;

public:
    /**
    *
    * Конструктор базового класса
    * @param epsilon точность оптимизации
    */
	Optimizing(const double& epsilon = 0.001);
    /**
    *
    * Виртуальная функция оптимизации
    * @param x0 начальная точка
    * @param f функция, значение которой минимизируется
    * @param area область, в которой минимизируются значения
    * @param gradf градиент функции f
    * @param state выбор критерия остановки
    */
    virtual std::vector<std::vector<double>> optimize(const std::vector<double>& x0, const std::function<double(std::vector<double>)>& f, const Area& area, const std::function<std::vector<double>(std::vector<double>)>& gradf, stopCriterion::State state = stopCriterion::State::grad) = 0;
    virtual ~Optimizing(){};
};

/**
*
* Одномерная оптимизация методом золотых сечений
* @param epsilon точность оптимизации
* @param lInterval длина интервала разбиения
*/
class GROptimizing {
	double epsilon;
	const double GOLDEN_RATIO = (pow(5, 0.5) + 1) / 2;
	double lInterval;

    /**
    *
    * Оптимизация на отрезке разбиения
    * @param f функция, значение которой минимизируется
    * @param l левый конец отрезка
    * @param r правый конец отрезка
    */
    double optimize(const std::function<double(double)>& f, double l, double r) const;

public:

	GROptimizing( const double& epsilon = 0.001, const double& lInterval = 0.1);

    /**
    *
    * Оптимизация на всем отрезке
    * @param f функция, значение которой минимизируется
    * @param a левый конец отрезка
    * @param b правый конец отрезка
    */
	double optimize(const double& a, const double& b, const std::function<double(double)>& f);
};


/**
*
* Многомерная оптимизация методом градиентного спуска
*/
class GradientOptimizing : public Optimizing{

public:
	GradientOptimizing(const double& epsilon = 0.01);

    std::vector<std::vector<double>> optimize(const std::vector<double>& x0, const std::function<double(std::vector<double>)>& f, const Area& area, const std::function<std::vector<double>(std::vector<double>)>& gradf, stopCriterion::State state = stopCriterion::State::grad) override;
    ~GradientOptimizing(){};
};

/**
*
* Многомерная оптимизация стохастическим методом
* @param delta задает локальную область поиска
* @param prob вероятность поиска в локальной области
* @param rd генератор случайных чисел
*/
class StochasticOptimizing : public Optimizing{
	double delta;
	double prob;
	std::random_device rd;

    /**
    *
    * Генерация случайной точки в заданной области
    * @param x генерируемая точка
    * @param a левая граница
    * @param b правая граница
    */
	std::vector<double>& xgen(std::vector<double>& x, const std::vector<double>& a, const std::vector<double>& b);

public:
	StochasticOptimizing(const double& epsilon = 0.001, const double& delta = 0.1, const double& prob = 0.8);
    std::vector<std::vector<double>> optimize(const std::vector<double>& x0, const std::function<double(std::vector<double>)>& f, const Area& area, const std::function<std::vector<double>(std::vector<double>)>& gradf = nullptr, stopCriterion::State state = stopCriterion::State::grad) override;
    ~StochasticOptimizing(){};
};
