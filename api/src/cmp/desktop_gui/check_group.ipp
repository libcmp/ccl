// Copyright (C) 2025 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/desktop_gui/check_group.hpp>

namespace cmp {

// ---------------------------------------------------------- cmp::check_group

// Accessors ------------------------------------------------------------------

template <
    typename T
>
const std::vector<cmp::trusted_ptr<typename check_group<T>::element_type>>&
check_group<T>::grab_elements ()
const noexcept
{
    return m_elements;
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

template <
    typename T
>
void
check_group<T>::add_element (
    cmp::trusted_ptr<element_type> element
) {
    m_elements.push_back(element);
} // function -----------------------------------------------------------------

template <
    typename T
>
void
check_group<T>::uncheck_complement (
    cmp::trusted_ptr<element_type> element
) {
    for (auto& current_element : m_elements) {
        if (current_element != element) {
            current_element->set_checked(false);
        }
    }
} // functions ----------------------------------------------------------------

// Private Functions ----------------------------------------------------------

template <
    typename T
>
void
check_group<T>::remove_element (
    cmp::trusted_ptr<element_type> element
) {
    auto iterator{std::find(m_elements.begin(), m_elements.end(), element)};
    if (iterator != m_elements.end()) {
        m_elements.erase(iterator);
    }
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
