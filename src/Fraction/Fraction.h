#pragma once

namespace LinearAlgebra {
    template<typename T>
    class Fraction {
    private:
        T numerator;
        T denominator;
    public:
        Fraction(T numerator, T denominator)
            : numerator(numerator), denominator(denominator)
        {}

        Fraction(T numerator)
            : numerator(numerator), denominator(static_cast<T>(1))
        {}

        Fraction()
            : numerator(static_cast<T>(1)), denominator(static_cast<T>(1))
        {}

        static Fraction<T> Create(T numerator_) {
            return Fraction(numerator_);
        }

        T getNumerator() const {
            return numerator;
        }
        T getDenominator() const {
            return denominator;
        }

        void setNumerator(T newNumerator) {
            Fraction::numerator = newNumerator;
        }
        void setDenominator(T newDenominator) {
            Fraction::denominator = newDenominator;
        }

        __declspec(property(get = getNumerator, put = setNumerator)) T Numerator;
        __declspec(property(get = getDenominator, put = setDenominator)) T Denominator;

    public:

        friend Fraction<T> operator*(const Fraction<T>& first, const Fraction<T>& second) {
            return Fraction<T>(
                first.Numerator * second.Numerator,
                first.Denominator * second.Denominator
            );
        }
        Fraction<T>& operator*=(const Fraction<T>& other) {
            numerator *= other.Numerator;
            denominator *= other.Denominator;
            return *this;
        }

        friend std::ostream& operator<<(std::ostream& stream, Fraction<T> fraction) {
            stream << fraction.Numerator << "/" << fraction.Denominator;
            return stream;
        }



        void Reduce() {
            if (numerator % denominator == 0) {
                numerator = 1;
                denominator = 1;
            }

            // TODO reduce fraction

        }

        template<typename TDiv>
        friend TDiv Calculate(const Fraction<T>& fraction) {
            return static_cast<TDiv>(fraction.numerator)
                / static_cast<TDiv>(fraction.denominator);
        }

        template<typename TResult>
        explicit operator TResult() const {
            return static_cast<TResult>(numerator)
                / static_cast<TResult>(denominator);
        }

    };

}
