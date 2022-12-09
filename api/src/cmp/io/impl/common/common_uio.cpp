// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/io/impl/common/common_uio.hpp>

namespace cmp {

// -------------------------------------------------------- cmp::stdout_stream

// Constructors and Destructor ------------------------------------------------

stdout_stream::stdout_stream (
    wrapped_resource_type& resource,
    flush_strategy fs
)
noexcept
    : text_output_stream<stdout_resource>{
          resource,
          utf8,
          std::endian::native,
          fs
      }
{
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
