// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_IO_INCLUSION_ASSERT_HPP_INCLUDED
#define CMP_IO_INCLUSION_ASSERT_HPP_INCLUDED

#include <bit>

#include <cmp/core/config.hpp>

static_assert(
    CMP_CONFIG_IO_PACKAGE_EXCLUDED == false,
    "The IO package must be included for this header to be used."
);

static_assert(
    std::endian::native == std::endian::little
        || std::endian::native == std::endian::big,
    "Mixed endianness is not allowed, the endianness "
    "must be exclusively little or exclusively big."
);

#endif // CMP_IO_INCLUSION_ASSERT_HPP_INCLUDED
