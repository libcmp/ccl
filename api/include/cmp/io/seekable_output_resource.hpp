// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_IO_SEEKABLE_OUTPUT_RESOURCE_HPP_INCLUDED
#define CMP_IO_SEEKABLE_OUTPUT_RESOURCE_HPP_INCLUDED

#include <cstdint>

#include <cmp/io/inclusion_assert.hpp>
#include <cmp/io/output_resource.hpp>
#include <cmp/io/seekable_transfer_resource.hpp>

namespace cmp {

template <
    typename Position
>
class seekable_output_resource
    : public output_resource
    , public seekable_transfer_resource<Position>
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
            Constructs a seekable output resource
            with the given buffer capacity.

        Parameters:
            buffer_capacity:
                The capacity of the I/O buffer. If this is zero, the
                seekable output resource is completely unbuffered.
    */
    explicit
    seekable_output_resource (
        std::size_t buffer_capacity = io_buffer::default_buffer_capacity
    );

    virtual
    ~seekable_output_resource ()
    noexcept = default;

    // Accessors --------------------------------------------------------------

    /**
        Description:
            Sets the position of <#this/> seekable output resource.

        Parameters:
            new_position:
                The new position of <#this/> seekable output resource.
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

#include <cmp/io/seekable_output_resource.ipp>

#endif // CMP_IO_SEEKABLE_OUTPUT_RESOURCE_HPP_INCLUDED
