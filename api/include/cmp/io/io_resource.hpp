// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_IO_IO_RESOURCE_HPP_INCLUDED
#define CMP_IO_IO_RESOURCE_HPP_INCLUDED

#include <cmp/io/inclusion_assert.hpp>
#include <cmp/io/input_resource.hpp>
#include <cmp/io/output_resource.hpp>

namespace cmp {

class CMP_LIBRARY_NAME io_resource
    : public input_resource
    , public output_resource
{
public:
    // Constructors and Destructor --------------------------------------------

    /**
        Description:
            Constructs an I/O resource with the given buffer capacity.

        Parameters:
            buffer_capacity:
                The capacity of the I/O buffer. If this is zero,
                the I/O resource is completely unbuffered.
    */
    explicit
    io_resource (
        std::size_t buffer_capacity
    );

    virtual
    ~io_resource ()
    noexcept = default;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#if CMP_CONFIG_HEADER_ONLY == true
#   include <cmp/io/io_resource.cpp>
#endif // CMP_CONFIG_HEADER_ONLY

#endif // CMP_IO_IO_RESOURCE_HPP_INCLUDED
