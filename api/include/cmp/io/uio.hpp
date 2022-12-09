// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_IO_UIO_HPP_INCLUDED
#define CMP_IO_UIO_HPP_INCLUDED

#include <cmp/io/inclusion_assert.hpp>
#include <cmp/io/impl/common/common_uio.hpp>

namespace cmp {

inline stdin_stream uin{uin_resource};
inline stdout_stream uout{uout_resource};
inline stdout_stream uerr{uerr_resource};

} // namespace ----------------------------------------------------------------

#endif // CMP_IO_UIO_HPP_INCLUDED
