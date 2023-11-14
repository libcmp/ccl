// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_CORE_TYPE_TRAITS_HPP_INCLUDED
#define CMP_CORE_TYPE_TRAITS_HPP_INCLUDED

namespace cmp {

namespace impl {

template <
    typename T,
    bool argument1_is_larger,
    T argument1,
    T argument2
>
class constant_max {
public:
    static constexpr T value{};
}; // class -------------------------------------------------------------------

template <
    typename T,
    T argument1,
    T argument2
>
class constant_max<T, true, argument1, argument2> {
public:
    static constexpr T value = argument1;
}; // class -------------------------------------------------------------------

template <
    typename T,
    T argument1,
    T argument2
>
class constant_max<T, false, argument1, argument2> {
public:
    static constexpr T value = argument2;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

template <
    typename T
>
using value_type_t
    = std::remove_reference_t<decltype(*std::begin(std::declval<T&>()))>;

template <
    typename T,
    T argument1,
    T argument2
>
using constant_max_t = T;

template <
    typename T,
    T argument1,
    T argument2
>
constexpr T constant_max_v = impl::constant_max<
    T,
    (argument1 > argument2),
    argument1,
    argument2
>::value;

} // namespace ----------------------------------------------------------------

#endif // CMP_CORE_TYPE_TRAITS_HPP_INCLUDED
