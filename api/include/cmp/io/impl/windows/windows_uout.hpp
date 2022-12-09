// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_IO_WINDOWS_UOUT_HPP_INCLUDED
#define CMP_IO_WINDOWS_UOUT_HPP_INCLUDED

#include <Windows.h>

#include <cmp/core/platform.hpp>
#include <cmp/io/inclusion_assert.hpp>
#include <cmp/io/output_resource.hpp>

namespace cmp {

class CMP_LIBRARY_NAME stdout_resource
    : public output_resource
{
public:
    // Constructors and Destructor --------------------------------------------

    explicit
    stdout_resource (
        DWORD handle_identifier,
        std::size_t buffer_capacity = io_buffer::default_buffer_capacity
    )
    noexcept;

    ~stdout_resource ()
    noexcept = default;

    // Accessors --------------------------------------------------------------

    bool
    is_at_end ()
    const noexcept override;

    // Core -------------------------------------------------------------------

    std::size_t
    write_raw (
        const std::byte* data,
        std::size_t byte_count
    )
    override;

private:
    // Private Data -----------------------------------------------------------

    HANDLE m_handle;
}
    inline uout_resource{
        STD_OUTPUT_HANDLE,
        CMP_CONFIG_DEFAULT_STDOUT_BUFFER_CAPACITY
    },
    uerr_resource{
        STD_ERROR_HANDLE,
        CMP_CONFIG_DEFAULT_STDERR_BUFFER_CAPACITY
    }
; // class --------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#if CMP_CONFIG_HEADER_ONLY == true
#   include <cmp/io/impl/windows/windows_uout.cpp>
#endif // CMP_CONFIG_HEADER_ONLY

#endif // CMP_IO_WINDOWS_UOUT_HPP_INCLUDED
