// Copyright (C) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_DESKTOP_GUI_CHECK_GROUP_HPP_INCLUDED
#define CMP_DESKTOP_GUI_CHECK_GROUP_HPP_INCLUDED

#include <vector>

#include <cmp/desktop_gui/inclusion_assert.hpp>
#include <cmp/core/trusted_ptr.hpp>

namespace cmp {

/**
    Description:
        A check group enforces that at most one checkable object of a group
        is checked at any given time. This is most commonly used with radio
        buttons, but any type that supports the
        <#function>is_checked</#function> and
        <#function>set_checked</#function> member
        functions can be used with a check group.
*/
template <
    typename T
>
class check_group {
public:
    // Types ------------------------------------------------------------------

    using element_type = T;

    // Constructors and Destructor --------------------------------------------

    /**
        Description:
            Constructs an empty check group.
    */
    check_group ()
    noexcept = default;

    ~check_group ()
    = default;

    // Copy Operations --------------------------------------------------------

    /**
        Description:
            Copy-constructs a <#type>check_group</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>check_group</#type>
                to copy from.
    */
    check_group (
        const check_group& other
    )
    = default;

    /**
        Description:
            Copy-assigns a <#type>check_group</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>check_group</#type>
                to copy from.
    */
    check_group&
    operator = (
        const check_group& other
    ) &
    = default;

    // Move Operations --------------------------------------------------------

    /**
        Description:
            Move-constructs a <#type>check_group</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>check_group</#type>
                to move from.
    */
    check_group (
        check_group&& other
    )
    noexcept = default;

    /**
        Description:
            Move-assigns a <#type>check_group</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>check_group</#type>
                to move from.
    */
    check_group&
    operator = (
        check_group&& other
    ) &
    noexcept = default;

    // Accessors --------------------------------------------------------------

    const std::vector<cmp::trusted_ptr<element_type>>&
    grab_elements ()
    const noexcept;

    // Core -------------------------------------------------------------------

    /**
        Description:
            Adds an element to <#this/> <#type>check_group</#type>.

        Parameters:
            element:
                The element to add to the check group.
    */
    void
    add_element (
        cmp::trusted_ptr<element_type> element
    );

    /**
        Description:
            Unchecks all elements other than the one provided.

        Parameters:
            element:
                The only element not to uncheck.
    */
    void
    uncheck_complement (
        cmp::trusted_ptr<element_type> element
    );

private:
    // Private Data -----------------------------------------------------------

    std::vector<trusted_ptr<element_type>> m_elements;

    // Private Functions ------------------------------------------------------

    /**
        Description:
            Removes an element from <#this/> <#type>check_group</#type>.

        Parameters:
            element:
                The element to remove from the check group.
    */
    void
    remove_element (
        cmp::trusted_ptr<element_type> element
    );
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#include <cmp/desktop_gui/check_group.ipp>

#endif // CMP_DESKTOP_GUI_CHECK_GROUP_HPP_INCLUDED
