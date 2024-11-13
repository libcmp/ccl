// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_CORE_TRUSTED_PTR_HPP_INCLUDED
#define CMP_CORE_TRUSTED_PTR_HPP_INCLUDED

#include <string_view>
#include <string>

#include <cmp/core/config.hpp>

namespace cmp {

/**
    Description:
        This class represents a trusted pointer. A trusted pointer is a pointer
        that does not own the pointed-to object, but is free to access it under
        the assumption that the trusted pointer will access it correctly.
        Correct usage of a trusted pointer will depend on the context but
        the idea is that the code using the trusted pointer won't violate
        the trust it has been given. Correct usage of a trusted pointer is
        not enforced, hence the idea of trust.
*/
template <
    typename T
>
class CMP_CONDITIONAL_EXPORT_CLASS trusted_ptr {
public:
    // Types ------------------------------------------------------------------

    using pointer = T*;

    using element_type = T;

    // Constructors and Destructor --------------------------------------------

    trusted_ptr ()
    noexcept;

    ~trusted_ptr ()
    = default;

    // Copy Operations --------------------------------------------------------

    trusted_ptr (
        const trusted_ptr& rhs
    )
    = default;

    trusted_ptr&
    operator = (
        const trusted_ptr& rhs
    )
    = default;

    // Move Operations --------------------------------------------------------

    trusted_ptr (
        trusted_ptr&& rhs
    )
    = default;

    trusted_ptr&
    operator = (
        trusted_ptr&& rhs
    )
    = default;

    // Core -------------------------------------------------------------------

    /**
        Description:
            Returns a trusted pointer that points to
            the same object as the given raw pointer.

        Parameters:
            raw_pointer:
                The raw pointer that the trusted
                pointer will be trusted with.
    */
    static
    trusted_ptr
    assure (
        pointer raw_pointer
    )
    noexcept;

    // Operator Overloads -----------------------------------------------------

    /**
        Description:
            Returns a pointer to the pointed-to object,
            enabling use of the arrow operator.
    */
    pointer
    operator -> ()
    const noexcept;

private:
    // Private Data -----------------------------------------------------------

    pointer m_underlying_pointer;

    // Private Functions ------------------------------------------------------

    explicit
    trusted_ptr (
        pointer initial_underlying_pointer
    )
    noexcept;
}; // class -------------------------------------------------------------------

// Free Functions -------------------------------------------------------------

template <
    typename T
>
trusted_ptr<T>
assure (
    T* raw_pointer
)
noexcept;

} // namespace ----------------------------------------------------------------

#include <cmp/core/trusted_ptr.ipp>

#endif // CMP_CORE_TRUSTED_PTR_HPP_INCLUDED
