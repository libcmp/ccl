// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/desktop_gui/general.hpp>

namespace cmp {

// Free Functions -------------------------------------------------------------

std::u8string
to_u8string (
    key source
) {
    switch (source) {
        case key::f1:
            return u8"F1";
        case key::f2:
            return u8"F2";
        case key::f3:
            return u8"F3";
        case key::f4:
            return u8"F4";
        case key::f5:
            return u8"F5";
        case key::f6:
            return u8"F6";
        case key::f7:
            return u8"F7";
        case key::f8:
            return u8"F8";
        case key::f9:
            return u8"F9";
        case key::f10:
            return u8"F10";
        case key::f11:
            return u8"F11";
        case key::f12:
            return u8"F12";
        case key::f13:
            return u8"F13";
        case key::f14:
            return u8"F14";
        case key::f15:
            return u8"F15";
        case key::f16:
            return u8"F16";
        case key::f17:
            return u8"F17";
        case key::f18:
            return u8"F18";
        case key::f19:
            return u8"F19";
        case key::f20:
            return u8"F20";
        case key::f21:
            return u8"F21";
        case key::f22:
            return u8"F22";
        case key::f23:
            return u8"F23";
        case key::f24:
            return u8"F24";
        case key::number_0:
            return u8"0";
        case key::number_1:
            return u8"1";
        case key::number_2:
            return u8"2";
        case key::number_3:
            return u8"3";
        case key::number_4:
            return u8"4";
        case key::number_5:
            return u8"5";
        case key::number_6:
            return u8"6";
        case key::number_7:
            return u8"7";
        case key::number_8:
            return u8"8";
        case key::number_9:
            return u8"9";
        case key::numpad_0:
            return u8"Numpad 0";
        case key::numpad_1:
            return u8"Numpad 1";
        case key::numpad_2:
            return u8"Numpad 2";
        case key::numpad_3:
            return u8"Numpad 3";
        case key::numpad_4:
            return u8"Numpad 4";
        case key::numpad_5:
            return u8"Numpad 5";
        case key::numpad_6:
            return u8"Numpad 6";
        case key::numpad_7:
            return u8"Numpad 7";
        case key::numpad_8:
            return u8"Numpad 8";
        case key::numpad_9:
            return u8"Numpad 9";
        case key::a:
            return u8"A";
        case key::b:
            return u8"B";
        case key::c:
            return u8"C";
        case key::d:
            return u8"D";
        case key::e:
            return u8"E";
        case key::f:
            return u8"F";
        case key::g:
            return u8"G";
        case key::h:
            return u8"H";
        case key::i:
            return u8"I";
        case key::j:
            return u8"J";
        case key::k:
            return u8"K";
        case key::l:
            return u8"L";
        case key::m:
            return u8"M";
        case key::n:
            return u8"N";
        case key::o:
            return u8"O";
        case key::p:
            return u8"P";
        case key::q:
            return u8"Q";
        case key::r:
            return u8"R";
        case key::s:
            return u8"S";
        case key::t:
            return u8"T";
        case key::u:
            return u8"U";
        case key::v:
            return u8"V";
        case key::w:
            return u8"W";
        case key::x:
            return u8"X";
        case key::y:
            return u8"Y";
        case key::z:
            return u8"Z";
        case key::space_bar:
            return u8"Space Bar";
        case key::unknown:
            return u8"Unknown";
    }
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
