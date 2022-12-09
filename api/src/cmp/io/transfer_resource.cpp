// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/io/transfer_resource.hpp>

namespace cmp {

// ---------------------------------------------------- cmp::transfer_resource

// Constructors and Destructor ------------------------------------------------

transfer_resource::transfer_resource (
    std::size_t buffer_capacity
)
    : m_buffer{buffer_capacity}
{
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
