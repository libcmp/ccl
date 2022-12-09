// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/io/impl/windows/windows_uout.hpp>

namespace cmp {

// ------------------------------------------------------ cmp::stdout_resource

// Constructors and Destructor ------------------------------------------------

stdout_resource::stdout_resource (
    DWORD handle_identifier,
    std::size_t buffer_capacity
)
noexcept
    : transfer_resource{buffer_capacity}
    , output_resource{buffer_capacity}
    , m_handle{GetStdHandle(handle_identifier)}
{
    SetConsoleOutputCP(CP_UTF8);
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

bool
stdout_resource::is_at_end ()
const noexcept
{
    return false;
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

std::size_t
stdout_resource::write_raw (
    const std::byte* data,
    std::size_t byte_count
) {
    // /*
    DWORD bytes_written{0};
    WriteFile(
        m_handle,
        static_cast<LPCVOID>(data),
        static_cast<DWORD>(byte_count),
        &bytes_written,
        nullptr
    );
    return bytes_written;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
