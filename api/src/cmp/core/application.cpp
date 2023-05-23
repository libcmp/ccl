// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/core/application.hpp>

namespace cmp {

// ---------------------------------------------------------- cmp::application

// Constructors and Destructor ------------------------------------------------

application::application (
    int argc,
    char **argv
)
noexcept
    : m_argc{argc}
    , m_argv{argv}
{
    set_instance_ptr(this);
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

int
application::run ()
noexcept
{
    return 0;
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

application*
application::get_instance_ptr ()
noexcept
{
    return g_instance_ptr;
} // function -----------------------------------------------------------------

int
application::get_argc()
const
{
    return m_argc;
} // function -----------------------------------------------------------------

char**
application::get_argv()
const
{
    return m_argv;
} // function -----------------------------------------------------------------

std::u8string_view
application::get_copyright_notice ()
const
{
    return m_copyright_notice;
} // function -----------------------------------------------------------------

void
application::set_copyright_notice (
    std::u8string_view new_copyright_notice
) {
    m_copyright_notice = new_copyright_notice;
} // function -----------------------------------------------------------------

// Protected Functions --------------------------------------------------------

void
application::set_instance_ptr (
    application* instance_ptr
)
noexcept
{
    g_instance_ptr = instance_ptr;
} // function -----------------------------------------------------------------

// Private Data ---------------------------------------------------------------

application* application::g_instance_ptr;

} // namespace ----------------------------------------------------------------
