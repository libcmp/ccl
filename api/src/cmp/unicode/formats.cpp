// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/unicode/formats.hpp>

namespace cmp {

// -------------------------------------------------------- cmp::invalid_radix

// Constructors and Destructor ------------------------------------------------

invalid_radix::invalid_radix ()
noexcept
    : std::invalid_argument{
          "The supplied radix was less than 2 or greater than 36."
      }
{
} // function -----------------------------------------------------------------

// ---------------------------------------------------------- cmp::bool_format

// Constructors and Destructor ------------------------------------------------

bool_format::bool_format ()
noexcept
    : m_true_string{u8"1"}
    , m_false_string{u8"0"}
{
} // function -----------------------------------------------------------------

bool_format::bool_format (
    const std::u8string &initial_true_string,
    const std::u8string &initial_false_string
)
    : m_true_string{initial_true_string}
    , m_false_string{initial_false_string}
{
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

std::u8string
bool_format::get_true_string ()
const noexcept
{
    return m_true_string;
} // function -----------------------------------------------------------------

void
bool_format::set_true_string (
    const std::u8string& new_true_string
)
noexcept
{
    m_true_string = new_true_string;
} // function -----------------------------------------------------------------

std::u8string
bool_format::get_false_string ()
const noexcept
{
    return m_false_string;
} // function -----------------------------------------------------------------

void
bool_format::set_false_string (
    const std::u8string& new_false_string
)
noexcept
{
    m_false_string = new_false_string;
} // function -----------------------------------------------------------------

// ------------------------------------------------------- cmp::integer_format

// Constructors and Destructor ------------------------------------------------

integer_format::integer_format ()
noexcept
    : m_radix{10}
    , m_sign_status{sign_status::only_when_negative}
    , m_thousands_separator{thousands_separator::none}
{
} // function -----------------------------------------------------------------

integer_format::integer_format (
    unsigned int initial_radix,
    sign_status initial_sign_status,
    thousands_separator initial_thousands_separator
)
    : m_radix{initial_radix}
    , m_sign_status{initial_sign_status}
    , m_thousands_separator{initial_thousands_separator}
{
    if (m_radix < 2 || m_radix > 36) {
        throw invalid_radix{};
    }
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

unsigned int
integer_format::get_radix ()
const noexcept
{
    return m_radix;
} // function -----------------------------------------------------------------

void
integer_format::set_radix (
    unsigned int new_radix
)
noexcept
{
    m_radix = new_radix;
} // function -----------------------------------------------------------------

sign_status
integer_format::get_sign_status ()
const noexcept
{
    return m_sign_status;
} // function -----------------------------------------------------------------

void
integer_format::set_sign_status (
    sign_status new_sign_status
)
noexcept
{
    m_sign_status = new_sign_status;
} // function -----------------------------------------------------------------

thousands_separator
integer_format::get_thousands_separator ()
const noexcept
{
    return m_thousands_separator;
} // function -----------------------------------------------------------------

void
integer_format::set_thousands_separator (
    thousands_separator new_thousands_separator
)
noexcept
{
    m_thousands_separator = new_thousands_separator;
} // function -----------------------------------------------------------------

// ------------------------------------------------ cmp::floating_point_format

// Constructors and Destructor ------------------------------------------------

floating_point_format::floating_point_format ()
noexcept
    : m_radix{10}
    , m_sign_status{sign_status::only_when_negative}
    , m_thousands_separator{thousands_separator::none}
    , m_radix_character{radix_character::period}
    , m_radix_place_limit{radix_place_limit::none}
    , m_radix_place_count{0}
{
} // function -----------------------------------------------------------------

floating_point_format::floating_point_format (
    unsigned int initial_radix,
    sign_status initial_sign_status,
    thousands_separator initial_thousands_separator,
    radix_character initial_radix_character,
    radix_place_limit initial_radix_place_limit,
    unsigned int initial_radix_place_count
)
    : m_radix{initial_radix}
    , m_sign_status{initial_sign_status}
    , m_thousands_separator{initial_thousands_separator}
    , m_radix_character{initial_radix_character}
    , m_radix_place_limit{initial_radix_place_limit}
    , m_radix_place_count{initial_radix_place_count}
{
    if (m_radix < 2 || m_radix > 36) {
        throw invalid_radix{};
    }
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

unsigned int
floating_point_format::get_radix ()
const noexcept
{
    return m_radix;
} // function -----------------------------------------------------------------

void
floating_point_format::set_radix (
    unsigned int new_radix
)
noexcept
{
    m_radix = new_radix;
} // function -----------------------------------------------------------------

sign_status
floating_point_format::get_sign_status ()
const noexcept
{
    return m_sign_status;
} // function -----------------------------------------------------------------

void
floating_point_format::set_sign_status (
    sign_status new_sign_status
)
noexcept
{
    m_sign_status = new_sign_status;
} // function -----------------------------------------------------------------

thousands_separator
floating_point_format::get_thousands_separator ()
const noexcept
{
    return m_thousands_separator;
} // function -----------------------------------------------------------------

void
floating_point_format::set_thousands_separator (
    thousands_separator new_thousands_separator
)
noexcept
{
    m_thousands_separator = new_thousands_separator;
} // function -----------------------------------------------------------------

radix_character
floating_point_format::get_radix_character ()
const noexcept
{
    return m_radix_character;
} // function -----------------------------------------------------------------

void
floating_point_format::set_radix_character (
    radix_character new_radix_character
)
noexcept
{
    m_radix_character = new_radix_character;
} // function -----------------------------------------------------------------

radix_place_limit
floating_point_format::get_radix_place_limit ()
const noexcept
{
    return m_radix_place_limit;
} // function -----------------------------------------------------------------

void
floating_point_format::set_radix_place_limit (
    radix_place_limit new_radix_place_limit
)
noexcept
{
    m_radix_place_limit = new_radix_place_limit;
} // function -----------------------------------------------------------------

unsigned int
floating_point_format::get_radix_place_count ()
const noexcept
{
    return m_radix_place_count;
} // function -----------------------------------------------------------------

void
floating_point_format::set_radix_place_count (
    unsigned int new_radix_place_count
)
noexcept
{
    m_radix_place_count = new_radix_place_count;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
