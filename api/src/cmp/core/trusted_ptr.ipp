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

template <
    typename T
>
trusted_ptr<T>::trusted_ptr (
    std::nullptr_t null_pointer
)
noexcept
    : m_underlying_pointer{nullptr}
{
} // function -----------------------------------------------------------------

template <
    typename T
>
template <
    typename U
>
requires (std::is_base_of_v<T, U>)
trusted_ptr<T>::trusted_ptr (
    const trusted_ptr<U>& other
)
    : m_underlying_pointer{static_cast<T*>(other.get_underlying_pointer())}
{
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

template <
    typename T
>
trusted_ptr<T>::pointer
trusted_ptr<T>::get_underlying_pointer ()
const noexcept
{
    return m_underlying_pointer;
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

template <
    typename T
>
template <
    typename U
>
trusted_ptr<U>
trusted_ptr<T>::as_pointer_of ()
const noexcept
{
    return trusted_ptr<U>::assure(static_cast<U*>(m_underlying_pointer));
} // function -----------------------------------------------------------------

// Operator Overloads ---------------------------------------------------------

template <
    typename T
>
template <
    typename U
>
requires (std::is_base_of_v<T, U>)
trusted_ptr<T>::operator trusted_ptr<U> ()
noexcept
{
    return trusted_ptr<U>::assure(static_cast<U*>(m_underlying_pointer));
} // function -----------------------------------------------------------------

template <
    typename T
>
trusted_ptr<T>::operator bool ()
const noexcept
{
    return m_underlying_pointer;
} // function -----------------------------------------------------------------

template <
    typename T
>
typename trusted_ptr<T>::reference
trusted_ptr<T>::operator * ()
noexcept
{
    return *m_underlying_pointer;
} // function -----------------------------------------------------------------

template <
    typename T
>
typename trusted_ptr<T>::const_reference
trusted_ptr<T>::operator * ()
const noexcept
{
    return *m_underlying_pointer;
} // function -----------------------------------------------------------------

template <
    typename T
>
trusted_ptr<T>::pointer
trusted_ptr<T>::operator -> ()
const noexcept
{
    return m_underlying_pointer;
} // function -----------------------------------------------------------------

template <
    typename T
>
bool
operator == (
    const trusted_ptr<T>& left_operand,
    const trusted_ptr<T>& right_operand
)
noexcept
{
    return left_operand.m_underlying_pointer
        == right_operand.m_underlying_pointer;
} // function -----------------------------------------------------------------

template <
    typename T
>
bool
operator != (
    const trusted_ptr<T>& left_operand,
    const trusted_ptr<T>& right_operand
)
noexcept
{
    return left_operand.m_underlying_pointer
        != right_operand.m_underlying_pointer;
} // function -----------------------------------------------------------------

template <
    typename T
>
bool
operator < (
    const trusted_ptr<T>& left_operand,
    const trusted_ptr<T>& right_operand
)
noexcept
{
    return left_operand.m_underlying_pointer
        < right_operand.m_underlying_pointer;
} // function -----------------------------------------------------------------

template <
    typename T
>
bool
operator > (
    const trusted_ptr<T>& left_operand,
    const trusted_ptr<T>& right_operand
)
noexcept
{
    return left_operand.m_underlying_pointer
        > right_operand.m_underlying_pointer;
} // function -----------------------------------------------------------------

template <
    typename T
>
bool
operator <= (
    const trusted_ptr<T>& left_operand,
    const trusted_ptr<T>& right_operand
)
noexcept
{
    return left_operand.m_underlying_pointer
        <= right_operand.m_underlying_pointer;
} // function -----------------------------------------------------------------

template <
    typename T
>
bool
operator >= (
    const trusted_ptr<T>& left_operand,
    const trusted_ptr<T>& right_operand
)
noexcept
{
    return left_operand.m_underlying_pointer
        >= right_operand.m_underlying_pointer;
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

template <
    typename Target,
    typename Source
>
trusted_ptr<Target>
assure_as (
    Source* raw_pointer
)
noexcept
{
    return assure(raw_pointer).template as_pointer_of<Target>();
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
