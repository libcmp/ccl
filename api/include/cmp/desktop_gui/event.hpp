// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_DESKTOP_GUI_EVENT_HPP_INCLUDED
#define CMP_DESKTOP_GUI_EVENT_HPP_INCLUDED

#include <cmp/desktop_gui/inclusion_assert.hpp>

namespace cmp {

/**
    Description:
        Represents the kind of an event.
*/
enum class event_type {
    key_event,
    close_event
}; // enum --------------------------------------------------------------------

/**
    Description:
        This is the base class of all GUI event classes.
*/
class CMP_LIBRARY_NAME event {
public:
    // Constructors and Destructor --------------------------------------------

    /**
        Description:
            Constructs an <#type>event</#type> with the given event type.

        Parameters:
            initial_event_type:
                The type of <#this/> event.
    */
    explicit
    event (
        event_type initial_event_type
    )
    noexcept;

    ~event ()
    = default;

    // Copy Operations --------------------------------------------------------

    /**
        Description:
            Copy-constructs an <#type>event</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>event</#type>
                to copy from.
    */
    event (
        const event& other
    )
    = default;

    /**
        Description:
            Copy-assigns an <#type>event</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>event</#type>
                to copy from.
    */
    event&
    operator = (
        const event& other
    )
    = default;

    // Move Operations --------------------------------------------------------

    /**
        Description:
            Move-constructs an <#type>event</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>event</#type>
                to move from.
    */
    event (
        event&& other
    )
    noexcept = default;

    /**
        Description:
            Move-assigns an <#type>event</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>event</#type>
                to move from.
    */
    event&
    operator = (
        event&& other
    )
    noexcept = default;

    // Accessors --------------------------------------------------------------

    /**
        Description:
            Returns the event type of <#this/> <#type>event</#type>.
    */
    event_type
    get_event_type ()
    const noexcept;

private:
    // Private Data -----------------------------------------------------------

    event_type m_event_type;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#endif // CMP_DESKTOP_GUI_EVENT_HPP_INCLUDED
