// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_UNICODE_CONCEPTS_HPP_INCLUDED
#define CMP_UNICODE_CONCEPTS_HPP_INCLUDED

#include <cmp/unicode/inclusion_assert.hpp>
#include <cmp/unicode/type_traits.hpp>

namespace cmp {

// Unicode Text Objects -------------------------------------------------------

template <
    typename T
>
concept writable_unicode_text_object = is_writable_unicode_text_object_v<T>;

template <
    typename T
>
concept unicode_text_object = is_unicode_text_object_v<T>;

template <
    typename T
>
concept writable_raii_unicode_text_object
    = is_writable_raii_unicode_text_object_v<T>;

template <
    typename T
>
concept raii_unicode_text_object = is_raii_unicode_text_object_v<T>;

// Text Objects ---------------------------------------------------------------

template <
    typename T
>
concept writable_text_object = is_writable_text_object_v<T>;

template <
    typename T
>
concept text_object = is_text_object_v<T>;

template <
    typename T
>
concept writable_raii_text_object = is_writable_raii_text_object_v<T>;

template <
    typename T
>
concept raii_text_object = is_raii_text_object_v<T>;

} // namespace ----------------------------------------------------------------

#endif // CMP_UNICODE_CONCEPTS_HPP_INCLUDED
