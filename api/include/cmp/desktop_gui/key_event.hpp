// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_DESKTOP_GUI_KEY_EVENT_HPP_INCLUDED
#define CMP_DESKTOP_GUI_KEY_EVENT_HPP_INCLUDED

#include <cmp/desktop_gui/inclusion_assert.hpp>
#include <cmp/desktop_gui/event.hpp>
#include <cmp/desktop_gui/general.hpp>

namespace cmp {

enum class key_event_type {
    key_down,
    key_up
}; // enum --------------------------------------------------------------------

class CMP_LIBRARY_NAME key_event
    : public event
{
public:
    // Constructors and Destructor --------------------------------------------

    key_event (
        key_event_type initial_key_event_type,
        key initial_key
    )
    noexcept;

    ~key_event ()
    noexcept = default;

    // Accessors --------------------------------------------------------------

    key_event_type
    get_key_event_type ()
    const noexcept;

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
