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

    CMP_CONDITIONAL_INLINE
    close_event (
        bool initial_should_close
    )
    noexcept;

    CMP_CONDITIONAL_INLINE
    ~close_event ()
    noexcept = default;

    // Accessors --------------------------------------------------------------

    CMP_CONDITIONAL_INLINE
    bool
    should_close ()
    const noexcept;

    CMP_CONDITIONAL_INLINE
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

#if CMP_CONFIG_HEADER_ONLY == true
#   include <cmp/desktop_gui/close_event.cpp>
#endif // CMP_CONFIG_HEADER_ONLY

#endif // CMP_DESKTOP_GUI_CLOSE_EVENT_HPP_INCLUDED
