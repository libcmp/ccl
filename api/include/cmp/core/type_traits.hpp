// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_CORE_TYPE_TRAITS_HPP_INCLUDED
#define CMP_CORE_TYPE_TRAITS_HPP_INCLUDED

namespace cmp {

template <
    typename T
>
using value_type_t
    = std::remove_reference_t<decltype(*std::begin(std::declval<T&>()))>;

} // namespace ----------------------------------------------------------------

#endif // CMP_CORE_TYPE_TRAITS_HPP_INCLUDED
