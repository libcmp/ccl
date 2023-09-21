// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/desktop_gui/impl/common/common_desktop_gui_application.hpp>

namespace cmp {

desktop_gui_application*
dgui_app ()
noexcept
{
    return desktop_gui_application::get_instance_ptr();
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
