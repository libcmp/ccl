// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_IO_TRANSPARENT_CONTAINER_IO_RESOURCE_HPP_INCLUDED
#define CMP_IO_TRANSPARENT_CONTAINER_IO_RESOURCE_HPP_INCLUDED

#include <string>

#include <cmp/io/inclusion_assert.hpp>
#include <cmp/core/type_traits.hpp>
#include <cmp/io/impl/ctr_essence.hpp>
#include <cmp/io/seekable_io_resource.hpp>

namespace cmp {

template <
    typename Container
>
class transparent_container_io_resource
    : public seekable_io_resource<std::int64_t>
    , public impl::ctr_essence<Container>
{
public:
    // Types ------------------------------------------------------------------

    /**
        Description:
            The type of content referenced by <#this/>
            transparent container I/O resource.
    */
    using content_type = Container;

    /**
        Description:
            The type of element of the content referenced by
            <#this/> transparent container I/O resource.
    */
    using element_type = Container::value_type;

    // Constructors and Destructor --------------------------------------------

    /**
        Description:
            Constructs a transparent container I/O resource
            with the given initial content and buffer capacity.

        Parameters:
            initial_content:
                The content that <#this/> transparent
                container I/O resource will reference.
            buffer_capacity:
                The capacity of the I/O buffer. If this is zero, the
                transparent container I/O resource is completely unbuffered.
    */
    explicit
    transparent_container_io_resource (
        content_type& initial_content,
        std::size_t buffer_capacity = 0
    );

    ~transparent_container_io_resource ()
    noexcept = default;

    // Accessors --------------------------------------------------------------

    /**
        Description:
            Returns true if <#this/> transparent container I/O resource is
            at the end of its referenced content. Otherwise, returns false.
    */
    bool
    is_at_end ()
    const noexcept override;

    /**
        Description:
            Returns the position <#this/> transparent
            container I/O resource is at, that is,
            the position at which read operations will
            take place next.
    */
    std::int64_t
    get_position ()
    const noexcept override;

    /**
        Description:
            Returns a non-constant reference to the referenced content.
    */
    content_type&
    grab_content ()
    noexcept;

    /**
        Description:
            Returns a constant reference to the referenced content.
    */
    const content_type&
    grab_content ()
    const noexcept;

protected:
    // Protected Types --------------------------------------------------------

    using essence_type
        = impl::ctr_essence<Container>;

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
            <#this/> transparent container I/O resource and places
            them in the provided <#parameter>data</#parameter> array.

        Parameters:
            data:
                The array into which the read bytes will be placed.
            byte_count:
                The number of bytes to read from <#this/> I/O resource.
            rr:
                The kind of read request that is being
                issued to <#this/> I/O resource.
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
            <#this/> transparent container output resource.

        Parameters:
            data:
                The array of bytes that will be
                written to <#this/> output resource.
            byte_count:
                The number of bytes to write
                to <#this/> output resource.
    */
    std::size_t
    write_raw (
        const std::byte* data,
        std::size_t byte_count
    )
    override;
}; // class -------------------------------------------------------------------

using transparent_blob_io_resource
    = transparent_container_io_resource<std::vector<std::byte>>;

using transparent_string_io_resource
    = transparent_container_io_resource<std::string>;

using transparent_u8string_io_resource
    = transparent_container_io_resource<std::u8string>;

using transparent_u16string_io_resource
    = transparent_container_io_resource<std::u16string>;

using transparent_u32string_io_resource
    = transparent_container_io_resource<std::u32string>;

using transparent_wstring_io_resource
    = transparent_container_io_resource<std::wstring>;

} // namespace ----------------------------------------------------------------

#include <cmp/io/transparent_container_io_resource.ipp>

#endif // CMP_IO_TRANSPARENT_CONTAINER_IO_RESOURCE_HPP_INCLUDED
