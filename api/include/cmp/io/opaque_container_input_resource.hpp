// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_IO_OPAQUE_CONTAINER_INPUT_RESOURCE_HPP_INCLUDED
#define CMP_IO_OPAQUE_CONTAINER_INPUT_RESOURCE_HPP_INCLUDED

#include <string>

#include <cmp/io/inclusion_assert.hpp>
#include <cmp/core/type_traits.hpp>
#include <cmp/io/impl/ctr_essence.hpp>
#include <cmp/io/seekable_input_resource.hpp>

namespace cmp {

/**
    Description:
        An opaque container input resource is an input resource that
        reads from a container that it owns.
*/
template <
    typename Container
>
class opaque_container_input_resource
    : public virtual seekable_input_resource<std::int64_t>
    , public virtual impl::ctr_essence<Container>
{
public:
    // Types ------------------------------------------------------------------

    /**
        Description:
            The type of content referenced by <#this/>
            opaque container input resource.
    */
    using content_type = Container;

    /**
        Description:
            The type of element of the content referenced by
            <#this/> opaque container input resource.
    */
    using element_type = typename Container::value_type;

    // Constructors and Destructor --------------------------------------------

    /**
        Description:
            Constructs an opaque container input resource with
            the given buffer capacity and a default-constructed
            content object.

        Parameters:
            buffer_capacity:
                The capacity of the I/O buffer. If this is zero, the
                opaque container input resource is completely unbuffered.
    */
    explicit
    opaque_container_input_resource (
        std::size_t buffer_capacity = 0
    );

    /**
        Description:
            Constructs an opaque container input resource
            with the given initial content and buffer capacity.

        Parameters:
            initial_content:
                The content that <#this/> opaque
                container input resource will reference.
            buffer_capacity:
                The capacity of the I/O buffer. If this is zero, the
                opaque container input resource is completely unbuffered.
    */
    explicit
    opaque_container_input_resource (
        const content_type& initial_content,
        std::size_t buffer_capacity = 0
    );

    /**
        Description:
            Constructs an opaque container input resource
            with the given initial content and buffer capacity.

        Parameters:
            initial_content:
                The content that <#this/> opaque
                container input resource will reference.
            buffer_capacity:
                The capacity of the I/O buffer. If this is zero, the
                opaque container input resource is completely unbuffered.
    */
    explicit
    opaque_container_input_resource (
        content_type&& initial_content,
        std::size_t buffer_capacity = 0
    );

    ~opaque_container_input_resource ()
    override = default;

    // Copy Operations --------------------------------------------------------

    /**
        Description:
            Copy-constructs an <#type>opaque_container_input_resource</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>opaque_container_input_resource</#type>
                to copy from.
    */
    opaque_container_input_resource (
        const opaque_container_input_resource& other
    )
    = default;

    /**
        Description:
            Copy-assigns an <#type>opaque_container_input_resource</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>opaque_container_input_resource</#type>
                to copy from.
    */
    opaque_container_input_resource&
    operator = (
        const opaque_container_input_resource& other
    )
    = default;

    // Move Operations --------------------------------------------------------

    /**
        Description:
            Move-constructs an <#type>opaque_container_input_resource</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>opaque_container_input_resource</#type>
                to move from.
    */
    opaque_container_input_resource (
        opaque_container_input_resource&& other
    )
    noexcept = default;

    /**
        Description:
            Move-assigns an <#type>opaque_container_input_resource</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>opaque_container_input_resource</#type>
                to move from.
    */
    opaque_container_input_resource&
    operator = (
        opaque_container_input_resource&& other
    )
    noexcept = default;

    // Accessors --------------------------------------------------------------

    /**
        Description:
            Returns true if <#this/> opaque container input resource is
            at the end of its referenced content. Otherwise, returns false.
    */
    bool
    is_at_end ()
    const noexcept override;

    /**
        Description:
            Returns the position <#this/> opaque
            container input resource is at, that is,
            the position at which read operations will
            take place next.
    */
    std::int64_t
    get_position ()
    const noexcept override;

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
            <#this/> opaque container input resource and places
            them in the provided <#parameter>data</#parameter> array.

        Parameters:
            data:
                The array into which the read bytes will be placed.
            byte_count:
                The number of bytes to read from <#this/> input resource.
            rr:
                The kind of read request that is being
                issued to <#this/> input resource.
    */
    std::size_t
    read_raw (
        std::byte* data,
        std::size_t byte_count,
        read_request rr
    )
    override;

private:
    // Private Data -----------------------------------------------------------

    content_type m_content;
}; // class -------------------------------------------------------------------

using opaque_blob_input_resource
    = opaque_container_input_resource<std::vector<std::byte>>;

using opaque_string_input_resource
    = opaque_container_input_resource<std::string>;

using opaque_u8string_input_resource
    = opaque_container_input_resource<std::u8string>;

using opaque_u16string_input_resource
    = opaque_container_input_resource<std::u16string>;

using opaque_u32string_input_resource
    = opaque_container_input_resource<std::u32string>;

using opaque_wstring_input_resource
    = opaque_container_input_resource<std::wstring>;

} // namespace ----------------------------------------------------------------

#include <cmp/io/opaque_container_input_resource.ipp>

#endif // CMP_IO_OPAQUE_CONTAINER_INPUT_RESOURCE_HPP_INCLUDED
