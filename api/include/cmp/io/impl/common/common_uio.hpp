// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_IO_COMMON_UIO_HPP_INCLUDED
#define CMP_IO_COMMON_UIO_HPP_INCLUDED

#include <cmp/core/platform.hpp>
#include <cmp/io/inclusion_assert.hpp>
#include <cmp/io/text_output_stream.hpp>
#include <cmp/io/text_input_stream.hpp>
#include <cmp/io/output_resource.hpp>

#if defined(CMP_OS_WINDOWS)
#   include <cmp/io/impl/windows/windows_uin.hpp>
#elif defined(CMP_OS_UNIX_LIKE)
#   include <cmp/io/impl/unix_like/unix_like_uin.hpp>
#endif

namespace cmp {

class CMP_LIBRARY_NAME stdout_stream final
    : public text_output_stream<stdout_resource>
{
public:
    // Types ------------------------------------------------------------------

    using wrapped_resource_type = stdout_resource;

    // Constructors and Destructor --------------------------------------------

    CMP_CONDITIONAL_INLINE
    explicit
    stdout_stream (
        wrapped_resource_type& resource,
        flush_strategy fs = flush_strategy::automatic
    )
    noexcept;

    CMP_CONDITIONAL_INLINE
    virtual
    ~stdout_stream ()
    = default;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#if CMP_CONFIG_HEADER_ONLY == true
#   include <cmp/io/impl/common/common_uio.cpp>
#endif // CMP_CONFIG_HEADER_ONLY

#endif // CMP_IO_COMMON_UIO_HPP_INCLUDED
