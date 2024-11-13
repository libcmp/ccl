// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/desktop_gui/dotval.hpp>

namespace cmp {

// --------------------------------------------------------------- cmp::dotval

// Constructors and Destructor ------------------------------------------------

dotval::dotval (
    value_type initial_value
)
noexcept
    : m_value{initial_value}
{
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

typename dotval::value_type
dotval::get_value ()
const noexcept
{
    return m_value;
} // function -----------------------------------------------------------------

void
dotval::set_value (
    value_type new_value
)
noexcept
{
    m_value = new_value;
} // function -----------------------------------------------------------------

const typename dotval::value_type&
dotval::grab_value ()
const noexcept
{
    return m_value;
} // function -----------------------------------------------------------------

typename dotval::value_type&
dotval::grab_value ()
noexcept
{
    return m_value;
} // function -----------------------------------------------------------------

// Operator Overloads ---------------------------------------------------------

bool
operator == (
    const dotval& left_operand,
    const dotval& right_operand
)
noexcept
{
    return left_operand.m_value == right_operand.m_value;
} // function -----------------------------------------------------------------

bool
operator != (
    const dotval& left_operand,
    const dotval& right_operand
)
noexcept
{
    return left_operand.m_value != right_operand.m_value;
} // function -----------------------------------------------------------------

bool
operator < (
    const dotval& left_operand,
    const dotval& right_operand
)
noexcept
{
    return left_operand.m_value < right_operand.m_value;
} // function -----------------------------------------------------------------

bool
operator > (
    const dotval& left_operand,
    const dotval& right_operand
)
noexcept
{
    return left_operand.m_value > right_operand.m_value;
} // function -----------------------------------------------------------------

bool
operator <= (
    const dotval& left_operand,
    const dotval& right_operand
)
noexcept
{
    return left_operand.m_value <= right_operand.m_value;
} // function -----------------------------------------------------------------

bool
operator >= (
    const dotval& left_operand,
    const dotval& right_operand
)
noexcept
{
    return left_operand.m_value >= right_operand.m_value;
} // function -----------------------------------------------------------------

dotval
dotval::operator + ()
const noexcept
{
    return *this;
} // function -----------------------------------------------------------------

dotval
dotval::operator - ()
const noexcept
{
    return dotval{-m_value};
} // function -----------------------------------------------------------------

dotval
operator + (
    const dotval& left_operand,
    const dotval& right_operand
)
noexcept
{
    return dotval{left_operand.m_value + right_operand.m_value};
} // function -----------------------------------------------------------------

dotval
operator - (
    const dotval& left_operand,
    const dotval& right_operand
)
noexcept
{
    return dotval{left_operand.m_value - right_operand.m_value};
} // function -----------------------------------------------------------------

dotval
operator * (
    const dotval& left_operand,
    const dotval& right_operand
)
noexcept
{
    return dotval{left_operand.m_value * right_operand.m_value};
} // function -----------------------------------------------------------------

dotval
operator / (
    const dotval& left_operand,
    const dotval& right_operand
)
noexcept
{
    return dotval{left_operand.m_value / right_operand.m_value};
} // function -----------------------------------------------------------------

dotval
operator % (
    const dotval& left_operand,
    const dotval& right_operand
)
noexcept
{
    return dotval{left_operand.m_value % right_operand.m_value};
} // function -----------------------------------------------------------------

dotval
operator ~ (
    const dotval& operand
)
noexcept
{
    return dotval{~(operand.m_value)};
} // function -----------------------------------------------------------------

dotval
operator & (
    const dotval& left_operand,
    const dotval& right_operand
)
noexcept
{
    return dotval{left_operand.m_value & right_operand.m_value};
} // function -----------------------------------------------------------------

dotval
operator | (
    const dotval& left_operand,
    const dotval& right_operand
)
noexcept
{
    return dotval{left_operand.m_value | right_operand.m_value};
} // function -----------------------------------------------------------------

dotval
operator ^ (
    const dotval& left_operand,
    const dotval& right_operand
)
noexcept
{
    return dotval{left_operand.m_value ^ right_operand.m_value};
} // function -----------------------------------------------------------------

dotval
operator << (
    const dotval& left_operand,
    const dotval& right_operand
)
noexcept
{
    return dotval{left_operand.m_value << right_operand.m_value};
} // function -----------------------------------------------------------------

dotval
operator >> (
    const dotval& left_operand,
    const dotval& right_operand
)
noexcept
{
    return dotval{left_operand.m_value >> right_operand.m_value};
} // function -----------------------------------------------------------------

dotval&
dotval::operator += (
    const dotval& operand
)
noexcept
{
    m_value += operand.m_value;
    return *this;
} // function -----------------------------------------------------------------

dotval&
dotval::operator -= (
    const dotval& operand
)
noexcept
{
    m_value -= operand.m_value;
    return *this;
} // function -----------------------------------------------------------------

dotval&
dotval::operator *= (
    const dotval& operand
)
noexcept
{
    m_value *= operand.m_value;
    return *this;
} // function -----------------------------------------------------------------

dotval&
dotval::operator /= (
    const dotval& operand
)
noexcept
{
    m_value /= operand.m_value;
    return *this;
} // function -----------------------------------------------------------------

dotval&
dotval::operator %= (
    const dotval& operand
)
noexcept
{
    m_value %= operand.m_value;
    return *this;
} // function -----------------------------------------------------------------

dotval&
dotval::operator &= (
    const dotval& operand
)
noexcept
{
    m_value &= operand.m_value;
    return *this;
} // function -----------------------------------------------------------------

dotval&
dotval::operator |= (
    const dotval& operand
)
noexcept
{
    m_value |= operand.m_value;
    return *this;
} // function -----------------------------------------------------------------

dotval&
dotval::operator ^= (
    const dotval& operand
)
noexcept
{
    m_value ^= operand.m_value;
    return *this;
} // function -----------------------------------------------------------------

dotval&
dotval::operator <<= (
    const dotval& operand
)
noexcept
{
    m_value <<= operand.m_value;
    return *this;
} // function -----------------------------------------------------------------

dotval&
dotval::operator >>= (
    const dotval& operand
)
noexcept
{
    m_value >>= operand.m_value;
    return *this;
} // function -----------------------------------------------------------------

dotval&
dotval::operator ++ ()
noexcept
{
    ++m_value;
    return *this;
} // function -----------------------------------------------------------------

dotval&
dotval::operator -- ()
noexcept
{
    --m_value;
    return *this;
} // function -----------------------------------------------------------------

dotval
dotval::operator ++ (
    int
)
noexcept
{
    dotval copy{*this};
    ++m_value;
    return copy;
} // function -----------------------------------------------------------------

dotval
dotval::operator -- (
    int
)
noexcept
{
    dotval copy{*this};
    --m_value;
    return copy;
} // function -----------------------------------------------------------------

std::ostream&
operator << (
    std::ostream& stream,
    const dotval& source
)
noexcept
{
    stream << source.m_value;
    return stream;
} // function -----------------------------------------------------------------

std::istream&
operator >> (
    std::istream& stream,
    dotval& target
)
noexcept
{
    stream >> target.m_value;
    return stream;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
