// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/core/trusted_ptr.hpp>

namespace cmp {

// ------------------------------------------------------- cmp::trusted_ptr<T>

// Constructors and Destructor ------------------------------------------------

template <
    typename T
>
trusted_ptr<T>::trusted_ptr ()
noexcept
    : m_underlying_pointer{nullptr}
{
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

template <
    typename T
>
trusted_ptr<T>
trusted_ptr<T>::assure (
    pointer raw_pointer
)
noexcept
{
    return trusted_ptr{raw_pointer};
} // function -----------------------------------------------------------------

// Operator Overloads ---------------------------------------------------------

template <
    typename T
>
trusted_ptr<T>::pointer
trusted_ptr<T>::operator -> ()
const noexcept
{
    return m_underlying_pointer;
} // function -----------------------------------------------------------------

// Private Functions ----------------------------------------------------------

template <
    typename T
>
trusted_ptr<T>::trusted_ptr (
    pointer initial_underlying_pointer
)
noexcept
    : m_underlying_pointer{initial_underlying_pointer}
{
} // function -----------------------------------------------------------------

// Free Functions -------------------------------------------------------------

template <
    typename T
>
trusted_ptr<T>
assure (
    T* raw_pointer
)
noexcept
{
    return trusted_ptr<T>::assure(raw_pointer);
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
