#include <functional>
#include "ovector.h"
#pragma once

/**
 * Базовый класс критерия остановки
 * @param maxIteration максимальное количество итераций до остановки
 * @param epsilon точность, задающая остановку при ее достижении
 */
class stopCriterion {
protected:
	unsigned int maxIteration;
	double epsilon;

public:
     ///Набор критериев для остановки
    enum class State { grad///< Остановка по норме градиента
                       , diffElem///< Остановка по норме разности аргументов
                       ,relDiffFun///< Остановка по относительной норме разности значений функции
    };
	stopCriterion(unsigned int maxIteration, double epsilon);
    /**
     * Возвращает true, если количество итераций привысило максимум
     * @param i количество итераций
     */
	bool nStop(const unsigned int& i) const;
    /**
     * Виртуальная функция остановки (возвращает true, если остановка необходима)
     * @param i количество итераций
     * @param count количество итераций с последнего улучшения
     * @param x текущая точка
     * @param xOld предыдущая точка
     * @param f функция, значение которой минимизируется
     * @param gradf градиент функции f
     * @return
     */
	virtual bool stop(const unsigned int& i, const unsigned int& count, const std::vector<double>& x, const std::vector<double>& xOld, const std::function<double(std::vector<double>)> & f = nullptr, const std::function<std::vector<double>(std::vector<double>)> & gradf = nullptr) const = 0;
    virtual ~stopCriterion(){};
};

/**
 * Остановка на основе нормы градиента (для метода ГС)
 */
class stopGrad : public stopCriterion {
public:
	stopGrad(unsigned int maxIteration = 100, double epsilon = 0.1);
	bool stop(const unsigned int& i, const unsigned int& count, const std::vector<double>& x, const std::vector<double>& xOld, const std::function<double(std::vector<double>)>& f = nullptr, const std::function<std::vector<double>(std::vector<double>)>& gradf = nullptr) const override;
    ~stopGrad(){};
};

/**
 * Остановка на основе нормы разности элементов (для метода ГС)
 */
class stopDiffElem : public stopCriterion {
public:
	stopDiffElem(unsigned int maxIteration = 1000, double epsilon = 0.1);
	bool stop(const unsigned int& i, const unsigned int& count, const std::vector<double>& x, const std::vector<double>& xOld, const std::function<double(std::vector<double>)>& f = nullptr, const std::function<std::vector<double>(std::vector<double>)>& gradf = nullptr) const override;
    ~stopDiffElem(){};
};

/**
 * Остановка на основе относительной нормы разности значений функции (для метода ГС)
 */
class stopRelDiffFun : public stopCriterion {
public:
	stopRelDiffFun(unsigned int maxIteration = 100, double epsilon = 0.1);
	bool stop(const unsigned int& i, const unsigned int& count, const std::vector<double>& x, const std::vector<double>& xOld, const std::function<double(std::vector<double>)>& f = nullptr, const std::function<std::vector<double>(std::vector<double>)>& gradf = nullptr) const override;
    ~stopRelDiffFun(){};
};

/**
 * Остановка на основе количества итераций с последнего улучшения (для стохастического метода)
 */
class stopStochastic : public stopCriterion {
public:
	stopStochastic(unsigned int maxIteration = 10000, double epsilon = 0.01);
	bool stop(const unsigned int& i, const unsigned int& count, const std::vector<double>& x, const std::vector<double>& xOld, const std::function<double(std::vector<double>)>& f = nullptr, const std::function<std::vector<double>(std::vector<double>)>& gradf = nullptr) const override;
    ~stopStochastic(){};
};

