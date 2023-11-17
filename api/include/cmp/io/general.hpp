// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_IO_GENERAL_HPP_INCLUDED
#define CMP_IO_GENERAL_HPP_INCLUDED

#include <bit>
#include <exception>
#include <cstddef>

#include <cmp/io/inclusion_assert.hpp>

namespace cmp {

enum access_mode {
    read_only,
    write_only,
    read_and_write
}; // enum --------------------------------------------------------------------

enum encoding_form {
    utf8,
    utf16,
    utf32
}; // enum --------------------------------------------------------------------

enum class read_request {
    lean_retrieval,
    fill_buffer
}; // enum --------------------------------------------------------------------

enum class flush_t {
} inline flush;

enum class position_reference {
    begin,
    current,
    end
}; // enum --------------------------------------------------------------------

enum class if_not_there {
    fail,
    create
}; // enum --------------------------------------------------------------------

/**
    Description:
        Returns the endianness opposite to the endianness provided. For
        example, the opposite of std::endian::big is std::endian::little
        and vice-versa.

    Parameters:
        endianness:
            The endianness to get the opposite of.
*/
CMP_CONDITIONAL_INLINE
CMP_LIBRARY_NAME
constexpr
std::endian
get_opposite_endianness (
    std::endian endianness
)
noexcept;

/**
    Description:
        Reverses the order of the bytes in the
        <#parameter>data</#parameter> array.

    Parameters:
        data:
            The array of bytes to reverse.
        byte_count:
            The number of bytes in the array.
*/
CMP_CONDITIONAL_INLINE
CMP_LIBRARY_NAME
void
invert_endianness (
    std::byte* data,
    std::size_t byte_count
)
noexcept;

} // namespace ----------------------------------------------------------------

#include <cmp/io/general.ipp>
#if CMP_CONFIG_HEADER_ONLY == true
#   include <cmp/io/general.cpp>
#endif // CMP_CONFIG_HEADER_ONLY

#endif // CMP_IO_GENERAL_HPP_INCLUDED
