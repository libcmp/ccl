// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_IO_OPAQUE_CONTAINER_OUTPUT_RESOURCE_HPP_INCLUDED
#define CMP_IO_OPAQUE_CONTAINER_OUTPUT_RESOURCE_HPP_INCLUDED

#include <string>

#include <cmp/io/inclusion_assert.hpp>
#include <cmp/core/type_traits.hpp>
#include <cmp/io/impl/ctr_essence.hpp>
#include <cmp/io/seekable_output_resource.hpp>

namespace cmp {

template <
    typename Container
>
class opaque_container_output_resource
    : public seekable_output_resource<std::int64_t>
    , public impl::ctr_essence<Container>
{
public:
    // Types ------------------------------------------------------------------

    /**
        Description:
            The type of content referenced by <#this/>
            opaque container output resource.
    */
    using content_type = Container;

    /**
        Description:
            The type of element of the content referenced by
            <#this/> opaque container output resource.
    */
    using element_type = Container::value_type;

    // Constructors and Destructor --------------------------------------------

    /**
        Description:
            Constructs an opaque container output resource with
            the given buffer capacity and a default-constructed
            content object.

        Parameters:
            buffer_capacity:
                The capacity of the I/O buffer. If this is zero, the
                opaque container output resource is completely unbuffered.
    */
    explicit
    opaque_container_output_resource (
        std::size_t buffer_capacity = 0
    );

    /**
        Description:
            Constructs an opaque container output resource
            with the given initial content and buffer capacity.

        Parameters:
            initial_content:
                The content that <#this/> opaque
                container output resource will reference.
            buffer_capacity:
                The capacity of the I/O buffer. If this is zero, the
                opaque container output resource is completely unbuffered.
    */
    explicit
    opaque_container_output_resource (
        const content_type& initial_content,
        std::size_t buffer_capacity = 0
    );

    /**
        Description:
            Constructs an opaque container output resource
            with the given initial content and buffer capacity.

        Parameters:
            initial_content:
                The content that <#this/> opaque
                container output resource will reference.
            buffer_capacity:
                The capacity of the I/O buffer. If this is zero, the
                opaque container output resource is completely unbuffered.
    */
    explicit
    opaque_container_output_resource (
        content_type&& initial_content,
        std::size_t buffer_capacity = 0
    );

    ~opaque_container_output_resource ()
    noexcept = default;

    // Accessors --------------------------------------------------------------

    /**
        Description:
            Returns true if <#this/> opaque container output resource is
            at the end of its referenced content. Otherwise, returns false.
    */
    bool
    is_at_end ()
    const noexcept override;

    /**
        Description:
            Returns the position <#this/> opaque
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
            <#this/> opaque container output resource.

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

private:
    // Private Data -----------------------------------------------------------

    content_type m_content;
}; // class -------------------------------------------------------------------

using opaque_blob_output_resource
    = opaque_container_output_resource<std::vector<std::byte>>;

using opaque_string_output_resource
    = opaque_container_output_resource<std::string>;

using opaque_u8string_output_resource
    = opaque_container_output_resource<std::u8string>;

using opaque_u16string_output_resource
    = opaque_container_output_resource<std::u16string>;

using opaque_u32string_output_resource
    = opaque_container_output_resource<std::u32string>;

using opaque_wstring_output_resource
    = opaque_container_output_resource<std::wstring>;

} // namespace ----------------------------------------------------------------

#include <cmp/io/opaque_container_output_resource.ipp>

#endif // CMP_IO_OPAQUE_CONTAINER_OUTPUT_RESOURCE_HPP_INCLUDED
