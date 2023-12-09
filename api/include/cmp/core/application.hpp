// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_CORE_APPLICATION_HPP_INCLUDED
#define CMP_CORE_APPLICATION_HPP_INCLUDED

#include <string_view>

#include <cmp/core/config.hpp>

namespace cmp {

/**
    Description:
        This class represents the application object. The application object
        is responsible for all initialization necessary for a particular kind
        of program to work. This particular class doesn't do anything other
        than hold common information, like the command line arguments and
        the copyright notice (if any), but subclasses may do more useful
        work.
*/
class CMP_LIBRARY_NAME application {
public:
    // Constructors and Destructor --------------------------------------------

    /**
        Description:
            Constructs an <#type>application</#type>
            with the given command line arguments.

        Parameters:
            argc:
                The number of arguments given on the command line.
            argv:
                The array of pointers to the arguments
                given on the command line.
    */
    CMP_CONDITIONAL_INLINE
    application (
        int argc,
        char** argv
    )
    noexcept;

    CMP_CONDITIONAL_INLINE
    virtual
    ~application ()
    = default;

    // Copy Operations --------------------------------------------------------

    application (
        const application& other
    )
    = delete;

    application&
    operator = (
        const application& other
    )
    = delete;

    // Move Operations --------------------------------------------------------

    /**
        Description:
            Move-constructs an <#type>application</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>application</#type>
                to move from.
    */
    CMP_CONDITIONAL_INLINE
    application (
        application&& other
    )
    noexcept = default;

    /**
        Description:
            Move-assigns an <#type>application</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>application</#type>
                to move from.
    */
    CMP_CONDITIONAL_INLINE
    application&
    operator = (
        application&& other
    )
    noexcept = default;

    // Accessors --------------------------------------------------------------

    /**
        Description:
            Returns a pointer to the application object.
    */
    CMP_CONDITIONAL_INLINE
    static
    application*
    get_instance_ptr ()
    noexcept;

    /**
        Description:
            Returns the number of arguments that
            were given on the command line.
    */
    CMP_CONDITIONAL_INLINE
    int
    get_argc ()
    const;

    /**
        Description:
            Returns the array of pointers to the arguments
            that were given on the command line.
    */
    CMP_CONDITIONAL_INLINE
    char**
    get_argv ()
    const;

    /**
        Description:
            Returns the copyright notice held in <#this/> application object.
    */
    CMP_CONDITIONAL_INLINE
    std::u8string_view
    get_copyright_notice ()
    const;

    /**
        Description:
            Sets <#this/> application object's
            copyright notice to the one provided.

        Parameters:
            new_copyright_notice:
                The new copyright notice to store
                in <#this/> application object.
    */
    CMP_CONDITIONAL_INLINE
    void
    set_copyright_notice (
        std::u8string_view new_copyright_notice
    );

    // Core -------------------------------------------------------------------

    /**
        Description:
            Does nothing except return 0. A subclass
            may provide a more useful implementation.
    */
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

// Free Functions -------------------------------------------------------------

/**
    Description:
        Returns a pointer to the application object.
*/
CMP_CONDITIONAL_INLINE
CMP_LIBRARY_NAME
application*
app ()
noexcept;

} // namespace ----------------------------------------------------------------

#if CMP_CONFIG_HEADER_ONLY == true
#   include <cmp/core/application.cpp>
#endif // CMP_CONFIG_HEADER_ONLY

#endif // CMP_CORE_APPLICATION_HPP_INCLUDED
