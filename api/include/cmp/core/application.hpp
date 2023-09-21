// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_CORE_APPLICATION_HPP_INCLUDED
#define CMP_CORE_APPLICATION_HPP_INCLUDED

#include <string_view>

#include <cmp/core/config.hpp>

namespace cmp {

class CMP_LIBRARY_NAME application {
public:
    // Constructors and Destructor --------------------------------------------

    CMP_CONDITIONAL_INLINE
    application (
        int argc,
        char** argv
    )
    noexcept;

    // Accessors --------------------------------------------------------------

    CMP_CONDITIONAL_INLINE
    static
    application*
    get_instance_ptr ()
    noexcept;

    CMP_CONDITIONAL_INLINE
    int
    get_argc ()
    const;

    CMP_CONDITIONAL_INLINE
    char**
    get_argv ()
    const;

    CMP_CONDITIONAL_INLINE
    std::u8string_view
    get_copyright_notice ()
    const;

    CMP_CONDITIONAL_INLINE
    void
    set_copyright_notice (
        std::u8string_view new_copyright_notice
    );

    // Core -------------------------------------------------------------------

    CMP_CONDITIONAL_INLINE
    virtual
    int
    run ();

private:
    // Private Data -----------------------------------------------------------

    static application* g_instance_ptr;

    int m_argc;
    char** m_argv;
    std::u8string_view m_copyright_notice;
}; // class -------------------------------------------------------------------

CMP_CONDITIONAL_INLINE
application*
app ()
noexcept;

} // namespace ----------------------------------------------------------------

#if CMP_CONFIG_HEADER_ONLY == true
#   include <cmp/core/application.cpp>
#endif // CMP_CONFIG_HEADER_ONLY

#endif // CMP_CORE_APPLICATION_HPP_INCLUDED
