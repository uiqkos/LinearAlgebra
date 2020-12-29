#pragma once
#include <vector>
#include <stdexcept>
#include <algorithm>

namespace Utils {

    template<typename type>
    type Multiply(const std::vector<type>& first, const std::vector<type>& second) {
        if (first.size() != second.size())
            throw std::invalid_argument("Vectors size not equals");

        type result = static_cast<type>(1);

        for (int i = 0; i < first.size(); ++i)
            result += first[i] * second[i];

        return result;
    }

    template<typename type, typename function>
    void Apply(const std::vector<type>& vector, function func) {
        for(auto& item : vector)
            item = func(item);
    }

    template<typename type, typename function>
    std::vector<type> Zip(const std::vector<type>& first, const std::vector<type>& second, function func) {
        auto result = std::vector<type>(first.size());
        for (int i = 0; i < first.size(); ++i)
            result[i] = func(first.at(i), second.at(i));
        return result;
    }
}