// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_IO_STRING_IO_RESOURCE_HPP_INCLUDED
#define CMP_IO_STRING_IO_RESOURCE_HPP_INCLUDED

#include <string>

#include <cmp/io/inclusion_assert.hpp>
#include <cmp/core/type_traits.hpp>
#include <cmp/unicode/algorithms.hpp>
#include <cmp/io/seekable_io_resource.hpp>

namespace cmp {

template <
    writable_unicode_string T
>
class string_io_resource
    : public seekable_io_resource<std::int64_t>
{
public:
    // Types ------------------------------------------------------------------

    /**
        Description:
            The type of string contained in <#this/> string I/O resource.
    */
    using string_type = T;

    /**
        Description:
            The type of code unit of the string
            contained in <#this/> string I/O resource.
    */
    using code_unit_type = value_type_t<string_type>;

    // Constructors and Destructor --------------------------------------------

    /**
        Description:
            Constructs a string I/O resource with the given buffer capacity.

        Parameters:
            buffer_capacity:
                The capacity of the I/O buffer. If this is zero,
                the string I/O resource is completely unbuffered.
    */
    explicit
    string_io_resource (
        std::size_t buffer_capacity = io_buffer::default_buffer_capacity
    );

    /**
        Description:
            Constructs a string I/O resource with the
            given initial content and buffer capacity.

        Parameters:
            initial_content:
                The content that <#this/> string I/O resource will start with.
            buffer_capacity:
                The capacity of the I/O buffer. If this is zero,
                the string I/O resource is completely unbuffered.
    */
    explicit
    string_io_resource (
        string_type initial_content,
        std::size_t buffer_capacity = io_buffer::default_buffer_capacity
    );

    ~string_io_resource ()
    noexcept = default;

    // Accessors --------------------------------------------------------------

    /**
        Description:
            Returns true if <#this/> string I/O resource is at the end
            of its contained string. Otherwise, returns false.
    */
    bool
    is_at_end ()
    const noexcept override;

    /**
        Description:
            Returns a non-constant reference to the contained string.
    */
    T&
    grab_content ()
    noexcept;

    /**
        Description:
            Returns a constant reference to the contained string.
    */
    const T&
    grab_content ()
    const noexcept;

    // Core -------------------------------------------------------------------

    /**
        Description:
            Returns the position <#/this> string I/O resource is at, that
            is, the position at which read and write operations will take
            place next.
    */
    std::int64_t
    get_position ()
    const noexcept override;

protected:
    // Protected Functions ----------------------------------------------------

    void
    set_position_raw (
        std::int64_t new_position,
        position_reference pr
    )
    noexcept override;

    /**
        Description:
            Reads <#parameter>byte_count</#parameter> bytes from
            <#this/> string I/O resource and places them in the
            provided <#parameter>data</#parameter> array.

        Parameters:
            data:
                The array into which the read bytes will be placed.
            byte_count:
                The number of bytes to read from <#this/> input resource.
            rr:
                The kind of read request that is being
                issued to <#this/> string I/O resource.
    */
    std::size_t
    read_raw (
        std::byte* data,
        std::size_t byte_count,
        read_request rr
    )
    override;

    /**
        Description:
            Writes <#parameter>byte_count</#parameter> bytes
            from the <#parameter>data</#parameter> array to
            <#this/> string I/O resource.

        Parameters:
            data:
                The array of bytes that will be written
                to <#this/> string I/O resource.
            byte_count:
                The number of bytes to write to <#this/> string I/O resource.
    */
    std::size_t
    write_raw (
        const std::byte* data,
        std::size_t byte_count
    )
    override;

private:
    // Private Data -----------------------------------------------------------

    T m_content;
    std::int64_t m_position;
    std::size_t m_last_fill_amount;
}; // class -------------------------------------------------------------------

using u8string_io_resource = string_io_resource<std::u8string>;
using u16string_io_resource = string_io_resource<std::u16string>;
using u32string_io_resource = string_io_resource<std::u32string>;

} // namespace ----------------------------------------------------------------

#include <cmp/io/string_io_resource.ipp>

#endif // CMP_IO_STRING_IO_RESOURCE_HPP_INCLUDED
