// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/io/impl/windows/windows_uin.hpp>

namespace cmp {

// ------------------------------------------------------- cmp::stdin_resource

// Constructors and Destructor ------------------------------------------------

stdin_resource::stdin_resource (
    std::size_t buffer_capacity
)
noexcept
    : transfer_resource{buffer_capacity}
    , input_resource{buffer_capacity}
    , m_handle{GetStdHandle(STD_INPUT_HANDLE)}
{
    tie(uout_resource);
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

bool
stdin_resource::is_at_end ()
const noexcept
{
    return false;
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

std::size_t
stdin_resource::read_raw (
    std::byte* data,
    std::size_t byte_count,
    read_request rr
) {
    DWORD chars_read;
    ReadConsoleW(
        m_handle,
        static_cast<LPVOID>(data),
        static_cast<DWORD>(byte_count / sizeof (WCHAR)),
        &chars_read,
        nullptr
    );
    return chars_read * sizeof (WCHAR);
} // function -----------------------------------------------------------------

// --------------------------------------------------------- cmp::stdin_stream

// Constructors and Destructor ------------------------------------------------

stdin_stream::stdin_stream (
    referenced_resource_type& resource
)
noexcept
    : text_input_stream<stdin_resource>{resource, utf16, std::endian::native}
{
} // function -----------------------------------------------------------------

#if CMP_CONFIG_HEADER_ONLY == false

stdin_resource uin_resource{CMP_CONFIG_DEFAULT_STDIN_BUFFER_CAPACITY};

#endif

} // namespace ----------------------------------------------------------------
