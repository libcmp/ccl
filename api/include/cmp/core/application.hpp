// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_CORE_APPLICATION_HPP_INCLUDED
#define CMP_CORE_APPLICATION_HPP_INCLUDED

#include <cmp/core/config.hpp>

namespace cmp {

class application {
public:
    // Constructors and Destructor --------------------------------------------

    application (
        int argc,
        char** argv
    )
    noexcept;

    // Core -------------------------------------------------------------------

    virtual
    int
    run ()
    noexcept;

    // Accessors --------------------------------------------------------------

    static
    application*
    get_instance_ptr ()
    noexcept;

    int
    get_argc()
    const;

    char**
    get_argv()
    const;

protected:
    // Protected Functions ----------------------------------------------------

    static
    void
    set_instance_ptr (
        application* instance_ptr
    )
    noexcept;

private:
    // Private Data -----------------------------------------------------------

    int m_argc;
    char** m_argv;
    static application* g_instance_ptr;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#if CMP_HEADER_ONLY == true
#   include <cmp/core/application.cpp>
#endif // CMP_HEADER_ONLY

#endif // CMP_CORE_APPLICATION_HPP_INCLUDED
