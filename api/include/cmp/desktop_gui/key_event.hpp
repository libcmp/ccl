// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_DESKTOP_GUI_KEY_EVENT_HPP_INCLUDED
#define CMP_DESKTOP_GUI_KEY_EVENT_HPP_INCLUDED

#include <cmp/desktop_gui/inclusion_assert.hpp>
#include <cmp/desktop_gui/event.hpp>
#include <cmp/desktop_gui/general.hpp>

namespace cmp {

/**
    Description:
        Represents the kind of a key event.
*/
enum class key_event_type {
    key_down,
    key_up
}; // enum --------------------------------------------------------------------

/**
    Description:
        A key event is an event which describes a key press or a key
        release. You call <#function>get_key</#function> to get the
        key that was pressed or released.
*/
class CMP_LIBRARY_NAME key_event
    : public event
{
public:
    // Constructors and Destructor --------------------------------------------

    /**
        Description:
            Constructs a key event with the given key event type and key.

        Parameters:
            initial_key_event_type:
                The kind of the key event.
            initial_key:
                The key associated with the key event.
    */
    key_event (
        key_event_type initial_key_event_type,
        key initial_key
    )
    noexcept;

    ~key_event ()
    = default;

    // Copy Operations --------------------------------------------------------

    /**
        Description:
            Copy-constructs a <#type>key_event</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>key_event</#type>
                to copy from.
    */
    key_event (
        const key_event& other
    )
    = default;

    /**
        Description:
            Copy-assigns a <#type>key_event</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>key_event</#type>
                to copy from.
    */
    key_event&
    operator = (
        const key_event& other
    )
    = default;

    // Move Operations --------------------------------------------------------

    /**
        Description:
            Move-constructs a <#type>key_event</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>key_event</#type>
                to move from.
    */
    key_event (
        key_event&& other
    )
    noexcept = default;

    /**
        Description:
            Move-assigns a <#type>key_event</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>key_event</#type>
                to move from.
    */
    key_event&
    operator = (
        key_event&& other
    )
    noexcept = default;

    // Accessors --------------------------------------------------------------

    /**
        Description:
            Returns the key event type of <#this/> <#type>key_event</#type>.
    */
    key_event_type
    get_key_event_type ()
    const noexcept;

    /**
        Description:
            Returns the key that was pressed or released.
    */
    key
    get_key ()
    const noexcept;

private:
    // Private Data -----------------------------------------------------------

    key_event_type m_key_event_type;
    key m_key;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#endif // CMP_DESKTOP_GUI_KEY_EVENT_HPP_INCLUDED
