// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/io/impl/windows/windows_file.hpp>

namespace cmp {

// ----------------------------------------------------------------- cmp::file

// Constructors and Destructor ------------------------------------------------

file::file ()
noexcept
    : transfer_resource{io_buffer::default_buffer_capacity}
    , basic_file{}
    , m_handle{INVALID_HANDLE_VALUE}
{
} // function -----------------------------------------------------------------

file::file (
    const std::filesystem::path &file_path,
    access_mode mode,
    if_not_there if_file_not_there,
    std::size_t buffer_capacity
)
    : transfer_resource{buffer_capacity}
    , basic_file{file_path, mode, buffer_capacity}
    , m_handle{INVALID_HANDLE_VALUE}
{
    open(m_file_path, m_access_mode, if_file_not_there);
} // function -----------------------------------------------------------------

file::~file ()
{
    close();
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

bool
file::is_open ()
const noexcept
{
    return m_handle != INVALID_HANDLE_VALUE;
} // function -----------------------------------------------------------------

std::int64_t
file::get_position ()
const noexcept
{
    LARGE_INTEGER distance_to_move;
    distance_to_move.QuadPart = 0;
    LARGE_INTEGER position_structure;
    SetFilePointerEx(
        m_handle,
        distance_to_move,
        &position_structure,
        FILE_CURRENT
    );
    return position_structure.QuadPart + m_buffer.get_position();
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

bool
file::open (
    const std::filesystem::path& file_path,
    access_mode mode,
    if_not_there if_file_not_there
)
noexcept
{
    if (is_open()) {
        close();
    }
    std::error_code ec;
    if (
        if_file_not_there == if_not_there::fail
            && !std::filesystem::exists(file_path, ec)
    ) {
        return false;
    }
    DWORD desired_access;
    switch (mode) {
        case read_only:
            desired_access = GENERIC_READ;
            break;
        case write_only:
            desired_access = GENERIC_WRITE;
            break;
        case read_and_write:
            desired_access = GENERIC_READ | GENERIC_WRITE;
            break;
    }
    SECURITY_ATTRIBUTES security_attributes;
    security_attributes.nLength = sizeof (security_attributes);
    security_attributes.lpSecurityDescriptor = nullptr;
    security_attributes.bInheritHandle = true;
    std::wstring file_path_wstring{file_path.wstring()};
    m_handle = CreateFileW(
        file_path_wstring.c_str(),
        desired_access,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        &security_attributes,
        OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        nullptr
    );
    m_access_mode = mode;
    return is_open();
} // function -----------------------------------------------------------------

void
file::close ()
noexcept
{
    this->flush();
    CloseHandle(m_handle);
    m_handle = INVALID_HANDLE_VALUE;
} // function -----------------------------------------------------------------

// Protected Functions --------------------------------------------------------

void
file::set_position_raw (
    std::int64_t new_position,
    position_reference pr
)
noexcept
{
    LARGE_INTEGER distance_to_move;
    distance_to_move.QuadPart = new_position;

    int windows_position_reference;
    switch (pr) {
        case position_reference::begin:
            windows_position_reference = FILE_BEGIN;
            if (new_position < 0) {
                new_position = 0;
            }
            break;
        case position_reference::current:
            windows_position_reference = FILE_CURRENT;
            break;
        case position_reference::end:
            windows_position_reference = FILE_END;
            break;
    }

    SetFilePointerEx(
        m_handle,
        distance_to_move,
        nullptr,
        windows_position_reference
    );

    m_last_fill_amount = 0;
} // function -----------------------------------------------------------------

std::size_t
file::read_raw (
    std::byte* data,
    std::size_t byte_count,
    read_request rr
)
noexcept
{
    if (rr == read_request::fill_buffer && m_last_fill_amount > 0) {
        go_forward(m_last_fill_amount);
    }

    std::size_t total_result;
    DWORD native_bytes_read{0};
    const DWORD dword_max{(std::numeric_limits<DWORD>::max)()};
    if constexpr ((std::numeric_limits<std::size_t>::max)() <= dword_max) {
        total_result = read_block(data, byte_count);
    } else {
        std::size_t bytes_read{0};
        DWORD native_byte_count;
        while (byte_count > 0) {
            if (byte_count <= dword_max) {
                native_byte_count = byte_count;
                byte_count = 0;
            } else {
                native_byte_count = dword_max;
                byte_count -= dword_max;
            }
            native_bytes_read = read_block(data, native_byte_count);
            bytes_read += native_bytes_read;
            if (native_bytes_read != native_byte_count) {
                break;
            }
        }
        total_result = bytes_read;
    }

    /*
        If the read request is meant to fill the buffer
        then we go back by the number of bytes read.
    */
    if (rr == read_request::fill_buffer) {
        go_back(static_cast<position_type>(total_result));
        m_last_fill_amount = total_result;
    }

    return total_result;
} // function -----------------------------------------------------------------

std::size_t
file::write_raw (
    const std::byte* data,
    std::size_t byte_count
)
noexcept
{
    std::size_t total_result;
    DWORD native_bytes_written{0};
    const DWORD dword_max{(std::numeric_limits<DWORD>::max)()};
    if constexpr ((std::numeric_limits<std::size_t>::max)() <= dword_max) {
        total_result = write_block(data, byte_count);
    } else {
        std::size_t bytes_written{0};
        DWORD native_byte_count;
        while (byte_count > 0) {
            if (byte_count <= dword_max) {
                native_byte_count = byte_count;
                byte_count = 0;
            } else {
                native_byte_count = dword_max;
                byte_count -= dword_max;
            }
            native_bytes_written = write_block(data, native_byte_count);
            bytes_written += native_bytes_written;
            if (native_bytes_written != native_byte_count) {
                break;
            }
        }
        total_result = bytes_written;
    }
    return total_result;
} // function -----------------------------------------------------------------

// Private Functions ----------------------------------------------------------

DWORD
file::read_block (
    std::byte* data,
    DWORD byte_count
)
noexcept
{
    DWORD bytes_read_last;
    DWORD bytes_read_total{0};
    HRESULT result;
    while (true) {
        result = ReadFile(
            m_handle,
            static_cast<LPVOID>(data + bytes_read_total),
            byte_count - bytes_read_total,
            &bytes_read_last,
            nullptr
        );
        bytes_read_total += bytes_read_last;
        if (result == TRUE) {
            if (bytes_read_last == 0 || bytes_read_total == byte_count) {
                break;
            }
        } else {
            break;
        }
    }

    return bytes_read_total;
} // function -----------------------------------------------------------------

DWORD
file::write_block (
    const std::byte* data,
    DWORD byte_count
)
noexcept
{
    DWORD bytes_written;
    WriteFile(
        m_handle,
        static_cast<LPCVOID>(data),
        byte_count,
        &bytes_written,
        nullptr
    );
    return bytes_written;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
