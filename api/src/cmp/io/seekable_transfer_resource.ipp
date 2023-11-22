// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/io/seekable_transfer_resource.hpp>

namespace cmp {

// --------------------------------- cmp::seekable_transfer_resource<Position>

// Constructors and Destructor ------------------------------------------------

template <
    typename Position
>
seekable_transfer_resource<Position>::seekable_transfer_resource (
    std::size_t buffer_capacity
)
    : transfer_resource{buffer_capacity}
{
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

template <
    typename Position
>
void
seekable_transfer_resource<Position>::go_back (
    position_type count
)
noexcept
{
    set_position_raw(-count, position_reference::current);
} // function -----------------------------------------------------------------

template <
    typename Position
>
void
seekable_transfer_resource<Position>::go_forward (
    position_type count
)
noexcept
{
    set_position_raw(count, position_reference::current);
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
