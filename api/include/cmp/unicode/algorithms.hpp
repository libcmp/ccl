// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_UNICODE_ALGORITHMS_HPP_INCLUDED
#define CMP_UNICODE_ALGORITHMS_HPP_INCLUDED

#include <string_view>
#include <cstring>

#include <cmp/unicode/inclusion_assert.hpp>
#include <cmp/core/config.hpp>
#include <cmp/unicode/concepts.hpp>
#include <cmp/unicode/by_code_point.hpp>
#include <cmp/unicode/exceptions.hpp>

namespace cmp {

// Free Functions -------------------------------------------------------------

/**
    Description:
        Returns true if the <#parameter>content</#parameter> strings
        starts with the contents of <#parameter>substring</#parameter>.

    Parameters:
        content:
            The string to look at the start of.
        substring:
            The substring to look for.
*/
template <
    text_object ContentString,
    text_object Substring
>
bool
starts_with (
    const ContentString& content,
    const Substring& substring
)
noexcept;

/**
    Description:
        Returns true if the <#parameter>content</#parameter> strings
        ends with the contents of <#parameter>substring</#parameter>.

    Parameters:
        content:
            The string to look at the end of.
        substring:
            The substring to look for.
*/
template <
    text_object ContentString,
    text_object Substring
>
bool
ends_with (
    const ContentString& content,
    const Substring& substring
)
noexcept;

/**
    Description:
        Returns the number of characters in the given string.

    Parameters:
        s:
            The string to get the size of.
*/
CMP_CONDITIONAL_INLINE
CMP_LIBRARY_NAME
std::size_t
string_size (
    const std::string& s
)
noexcept;

/**
    Description:
        Returns the number of code units in the given string.

    Parameters:
        s:
            The string to get the size of.
*/
CMP_CONDITIONAL_INLINE
CMP_LIBRARY_NAME
std::size_t
string_size (
    const std::u8string& s
)
noexcept;

/**
    Description:
        Returns the number of code units in the given string.

    Parameters:
        s:
            The string to get the size of.
*/
CMP_CONDITIONAL_INLINE
CMP_LIBRARY_NAME
std::size_t
string_size (
    const std::u16string& s
)
noexcept;

/**
    Description:
        Returns the number of code units in the given string.

    Parameters:
        s:
            The string to get the size of.
*/
CMP_CONDITIONAL_INLINE
CMP_LIBRARY_NAME
std::size_t
string_size (
    const std::u32string& s
)
noexcept;

/**
    Description:
        Returns the number of code units in the given string.

    Parameters:
        s:
            The string to get the size of.
*/
CMP_CONDITIONAL_INLINE
CMP_LIBRARY_NAME
std::size_t
string_size (
    const std::wstring& s
)
noexcept;

/**
    Description:
        Returns the number of characters in the given string.

    Parameters:
        s:
            The string to get the size of.
*/
CMP_CONDITIONAL_INLINE
CMP_LIBRARY_NAME
std::size_t
string_size (
    const std::string_view& s
)
noexcept;

/**
    Description:
        Returns the number of code units in the given string.

    Parameters:
        s:
            The string to get the size of.
*/
CMP_CONDITIONAL_INLINE
CMP_LIBRARY_NAME
std::size_t
string_size (
    const std::u8string_view& s
)
noexcept;

/**
    Description:
        Returns the number of code units in the given string.

    Parameters:
        s:
            The string to get the size of.
*/
CMP_CONDITIONAL_INLINE
CMP_LIBRARY_NAME
std::size_t
string_size (
    const std::u16string_view& s
)
noexcept;

/**
    Description:
        Returns the number of code units in the given string.

    Parameters:
        s:
            The string to get the size of.
*/
CMP_CONDITIONAL_INLINE
CMP_LIBRARY_NAME
std::size_t
string_size (
    const std::u32string_view& s
)
noexcept;

/**
    Description:
        Returns the number of code units in the given string.

    Parameters:
        s:
            The string to get the size of.
*/
CMP_CONDITIONAL_INLINE
CMP_LIBRARY_NAME
std::size_t
string_size (
    const std::wstring_view& s
)
noexcept;

/**
    Description:
        Returns the number of characters in the given string.

    Parameters:
        s:
            The string to get the size of.
*/
CMP_CONDITIONAL_INLINE
CMP_LIBRARY_NAME
std::size_t
string_size (
    const char* s
)
noexcept;

/**
    Description:
        Returns the number of code units in the given string.

    Parameters:
        s:
            The string to get the size of.
*/
CMP_CONDITIONAL_INLINE
CMP_LIBRARY_NAME
std::size_t
string_size (
    const char8_t* s
)
noexcept;

/**
    Description:
        Returns the number of code units in the given string.

    Parameters:
        s:
            The string to get the size of.
*/
CMP_CONDITIONAL_INLINE
CMP_LIBRARY_NAME
std::size_t
string_size (
    const char16_t* s
)
noexcept;

/**
    Description:
        Returns the number of code units in the given string.

    Parameters:
        s:
            The string to get the size of.
*/
CMP_CONDITIONAL_INLINE
CMP_LIBRARY_NAME
std::size_t
string_size (
    const char32_t* s
)
noexcept;

/**
    Description:
        Returns the number of code units in the given string.

    Parameters:
        s:
            The string to get the size of.
*/
CMP_CONDITIONAL_INLINE
CMP_LIBRARY_NAME
std::size_t
string_size (
    const wchar_t* s
)
noexcept;

/**
    Description:
        Inserts the given code point into the given string at the given index.

    Parameters:
        s:
            The string to insert the code point into.
        code_point:
            The code point to insert.
        index:
            The index of the string at which to insert the code point.
*/
template <
    writable_raii_text_object TargetString
>
void
insert_code_point (
    TargetString& s,
    char32_t code_point,
    typename TargetString::size_type index
);

/**
    Description:
        Appends the given code point to the given string.

    Parameters:
        s:
            The string to append the code point to.
        code_point:
            The code point to append.
*/
template <
    writable_raii_text_object TargetString
>
void
append_code_point (
    TargetString& s,
    char32_t code_point
);

/**
    Description:
        Prepends the given code point to the given string.

    Parameters:
        s:
            The string to prepend the code point to.
        code_point:
            The code point to prepend.
*/
template <
    writable_raii_text_object TargetString
>
void
prepend_code_point (
    TargetString& s,
    char32_t code_point
);

/**
    Description:
        Converts the given string to the requested string type.

    Parameters:
        s:
            The string to convert.
*/
template <
    writable_raii_text_object OutputString,
    text_object InputString
>
OutputString
convert_string (
    const InputString& s
);

/**
    Description:
        Converts the given string to a <#type>std::string</#type>.

    Parameters:
        s:
            The string to convert to <#type>std::string</#type>.
*/
template <
    text_object InputString
>
std::string
to_string (
    const InputString& s
);

/**
    Description:
        Converts the given string to a <#type>std::u8string</#type>.

    Parameters:
        s:
            The string to convert to <#type>std::u8string</#type>.
*/
template <
    text_object InputString
>
std::u8string
to_u8string (
    const InputString& s
);

/**
    Description:
        Converts the given string to a <#type>std::u16string</#type>.

    Parameters:
        s:
            The string to convert to <#type>std::u16string</#type>.
*/
template <
    text_object InputString
>
std::u16string
to_u16string (
    const InputString& s
);

/**
    Description:
        Converts the given string to a <#type>std::u32string</#type>.

    Parameters:
        s:
            The string to convert to <#type>std::u32string</#type>.
*/
template <
    text_object InputString
>
std::u32string
to_u32string (
    const InputString& s
);

/**
    Description:
        Converts the given string to a <#type>std::wstring</#type>.

    Parameters:
        s:
            The string to convert to <#type>std::wstring</#type>.
*/
template <
    text_object InputString
>
std::wstring
to_wstring (
    const InputString& s
);

/**
    Description:
        Validates the given string and returns a by_code_point constant
        iterator just past the last valid code point, which is the end
        iterator if the entire string is valid.

    Parameters:
        s:
            The string to validate.
*/
template <
    text_object InputString
>
typename by_code_point<value_type_t<InputString>>::const_iterator
validate_string (
    const InputString& s
)
noexcept;

} // namespace ----------------------------------------------------------------

#include <cmp/unicode/algorithms.ipp>
#if CMP_CONFIG_HEADER_ONLY == true
#   include <cmp/unicode/algorithms.cpp>
#endif // CMP_CONFIG_HEADER_ONLY

#endif // CMP_UNICODE_ALGORITHMS_HPP_INCLUDED
