// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/io/exceptions.hpp>

namespace cmp {

// -------------------------------------------------------- cmp::read_past_end

// Core -----------------------------------------------------------------------

const char*
read_past_end::what ()
const noexcept
{
    return "An attempt was made to read past the end of a stream.";
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
