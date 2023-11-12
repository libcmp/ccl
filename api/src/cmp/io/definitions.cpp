// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/core/config.hpp>
#include <cmp/core/platform.hpp>

#if CMP_CONFIG_HEADER_ONLY == false && CMP_CONFIG_IO_PACKAGE_EXCLUDED == false
#   include <cmp/io/impl/common/common_uio.cpp>
#   if defined(CMP_OS_WINDOWS)
#       include <cmp/io/impl/windows/windows_file.cpp>
#       include <cmp/io/impl/windows/windows_uin.cpp>
#       include <cmp/io/impl/windows/windows_uout.cpp>
#   elif defined(CMP_OS_UNIX_LIKE)
#       include <cmp/io/impl/unix_like/unix_like_file.cpp>
#       include <cmp/io/impl/unix_like/unix_like_uin.cpp>
#       include <cmp/io/impl/unix_like/unix_like_uout.cpp>
#   endif
#   include <cmp/io/exceptions.cpp>
#   include <cmp/io/file.cpp>
#   include <cmp/io/general.cpp>
#   include <cmp/io/input_resource.cpp>
#   include <cmp/io/io_buffer.cpp>
#   include <cmp/io/io_resource.cpp>
#   include <cmp/io/output_resource.cpp>
#   include <cmp/io/transfer_resource.cpp>
#endif
