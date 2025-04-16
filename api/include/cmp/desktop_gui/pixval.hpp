// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_DESKTOP_GUI_PIXVAL_HPP_INCLUDED
#define CMP_DESKTOP_GUI_PIXVAL_HPP_INCLUDED

#include <cmp/desktop_gui/inclusion_assert.hpp>

namespace cmp {

class pixval {
public:
    // Types ------------------------------------------------------------------

    using value_type = int;

    // Constructors and Destructor --------------------------------------------

    pixval ()
    noexcept = default;

    CMP_CONDITIONAL_EXPORT
    explicit(false)
    pixval (
        value_type initial_value
    )
    noexcept;

    ~pixval ()
    = default;

    // Copy Operations --------------------------------------------------------

    pixval (
        const pixval& other
    )
    = default;

    pixval&
    operator = (
        const pixval& other
    ) &
    = default;

    // Move Operations --------------------------------------------------------

    pixval (
        pixval&& other
    )
    noexcept = default;

    pixval&
    operator = (
        pixval&& other
    ) &
    noexcept = default;

    // Accessors --------------------------------------------------------------

    [[nodiscard]]
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

    [[nodiscard]]
    CMP_CONDITIONAL_EXPORT
    const value_type&
    grab_value ()
    const noexcept;

    [[nodiscard]]
    CMP_CONDITIONAL_EXPORT
    value_type&
    grab_value ()
    noexcept;

    // Operator Overloads -----------------------------------------------------

    CMP_CONDITIONAL_EXPORT
    friend
    bool
    operator == (
        const pixval& left_operand,
        const pixval& right_operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    friend
    bool
    operator != (
        const pixval& left_operand,
        const pixval& right_operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    friend
    bool
    operator < (
        const pixval& left_operand,
        const pixval& right_operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    friend
    bool
    operator > (
        const pixval& left_operand,
        const pixval& right_operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    friend
    bool
    operator <= (
        const pixval& left_operand,
        const pixval& right_operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    friend
    bool
    operator >= (
        const pixval& left_operand,
        const pixval& right_operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    pixval
    operator + ()
    const noexcept;

    CMP_CONDITIONAL_EXPORT
    pixval
    operator - ()
    const noexcept;

    CMP_CONDITIONAL_EXPORT
    friend
    pixval
    operator + (
        const pixval& left_operand,
        const pixval& right_operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    friend
    pixval
    operator - (
        const pixval& left_operand,
        const pixval& right_operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    friend
    pixval
    operator * (
        const pixval& left_operand,
        const pixval& right_operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    friend
    pixval
    operator / (
        const pixval& left_operand,
        const pixval& right_operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    friend
    pixval
    operator % (
        const pixval& left_operand,
        const pixval& right_operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    friend
    pixval
    operator ~ (
        const pixval& operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    friend
    pixval
    operator & (
        const pixval& left_operand,
        const pixval& right_operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    friend
    pixval
    operator | (
        const pixval& left_operand,
        const pixval& right_operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    friend
    pixval
    operator ^ (
        const pixval& left_operand,
        const pixval& right_operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    friend
    pixval
    operator << (
        const pixval& left_operand,
        const pixval& right_operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    friend
    pixval
    operator >> (
        const pixval& left_operand,
        const pixval& right_operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    pixval&
    operator += (
        const pixval& operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    pixval&
    operator -= (
        const pixval& operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    pixval&
    operator *= (
        const pixval& operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    pixval&
    operator /= (
        const pixval& operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    pixval&
    operator %= (
        const pixval& operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    pixval&
    operator &= (
        const pixval& operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    pixval&
    operator |= (
        const pixval& operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    pixval&
    operator ^= (
        const pixval& operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    pixval&
    operator <<= (
        const pixval& operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    pixval&
    operator >>= (
        const pixval& operand
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    pixval&
    operator ++ ()
    noexcept;

    CMP_CONDITIONAL_EXPORT
    pixval&
    operator -- ()
    noexcept;

    CMP_CONDITIONAL_EXPORT
    pixval
    operator ++ (
        int
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    pixval
    operator -- (
        int
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    friend
    std::ostream&
    operator << (
        std::ostream& stream,
        const pixval& source
    )
    noexcept;

    CMP_CONDITIONAL_EXPORT
    friend
    std::istream&
    operator >> (
        std::istream& stream,
        pixval& target
    )
    noexcept;

private:
    // Private Data -----------------------------------------------------------

    value_type m_value;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#endif // CMP_DESKTOP_GUI_PIXVAL_HPP_INCLUDED
