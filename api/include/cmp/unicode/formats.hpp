// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_UNICODE_FORMATS_HPP_INCLUDED
#define CMP_UNICODE_FORMATS_HPP_INCLUDED

#include <concepts>
#include <stdexcept>
#include <string>

#include <cmp/unicode/inclusion_assert.hpp>

namespace cmp {

/**
    Description:
        This exception type indicates that an invalid radix was supplied.
*/
class CMP_LIBRARY_NAME invalid_radix
    : public std::invalid_argument
{
public:
    // Constructors and Destructor --------------------------------------------

    /**
        Description:
            Constructs an <#type>invalid_radix</#type>.
    */
    CMP_CONDITIONAL_INLINE
    invalid_radix ()
    noexcept;

    CMP_CONDITIONAL_INLINE
    ~invalid_radix ()
    noexcept = default;
}; // class -------------------------------------------------------------------

enum class sign_status {
    always_show,
    only_when_negative
}; // enum --------------------------------------------------------------------

enum class thousands_separator {
    none,
    comma,
    period
}; // enum --------------------------------------------------------------------

enum class radix_character {
    comma,
    period
}; // enum --------------------------------------------------------------------

enum class radix_place_limit {
    none,
    exactly_equal,
    up_to
};

class CMP_LIBRARY_NAME bool_format {
public:
    // Constructors and Destructor --------------------------------------------

    /**
        Description:
            Construct a default bool format, where the true
            string is u8"1" and the false string is u8"0".
    */
    CMP_CONDITIONAL_INLINE
    bool_format ()
    noexcept;

    /**
        Description:
            Construct a bool format with the
            given true string and false string.

        Parameters:
            initial_true_string:
                The string to use when the bool value is true.
            initial_false_string:
                The string to use when the bool value is false.
    */
    CMP_CONDITIONAL_INLINE
    bool_format (
        const std::u8string& initial_true_string,
        const std::u8string& initial_false_string
    );

    CMP_CONDITIONAL_INLINE
    ~bool_format ()
    noexcept = default;

    // Copy Operations --------------------------------------------------------

    /**
        Description:
            Copy-constructs a <#type>bool_format</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>bool_format</#type> to copy from.
    */
    CMP_CONDITIONAL_INLINE
    bool_format (
        const bool_format& other
    )
    = default;

    /**
        Description:
            Copy-assigns a <#type>bool_format</#type> into <#this/> one.

        Parameters:
            other:
                The <#type>bool_format</#type> to copy from.
    */
    CMP_CONDITIONAL_INLINE
    bool_format&
    operator = (
        const bool_format& other
    )
    = default;

    // Move Operations --------------------------------------------------------

    /**
        Description:
            Move-constructs a <#type>bool_format</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>bool_format</#type> to move from.
    */
    CMP_CONDITIONAL_INLINE
    bool_format (
        bool_format&& other
    )
    noexcept = default;

    /**
        Description:
            Move-assigns a <#type>bool_format</#type> into <#this/> one.

        Parameters:
            other:
                The <#type>bool_format</#type> to move from.
    */
    CMP_CONDITIONAL_INLINE
    bool_format&
    operator = (
        bool_format&& other
    )
    noexcept = default;

    // Accessors --------------------------------------------------------------

    /**
        Description:
            Returns the true string of <#this/> bool format.
    */
    CMP_CONDITIONAL_INLINE
    std::u8string
    get_true_string ()
    const noexcept;

    /**
        Description:
            Sets the true string of <#this/> bool format.

        Parameters:
            new_true_string:
                The new true string of <#this/> bool format.
    */
    CMP_CONDITIONAL_INLINE
    void
    set_true_string (
        const std::u8string& new_true_string
    )
    noexcept;

    /**
        Description:
            Returns the false string of <#this/> bool format.
    */
    CMP_CONDITIONAL_INLINE
    std::u8string
    get_false_string ()
    const noexcept;

    /**
        Description:
            Sets the false string of <#this/> bool format.

        Parameters:
            new_false_string:
                The new false string of <#this/> bool format.
    */
    CMP_CONDITIONAL_INLINE
    void
    set_false_string (
        const std::u8string& new_false_string
    )
    noexcept;

private:
    // Private Data -----------------------------------------------------------

    std::u8string m_true_string;
    std::u8string m_false_string;
}; // class -------------------------------------------------------------------

class CMP_LIBRARY_NAME integer_format {
public:
    // Constructors and Destructor --------------------------------------------

    /**
        Description:
            Construct a default integer format, where
            the radix is 10, the sign status is
            <#enumerator>sign_status::only_when_negative</#enumerator>,
            and the thousands separator is
            <#enumerator>thousands_separator::none</#enumerator>.
    */
    CMP_CONDITIONAL_INLINE
    integer_format ()
    noexcept;

    /**
        Description:
            Construct an integer format with the given
            radix, sign status and thousands separator.

        Parameters:
            initial_radix:
                The radix.
            initial_sign_status:
                The sign status.
            initial_thousands_separator:
                The thousands separator.
    */
    CMP_CONDITIONAL_INLINE
    integer_format (
        unsigned int initial_radix,
        sign_status initial_sign_status,
        thousands_separator initial_thousands_separator
    );

    CMP_CONDITIONAL_INLINE
    ~integer_format ()
    noexcept = default;

    // Copy Operations --------------------------------------------------------

    /**
        Description:
            Copy-constructs an <#type>integer_format</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>integer_format</#type> to copy from.
    */
    CMP_CONDITIONAL_INLINE
    integer_format (
        const integer_format& other
    )
    = default;

    /**
        Description:
            Copy-assigns an <#type>integer_format</#type> into <#this/> one.

        Parameters:
            other:
                The <#type>integer_format</#type> to copy from.
    */
    CMP_CONDITIONAL_INLINE
    integer_format&
    operator = (
        const integer_format& other
    )
    = default;

    // Move Operations --------------------------------------------------------

    /**
        Description:
            Move-constructs an <#type>integer_format</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>integer_format</#type> to move from.
    */
    CMP_CONDITIONAL_INLINE
    integer_format (
        integer_format&& other
    )
    noexcept = default;

    /**
        Description:
            Move-assigns an <#type>integer_format</#type> into <#this/> one.

        Parameters:
            other:
                The <#type>integer_format</#type> to move from.
    */
    CMP_CONDITIONAL_INLINE
    integer_format&
    operator = (
        integer_format&& other
    )
    noexcept = default;

    // Accessors --------------------------------------------------------------

    /**
        Description:
            Returns the radix of <#this/> integer format.
    */
    CMP_CONDITIONAL_INLINE
    unsigned int
    get_radix ()
    const noexcept;

    /**
        Description:
            Sets the radix of <#this/> integer format.

        Parameters:
            new_radix:
                The new radix of <#this/> integer format.
    */
    CMP_CONDITIONAL_INLINE
    void
    set_radix (
        unsigned int new_radix
    )
    noexcept;

    /**
        Description:
            Returns the sign status of <#this/> integer format.
    */
    CMP_CONDITIONAL_INLINE
    sign_status
    get_sign_status ()
    const noexcept;

    /**
        Description:
            Sets the sign status of <#this/> integer format.

        Parameters:
            new_sign_status:
                The new sign status of <#this/> integer format.
    */
    CMP_CONDITIONAL_INLINE
    void
    set_sign_status (
        sign_status new_sign_status
    )
    noexcept;

    /**
        Description:
            Returns the thousands separator of <#this/> integer format.
    */
    CMP_CONDITIONAL_INLINE
    thousands_separator
    get_thousands_separator ()
    const noexcept;

    /**
        Description:
            Sets the thousands separator of <#this/> integer format.

        Parameters:
            new_thousands_separator:
                The new thousands separator of <#this/> integer format.
    */
    CMP_CONDITIONAL_INLINE
    void
    set_thousands_separator (
        thousands_separator new_thousands_separator
    )
    noexcept;

private:
    // Private Data -----------------------------------------------------------

    unsigned int m_radix;
    sign_status m_sign_status;
    thousands_separator m_thousands_separator;
}; // class -------------------------------------------------------------------

class CMP_LIBRARY_NAME floating_point_format {
public:
    // Constructors and Destructor --------------------------------------------

    /**
        Description:
            Construct a default floating point format, where
            the radix is 10, the sign status is
            <#enumerator>sign_status::only_when_negative</#enumerator>,
            the thousands separator is
            <#enumerator>thousands_separator::none</#enumerator>, the radix
            character is <#enumerator>radix_character::period</#enumerator>,
            the radix place limit is
            <#enumerator>radix_place_limit::none</#enumerator> and the radix
            place count is 0.
    */
    CMP_CONDITIONAL_INLINE
    floating_point_format ()
    noexcept;

    /**
        Description:
            Construct a floating point format with the given radix,
            sign status, thousands separator, radix character, radix
            place limit and radix place count.

        Parameters:
            initial_radix:
                The radix.
            initial_sign_status:
                The sign status.
            initial_thousands_separator:
                The thousands separator.
            initial_radix_character:
                The radix character.
            initial_radix_place_limit:
                The radix place limit.
            initial_radix_place_count:
                The radix place count.
    */
    CMP_CONDITIONAL_INLINE
    floating_point_format (
        unsigned int initial_radix,
        sign_status initial_sign_status,
        thousands_separator initial_thousands_separator,
        radix_character initial_radix_character,
        radix_place_limit initial_radix_place_limit,
        unsigned int initial_radix_place_count
    );

    CMP_CONDITIONAL_INLINE
    ~floating_point_format ()
    noexcept = default;

    // Copy Operations --------------------------------------------------------

    /**
        Description:
            Copy-constructs a <#type>floating_point_format</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>floating_point_format</#type> to copy from.
    */
    CMP_CONDITIONAL_INLINE
    floating_point_format (
        const floating_point_format& other
    )
    = default;

    /**
        Description:
            Copy-assigns a <#type>floating_point_format</#type> into <#this/>
            one.

        Parameters:
            other:
                The <#type>floating_point_format</#type> to copy from.
    */
    CMP_CONDITIONAL_INLINE
    floating_point_format&
    operator = (
        const floating_point_format& other
    )
    = default;

    // Move Operations --------------------------------------------------------

    /**
        Description:
            Move-constructs a <#type>floating_point_format</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>floating_point_format</#type> to move from.
    */
    CMP_CONDITIONAL_INLINE
    floating_point_format (
        floating_point_format&& other
    )
    noexcept = default;

    /**
        Description:
            Move-assigns a <#type>floating_point_format</#type> into <#this/>
            one.

        Parameters:
            other:
                The <#type>floating_point_format</#type> to move from.
    */
    CMP_CONDITIONAL_INLINE
    floating_point_format&
    operator = (
        floating_point_format&& other
    )
    noexcept = default;

    // Accessors --------------------------------------------------------------

    /**
        Description:
            Returns the radix of <#this/> floating point format.
    */
    CMP_CONDITIONAL_INLINE
    unsigned int
    get_radix ()
    const noexcept;

    /**
        Description:
            Sets the radix of <#this/> floating point format.

        Parameters:
            new_radix:
                The new radix of <#this/> floating point format.
    */
    CMP_CONDITIONAL_INLINE
    void
    set_radix (
        unsigned int new_radix
    )
    noexcept;

    /**
        Description:
            Returns the sign status of <#this/> floating point format.
    */
    CMP_CONDITIONAL_INLINE
    sign_status
    get_sign_status ()
    const noexcept;

    /**
        Description:
            Sets the sign status of <#this/> floating point format.

        Parameters:
            new_sign_status:
                The new sign status of <#this/> floating point format.
    */
    CMP_CONDITIONAL_INLINE
    void
    set_sign_status (
        sign_status new_sign_status
    )
    noexcept;

    /**
        Description:
            Returns the thousands separator of <#this/> floating point format.
    */
    CMP_CONDITIONAL_INLINE
    thousands_separator
    get_thousands_separator ()
    const noexcept;

    /**
        Description:
            Sets the thousands separator of <#this/> floating point format.

        Parameters:
            new_thousands_separator:
                The new thousands separator of <#this/> floating point format.
    */
    CMP_CONDITIONAL_INLINE
    void
    set_thousands_separator (
        thousands_separator new_thousands_separator
    )
    noexcept;

    /**
        Description:
            Returns the radix character of <#this/> floating point format.
    */
    CMP_CONDITIONAL_INLINE
    radix_character
    get_radix_character ()
    const noexcept;

    /**
        Description:
            Sets the radix character of <#this/> floating point format.

        Parameters:
            new_radix_character:
                The new radix character of <#this/> floating point format.
    */
    CMP_CONDITIONAL_INLINE
    void
    set_radix_character (
        radix_character new_radix_character
    )
    noexcept;

    /**
        Description:
            Returns the radix place limit of <#this/> floating point format.
    */
    CMP_CONDITIONAL_INLINE
    radix_place_limit
    get_radix_place_limit ()
    const noexcept;

    /**
        Description:
            Sets the radix place limit of <#this/> floating point format.

        Parameters:
            new_radix_place_limit:
                The new radix place limit of <#this/> floating point format.
    */
    CMP_CONDITIONAL_INLINE
    void
    set_radix_place_limit (
        radix_place_limit new_radix_place_limit
    )
    noexcept;

    /**
        Description:
            Returns the radix place count of <#this/> floating point format.
    */
    CMP_CONDITIONAL_INLINE
    unsigned int
    get_radix_place_count ()
    const noexcept;

    /**
        Description:
            Sets the radix place count of <#this/> floating point format.

        Parameters:
            new_radix_place_count:
                The new radix place count of <#this/> floating point format.
    */
    CMP_CONDITIONAL_INLINE
    void
    set_radix_place_count (
        unsigned int new_radix_place_count
    )
    noexcept;

private:
    // Private Data -----------------------------------------------------------

    unsigned int m_radix;
    sign_status m_sign_status;
    thousands_separator m_thousands_separator;
    radix_character m_radix_character;
    radix_place_limit m_radix_place_limit;
    unsigned int m_radix_place_count;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#if CMP_CONFIG_HEADER_ONLY == true
#   include <cmp/unicode/formats.cpp>
#endif // CMP_CONFIG_HEADER_ONLY

#endif // CMP_UNICODE_FORMATS_HPP_INCLUDED
