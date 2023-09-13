// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_IO_TRANSFER_RESOURCE_HPP_INCLUDED
#define CMP_IO_TRANSFER_RESOURCE_HPP_INCLUDED

#include <cmp/io/inclusion_assert.hpp>
#include <cmp/io/io_buffer.hpp>

namespace cmp {

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
