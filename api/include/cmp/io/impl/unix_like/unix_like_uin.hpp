// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_IO_UNIX_LIKE_UIN_HPP_INCLUDED
#define CMP_IO_UNIX_LIKE_UIN_HPP_INCLUDED

#include <unistd.h>

#include <cmp/io/inclusion_assert.hpp>
#include <cmp/core/platform.hpp>
#include <cmp/io/impl/unix_like/unix_like_uout.hpp>
#include <cmp/io/input_resource.hpp>
#include <cmp/io/text_input_stream.hpp>

namespace cmp {

class CMP_LIBRARY_NAME stdin_resource
    : public input_resource
{
public:
    // Constructors and Destructor --------------------------------------------

    CMP_CONDITIONAL_INLINE
    stdin_resource (
        std::size_t buffer_capacity = io_buffer::default_buffer_capacity
    )
    noexcept;

    CMP_CONDITIONAL_INLINE
    ~stdin_resource ()
    override = default;

    // Accessors --------------------------------------------------------------

    CMP_CONDITIONAL_INLINE
    bool
    is_at_end ()
    const noexcept override;

    // Core -------------------------------------------------------------------

    CMP_CONDITIONAL_INLINE
    std::size_t
    read_raw (
        std::byte* data,
        std::size_t byte_count,
        read_request rr
    )
    override;
}; // class -------------------------------------------------------------------

class CMP_LIBRARY_NAME stdin_stream final
    : public text_input_stream<stdin_resource>
{
public:
    // Types ------------------------------------------------------------------

    using referenced_resource_type = stdin_resource;

    // Constructors and Destructor --------------------------------------------

    CMP_CONDITIONAL_INLINE
    explicit
    stdin_stream (
        referenced_resource_type& resource
    )
    noexcept;

    CMP_CONDITIONAL_INLINE
    ~stdin_stream ()
    override = default;
}; // class -------------------------------------------------------------------

#if CMP_CONFIG_HEADER_ONLY == true

inline stdin_resource uin_resource{CMP_CONFIG_DEFAULT_STDIN_BUFFER_CAPACITY};

#else

extern CMP_LIBRARY_NAME stdin_resource uin_resource;

#endif

} // namespace ----------------------------------------------------------------

#if CMP_CONFIG_HEADER_ONLY == true
#   include <cmp/io/impl/unix_like/unix_like_uin.cpp>
#endif // CMP_CONFIG_HEADER_ONLY

#endif // CMP_IO_UNIX_LIKE_UIN_HPP_INCLUDED
