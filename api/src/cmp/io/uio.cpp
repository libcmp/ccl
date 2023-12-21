// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/io/uio.hpp>

namespace cmp {

stdin_stream uin{uin_resource};
stdout_stream uout{uout_resource};
stdout_stream uerr{uerr_resource};

} // namespace ----------------------------------------------------------------
