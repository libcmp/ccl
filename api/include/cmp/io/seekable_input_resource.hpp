// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_IO_SEEKABLE_INPUT_RESOURCE_HPP_INCLUDED
#define CMP_IO_SEEKABLE_INPUT_RESOURCE_HPP_INCLUDED

#include <cstdint>

#include <cmp/io/inclusion_assert.hpp>
#include <cmp/io/input_resource.hpp>
#include <cmp/io/seekable_transfer_resource.hpp>

namespace cmp {

/**
    Description:
        A seekable input resource is an input resource that can seek,
        that is, change where read operations will take place next.
*/
template <
    typename Position
>
class seekable_input_resource
    : public virtual seekable_transfer_resource<Position>
    , public input_resource
{
public:
    // Types ------------------------------------------------------------------

    /**
        Description:
            The type of this resource's position.
    */
    using position_type = Position;

    // Constructors and Destructor --------------------------------------------

    /**
        Description:
            Constructs a seekable input resource
            with the given buffer capacity.

        Parameters:
            buffer_capacity:
                The capacity of the I/O buffer. If this is zero, the
                seekable input resource is completely unbuffered.
    */
    explicit
    seekable_input_resource (
        std::size_t buffer_capacity = io_buffer::default_buffer_capacity
    );

    ~seekable_input_resource ()
    override = default;

    // Copy Operations --------------------------------------------------------

    /**
        Description:
            Copy-constructs a <#type>seekable_input_resource</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>seekable_input_resource</#type>
                to copy from.
    */
    seekable_input_resource (
        const seekable_input_resource& other
    )
    = default;

    /**
        Description:
            Copy-assigns a <#type>seekable_input_resource</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>seekable_input_resource</#type>
                to copy from.
    */
    seekable_input_resource&
    operator = (
        const seekable_input_resource& other
    )
    = default;

    // Move Operations --------------------------------------------------------

    /**
        Description:
            Move-constructs a <#type>seekable_input_resource</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>seekable_input_resource</#type>
                to move from.
    */
    seekable_input_resource (
        seekable_input_resource&& other
    )
    noexcept = default;

    /**
        Description:
            Move-assigns a <#type>seekable_input_resource</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>seekable_input_resource</#type>
                to move from.
    */
    seekable_input_resource&
    operator = (
        seekable_input_resource&& other
    )
    noexcept = default;

    // Accessors --------------------------------------------------------------

    /**
        Description:
            Sets the position of <#this/> seekable input resource.

        Parameters:
            new_position:
                The new position of <#this/> seekable input resource.
            pr:
                The reference that the new position is relative to.
    */
    void
    set_position (
        position_type new_position,
        position_reference pr
    )
    noexcept override;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#include <cmp/io/seekable_input_resource.ipp>

#endif // CMP_IO_SEEKABLE_INPUT_RESOURCE_HPP_INCLUDED
