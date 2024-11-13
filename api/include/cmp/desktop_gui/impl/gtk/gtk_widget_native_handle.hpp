// Copyright (C) 2024 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_DESKTOP_GUI_GTK_WIDGET_NATIVE_HANDLE_HPP_INCLUDED
#define CMP_DESKTOP_GUI_GTK_WIDGET_NATIVE_HANDLE_HPP_INCLUDED

#include <gtk/gtk.h>

namespace cmp {

class CMP_CONDITIONAL_EXPORT_CLASS widget_native_handle {
public:
    GtkWidget* parent_handle;
    GtkWidget* widget_handle;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#endif // CMP_DESKTOP_GUI_GTK_WIDGET_NATIVE_HANDLE_HPP_INCLUDED
