// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_IO_UNIX_LIKE_UOUT_HPP_INCLUDED
#define CMP_IO_UNIX_LIKE_UOUT_HPP_INCLUDED

#include <unistd.h>

#include <cmp/io/inclusion_assert.hpp>
#include <cmp/core/platform.hpp>
#include <cmp/io/output_resource.hpp>

namespace cmp {

class CMP_LIBRARY_NAME stdout_resource
    : public output_resource
{
public:
    // Constructors and Destructor --------------------------------------------

    CMP_CONDITIONAL_INLINE
    explicit
    stdout_resource (
        int file_descriptor,
        std::size_t buffer_capacity = io_buffer::default_buffer_capacity
    )
    noexcept;

    CMP_CONDITIONAL_INLINE
    ~stdout_resource ()
    noexcept = default;

    // Accessors --------------------------------------------------------------

    CMP_CONDITIONAL_INLINE
    bool
    is_at_end ()
    const noexcept override;

    // Core -------------------------------------------------------------------

    CMP_CONDITIONAL_INLINE
    std::size_t
    write_raw (
        const std::byte* data,
        std::size_t byte_count
    )
    override;

private:
    // Private Data -----------------------------------------------------------

    int m_file_descriptor;
}
    inline uout_resource{
        STDOUT_FILENO,
        CMP_CONFIG_DEFAULT_STDOUT_BUFFER_CAPACITY
    },
    uerr_resource{
        STDERR_FILENO,
        CMP_CONFIG_DEFAULT_STDERR_BUFFER_CAPACITY
    }
; // class --------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#if CMP_CONFIG_HEADER_ONLY == true
#   include <cmp/io/impl/unix_like/unix_like_uout.cpp>
#endif // CMP_CONFIG_HEADER_ONLY

#endif // CMP_IO_UNIX_LIKE_UOUT_HPP_INCLUDED
