//
// Created by jieggii on 10/28/24.
//

#ifndef ENV_EVAL_H
#define ENV_EVAL_H

// TODO: should we use a namespace here?
// consider wrapping all modules to namespaces.
namespace EnvEval {
    /**
     * Represents a range of values.
     */
    template <typename T>
    struct ValueRange {
        T min;
        T max;
    };

    /**
     * Represents the evaluation of a value.
     */
    enum class Evaluation {
        OPTIMAL,
        ACCEPTABLE,
        BAD,
    };

    /**
     * Evaluates a value by comparing it to the optimal and acceptable ranges (inclusive).
     * @return The evaluation of the value.
     */
    template <typename T>
    Evaluation evaluateByRange(T value, ValueRange<T> optimalRange, ValueRange<T> acceptableRange) {
        if (value >= optimalRange.min && value <= optimalRange.max) {
            return Evaluation::OPTIMAL;
        }

        if (value >= acceptableRange.min && value <= acceptableRange.max) {
            return Evaluation::ACCEPTABLE;
        }

        return Evaluation::BAD;
    }

    /**
     * Evaluates a value by comparing it to the optimal and acceptable max values (inclusive).
     * TODO: do we need template here?
     */
    template <typename T>
    Evaluation evaluateByMax(T value, T optimalMax, T acceptableMax) {
        if (value <= optimalMax) {
            return Evaluation::OPTIMAL;
        }

        if (value <= acceptableMax) {
            return Evaluation::ACCEPTABLE;
        }

        return Evaluation::BAD;
    }

}  // namespace EnvEval

#endif  // ENV_EVAL_H
