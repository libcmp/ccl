// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/desktop_gui/close_event.hpp>

namespace cmp {

// ---------------------------------------------------------- cmp::close_event

// Constructors and Destructor ------------------------------------------------

close_event::close_event (
    bool initial_should_close
)
noexcept
    : event{event_type::close_event}
    , m_should_close{initial_should_close}
{
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

bool
close_event::should_close ()
const noexcept
{
    return m_should_close;
} // function -----------------------------------------------------------------

void
close_event::set_should_close (
    bool new_value
)
noexcept
{
    m_should_close = new_value;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
