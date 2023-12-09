// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_IO_TRANSFER_RESOURCE_HPP_INCLUDED
#define CMP_IO_TRANSFER_RESOURCE_HPP_INCLUDED

#include <cmp/io/inclusion_assert.hpp>
#include <cmp/io/io_buffer.hpp>

namespace cmp {

/**
    Description:
        This class is the base class for transfer resources. A transfer
        resource can be an input resource (a source of input), an output
        resource (a destination for output), or both.
*/
class CMP_LIBRARY_NAME transfer_resource {
public:
    // Constructors and Destructor --------------------------------------------

    /**
        Description:
            Constructs a transfer resource with the given buffer capacity.

        Parameters:
            buffer_capacity:
                The capacity of the I/O buffer. If this is zero,
                the transfer resource is completely unbuffered.
    */
    CMP_CONDITIONAL_INLINE
    explicit
    transfer_resource (
        std::size_t buffer_capacity = io_buffer::default_buffer_capacity
    );

    CMP_CONDITIONAL_INLINE
    virtual
    ~transfer_resource ()
    = default;

    // Copy Operations --------------------------------------------------------

    /**
        Description:
            Copy-constructs a <#type>transfer_resource</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>transfer_resource</#type>
                to copy from.
    */
    CMP_CONDITIONAL_INLINE
    transfer_resource (
        const transfer_resource& other
    )
    = default;

    /**
        Description:
            Copy-assigns a <#type>transfer_resource</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>transfer_resource</#type>
                to copy from.
    */
    CMP_CONDITIONAL_INLINE
    transfer_resource&
    operator = (
        const transfer_resource& other
    )
    = default;

    // Move Operations --------------------------------------------------------

    /**
        Description:
            Move-constructs a <#type>transfer_resource</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>transfer_resource</#type>
                to move from.
    */
    CMP_CONDITIONAL_INLINE
    transfer_resource (
        transfer_resource&& other
    )
    noexcept = default;

    /**
        Description:
            Move-assigns a <#type>transfer_resource</#type>
            into <#this/> one.

        Parameters:
            other:
                The <#type>transfer_resource</#type>
                to move from.
    */
    CMP_CONDITIONAL_INLINE
    transfer_resource&
    operator = (
        transfer_resource&& other
    )
    noexcept = default;

    // Accessors --------------------------------------------------------------

    /**
        Description:
            Tells whether this transfer resource is at its end.
    */
    CMP_CONDITIONAL_INLINE
    virtual
    bool
    is_at_end ()
    const noexcept = 0;

protected:
    // Protected Data ---------------------------------------------------------

    io_buffer m_buffer;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#if CMP_CONFIG_HEADER_ONLY == true
#   include <cmp/io/transfer_resource.cpp>
#endif // CMP_CONFIG_HEADER_ONLY

#endif // CMP_IO_TRANSFER_RESOURCE_HPP_INCLUDED
