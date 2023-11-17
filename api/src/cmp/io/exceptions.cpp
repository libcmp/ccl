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

// -------------------------------------------------- cmp::invalid_access_mode

// Core -----------------------------------------------------------------------

const char*
invalid_access_mode::what ()
const noexcept
{
    return "The IO operation attempted is not permitted under the access "
           "mode used. For example, trying to write to a file that was "
           "opened as read-only.";
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
