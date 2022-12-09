// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/unicode/exceptions.hpp>

namespace cmp {

// --------------------------------------------------- cmp::invalid_code_point

// Core -----------------------------------------------------------------------

const char*
invalid_code_point::what ()
const noexcept
{
    return "Invalid code point.";
} // function -----------------------------------------------------------------

// --------------------------------------------- cmp::invalid_unicode_encoding

// Core -----------------------------------------------------------------------

const char*
invalid_unicode_encoding::what ()
const noexcept
{
    return "The data read from the stream or string is not valid "
           "UTF-8 or UTF-16. UTF-32 is not affected because it is "
           "not a variable length encoding.";
} // function -----------------------------------------------------------------

// ---------------------------------------------------- cmp::iterated_past_end

// Core -----------------------------------------------------------------------

const char*
iterated_past_end::what ()
const noexcept
{
    return "An attempt was made to iterate past the end of a string.";
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
