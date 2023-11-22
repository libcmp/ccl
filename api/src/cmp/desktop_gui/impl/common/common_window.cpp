// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/desktop_gui/impl/common/common_window.hpp>

namespace cmp {

namespace impl {

// Free Functions -------------------------------------------------------------

void
update_window (
    window* w
) {
    std::chrono::steady_clock::time_point current_time{
        std::chrono::steady_clock::now()
    };
    std::chrono::duration<double> difference{
        std::chrono::duration_cast<
            std::chrono::duration<double>
        >(current_time - w->m_last_time)
    };
    double delta_seconds{difference.count()};

    w->m_last_time = current_time;
    difference = std::chrono::duration_cast<
        std::chrono::duration<double>
    >(current_time - w->m_start_time);
    double total_seconds{difference.count()};

    w->update(delta_seconds, total_seconds);
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
