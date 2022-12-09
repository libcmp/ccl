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
    set_only_instance(this);
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
application::get_only_instance ()
noexcept
{
    return g_application;
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

// Protected Functions --------------------------------------------------------

void
application::set_only_instance (
    application* application_instance
)
noexcept
{
    g_application = application_instance;
} // function -----------------------------------------------------------------

// Private Data ---------------------------------------------------------------

inline application* application::g_application;

} // namespace ----------------------------------------------------------------
