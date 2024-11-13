// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_DESKTOP_GUI_DOTVAL_HPP_INCLUDED
#define CMP_DESKTOP_GUI_DOTVAL_HPP_INCLUDED

#include <cmp/desktop_gui/inclusion_assert.hpp>

namespace cmp {

class dotval {
public:
    // Types ------------------------------------------------------------------

    using value_type = int;

    // Constructors and Destructor --------------------------------------------

    dotval ()
    noexcept = default;

    CMP_CONDITIONAL_EXPORT
    explicit
    dotval (
        value_type initial_value
    )
    noexcept;

    ~dotval ()
    = default;

    // Copy Operations --------------------------------------------------------

    dotval (
        const dotval& other
    )
    = default;

    dotval&
    operator = (
        const dotval& other
    )
    = default;

    // Move Operations --------------------------------------------------------

    dotval (
        dotval&& other
    )
    noexcept = default;

    dotval&
    operator = (
        dotval&& other
    )
    noexcept = default;

    // Accessors --------------------------------------------------------------

    CMP_CONDITIONAL_EXPORT
    value_type
    get_value ()
    const noexcept;

    CMP_CONDITIONAL_EXPORT
    void
    set_value (
        value_type new_value
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    const value_type&
    grab_value ()
    const noexcept;

    CMP_CONDITIONAL_EXPORT
    value_type&
    grab_value ()
    noexcept;

    // Operator Overloads -----------------------------------------------------

    CMP_CONDITIONAL_EXPORT
    friend
    bool
    operator == (
        const dotval& left_operand,
        const dotval& right_operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    friend
    bool
    operator != (
        const dotval& left_operand,
        const dotval& right_operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    friend
    bool
    operator < (
        const dotval& left_operand,
        const dotval& right_operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    friend
    bool
    operator > (
        const dotval& left_operand,
        const dotval& right_operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    friend
    bool
    operator <= (
        const dotval& left_operand,
        const dotval& right_operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    friend
    bool
    operator >= (
        const dotval& left_operand,
        const dotval& right_operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    dotval
    operator + ()
    const noexcept;

    CMP_CONDITIONAL_EXPORT
    dotval
    operator - ()
    const noexcept;

    CMP_CONDITIONAL_EXPORT
    friend
    dotval
    operator + (
        const dotval& left_operand,
        const dotval& right_operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    friend
    dotval
    operator - (
        const dotval& left_operand,
        const dotval& right_operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    friend
    dotval
    operator * (
        const dotval& left_operand,
        const dotval& right_operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    friend
    dotval
    operator / (
        const dotval& left_operand,
        const dotval& right_operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    friend
    dotval
    operator % (
        const dotval& left_operand,
        const dotval& right_operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    friend
    dotval
    operator ~ (
        const dotval& operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    friend
    dotval
    operator & (
        const dotval& left_operand,
        const dotval& right_operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    friend
    dotval
    operator | (
        const dotval& left_operand,
        const dotval& right_operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    friend
    dotval
    operator ^ (
        const dotval& left_operand,
        const dotval& right_operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    friend
    dotval
    operator << (
        const dotval& left_operand,
        const dotval& right_operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    friend
    dotval
    operator >> (
        const dotval& left_operand,
        const dotval& right_operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    dotval&
    operator += (
        const dotval& operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    dotval&
    operator -= (
        const dotval& operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    dotval&
    operator *= (
        const dotval& operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    dotval&
    operator /= (
        const dotval& operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    dotval&
    operator %= (
        const dotval& operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    dotval&
    operator &= (
        const dotval& operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    dotval&
    operator |= (
        const dotval& operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    dotval&
    operator ^= (
        const dotval& operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    dotval&
    operator <<= (
        const dotval& operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    dotval&
    operator >>= (
        const dotval& operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    dotval&
    operator ++ ()
    noexcept;

    CMP_CONDITIONAL_EXPORT
    dotval&
    operator -- ()
    noexcept;

    CMP_CONDITIONAL_EXPORT
    dotval
    operator ++ (
        int
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    dotval
    operator -- (
        int
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    friend
    std::ostream&
    operator << (
        std::ostream& stream,
        const dotval& source
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    friend
    std::istream&
    operator >> (
        std::istream& stream,
        dotval& target
    )
    noexcept;

private:
    // Private Data -----------------------------------------------------------

    value_type m_value;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#endif // CMP_DESKTOP_GUI_DOTVAL_HPP_INCLUDED
