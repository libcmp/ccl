// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <iostream>
#include <cmp/io/uio.hpp>

int
main ()
{
    std::cout << "How easy does CCL make it to do Unicode in C++?\n";
    cmp::uout << u8"I dunno, try it ¯\\_(ツ)_/¯\n";
    cmp::uout << u"Huh, let me see. Say something in Unicode: ";
    std::u8string input;
    cmp::uin >> input;
    cmp::uout << U"You said: " << input << '\n';
    cmp::uout << "Cool.\n";

    return 0;
} // function -----------------------------------------------------------------
