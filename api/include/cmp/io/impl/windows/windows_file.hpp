// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_IO_WINDOWS_FILE_HPP_INCLUDED
#define CMP_IO_WINDOWS_FILE_HPP_INCLUDED

#include <Windows.h>

#include <cmp/io/inclusion_assert.hpp>
#include <cmp/io/file.hpp>

namespace cmp {

class CMP_LIBRARY_NAME file final
    : public basic_file
{
public:
    // Constructors and Destructor --------------------------------------------

    file ()
    noexcept;

    file (
        const std::filesystem::path& file_path,
        access_mode mode,
        if_not_there if_file_not_there,
        std::size_t buffer_capacity = io_buffer::default_buffer_capacity
    );

    ~file ()
    noexcept;

    // Accessors --------------------------------------------------------------

    bool
    is_open ()
    const noexcept override;

    std::int64_t
    get_position ()
    const noexcept override;

    // Core -------------------------------------------------------------------

    bool
    open (
        const std::filesystem::path& file_path,
        access_mode mode,
        if_not_there if_file_not_there
    )
    noexcept override;

    void
    close ()
    noexcept override;

protected:
    // Protected Function -----------------------------------------------------

    void
    set_position_raw (
        std::int64_t new_position,
        position_reference pr
    )
    noexcept override;

    std::size_t
    read_raw (
        std::byte* data,
        std::size_t byte_count,
        read_request rr
    )
    noexcept override;

    std::size_t
    write_raw (
        const std::byte* data,
        std::size_t byte_count
    )
    noexcept override;

private:
    // Private Data -----------------------------------------------------------

    HANDLE m_handle;

    // Private Functions ------------------------------------------------------

    DWORD
    read_block (
        std::byte* data,
        DWORD byte_count
    )
    noexcept;

    DWORD
    write_block (
        const std::byte* data,
        DWORD byte_count
    )
    noexcept;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#if CMP_CONFIG_HEADER_ONLY == true
#   include <cmp/io/impl/windows/windows_file.cpp>
#endif // CMP_CONFIG_HEADER_ONLY

#endif // CMP_IO_WINDOWS_FILE_HPP_INCLUDED
