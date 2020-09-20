#ifndef MACROS_HPP
#define MACROS_HPP

/**
 * CONSTEXPR_SUM sums a constexpr array
 * @tparam T Type of elements in the array
 * @tparam N Used to indicate total size of array
 * @param a Constant reference to the array
 * @param i Used as a recursive counter, default is 0
 */
template <typename T, unsigned N>
constexpr T CONSTEXPR_SUM(T const (&a)[N], unsigned i = 0u)
{
    return i < N ? (a[i] + CONSTEXPR_SUM(a, i + 1U)) : T{};
}

#endif
