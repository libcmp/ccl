// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/desktop_gui/event.hpp>

namespace cmp {

// ---------------------------------------------------------------- cmp::event

// Constructors and Destructor ------------------------------------------------

event::event (
    event_type initial_event_type
)
noexcept
    : m_event_type{initial_event_type}
{
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

event_type
event::get_event_type ()
const noexcept
{
    return m_event_type;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
