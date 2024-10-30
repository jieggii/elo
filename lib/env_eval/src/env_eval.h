//
// Created by jieggii on 10/28/24.
//

#ifndef ENV_EVAL_H
#define ENV_EVAL_H

#include <cmath>

// TODO: should we use a namespace here?
// consider wrapping all modules to namespaces.
namespace env_eval {
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
        BAD = 1,
        ACCEPTABLE = 2,
        OPTIMAL = 3,
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

    /**
     * Calculates the average evaluation from an array of evaluations.
     * @param evaluations evaluations to average.
     * TODO: do we need to pass evaluations as a variadic template?
     */
    template <typename... Evaluations>
    Evaluation averageEvaluation(Evaluations... evaluations) {
        const uint8_t sum = (static_cast<uint8_t>(evaluations) + ...);
        const auto avg = static_cast<uint8_t>(round(static_cast<double>(sum) / sizeof...(evaluations)));
        return static_cast<Evaluation>(avg);
    }

}  // namespace env_eval

#endif  // ENV_EVAL_H
