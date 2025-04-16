// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/io/file.hpp>

namespace cmp {

// ----------------------------------------------------------- cmp::basic_file

// Constructors and Destructor ------------------------------------------------

basic_file::basic_file ()
noexcept
    : m_file_path{}
    , m_access_mode{read_only}
    , m_last_fill_amount{0}
{
} // function -----------------------------------------------------------------

basic_file::basic_file (
    const std::filesystem::path& file_path,
    access_mode mode
)
    : m_file_path{file_path}
    , m_access_mode{mode}
    , m_last_fill_amount{0}
{
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

access_mode
basic_file::get_access_mode ()
const noexcept
{
    return m_access_mode;
} // function -----------------------------------------------------------------

bool
basic_file::is_at_end ()
const noexcept
{
    return get_position() == std::filesystem::file_size(m_file_path);
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

/*
    The reason for disabling this warning is that the compiler doesn't
    realize that the switch statement accounts for all possible values
    of $m_access_mode, and in each case there is a guaranteed return
    statement or throw statement, so control will never reach the end
    of this non-void function.
*/
CMP_DISABLE_WARNING_PUSH
CMP_DISABLE_WARNING(CMP_WARNING_ID_END_OF_NON_VOID)
std::size_t
basic_file::read (
    std::byte* data,
    std::size_t byte_count
) {
    switch (m_access_mode) {
        case read_only:
        case read_and_write:
            return input_resource::read(data, byte_count);
        case write_only:
            throw invalid_access_mode{};
    }
} // function -----------------------------------------------------------------
CMP_DISABLE_WARNING_POP

/*
    The reason for disabling this warning is that the compiler doesn't
    realize that the switch statement accounts for all possible values
    of $m_access_mode, and in each case there is a guaranteed return
    statement or throw statement, so control will never reach the end
    of this non-void function.
*/
CMP_DISABLE_WARNING_PUSH
CMP_DISABLE_WARNING(CMP_WARNING_ID_END_OF_NON_VOID)
std::size_t
basic_file::write (
    const std::byte* data,
    std::size_t byte_count
) {
    switch (m_access_mode) {
        case read_only:
            throw invalid_access_mode{};
        case write_only:
        case read_and_write:
            return output_resource::write(data, byte_count);
    }
} // function -----------------------------------------------------------------
CMP_DISABLE_WARNING_POP

} // namespace ----------------------------------------------------------------
