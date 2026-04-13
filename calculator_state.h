#ifndef CALCULATOR_STATE_H
#define CALCULATOR_STATE_H

#include <string>

class CalculatorState final {
public:
    CalculatorState() {};

    const std::string& getExpression() const {
        return currentExpression;
    }

    void setExpression(const std::string& expression) {
        currentExpression = expression;
    }

    double getResult() const {
        return currentResult;
    }

    void setResult(double value) {
        currentResult = value;
    }

private:
    std::string currentExpression;
    double currentResult;
};

#endif // CALCULATOR_STATE_H
