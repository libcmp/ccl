// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_IO_UNIX_LIKE_UIN_HPP_INCLUDED
#define CMP_IO_UNIX_LIKE_UIN_HPP_INCLUDED

#include <unistd.h>

#include <cmp/io/inclusion_assert.hpp>
#include <cmp/core/platform.hpp>
#include <cmp/io/input_resource.hpp>
#include <cmp/io/text_input_stream.hpp>
#include <cmp/io/impl/unix_like/unix_like_uout.hpp>

namespace cmp {

class CMP_LIBRARY_NAME stdin_resource
    : public input_resource
{
public:
    // Constructors and Destructor --------------------------------------------

    stdin_resource (
        std::size_t buffer_capacity = io_buffer::default_buffer_capacity
    )
    noexcept;

    ~stdin_resource ()
    noexcept = default;

    // Accessors --------------------------------------------------------------

    bool
    is_at_end ()
    const noexcept override;

    // Core -------------------------------------------------------------------

    std::size_t
    read_raw (
        std::byte* data,
        std::size_t byte_count,
        read_request rr
    )
    override;
}
    inline uin_resource{CMP_CONFIG_DEFAULT_STDIN_BUFFER_CAPACITY}
; // class --------------------------------------------------------------------

class CMP_LIBRARY_NAME stdin_stream final
    : public text_input_stream<stdin_resource>
{
public:
    // Types ------------------------------------------------------------------

    using wrapped_resource_type = stdin_resource;

    // Constructors and Destructor --------------------------------------------

    explicit
    stdin_stream (
        wrapped_resource_type& resource
    )
    noexcept;

    ~stdin_stream ()
    noexcept = default;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#if CMP_CONFIG_HEADER_ONLY == true
#   include <cmp/io/impl/unix_like/unix_like_uin.cpp>
#endif // CMP_CONFIG_HEADER_ONLY

#endif // CMP_IO_UNIX_LIKE_UIN_HPP_INCLUDED
