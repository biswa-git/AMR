#pragma once
/**--------power function: calculates x^y------*/
namespace detail
{
    template<class T, int N>
    struct helper
    {
        static constexpr T POW(const T x) {
            return helper<T, N - 1>::pow(x) * x;
        }
    };

    template<class T>
    struct helper<T, 1>
    {
        static constexpr T POW(const T x) {
            return x;
        }
    };

    template<class T>
    struct helper<T, 0>
    {
        static constexpr T POW(const T x) {
            return 1;
        }
    };

}

template<int N, class T>
T constexpr POW(T const x)
{
    return detail::helper<T, N>::POW(x);
}

template <unsigned int x>
constexpr std::enable_if_t<x != 0U, int> LOG2 = 1 + LOG2<x / 2U>;

template <>
constexpr int LOG2<1U> = 0;
/**--------------------------------------------*/