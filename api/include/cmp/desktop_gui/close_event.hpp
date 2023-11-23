// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_DESKTOP_GUI_CLOSE_EVENT_HPP_INCLUDED
#define CMP_DESKTOP_GUI_CLOSE_EVENT_HPP_INCLUDED

#include <cmp/desktop_gui/inclusion_assert.hpp>
#include <cmp/desktop_gui/event.hpp>

namespace cmp {

class CMP_LIBRARY_NAME close_event
    : public event
{
public:
    // Constructors and Destructor --------------------------------------------

    explicit
    close_event (
        bool initial_should_close
    )
    noexcept;

    ~close_event ()
    noexcept = default;

    // Accessors --------------------------------------------------------------

    bool
    should_close ()
    const noexcept;

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
