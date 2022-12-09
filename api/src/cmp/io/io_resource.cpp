// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/io/io_resource.hpp>

namespace cmp {

// ---------------------------------------------------------- cmp::io_resource

// Constructors and Destructor ------------------------------------------------

io_resource::io_resource (
    std::size_t buffer_capacity
)
    : transfer_resource{buffer_capacity}
{
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
