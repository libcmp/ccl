// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/io/seekable_output_resource.hpp>

namespace cmp {

// --------------------------------------------- cmp::seekable_output_resource

// Constructors and Destructor ------------------------------------------------

template <
    typename Position
>
seekable_output_resource<Position>::seekable_output_resource (
    std::size_t buffer_capacity
)
    : transfer_resource{buffer_capacity}
    , seekable_transfer_resource<Position>{buffer_capacity}
    , output_resource{buffer_capacity}
{
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

template <
    typename Position
>
void
seekable_output_resource<Position>::set_position (
    position_type new_position,
    position_reference pr
)
noexcept
{
    this->flush();
    this->set_position_raw(new_position, pr);
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
