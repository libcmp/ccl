// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_GUI_GENERAL_HPP_INCLUDED
#define CMP_GUI_GENERAL_HPP_INCLUDED

#include <string>

#include <cmp/desktop_gui/inclusion_assert.hpp>

namespace cmp {

class window;

namespace impl {

void
update_window (
    window* w
);

} // namespace ----------------------------------------------------------------

enum class window_mode {
    standard,
    maximized,
    minimized
}; // enum --------------------------------------------------------------------

enum class close_window : bool {
    no = false,
    yes = true
}; // enum --------------------------------------------------------------------

enum class key {
    f1,
    f2,
    f3,
    f4,
    f5,
    f6,
    f7,
    f8,
    f9,
    f10,
    f11,
    f12,
    f13,
    f14,
    f15,
    f16,
    f17,
    f18,
    f19,
    f20,
    f21,
    f22,
    f23,
    f24,
    number_0,
    number_1,
    number_2,
    number_3,
    number_4,
    number_5,
    number_6,
    number_7,
    number_8,
    number_9,
    numpad_0,
    numpad_1,
    numpad_2,
    numpad_3,
    numpad_4,
    numpad_5,
    numpad_6,
    numpad_7,
    numpad_8,
    numpad_9,
    a,
    b,
    c,
    d,
    e,
    f,
    g,
    h,
    i,
    j,
    k,
    l,
    m,
    n,
    o,
    p,
    q,
    r,
    s,
    t,
    u,
    v,
    w,
    x,
    y,
    z,
    space_bar,
    unknown
}; // enum --------------------------------------------------------------------

std::u8string
to_u8string (
    key source
);

} // namespace ----------------------------------------------------------------

#endif // CMP_GUI_GENERAL_HPP_INCLUDED
