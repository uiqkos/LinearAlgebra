#pragma once
#include <vector>
#include <stdexcept>

namespace Utils {
    template<typename type>
    type multiply(const std::vector<type>& first, const std::vector<type>& second) {
        if (first.size() != second.size())
            throw std::invalid_argument("Vectors size not equals");

        type result = static_cast<type>(0);

        for (int i = 0; i < first.size(); ++i)
            result += first[i] * second[i];

        return result;
    }

    template<typename type, typename function>
    std::vector<type> apply(const std::vector<type>& first, const std::vector<type>& second, function func, type start) {
        if (first.size() != second.size())
            throw std::invalid_argument("Vectors size not equals");

        std::vector<type> result = std::vector<type>(first.size());

        for (int i = 0; i < first.size(); ++i)
            result[i] = func(first[i], second[i]);

        return result;
    }
}