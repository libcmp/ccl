// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_CORE_APPLICATION_HPP_INCLUDED
#define CMP_CORE_APPLICATION_HPP_INCLUDED

#include <string_view>

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

    // Accessors --------------------------------------------------------------

    static
    application*
    get_instance_ptr ()
    noexcept;

    int
    get_argc ()
    const;

    char**
    get_argv ()
    const;

    std::u8string_view
    get_copyright_notice ()
    const;

    void
    set_copyright_notice (
        std::u8string_view new_copyright_notice
    );

    // Core -------------------------------------------------------------------

    virtual
    int
    run ();

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

    static application* g_instance_ptr;

    int m_argc;
    char** m_argv;
    std::u8string_view m_copyright_notice;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#if CMP_HEADER_ONLY == true
#   include <cmp/core/application.cpp>
#endif // CMP_HEADER_ONLY

#endif // CMP_CORE_APPLICATION_HPP_INCLUDED
