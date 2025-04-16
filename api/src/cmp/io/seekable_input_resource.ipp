// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/io/seekable_input_resource.hpp>

namespace cmp {

// ------------------------------------ cmp::seekable_input_resource<Position>

// Constructors and Destructor ------------------------------------------------

template <
    typename Position
>
seekable_input_resource<Position>::seekable_input_resource ()
{
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

template <
    typename Position
>
void
seekable_input_resource<Position>::set_position (
    position_type new_position,
    position_reference pr
)
noexcept
{
    this->set_position_raw(new_position, pr);
    m_buffer.set_read_dirty(true);
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
