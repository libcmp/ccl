// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_UNICODE_CONCEPTS_HPP_INCLUDED
#define CMP_UNICODE_CONCEPTS_HPP_INCLUDED

#include <cmp/unicode/type_traits.hpp>

namespace cmp {

template <
    typename T
>
concept writable_unicode_string = is_writable_unicode_string_v<T>;

template <
    typename T
>
concept unicode_string = is_unicode_string_v<T>;

template <
    typename T
>
concept writable_raii_unicode_string = is_writable_raii_unicode_string_v<T>;

template <
    typename T
>
concept raii_unicode_string = is_raii_unicode_string_v<T>;

} // namespace ----------------------------------------------------------------

#endif // CMP_UNICODE_CONCEPTS_HPP_INCLUDED
