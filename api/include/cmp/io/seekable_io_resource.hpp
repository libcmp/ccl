// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_IO_SEEKABLE_IO_RESOURCE_HPP_INCLUDED
#define CMP_IO_SEEKABLE_IO_RESOURCE_HPP_INCLUDED

#include <cstdint>

#include <cmp/io/inclusion_assert.hpp>
#include <cmp/io/seekable_input_resource.hpp>
#include <cmp/io/seekable_output_resource.hpp>

namespace cmp {

/**
    Description:
        A seekable I/O resource is an I/O resource that can seek,
        that is, change where read and write operations will take place next.
*/
template <
    typename Position
>
class seekable_io_resource
    : public virtual seekable_input_resource<Position>
    , public virtual seekable_output_resource<Position>
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
            Constructs a seekable I/O resource with the given buffer capacity.

        Parameters:
            buffer_capacity:
                The capacity of the I/O buffer. If this is zero,
                the seekable I/O resource is completely unbuffered.
    */
    explicit
    seekable_io_resource (
        std::size_t buffer_capacity = io_buffer::default_buffer_capacity
    );

    ~seekable_io_resource ()
    override = default;

    // Copy Operations --------------------------------------------------------

    /**
        Description:
            Copy-constructs a <#type>seekable_io_resource</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>seekable_io_resource</#type>
                to copy from.
    */
    seekable_io_resource (
        const seekable_io_resource& other
    )
    = default;

    /**
        Description:
            Copy-assigns a <#type>seekable_io_resource</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>seekable_io_resource</#type>
                to copy from.
    */
    seekable_io_resource&
    operator = (
        const seekable_io_resource& other
    )
    = default;

    // Move Operations --------------------------------------------------------

    /**
        Description:
            Move-constructs a <#type>seekable_io_resource</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>seekable_io_resource</#type>
                to move from.
    */
    seekable_io_resource (
        seekable_io_resource&& other
    )
    noexcept = default;

    /**
        Description:
            Move-assigns a <#type>seekable_io_resource</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>seekable_io_resource</#type>
                to move from.
    */
    seekable_io_resource&
    operator = (
        seekable_io_resource&& other
    )
    noexcept = default;

    // Accessors --------------------------------------------------------------

    /**
        Description:
            Sets the position of <#this/> seekable I/O resource.

        Parameters:
            new_position:
                The new position of <#this/> seekable I/o resource.
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

#include <cmp/io/seekable_io_resource.ipp>

#endif // CMP_IO_SEEKABLE_IO_RESOURCE_HPP_INCLUDED
