// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/desktop_gui/key_event.hpp>

namespace cmp {

// ------------------------------------------------------------ cmp::key_event

// Constructors and Destructor ------------------------------------------------

key_event::key_event (
    key_event_type initial_key_event_type,
    key initial_key
)
noexcept
    : event{event_type::key_event}
    , m_key_event_type{initial_key_event_type}
    , m_key{initial_key}
{
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

key_event_type
key_event::get_key_event_type ()
const noexcept
{
    return m_key_event_type;
} // function -----------------------------------------------------------------

key
key_event::get_key ()
const noexcept
{
    return m_key;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
