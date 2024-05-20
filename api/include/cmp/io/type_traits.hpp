// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_IO_TYPE_TRAITS_HPP_INCLUDED
#define CMP_IO_TYPE_TRAITS_HPP_INCLUDED

#include <cmp/io/opaque_container_io_resource.hpp>
#include <cmp/io/transparent_container_io_resource.hpp>

namespace cmp {

template <
    typename T
>
class is_opaque_ctr {
public:
    static constexpr bool value{false};
}; // class -------------------------------------------------------------------

template <
    typename T
>
class is_opaque_ctr<opaque_container_input_resource<T>> {
public:
    static constexpr bool value{true};
}; // class -------------------------------------------------------------------

template <
    typename T
>
class is_opaque_ctr<opaque_container_output_resource<T>> {
public:
    static constexpr bool value{true};
}; // class -------------------------------------------------------------------

template <
    typename T
>
class is_opaque_ctr<opaque_container_io_resource<T>> {
public:
    static constexpr bool value{true};
}; // class -------------------------------------------------------------------

template <
    typename T
>
constexpr bool is_opaque_ctr_v{is_opaque_ctr<T>::value};

template <
    typename T
>
class is_transparent_ctr {
public:
    static constexpr bool value{false};
}; // class -------------------------------------------------------------------

template <
    typename T
>
class is_transparent_ctr<transparent_container_input_resource<T>> {
public:
    static constexpr bool value{true};
}; // class -------------------------------------------------------------------

template <
    typename T
>
class is_transparent_ctr<transparent_container_output_resource<T>> {
public:
    static constexpr bool value{true};
}; // class -------------------------------------------------------------------

template <
    typename T
>
class is_transparent_ctr<transparent_container_io_resource<T>> {
public:
    static constexpr bool value{true};
}; // class -------------------------------------------------------------------

template <
    typename T
>
constexpr bool is_transparent_ctr_v{is_transparent_ctr<T>::value};

} // namespace ----------------------------------------------------------------

#endif // CMP_IO_TYPE_TRAITS_HPP_INCLUDED
