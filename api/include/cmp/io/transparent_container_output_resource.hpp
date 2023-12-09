// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_IO_TRANSPARENT_CONTAINER_OUTPUT_RESOURCE_HPP_INCLUDED
#define CMP_IO_TRANSPARENT_CONTAINER_OUTPUT_RESOURCE_HPP_INCLUDED

#include <string>

#include <cmp/io/inclusion_assert.hpp>
#include <cmp/core/type_traits.hpp>
#include <cmp/io/impl/ctr_essence.hpp>
#include <cmp/io/seekable_output_resource.hpp>

namespace cmp {

/**
    Description:
        A transparent container output resource is an output resource that
        writes to a container that it does not own.
*/
template <
    typename Container
>
class transparent_container_output_resource
    : public seekable_output_resource<std::int64_t>
    , public impl::ctr_essence<Container>
{
public:
    // Types ------------------------------------------------------------------

    /**
        Description:
            The type of content referenced by <#this/>
            transparent container output resource.
    */
    using content_type = Container;

    /**
        Description:
            The type of element of the content referenced by
            <#this/> transparent container output resource.
    */
    using element_type = Container::value_type;

    // Constructors and Destructor --------------------------------------------

    /**
        Description:
            Constructs a transparent container output resource
            with the given initial content and buffer capacity.

        Parameters:
            initial_content:
                The content that <#this/> transparent
                container output resource will reference.
            buffer_capacity:
                The capacity of the I/O buffer. If this is zero, the
                transparent container output resource is completely unbuffered.
    */
    explicit
    transparent_container_output_resource (
        content_type& initial_content,
        std::size_t buffer_capacity = 0
    );

    ~transparent_container_output_resource ()
    override = default;

    // Copy Operations --------------------------------------------------------

    /**
        Description:
            Copy-constructs a
            <#type>transparent_container_output_resource</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>transparent_container_output_resource</#type>
                to copy from.
    */
    transparent_container_output_resource (
        const transparent_container_output_resource& other
    )
    = default;

    /**
        Description:
            Copy-assigns a <#type>transparent_container_output_resource</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>transparent_container_output_resource</#type>
                to copy from.
    */
    transparent_container_output_resource&
    operator = (
        const transparent_container_output_resource& other
    )
    = default;

    // Move Operations --------------------------------------------------------

    /**
        Description:
            Move-constructs a
            <#type>transparent_container_output_resource</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>transparent_container_output_resource</#type>
                to move from.
    */
    transparent_container_output_resource (
        transparent_container_output_resource&& other
    )
    noexcept = default;

    /**
        Description:
            Move-assigns a <#type>transparent_container_output_resource</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>transparent_container_output_resource</#type>
                to move from.
    */
    transparent_container_output_resource&
    operator = (
        transparent_container_output_resource&& other
    )
    noexcept = default;

    // Accessors --------------------------------------------------------------

    /**
        Description:
            Returns true if <#this/> transparent container output resource is
            at the end of its referenced content. Otherwise, returns false.
    */
    bool
    is_at_end ()
    const noexcept override;

    /**
        Description:
            Returns the position <#this/> transparent
            container output resource is at, that is,
            the position at which write operations will
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

using transparent_blob_output_resource
    = transparent_container_output_resource<std::vector<std::byte>>;

using transparent_string_output_resource
    = transparent_container_output_resource<std::string>;

using transparent_u8string_output_resource
    = transparent_container_output_resource<std::u8string>;

using transparent_u16string_output_resource
    = transparent_container_output_resource<std::u16string>;

using transparent_u32string_output_resource
    = transparent_container_output_resource<std::u32string>;

using transparent_wstring_output_resource
    = transparent_container_output_resource<std::wstring>;

} // namespace ----------------------------------------------------------------

#include <cmp/io/transparent_container_output_resource.ipp>

#endif // CMP_IO_TRANSPARENT_CONTAINER_OUTPUT_RESOURCE_HPP_INCLUDED
