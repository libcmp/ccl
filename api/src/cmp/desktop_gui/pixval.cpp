// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/desktop_gui/pixval.hpp>

namespace cmp {

// --------------------------------------------------------------- cmp::pixval

// Constructors and Destructor ------------------------------------------------

pixval::pixval (
    value_type initial_value
)
noexcept
    : m_value{initial_value}
{
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

typename pixval::value_type
pixval::get_value ()
const noexcept
{
    return m_value;
} // function -----------------------------------------------------------------

void
pixval::set_value (
    value_type new_value
)
noexcept
{
    m_value = new_value;
} // function -----------------------------------------------------------------

const typename pixval::value_type&
pixval::grab_value ()
const noexcept
{
    return m_value;
} // function -----------------------------------------------------------------

typename pixval::value_type&
pixval::grab_value ()
noexcept
{
    return m_value;
} // function -----------------------------------------------------------------

// Operator Overloads ---------------------------------------------------------

bool
operator == (
    const pixval& left_operand,
    const pixval& right_operand
)
noexcept
{
    return left_operand.m_value == right_operand.m_value;
} // function -----------------------------------------------------------------

bool
operator != (
    const pixval& left_operand,
    const pixval& right_operand
)
noexcept
{
    return left_operand.m_value != right_operand.m_value;
} // function -----------------------------------------------------------------

bool
operator < (
    const pixval& left_operand,
    const pixval& right_operand
)
noexcept
{
    return left_operand.m_value < right_operand.m_value;
} // function -----------------------------------------------------------------

bool
operator > (
    const pixval& left_operand,
    const pixval& right_operand
)
noexcept
{
    return left_operand.m_value > right_operand.m_value;
} // function -----------------------------------------------------------------

bool
operator <= (
    const pixval& left_operand,
    const pixval& right_operand
)
noexcept
{
    return left_operand.m_value <= right_operand.m_value;
} // function -----------------------------------------------------------------

bool
operator >= (
    const pixval& left_operand,
    const pixval& right_operand
)
noexcept
{
    return left_operand.m_value >= right_operand.m_value;
} // function -----------------------------------------------------------------

pixval
pixval::operator + ()
const noexcept
{
    return *this;
} // function -----------------------------------------------------------------

pixval
pixval::operator - ()
const noexcept
{
    return -m_value;
} // function -----------------------------------------------------------------

pixval
operator + (
    const pixval& left_operand,
    const pixval& right_operand
)
noexcept
{
    return left_operand.m_value + right_operand.m_value;
} // function -----------------------------------------------------------------

pixval
operator - (
    const pixval& left_operand,
    const pixval& right_operand
)
noexcept
{
    return left_operand.m_value - right_operand.m_value;
} // function -----------------------------------------------------------------

pixval
operator * (
    const pixval& left_operand,
    const pixval& right_operand
)
noexcept
{
    return left_operand.m_value * right_operand.m_value;
} // function -----------------------------------------------------------------

pixval
operator / (
    const pixval& left_operand,
    const pixval& right_operand
)
noexcept
{
    return left_operand.m_value / right_operand.m_value;
} // function -----------------------------------------------------------------

pixval
operator % (
    const pixval& left_operand,
    const pixval& right_operand
)
noexcept
{
    return left_operand.m_value % right_operand.m_value;
} // function -----------------------------------------------------------------

pixval
operator ~ (
    const pixval& operand
)
noexcept
{
    return ~(operand.m_value);
} // function -----------------------------------------------------------------

pixval
operator & (
    const pixval& left_operand,
    const pixval& right_operand
)
noexcept
{
    return left_operand.m_value & right_operand.m_value;
} // function -----------------------------------------------------------------

pixval
operator | (
    const pixval& left_operand,
    const pixval& right_operand
)
noexcept
{
    return left_operand.m_value | right_operand.m_value;
} // function -----------------------------------------------------------------

pixval
operator ^ (
    const pixval& left_operand,
    const pixval& right_operand
)
noexcept
{
    return left_operand.m_value ^ right_operand.m_value;
} // function -----------------------------------------------------------------

pixval
operator << (
    const pixval& left_operand,
    const pixval& right_operand
)
noexcept
{
    return left_operand.m_value << right_operand.m_value;
} // function -----------------------------------------------------------------

pixval
operator >> (
    const pixval& left_operand,
    const pixval& right_operand
)
noexcept
{
    return left_operand.m_value >> right_operand.m_value;
} // function -----------------------------------------------------------------

pixval&
pixval::operator += (
    const pixval& operand
)
noexcept
{
    m_value += operand.m_value;
    return *this;
} // function -----------------------------------------------------------------

pixval&
pixval::operator -= (
    const pixval& operand
)
noexcept
{
    m_value -= operand.m_value;
    return *this;
} // function -----------------------------------------------------------------

pixval&
pixval::operator *= (
    const pixval& operand
)
noexcept
{
    m_value *= operand.m_value;
    return *this;
} // function -----------------------------------------------------------------

pixval&
pixval::operator /= (
    const pixval& operand
)
noexcept
{
    m_value /= operand.m_value;
    return *this;
} // function -----------------------------------------------------------------

pixval&
pixval::operator %= (
    const pixval& operand
)
noexcept
{
    m_value %= operand.m_value;
    return *this;
} // function -----------------------------------------------------------------

pixval&
pixval::operator &= (
    const pixval& operand
)
noexcept
{
    m_value &= operand.m_value;
    return *this;
} // function -----------------------------------------------------------------

pixval&
pixval::operator |= (
    const pixval& operand
)
noexcept
{
    m_value |= operand.m_value;
    return *this;
} // function -----------------------------------------------------------------

pixval&
pixval::operator ^= (
    const pixval& operand
)
noexcept
{
    m_value ^= operand.m_value;
    return *this;
} // function -----------------------------------------------------------------

pixval&
pixval::operator <<= (
    const pixval& operand
)
noexcept
{
    m_value <<= operand.m_value;
    return *this;
} // function -----------------------------------------------------------------

pixval&
pixval::operator >>= (
    const pixval& operand
)
noexcept
{
    m_value >>= operand.m_value;
    return *this;
} // function -----------------------------------------------------------------

pixval&
pixval::operator ++ ()
noexcept
{
    ++m_value;
    return *this;
} // function -----------------------------------------------------------------

pixval&
pixval::operator -- ()
noexcept
{
    --m_value;
    return *this;
} // function -----------------------------------------------------------------

pixval
pixval::operator ++ (
    int
)
noexcept
{
    pixval copy{*this};
    ++m_value;
    return copy;
} // function -----------------------------------------------------------------

pixval
pixval::operator -- (
    int
)
noexcept
{
    pixval copy{*this};
    --m_value;
    return copy;
} // function -----------------------------------------------------------------

std::ostream&
operator << (
    std::ostream& stream,
    const pixval& source
)
noexcept
{
    stream << source.m_value;
    return stream;
} // function -----------------------------------------------------------------

std::istream&
operator >> (
    std::istream& stream,
    pixval& target
)
noexcept
{
    stream >> target.m_value;
    return stream;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
