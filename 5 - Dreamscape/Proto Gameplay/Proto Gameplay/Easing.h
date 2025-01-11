#ifndef EASING_H
#define EASING_H
#include <cmath>
#include "CreaMaths.h"

class Easing {
public:

	/*
	* currentTime = Temps actuel
	* minValue = Valeur minimale voulue
	* maxValue = Valeur maximale voulue
	* totalTime = Temps voulu pour arriver a la valeur max
	*/

	static double linear(double currentTime, double minValue, double maxValue, double totalTime) {
		return maxValue * currentTime / totalTime + minValue;
	}

	static double easeInQuad(double currentTime, double minValue, double maxValue, double totalTime) {
		currentTime /= totalTime;
		return maxValue * currentTime * currentTime + minValue;
	}

	static double easeOutQuad(double currentTime, double minValue, double maxValue, double totalTime) {
		currentTime /= totalTime;
		return -maxValue * currentTime * (currentTime - 2) + minValue;
	}

	static double easeInOutQuad(double currentTime, double minValue, double maxValue, double totalTime) {
		currentTime /= totalTime / 2;
		if (currentTime < 1) return maxValue / 2 * currentTime * currentTime + minValue;
		currentTime--;
		return -maxValue / 2 * (currentTime * (currentTime - 2) - 1) + minValue;
	}

	static double easeInCubic(double currentTime, double minValue, double maxValue, double totalTime) {
		currentTime /= totalTime;
		return maxValue * currentTime * currentTime * currentTime + minValue;
	}

	static double easeOutCubic(double currentTime, double minValue, double maxValue, double totalTime) {
		currentTime /= totalTime;
		currentTime--;
		return maxValue * (currentTime * currentTime * currentTime + 1) + minValue;
	}

	static double easeInOutCubic(double currentTime, double minValue, double maxValue, double totalTime) {
		currentTime /= totalTime / 2;
		if (currentTime < 1) return maxValue / 2 * currentTime * currentTime * currentTime + minValue;
		currentTime -= 2;
		return maxValue / 2 * (currentTime * currentTime * currentTime + 2) + minValue;
	}

	static double easeInQuart(double currentTime, double minValue, double maxValue, double totalTime) {
		currentTime /= totalTime;
		return maxValue * currentTime * currentTime * currentTime * currentTime + minValue;
	}

	static double easeOutQuart(double currentTime, double minValue, double maxValue, double totalTime) {
		currentTime /= totalTime;
		currentTime--;
		return -maxValue * (currentTime * currentTime * currentTime * currentTime - 1) + minValue;
	}

	static double easeInOutQuart(double currentTime, double minValue, double maxValue, double totalTime) {
		currentTime /= totalTime / 2;
		if (currentTime < 1) return maxValue / 2 * currentTime * currentTime * currentTime * currentTime + minValue;
		currentTime -= 2;
		return -maxValue / 2 * (currentTime * currentTime * currentTime * currentTime - 2) + minValue;
	}

	static double easeInQuint(double currentTime, double minValue, double maxValue, double totalTime) {
		currentTime /= totalTime;
		return maxValue * currentTime * currentTime * currentTime * currentTime * currentTime + minValue;
	}

	static double easeOutQuint(double currentTime, double minValue, double maxValue, double totalTime) {
		currentTime /= totalTime;
		currentTime--;
		return maxValue * (currentTime * currentTime * currentTime * currentTime * currentTime + 1) + minValue;
	}

	static double easeInOutQuint(double currentTime, double minValue, double maxValue, double totalTime) {
		currentTime /= totalTime / 2;
		if (currentTime < 1) return maxValue / 2 * currentTime * currentTime * currentTime * currentTime * currentTime + minValue;
		currentTime -= 2;
		return maxValue / 2 * (currentTime * currentTime * currentTime * currentTime * currentTime + 2) + minValue;
	}

	static double easeInSine(double currentTime, double minValue, double maxValue, double totalTime) {
		return -maxValue * std::cos(currentTime / totalTime * (PI / 2)) + maxValue + minValue;
	}

	static double easeOutSine(double currentTime, double minValue, double maxValue, double totalTime) {
		return maxValue * std::sin(currentTime / totalTime * (PI / 2)) + minValue;
	}

	static double easeInOutSine(double currentTime, double minValue, double maxValue, double totalTime) {
		return -maxValue / 2 * (std::cos(PI * currentTime / totalTime) - 1) + minValue;
	}

	static double easeInExpo(double currentTime, double minValue, double maxValue, double totalTime) {
		return maxValue * std::pow(2, 10 * (currentTime / totalTime - 1)) + minValue;
	}

	static double easeOutExpo(double currentTime, double minValue, double maxValue, double totalTime) {
		return maxValue * (-std::pow(2, -10 * currentTime / totalTime) + 1) + minValue;
	}

	static double easeInOutExpo(double currentTime, double minValue, double maxValue, double totalTime) {
		currentTime /= totalTime / 2;
		if (currentTime < 1) return maxValue / 2 * std::pow(2, 10 * (currentTime - 1)) + minValue;
		currentTime--;
		return maxValue / 2 * (-std::pow(2, -10 * currentTime) + 2) + minValue;
	}

	static double easeInCirc(double currentTime, double minValue, double maxValue, double totalTime) {
		currentTime /= totalTime;
		return -maxValue * (std::sqrt(1 - currentTime * currentTime) - 1) + minValue;
	}

	static double easeOutCirc(double currentTime, double minValue, double maxValue, double totalTime) {
		currentTime /= totalTime;
		currentTime--;
		return maxValue * std::sqrt(1 - currentTime * currentTime) + minValue;
	}

	static double easeInOutCirc(double currentTime, double minValue, double maxValue, double totalTime) {
		currentTime /= totalTime / 2;
		if (currentTime < 1) return -maxValue / 2 * (std::sqrt(1 - currentTime * currentTime) - 1) + minValue;
		currentTime -= 2;
		return maxValue / 2 * (std::sqrt(1 - currentTime * currentTime) + 1) + minValue;
	}

	static double easeInBack(double currentTime, double minValue, double maxValue, double totalTime) {
		double s = 1.70158;
		double postFix = currentTime /= totalTime;
		return maxValue * (postFix)*currentTime * ((s + 1) * currentTime - s) + minValue;
	}

	static double easeOutBack(double currentTime, double minValue, double maxValue, double totalTime) {
		double s = 1.70158;
		currentTime = currentTime / totalTime - 1;
		return maxValue * (currentTime * currentTime * ((s + 1) * currentTime + s) + 1) + minValue;
	}

	static double easeInOutBack(double currentTime, double minValue, double maxValue, double totalTime) {
		double s = 1.70158;
		double postFix = currentTime /= totalTime / 2;
		if (postFix < 1) return maxValue / 2 * (postFix * postFix * (((s *= (1.525)) + 1) * postFix - s)) + minValue;
		double t2 = currentTime - 2;
		return maxValue / 2 * ((t2 * t2 * (((s *= (1.525)) + 1) * t2 + s) + 2)) + minValue;
	}

	static double easeInElastic(double currentTime, double minValue, double maxValue, double totalTime) {
		double s = 1.70158;
		double p = 0;
		double a = maxValue;
		if (currentTime == 0) return minValue;
		if ((currentTime /= totalTime) == 1) return minValue + maxValue;
		if (!p) p = totalTime * .3;
		if (a < std::abs(maxValue)) {
			a = maxValue;
			s = p / 4;
		}
		else {
			s = p / (2 * PI) * std::asin(maxValue / a);
		}
		return -(a * std::pow(2, 10 * (currentTime -= 1)) * std::sin((currentTime * totalTime - s) * (2 * PI) / p)) + minValue;
	}

	static double easeOutElastic(double currentTime, double minValue, double maxValue, double totalTime) {
		double s = 1.70158;
		double p = 0;
		double a = maxValue;
		if (currentTime == 0) return minValue;
		if ((currentTime /= totalTime) == 1) return minValue + maxValue;
		if (!p) p = totalTime * .3;
		if (a < std::abs(maxValue)) {
			a = maxValue;
			s = p / 4;
		}
		else {
			s = p / (2 * PI) * std::asin(maxValue / a);
		}
		return a * std::pow(2, -10 * currentTime) * std::sin((currentTime * totalTime - s) * (2 * PI) / p) + maxValue + minValue;
	}

	static double easeInOutElastic(double currentTime, double minValue, double maxValue, double totalTime) {
		double s = 1.70158;
		double p = 0;
		double a = maxValue;
		if (currentTime == 0) return minValue;
		if ((currentTime /= totalTime / 2) == 2) return minValue + maxValue;
		if (!p) p = totalTime * (.3 * 1.5);
		if (a < std::abs(maxValue)) {
			a = maxValue;
			s = p / 4;
		}
		else {
			s = p / (2 * PI) * std::asin(maxValue / a);
		}
		if (currentTime < 1) return -.5 * (a * std::pow(2, 10 * (currentTime -= 1)) * std::sin((currentTime * totalTime - s) * (2 * PI) / p)) + minValue;
		return a * std::pow(2, -10 * (currentTime -= 1)) * std::sin((currentTime * totalTime - s) * (2 * PI) / p) * .5 + maxValue + minValue;
	}

	static double easeInBounce(double currentTime, double minValue, double maxValue, double totalTime) {
		return maxValue - easeOutBounce(totalTime - currentTime, 0, maxValue, totalTime) + minValue;
	}

	static double easeOutBounce(double currentTime, double minValue, double maxValue, double totalTime) {
		if ((currentTime /= totalTime) < (1 / 2.75)) {
			return maxValue * (7.5625 * currentTime * currentTime) + minValue;
		}
		else if (currentTime < (2 / 2.75)) {
			double postFix = currentTime -= (1.5 / 2.75);
			return maxValue * (7.5625 * (postFix)*currentTime + .75) + minValue;
		}
		else if (currentTime < (2.5 / 2.75)) {
			double postFix = currentTime -= (2.25 / 2.75);
			return maxValue * (7.5625 * (postFix)*currentTime + .9375) + minValue;
		}
		else {
			double postFix = currentTime -= (2.625 / 2.75);
			return maxValue * (7.5625 * (postFix)*currentTime + .984375) + minValue;
		}
	}

	static double easeInOutBounce(double currentTime, double minValue, double maxValue, double totalTime) {
		if (currentTime < totalTime / 2) return easeInBounce(currentTime * 2, 0, maxValue, totalTime) * .5 + minValue;
		return easeOutBounce(currentTime * 2 - totalTime, 0, maxValue, totalTime) * .5 + maxValue * .5 + minValue;
	}
};


#endif
