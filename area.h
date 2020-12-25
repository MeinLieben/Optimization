#include <vector>
#include <algorithm>
#pragma once

/**
*
* Класс, задающий прямоугольную область
* @param a левая граница
* @param b правая граница
*/
class Area {
	std::vector<double> a;
	std::vector<double> b;

public:
	Area(const std::vector<double>& a, const std::vector<double>& b);

    /**
    *
    * Проверка, лежит ли заданная точка в области
    * @param x0 заданная точка
    */
	bool isInside(const std::vector<double>& x0) const;

    /**
    *
    * Расстояние от точки до границы области в выбранном направлении
    * @param x0 заданная точка
    * @param p выбранное направление
    */
	double distToBorder(const std::vector<double>& x0, const std::vector<double>& p) const;

    /**
     * Возвращает левую границу области
     */
	std::vector<double> geta() const;
    /**
     * Возвращает правую границу области
     */
	std::vector<double> getb() const;
};
