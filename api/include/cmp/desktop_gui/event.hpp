// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_DESKTOP_GUI_EVENT_HPP_INCLUDED
#define CMP_DESKTOP_GUI_EVENT_HPP_INCLUDED

#include <cmp/desktop_gui/inclusion_assert.hpp>

namespace cmp {

enum class event_type {
    key_event,
    close_event
}; // enum --------------------------------------------------------------------

class CMP_LIBRARY_NAME event {
public:
    // Constructors and Destructor --------------------------------------------

    explicit
    event (
        event_type initial_event_type
    )
    noexcept;

    ~event ()
    noexcept = default;

    // Accessors --------------------------------------------------------------

    event_type
    get_event_type ()
    const noexcept;

private:
    // Private Data -----------------------------------------------------------

    event_type m_event_type;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#endif // CMP_DESKTOP_GUI_EVENT_HPP_INCLUDED
