// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_DESKTOP_GUI_CLOSE_EVENT_HPP_INCLUDED
#define CMP_DESKTOP_GUI_CLOSE_EVENT_HPP_INCLUDED

#include <cmp/desktop_gui/inclusion_assert.hpp>
#include <cmp/desktop_gui/event.hpp>

namespace cmp {

/**
    Description:
        A close event occurs when a user tries to close a window. Call
        <#isnip>set_should_close(false)</#isnip> on the close event to
        specify that the window should not be closed.
*/
class CMP_LIBRARY_NAME close_event
    : public event
{
public:
    // Constructors and Destructor --------------------------------------------

    /**
        Description:
            Constructs a close event with the given decision as
            to whether the associated window should be closed.

        Parameters:
            initial_should_close:
                The value that indicates whether the
                associated window should be closed.
    */
    explicit
    close_event (
        bool initial_should_close
    )
    noexcept;

    ~close_event ()
    = default;

    // Copy Operations --------------------------------------------------------

    /**
        Description:
            Copy-constructs a <#type>close_event</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>close_event</#type>
                to copy from.
    */
    close_event (
        const close_event& other
    )
    = default;

    /**
        Description:
            Copy-assigns a <#type>close_event</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>close_event</#type>
                to copy from.
    */
    close_event&
    operator = (
        const close_event& other
    )
    = default;

    // Move Operations --------------------------------------------------------

    /**
        Description:
            Move-constructs a <#type>close_event</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>close_event</#type>
                to move from.
    */
    close_event (
        close_event&& other
    )
    noexcept = default;

    /**
        Description:
            Move-assigns a <#type>close_event</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>close_event</#type>
                to move from.
    */
    close_event&
    operator = (
        close_event&& other
    )
    noexcept = default;

    // Accessors --------------------------------------------------------------

    /**
        Description:
            Returns true if the window associated with <#this/> event should
            be closed. Otherwise, returns false. This is something you can
            change by calling <#function>set_should_close</#function>.
    */
    bool
    should_close ()
    const noexcept;

    /**
        Description:
            Records whether the window associated
            with <#this/> event should be closed.

        Parameters:
            new_value:
                The value that indicates whether the
                associated window should be closed.
    */
    void
    set_should_close (
        bool new_value
    )
    noexcept;

private:
    // Private Data -----------------------------------------------------------

    bool m_should_close;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#endif // CMP_DESKTOP_GUI_CLOSE_EVENT_HPP_INCLUDED
