// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_IO_SEEKABLE_TRANSFER_RESOURCE_HPP_INCLUDED
#define CMP_IO_SEEKABLE_TRANSFER_RESOURCE_HPP_INCLUDED

#include <cstdint>

#include <cmp/io/inclusion_assert.hpp>
#include <cmp/io/general.hpp>
#include <cmp/io/transfer_resource.hpp>

namespace cmp {

/**
    Description:
        A seekable transfer resource is a transfer resource that can seek,
        that is, change where read or write operations will take place next.
*/
template <
    typename Position
>
class seekable_transfer_resource
    : public virtual transfer_resource
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
            Constructs a seekable transfer resource
            with the given buffer capacity.

        Parameters:
            buffer_capacity:
                The capacity of the I/O buffer. If this is zero, the
                seekable transfer resource is completely unbuffered.
    */
    explicit
    seekable_transfer_resource (
        std::size_t buffer_capacity = io_buffer::default_buffer_capacity
    );

    ~seekable_transfer_resource ()
    override = default;

    // Copy Operations --------------------------------------------------------

    /**
        Description:
            Copy-constructs a <#type>seekable_transfer_resource</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>seekable_transfer_resource</#type>
                to copy from.
    */
    seekable_transfer_resource (
        const seekable_transfer_resource& other
    )
    = default;

    /**
        Description:
            Copy-assigns a <#type>seekable_transfer_resource</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>seekable_transfer_resource</#type>
                to copy from.
    */
    seekable_transfer_resource&
    operator = (
        const seekable_transfer_resource& other
    )
    = default;

    // Move Operations --------------------------------------------------------

    /**
        Description:
            Move-constructs a <#type>seekable_transfer_resource</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>seekable_transfer_resource</#type>
                to move from.
    */
    seekable_transfer_resource (
        seekable_transfer_resource&& other
    )
    noexcept = default;

    /**
        Description:
            Move-assigns a <#type>seekable_transfer_resource</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>seekable_transfer_resource</#type>
                to move from.
    */
    seekable_transfer_resource&
    operator = (
        seekable_transfer_resource&& other
    )
    noexcept = default;

    // Accessors --------------------------------------------------------------

    /**
        Description:
            This function must be overridden, and it is supposed to return
            the position that this seekable transfer resource is at.
    */
    virtual
    position_type
    get_position ()
    const noexcept = 0;

    /**
        Description:
            This function is overridden in
            <#type>seekable_input_resource</#type> and
            <#type>seekable_output_resource</#type>, it
            sets the position of this seekable transfer
            resource to <#parameter>new_position</#parameter>,
            relative to <#parameter>pr</#parameter>.

        Parameters:
            new_position:
                The new position of <#this/> seekable transfer resource.
            pr:
                The reference that the new position is relative to.
    */
    virtual
    void
    set_position (
        position_type new_position,
        position_reference pr
    )
    noexcept = 0;

    // Core -------------------------------------------------------------------

    /**
        Description:
            Sets the position of this seekable transfer resource to be
            -<#parameter>count</#parameter>, relative to the seekable
            transfer resource's current position.

        Parameters:
            count:
                The amount by which to go back in
                the seekable transfer resource.
    */
    void
    go_back (
        position_type count
    )
    noexcept;

    /**
        Description:
            Sets the position of this seekable transfer resource to be
            <#parameter>count</#parameter>, relative to the seekable
            transfer resource's current position.

        Parameters:
            count:
                The amount by which to go forward
                in the seekable transfer resource.
    */
    void
    go_forward (
        position_type count
    )
    noexcept;

protected:
    // Protected Functions ----------------------------------------------------

    /**
        Description:
            This function must be overridden, and it is supposed
            to set the position of this seekable transfer resource
            to <#parameter>new_position</#parameter>, relative to
            <#parameter>pr</#parameter>.

        Parameters:
            new_position:
                The new position of <#this/> seekable transfer resource.
            pr:
                The reference that the new position is relative to.
    */
    virtual
    void
    set_position_raw (
        position_type new_position,
        position_reference pr
    )
    noexcept = 0;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#include <cmp/io/seekable_transfer_resource.ipp>

#endif // CMP_IO_SEEKABLE_TRANSFER_RESOURCE_HPP_INCLUDED
