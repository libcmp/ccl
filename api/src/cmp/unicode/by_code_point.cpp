// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/unicode/by_code_point.hpp>

namespace cmp {

// ---------------------------------- cmp::by_code_point<char>::const_iterator

// Constructors and Destructor ------------------------------------------------

by_code_point<char>::const_iterator::const_iterator (
    std::string_view::const_iterator initial_current_iterator,
    std::string_view::const_iterator initial_end_iterator
)
noexcept
    : m_current_iterator{initial_current_iterator}
    , m_end_iterator{initial_end_iterator}
{
} // function -----------------------------------------------------------------

// Operator Overloads ---------------------------------------------------------

by_code_point<char>::const_iterator::reference
by_code_point<char>::const_iterator::operator * ()
const
{
    if (m_current_iterator == m_end_iterator) {
        throw iterated_past_end{};
    }
    return *m_current_iterator;
} // function -----------------------------------------------------------------

by_code_point<char>::const_iterator&
by_code_point<char>::const_iterator::operator ++ ()
{
    ++m_current_iterator;
    return *this;
} // function -----------------------------------------------------------------

by_code_point<char>::const_iterator
by_code_point<char>::const_iterator::operator ++ (
    int
) {
    const_iterator old_iterator{*this};
    ++m_current_iterator;
    return old_iterator;
} // function -----------------------------------------------------------------

const by_code_point<char>::const_iterator&
by_code_point<char>::const_iterator::operator += (
    by_code_point<char>::const_iterator::difference_type offset
) {
    m_current_iterator += offset;
    return *this;
} // function -----------------------------------------------------------------

by_code_point<char>::const_iterator&
by_code_point<char>::const_iterator::operator -- ()
noexcept
{
    --m_current_iterator;
    return *this;
} // function -----------------------------------------------------------------

by_code_point<char>::const_iterator
by_code_point<char>::const_iterator::operator -- (
    int
)
noexcept
{
    const_iterator old_iterator{*this};
    --m_current_iterator;
    return old_iterator;
} // function -----------------------------------------------------------------

const by_code_point<char>::const_iterator&
by_code_point<char>::const_iterator::operator -= (
    by_code_point<char>::const_iterator::difference_type offset
)
noexcept
{
    m_current_iterator -= offset;
    return *this;
} // function -----------------------------------------------------------------

by_code_point<char>::const_iterator
operator + (
    const by_code_point<char>::const_iterator& iterator,
    by_code_point<char>::const_iterator::difference_type offset
)
noexcept
{
    by_code_point<char>::const_iterator result_iterator{
        iterator.m_current_iterator,
        iterator.m_end_iterator
    };
    result_iterator.m_current_iterator += offset;
    return result_iterator;
} // function -----------------------------------------------------------------

by_code_point<char>::const_iterator
operator + (
    by_code_point<char>::const_iterator::difference_type offset,
    const by_code_point<char>::const_iterator& iterator
)
noexcept
{
    by_code_point<char>::const_iterator result_iterator{
        iterator.m_current_iterator,
        iterator.m_end_iterator
    };
    result_iterator.m_current_iterator += offset;
    return result_iterator;
} // function -----------------------------------------------------------------

by_code_point<char>::const_iterator
operator - (
    const by_code_point<char>::const_iterator& iterator,
    by_code_point<char>::const_iterator::difference_type offset
)
noexcept
{
    by_code_point<char>::const_iterator result_iterator{
        iterator.m_current_iterator,
        iterator.m_end_iterator
    };
    result_iterator.m_current_iterator -= offset;
    return result_iterator;
} // function -----------------------------------------------------------------

by_code_point<char>::const_iterator
operator - (
    by_code_point<char>::const_iterator::difference_type offset,
    const by_code_point<char>::const_iterator& iterator
)
noexcept
{
    by_code_point<char>::const_iterator result_iterator{
        iterator.m_current_iterator,
        iterator.m_end_iterator
    };
    result_iterator.m_current_iterator -= offset;
    return result_iterator;
} // function -----------------------------------------------------------------

bool
operator == (
    const by_code_point<char>::const_iterator& iterator1,
    const by_code_point<char>::const_iterator& iterator2
)
noexcept
{
    return
        iterator1.m_current_iterator == iterator2.m_current_iterator
            && iterator1.m_end_iterator == iterator2.m_end_iterator;
} // function -----------------------------------------------------------------

bool
operator != (
    const by_code_point<char>::const_iterator& iterator1,
    const by_code_point<char>::const_iterator& iterator2
)
noexcept
{
    return
        iterator1.m_current_iterator != iterator2.m_current_iterator
            || iterator1.m_end_iterator != iterator2.m_end_iterator;
} // function -----------------------------------------------------------------

// -------------------------------------------------- cmp::by_code_point<char>

// Constructors and Destructor ------------------------------------------------

by_code_point<char>::by_code_point (
    std::string_view string_to_iterate
)
noexcept
    : m_begin_iterator{string_to_iterate.cbegin()}
    , m_end_iterator{string_to_iterate.cend()}
{
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

by_code_point<char>::const_iterator
by_code_point<char>::begin ()
const noexcept
{
    return cbegin();
} // function -----------------------------------------------------------------

by_code_point<char>::const_iterator
by_code_point<char>::end ()
const noexcept
{
    return cend();
} // function -----------------------------------------------------------------

by_code_point<char>::const_iterator
by_code_point<char>::cbegin ()
const noexcept
{
    return const_iterator{m_begin_iterator, m_end_iterator};
} // function -----------------------------------------------------------------

by_code_point<char>::const_iterator
by_code_point<char>::cend ()
const noexcept
{
    return const_iterator{m_end_iterator, m_end_iterator};
} // function -----------------------------------------------------------------

by_code_point<char>::const_reverse_iterator
by_code_point<char>::crbegin ()
const noexcept
{
    return const_reverse_iterator{cend()};
} // function -----------------------------------------------------------------

by_code_point<char>::const_reverse_iterator
by_code_point<char>::crend ()
const noexcept
{
    return const_reverse_iterator{cbegin()};
} // function -----------------------------------------------------------------

// -------------------- cmp::by_code_point<char8_t>::const_iterator::reference

// Constructors and Destructor ------------------------------------------------

by_code_point<char8_t>::const_iterator::reference::reference (
    std::u8string_view::const_iterator initial_current_iterator,
    std::u8string_view::const_iterator initial_end_iterator
)
noexcept
    : m_current_iterator{initial_current_iterator}
    , m_end_iterator{initial_end_iterator}
{
} // function -----------------------------------------------------------------

// Operator Overloads ---------------------------------------------------------

by_code_point<char8_t>::const_iterator::reference::operator char32_t ()
const
{
    char8_t code_unit{*m_current_iterator};
    char32_t code_point;
    auto sequence_length{
        impl::initialize_utf8_sequence(code_unit, code_point)
    };
    code_point = finish_sequence(
        sequence_length,
        code_point,
        m_current_iterator
    );
    return code_point;
} // function -----------------------------------------------------------------

// Private Functions ----------------------------------------------------------

char32_t
by_code_point<char8_t>::const_iterator::reference::finish_sequence (
    int sequence_length,
    char32_t initial_code_point_value,
    std::u8string_view::const_iterator i
)
const
{
    char8_t code_unit;
    char32_t result{initial_code_point_value};
    if (sequence_length == 1) {
        return result;
    }
    while (--sequence_length > 0) {
        if (i + 1 == m_end_iterator) {
            throw iterated_past_end{};
        }
        code_unit = *(i + 1);
        if (!is_trailing_byte(code_unit)) {
            throw invalid_unicode_encoding{};
        }
        ++i;
        result <<= 6;
        result |= code_unit & 0b0011'1111;
    }
    return result;
} // function -----------------------------------------------------------------

// ------------------------------- cmp::by_code_point<char8_t>::const_iterator

// Constructors and Destructor ------------------------------------------------

by_code_point<char8_t>::const_iterator::const_iterator (
    std::u8string_view::const_iterator initial_current_iterator,
    std::u8string_view::const_iterator initial_end_iterator
)
noexcept
    : m_current_iterator{initial_current_iterator}
    , m_end_iterator{initial_end_iterator}
{
} // function -----------------------------------------------------------------

// Operator Overloads ---------------------------------------------------------

by_code_point<char8_t>::const_iterator::reference
by_code_point<char8_t>::const_iterator::operator * ()
const
{
    if (m_current_iterator == m_end_iterator) {
        throw iterated_past_end{};
    }
    return reference{m_current_iterator, m_end_iterator};
} // function -----------------------------------------------------------------

by_code_point<char8_t>::const_iterator&
by_code_point<char8_t>::const_iterator::operator ++ ()
{
    advance();
    return *this;
} // function -----------------------------------------------------------------

by_code_point<char8_t>::const_iterator
by_code_point<char8_t>::const_iterator::operator ++ (
    int
) {
    const_iterator old_iterator{*this};
    advance();
    return old_iterator;
} // function -----------------------------------------------------------------

const by_code_point<char8_t>::const_iterator&
by_code_point<char8_t>::const_iterator::operator += (
    difference_type offset
) {
    advance(offset);
    return *this;
} // function -----------------------------------------------------------------

by_code_point<char8_t>::const_iterator&
by_code_point<char8_t>::const_iterator::operator -- ()
noexcept
{
    retreat();
    return *this;
} // function -----------------------------------------------------------------

by_code_point<char8_t>::const_iterator
by_code_point<char8_t>::const_iterator::operator -- (
    int
)
noexcept
{
    const_iterator old_iterator{*this};
    retreat();
    return old_iterator;
} // function -----------------------------------------------------------------

const by_code_point<char8_t>::const_iterator&
by_code_point<char8_t>::const_iterator::operator -= (
    difference_type offset
)
noexcept
{
    retreat(offset);
    return *this;
} // function -----------------------------------------------------------------

by_code_point<char8_t>::const_iterator
operator + (
    const by_code_point<char8_t>::const_iterator& iterator,
    by_code_point<char8_t>::const_iterator::difference_type offset
)
noexcept
{
    by_code_point<char8_t>::const_iterator result_iterator{
        iterator.m_current_iterator,
        iterator.m_end_iterator
    };
    result_iterator.advance(offset);
    return result_iterator;
} // function -----------------------------------------------------------------

by_code_point<char8_t>::const_iterator
operator + (
    by_code_point<char8_t>::const_iterator::difference_type offset,
    const by_code_point<char8_t>::const_iterator& iterator
)
noexcept
{
    by_code_point<char8_t>::const_iterator result_iterator{
        iterator.m_current_iterator,
        iterator.m_end_iterator
    };
    result_iterator.advance(offset);
    return result_iterator;
} // function -----------------------------------------------------------------

by_code_point<char8_t>::const_iterator
operator - (
    const by_code_point<char8_t>::const_iterator& iterator,
    by_code_point<char8_t>::const_iterator::difference_type offset
)
noexcept
{
    by_code_point<char8_t>::const_iterator result_iterator{
        iterator.m_current_iterator,
        iterator.m_end_iterator
    };
    result_iterator.retreat(offset);
    return result_iterator;
} // function -----------------------------------------------------------------

by_code_point<char8_t>::const_iterator
operator - (
    by_code_point<char8_t>::const_iterator::difference_type offset,
    const by_code_point<char8_t>::const_iterator& iterator
)
noexcept
{
    by_code_point<char8_t>::const_iterator result_iterator{
        iterator.m_current_iterator,
        iterator.m_end_iterator
    };
    result_iterator.retreat(offset);
    return result_iterator;
} // function -----------------------------------------------------------------

bool
operator == (
    const by_code_point<char8_t>::const_iterator& iterator1,
    const by_code_point<char8_t>::const_iterator& iterator2
)
noexcept
{
    return
        iterator1.m_current_iterator == iterator2.m_current_iterator
            && iterator1.m_end_iterator == iterator2.m_end_iterator;
} // function -----------------------------------------------------------------

bool
operator != (
    const by_code_point<char8_t>::const_iterator& iterator1,
    const by_code_point<char8_t>::const_iterator& iterator2
)
noexcept
{
    return
        iterator1.m_current_iterator != iterator2.m_current_iterator
            || iterator1.m_end_iterator != iterator2.m_end_iterator;
} // function -----------------------------------------------------------------

// Private Functions ----------------------------------------------------------

char32_t
by_code_point<char8_t>::const_iterator::finish_sequence (
    int sequence_length,
    char32_t initial_code_point_value,
    std::u8string_view::const_iterator i
)
const
{
    char8_t code_unit;
    char32_t result{initial_code_point_value};
    if (sequence_length == 1) {
        return result;
    }
    while (--sequence_length > 0) {
        if (i == m_end_iterator) {
            throw iterated_past_end{};
        }
        code_unit = *(i + 1);
        if (!is_trailing_byte(code_unit)) {
            throw invalid_unicode_encoding{};
        }
        ++i;
        result <<= 6;
        result |= code_unit & 0b0011'1111;
    }
    return result;
} // function -----------------------------------------------------------------

char32_t
by_code_point<char8_t>::const_iterator::finish_sequence (
    int sequence_length,
    char32_t initial_code_point_value,
    std::u8string_view::const_iterator& i
) {
    char8_t code_unit;
    char32_t result{initial_code_point_value};
    if (sequence_length == 1) {
        ++i;
        return result;
    }
    while (--sequence_length > 0) {
        if (i == m_end_iterator) {
            throw iterated_past_end{};
        }
        code_unit = *(i + 1);
        if (!is_trailing_byte(code_unit)) {
            throw invalid_unicode_encoding{};
        }
        ++i;
        result <<= 6;
        result |= code_unit & 0b0011'1111;
    }
    ++i;
    return result;
} // function -----------------------------------------------------------------

void
by_code_point<char8_t>::const_iterator::advance ()
{
    char8_t code_unit{*m_current_iterator};
    char32_t code_point;
    auto sequence_length{
        impl::initialize_utf8_sequence(code_unit, code_point)
    };
    code_point = finish_sequence(
        sequence_length,
        code_point,
        m_current_iterator
    );
} // function -----------------------------------------------------------------

void
by_code_point<char8_t>::const_iterator::advance (
    difference_type offset
) {
    while (offset-- > 0) {
        advance();
    }
} // function -----------------------------------------------------------------

void
by_code_point<char8_t>::const_iterator::retreat ()
{
    char8_t code_unit{*(--m_current_iterator)};
    if (is_standalone_byte(code_unit)) {
        return;
    }
    while (is_trailing_byte(code_unit)) {
        code_unit = *(--m_current_iterator);
    }
} // function -----------------------------------------------------------------

void
by_code_point<char8_t>::const_iterator::retreat (
    difference_type offset
) {
    while (offset-- > 0) {
        retreat();
    }
} // function -----------------------------------------------------------------

// ----------------------------------------------- cmp::by_code_point<char8_t>

// Constructors and Destructor ------------------------------------------------

by_code_point<char8_t>::by_code_point (
    std::u8string_view string_to_iterate
)
noexcept
    : m_begin_iterator{string_to_iterate.cbegin()}
    , m_end_iterator{string_to_iterate.cend()}
{
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

by_code_point<char8_t>::const_iterator
by_code_point<char8_t>::begin ()
const noexcept
{
    return cbegin();
} // function -----------------------------------------------------------------

by_code_point<char8_t>::const_iterator
by_code_point<char8_t>::end ()
const noexcept
{
    return cend();
} // function -----------------------------------------------------------------

by_code_point<char8_t>::const_iterator
by_code_point<char8_t>::cbegin ()
const noexcept
{
    return const_iterator{m_begin_iterator, m_end_iterator};
} // function -----------------------------------------------------------------

by_code_point<char8_t>::const_iterator
by_code_point<char8_t>::cend ()
const noexcept
{
    return const_iterator{m_end_iterator, m_end_iterator};
} // function -----------------------------------------------------------------

by_code_point<char8_t>::const_reverse_iterator
by_code_point<char8_t>::crbegin ()
const noexcept
{
    return const_reverse_iterator{cend()};
} // function -----------------------------------------------------------------

by_code_point<char8_t>::const_reverse_iterator
by_code_point<char8_t>::crend ()
const noexcept
{
    return const_reverse_iterator{cbegin()};
} // function -----------------------------------------------------------------

// ------------------- cmp::by_code_point<char16_t>::const_iterator::reference

// Constructors and Destructor ------------------------------------------------

by_code_point<char16_t>::const_iterator::reference::reference (
    std::u16string_view::const_iterator initial_current_iterator,
    std::u16string_view::const_iterator initial_end_iterator
)
noexcept
    : m_current_iterator{initial_current_iterator}
    , m_end_iterator{initial_end_iterator}
{
} // function -----------------------------------------------------------------

// Operator Overloads ---------------------------------------------------------

by_code_point<char16_t>::const_iterator::reference::operator char32_t ()
const
{
    char16_t code_unit{*m_current_iterator};
    char32_t code_point;
    auto sequence_length{
        impl::initialize_utf16_sequence(code_unit, code_point)
    };
    code_point = finish_sequence(
        sequence_length,
        code_point,
        m_current_iterator
    );
    return code_point;
} // function -----------------------------------------------------------------

// Private Functions ----------------------------------------------------------

char32_t
by_code_point<char16_t>::const_iterator::reference::finish_sequence (
    int sequence_length,
    char32_t initial_code_point_value,
    std::u16string_view::const_iterator i
)
const
{
    if (sequence_length == 2) {
        if (i + 1 == m_end_iterator) {
            throw iterated_past_end{};
        }
        char16_t code_unit{*(i + 1)};
        if (!is_trailing_surrogate(code_unit)) {
            throw invalid_unicode_encoding{};
        }
        ++i;
        return initial_code_point_value + (code_unit - 0xDC00) + 0x10000;
    } else {
        return initial_code_point_value;
    }
} // function -----------------------------------------------------------------

// ------------------------------ cmp::by_code_point<char16_t>::const_iterator

// Constructors and Destructor ------------------------------------------------

by_code_point<char16_t>::const_iterator::const_iterator (
    std::u16string_view::const_iterator initial_current_iterator,
    std::u16string_view::const_iterator initial_end_iterator
)
noexcept
    : m_current_iterator{initial_current_iterator}
    , m_end_iterator{initial_end_iterator}
{
} // function -----------------------------------------------------------------

// Operator Overloads ---------------------------------------------------------

by_code_point<char16_t>::const_iterator::reference
by_code_point<char16_t>::const_iterator::operator * ()
const
{
    if (m_current_iterator == m_end_iterator) {
        throw iterated_past_end{};
    }
    return reference{m_current_iterator, m_end_iterator};
} // function -----------------------------------------------------------------

by_code_point<char16_t>::const_iterator&
by_code_point<char16_t>::const_iterator::operator ++ ()
{
    advance();
    return *this;
} // function -----------------------------------------------------------------

by_code_point<char16_t>::const_iterator
by_code_point<char16_t>::const_iterator::operator ++ (
    int
) {
    const_iterator old_iterator{*this};
    advance();
    return old_iterator;
} // function -----------------------------------------------------------------

const by_code_point<char16_t>::const_iterator&
by_code_point<char16_t>::const_iterator::operator += (
    difference_type offset
) {
    advance(offset);
    return *this;
} // function -----------------------------------------------------------------

by_code_point<char16_t>::const_iterator&
by_code_point<char16_t>::const_iterator::operator -- ()
noexcept
{
    retreat();
    return *this;
} // function -----------------------------------------------------------------

by_code_point<char16_t>::const_iterator
by_code_point<char16_t>::const_iterator::operator -- (
    int
)
noexcept
{
    const_iterator old_iterator{*this};
    retreat();
    return old_iterator;
} // function -----------------------------------------------------------------

const by_code_point<char16_t>::const_iterator&
by_code_point<char16_t>::const_iterator::operator -= (
    difference_type offset
)
noexcept
{
    retreat(offset);
    return *this;
} // function -----------------------------------------------------------------

by_code_point<char16_t>::const_iterator
operator + (
    const by_code_point<char16_t>::const_iterator& iterator,
    by_code_point<char16_t>::const_iterator::difference_type offset
)
noexcept
{
    by_code_point<char16_t>::const_iterator result_iterator{
        iterator.m_current_iterator,
        iterator.m_end_iterator
    };
    result_iterator.advance(offset);
    return result_iterator;
} // function -----------------------------------------------------------------

by_code_point<char16_t>::const_iterator
operator + (
    by_code_point<char16_t>::const_iterator::difference_type offset,
    const by_code_point<char16_t>::const_iterator& iterator
)
noexcept
{
    by_code_point<char16_t>::const_iterator result_iterator{
        iterator.m_current_iterator,
        iterator.m_end_iterator
    };
    result_iterator.advance(offset);
    return result_iterator;
} // function -----------------------------------------------------------------

by_code_point<char16_t>::const_iterator
operator - (
    const by_code_point<char16_t>::const_iterator& iterator,
    by_code_point<char16_t>::const_iterator::difference_type offset
)
noexcept
{
    by_code_point<char16_t>::const_iterator result_iterator{
        iterator.m_current_iterator,
        iterator.m_end_iterator
    };
    result_iterator.retreat(offset);
    return result_iterator;
} // function -----------------------------------------------------------------

by_code_point<char16_t>::const_iterator
operator - (
    by_code_point<char16_t>::const_iterator::difference_type offset,
    const by_code_point<char16_t>::const_iterator& iterator
)
noexcept
{
    by_code_point<char16_t>::const_iterator result_iterator{
        iterator.m_current_iterator,
        iterator.m_end_iterator
    };
    result_iterator.retreat(offset);
    return result_iterator;
} // function -----------------------------------------------------------------

bool
operator == (
    const by_code_point<char16_t>::const_iterator& iterator1,
    const by_code_point<char16_t>::const_iterator& iterator2
)
noexcept
{
    return
        iterator1.m_current_iterator == iterator2.m_current_iterator
            && iterator1.m_end_iterator == iterator2.m_end_iterator;
} // function -----------------------------------------------------------------

bool
operator != (
    const by_code_point<char16_t>::const_iterator& iterator1,
    const by_code_point<char16_t>::const_iterator& iterator2
)
noexcept
{
    return
        iterator1.m_current_iterator != iterator2.m_current_iterator
            || iterator1.m_end_iterator != iterator2.m_end_iterator;
} // function -----------------------------------------------------------------

// Private Functions ----------------------------------------------------------

char32_t
by_code_point<char16_t>::const_iterator::finish_sequence (
    int sequence_length,
    char32_t initial_code_point_value,
    std::u16string_view::const_iterator i
)
const
{
    if (sequence_length == 2) {
        if (i == m_end_iterator) {
            throw iterated_past_end{};
        }
        char16_t code_unit{*(i + 1)};
        if (!is_trailing_surrogate(code_unit)) {
            throw invalid_unicode_encoding{};
        }
        ++i;
        return initial_code_point_value + (code_unit - 0xDC00) + 0x10000;
    } else {
        return initial_code_point_value;
    }
} // function -----------------------------------------------------------------

char32_t
by_code_point<char16_t>::const_iterator::finish_sequence (
    int sequence_length,
    char32_t initial_code_point_value,
    std::u16string_view::const_iterator& i
) {
    if (sequence_length == 2) {
        if (i == m_end_iterator) {
            throw iterated_past_end{};
        }
        char16_t code_unit{*(i + 1)};
        if (!is_trailing_surrogate(code_unit)) {
            throw invalid_unicode_encoding{};
        }
        ++i;
        return initial_code_point_value + (code_unit - 0xDC00) + 0x10000;
    } else {
        ++i;
        return initial_code_point_value;
    }
} // function -----------------------------------------------------------------

void
by_code_point<char16_t>::const_iterator::advance ()
{
    char16_t code_unit{*m_current_iterator};
    char32_t code_point;
    auto sequence_length{
        impl::initialize_utf16_sequence(code_unit, code_point)
    };
    code_point = finish_sequence(
        sequence_length,
        code_point,
        m_current_iterator
    );
} // function -----------------------------------------------------------------

void
by_code_point<char16_t>::const_iterator::advance (
    difference_type offset
) {
    while (offset-- > 0) {
        advance();
    }
} // function -----------------------------------------------------------------

void
by_code_point<char16_t>::const_iterator::retreat ()
{
    char16_t code_unit{*(--m_current_iterator)};
    if (is_trailing_surrogate(code_unit)) {
        --m_current_iterator;
    }
} // function -----------------------------------------------------------------

void
by_code_point<char16_t>::const_iterator::retreat (
    difference_type offset
) {
    while (offset-- > 0) {
        advance();
    }
} // function -----------------------------------------------------------------

// ---------------------------------------------- cmp::by_code_point<char16_t>

// Constructors and Destructor ------------------------------------------------

by_code_point<char16_t>::by_code_point (
    std::u16string_view string_to_iterate
)
noexcept
    : m_begin_iterator{string_to_iterate.cbegin()}
    , m_end_iterator{string_to_iterate.cend()}
{
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

by_code_point<char16_t>::const_iterator
by_code_point<char16_t>::begin ()
const noexcept
{
    return cbegin();
} // function -----------------------------------------------------------------

by_code_point<char16_t>::const_iterator
by_code_point<char16_t>::end ()
const noexcept
{
    return cend();
} // function -----------------------------------------------------------------

by_code_point<char16_t>::const_iterator
by_code_point<char16_t>::cbegin ()
const noexcept
{
    return const_iterator{m_begin_iterator, m_end_iterator};
} // function -----------------------------------------------------------------

by_code_point<char16_t>::const_iterator
by_code_point<char16_t>::cend ()
const noexcept
{
    return const_iterator{m_end_iterator, m_end_iterator};
} // function -----------------------------------------------------------------

by_code_point<char16_t>::const_reverse_iterator
by_code_point<char16_t>::crbegin ()
const noexcept
{
    return const_reverse_iterator{cend()};
} // function -----------------------------------------------------------------

by_code_point<char16_t>::const_reverse_iterator
by_code_point<char16_t>::crend ()
const noexcept
{
    return const_reverse_iterator{cbegin()};
} // function -----------------------------------------------------------------

// ------------------------------ cmp::by_code_point<char32_t>::const_iterator

// Constructors and Destructor ------------------------------------------------

by_code_point<char32_t>::const_iterator::const_iterator (
    std::u32string_view::const_iterator initial_current_iterator,
    std::u32string_view::const_iterator initial_end_iterator
)
noexcept
    : m_current_iterator{initial_current_iterator}
    , m_end_iterator{initial_end_iterator}
{
} // function -----------------------------------------------------------------

// Operator Overloads ---------------------------------------------------------

by_code_point<char32_t>::const_iterator::reference
by_code_point<char32_t>::const_iterator::operator * ()
const
{
    if (m_current_iterator == m_end_iterator) {
        throw iterated_past_end{};
    }
    return *m_current_iterator;
} // function -----------------------------------------------------------------

by_code_point<char32_t>::const_iterator&
by_code_point<char32_t>::const_iterator::operator ++ ()
{
    ++m_current_iterator;
    return *this;
} // function -----------------------------------------------------------------

by_code_point<char32_t>::const_iterator
by_code_point<char32_t>::const_iterator::operator ++ (
    int
) {
    const_iterator old_iterator{*this};
    ++m_current_iterator;
    return old_iterator;
} // function -----------------------------------------------------------------

const by_code_point<char32_t>::const_iterator&
by_code_point<char32_t>::const_iterator::operator += (
    by_code_point<char32_t>::const_iterator::difference_type offset
) {
    m_current_iterator += offset;
    return *this;
} // function -----------------------------------------------------------------

by_code_point<char32_t>::const_iterator&
by_code_point<char32_t>::const_iterator::operator -- ()
noexcept
{
    --m_current_iterator;
    return *this;
} // function -----------------------------------------------------------------

by_code_point<char32_t>::const_iterator
by_code_point<char32_t>::const_iterator::operator -- (
    int
)
noexcept
{
    const_iterator old_iterator{*this};
    --m_current_iterator;
    return old_iterator;
} // function -----------------------------------------------------------------

const by_code_point<char32_t>::const_iterator&
by_code_point<char32_t>::const_iterator::operator -= (
    by_code_point<char32_t>::const_iterator::difference_type offset
)
noexcept
{
    m_current_iterator -= offset;
    return *this;
} // function -----------------------------------------------------------------

by_code_point<char32_t>::const_iterator
operator + (
    const by_code_point<char32_t>::const_iterator& iterator,
    by_code_point<char32_t>::const_iterator::difference_type offset
)
noexcept
{
    by_code_point<char32_t>::const_iterator result_iterator{
        iterator.m_current_iterator,
        iterator.m_end_iterator
    };
    result_iterator.m_current_iterator += offset;
    return result_iterator;
} // function -----------------------------------------------------------------

by_code_point<char32_t>::const_iterator
operator + (
    by_code_point<char32_t>::const_iterator::difference_type offset,
    const by_code_point<char32_t>::const_iterator& iterator
)
noexcept
{
    by_code_point<char32_t>::const_iterator result_iterator{
        iterator.m_current_iterator,
        iterator.m_end_iterator
    };
    result_iterator.m_current_iterator += offset;
    return result_iterator;
} // function -----------------------------------------------------------------

by_code_point<char32_t>::const_iterator
operator - (
    const by_code_point<char32_t>::const_iterator& iterator,
    by_code_point<char32_t>::const_iterator::difference_type offset
)
noexcept
{
    by_code_point<char32_t>::const_iterator result_iterator{
        iterator.m_current_iterator,
        iterator.m_end_iterator
    };
    result_iterator.m_current_iterator -= offset;
    return result_iterator;
} // function -----------------------------------------------------------------

by_code_point<char32_t>::const_iterator
operator - (
    by_code_point<char32_t>::const_iterator::difference_type offset,
    const by_code_point<char32_t>::const_iterator& iterator
)
noexcept
{
    by_code_point<char32_t>::const_iterator result_iterator{
        iterator.m_current_iterator,
        iterator.m_end_iterator
    };
    result_iterator.m_current_iterator -= offset;
    return result_iterator;
} // function -----------------------------------------------------------------

bool
operator == (
    const by_code_point<char32_t>::const_iterator& iterator1,
    const by_code_point<char32_t>::const_iterator& iterator2
)
noexcept
{
    return
        iterator1.m_current_iterator == iterator2.m_current_iterator
            && iterator1.m_end_iterator == iterator2.m_end_iterator;
} // function -----------------------------------------------------------------

bool
operator != (
    const by_code_point<char32_t>::const_iterator& iterator1,
    const by_code_point<char32_t>::const_iterator& iterator2
)
noexcept
{
    return
        iterator1.m_current_iterator != iterator2.m_current_iterator
            || iterator1.m_end_iterator != iterator2.m_end_iterator;
} // function -----------------------------------------------------------------

// ---------------------------------------------- cmp::by_code_point<char32_t>

// Constructors and Destructor ------------------------------------------------

by_code_point<char32_t>::by_code_point (
    std::u32string_view string_to_iterate
)
noexcept
    : m_begin_iterator{string_to_iterate.cbegin()}
    , m_end_iterator{string_to_iterate.cend()}
{
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

by_code_point<char32_t>::const_iterator
by_code_point<char32_t>::begin ()
const noexcept
{
    return cbegin();
} // function -----------------------------------------------------------------

by_code_point<char32_t>::const_iterator
by_code_point<char32_t>::end ()
const noexcept
{
    return cend();
} // function -----------------------------------------------------------------

by_code_point<char32_t>::const_iterator
by_code_point<char32_t>::cbegin ()
const noexcept
{
    return const_iterator{m_begin_iterator, m_end_iterator};
} // function -----------------------------------------------------------------

by_code_point<char32_t>::const_iterator
by_code_point<char32_t>::cend ()
const noexcept
{
    return const_iterator{m_end_iterator, m_end_iterator};
} // function -----------------------------------------------------------------

by_code_point<char32_t>::const_reverse_iterator
by_code_point<char32_t>::crbegin ()
const noexcept
{
    return const_reverse_iterator{cend()};
} // function -----------------------------------------------------------------

by_code_point<char32_t>::const_reverse_iterator
by_code_point<char32_t>::crend ()
const noexcept
{
    return const_reverse_iterator{cbegin()};
} // function -----------------------------------------------------------------

// -------------------- cmp::by_code_point<wchar_t>::const_iterator::reference

// Constructors and Destructor ------------------------------------------------

by_code_point<wchar_t>::const_iterator::reference::reference (
    std::wstring_view::const_iterator initial_current_iterator,
    std::wstring_view::const_iterator initial_end_iterator
)
noexcept
    : m_current_iterator{initial_current_iterator}
    , m_end_iterator{initial_end_iterator}
{
} // function -----------------------------------------------------------------

// Operator Overloads ---------------------------------------------------------

by_code_point<wchar_t>::const_iterator::reference::operator char32_t ()
const
{
    if constexpr (sizeof (wchar_t) == 2) {
        wchar_t code_unit{*m_current_iterator};
        char32_t code_point;
        auto sequence_length{
            impl::initialize_utf16_sequence(code_unit, code_point)
        };
        code_point = finish_sequence(
            sequence_length,
            code_point,
            m_current_iterator
        );
        return code_point;
    } else {
        return *m_current_iterator;
    }
} // function -----------------------------------------------------------------

// Private Functions ----------------------------------------------------------

char32_t
by_code_point<wchar_t>::const_iterator::reference::finish_sequence (
    int sequence_length,
    char32_t initial_code_point_value,
    std::wstring_view::const_iterator i
)
const
{
    if (sequence_length == 2) {
        if (i + 1 == m_end_iterator) {
            throw iterated_past_end{};
        }
        char16_t code_unit{*(i + 1)};
        if (!is_trailing_surrogate(code_unit)) {
            throw invalid_unicode_encoding{};
        }
        ++i;
        return initial_code_point_value + (code_unit - 0xDC00) + 0x10000;
    } else {
        return initial_code_point_value;
    }
} // function -----------------------------------------------------------------

// ------------------------------- cmp::by_code_point<wchar_t>::const_iterator

// Constructors and Destructor ------------------------------------------------

by_code_point<wchar_t>::const_iterator::const_iterator (
    std::wstring_view::const_iterator initial_current_iterator,
    std::wstring_view::const_iterator initial_end_iterator
)
noexcept
    : m_current_iterator{initial_current_iterator}
    , m_end_iterator{initial_end_iterator}
{
} // function -----------------------------------------------------------------

// Operator Overloads ---------------------------------------------------------

by_code_point<wchar_t>::const_iterator::reference
by_code_point<wchar_t>::const_iterator::operator * ()
const
{
    if (m_current_iterator == m_end_iterator) {
        throw iterated_past_end{};
    }
    return reference{m_current_iterator, m_end_iterator};
} // function -----------------------------------------------------------------

by_code_point<wchar_t>::const_iterator&
by_code_point<wchar_t>::const_iterator::operator ++ ()
{
    advance();
    return *this;
} // function -----------------------------------------------------------------

by_code_point<wchar_t>::const_iterator
by_code_point<wchar_t>::const_iterator::operator ++ (
    int
) {
    const_iterator old_iterator{*this};
    advance();
    return old_iterator;
} // function -----------------------------------------------------------------

const by_code_point<wchar_t>::const_iterator&
by_code_point<wchar_t>::const_iterator::operator += (
    difference_type offset
) {
    advance(offset);
    return *this;
} // function -----------------------------------------------------------------

by_code_point<wchar_t>::const_iterator&
by_code_point<wchar_t>::const_iterator::operator -- ()
noexcept
{
    retreat();
    return *this;
} // function -----------------------------------------------------------------

by_code_point<wchar_t>::const_iterator
by_code_point<wchar_t>::const_iterator::operator -- (
    int
)
noexcept
{
    const_iterator old_iterator{*this};
    retreat();
    return old_iterator;
} // function -----------------------------------------------------------------

const by_code_point<wchar_t>::const_iterator&
by_code_point<wchar_t>::const_iterator::operator -= (
    difference_type offset
)
noexcept
{
    retreat(offset);
    return *this;
} // function -----------------------------------------------------------------

by_code_point<wchar_t>::const_iterator
operator + (
    const by_code_point<wchar_t>::const_iterator& iterator,
    by_code_point<wchar_t>::const_iterator::difference_type offset
)
noexcept
{
    by_code_point<wchar_t>::const_iterator result_iterator{
        iterator.m_current_iterator,
        iterator.m_end_iterator
    };
    result_iterator.advance(offset);
    return result_iterator;
} // function -----------------------------------------------------------------

by_code_point<wchar_t>::const_iterator
operator + (
    by_code_point<wchar_t>::const_iterator::difference_type offset,
    const by_code_point<wchar_t>::const_iterator& iterator
)
noexcept
{
    by_code_point<wchar_t>::const_iterator result_iterator{
        iterator.m_current_iterator,
        iterator.m_end_iterator
    };
    result_iterator.advance(offset);
    return result_iterator;
} // function -----------------------------------------------------------------

by_code_point<wchar_t>::const_iterator
operator - (
    const by_code_point<wchar_t>::const_iterator& iterator,
    by_code_point<wchar_t>::const_iterator::difference_type offset
)
noexcept
{
    by_code_point<wchar_t>::const_iterator result_iterator{
        iterator.m_current_iterator,
        iterator.m_end_iterator
    };
    result_iterator.retreat(offset);
    return result_iterator;
} // function -----------------------------------------------------------------

by_code_point<wchar_t>::const_iterator
operator - (
    by_code_point<wchar_t>::const_iterator::difference_type offset,
    const by_code_point<wchar_t>::const_iterator& iterator
)
noexcept
{
    by_code_point<wchar_t>::const_iterator result_iterator{
        iterator.m_current_iterator,
        iterator.m_end_iterator
    };
    result_iterator.retreat(offset);
    return result_iterator;
} // function -----------------------------------------------------------------

bool
operator == (
    const by_code_point<wchar_t>::const_iterator& iterator1,
    const by_code_point<wchar_t>::const_iterator& iterator2
)
noexcept
{
    return
        iterator1.m_current_iterator == iterator2.m_current_iterator
            && iterator1.m_end_iterator == iterator2.m_end_iterator;
} // function -----------------------------------------------------------------

bool
operator != (
    const by_code_point<wchar_t>::const_iterator& iterator1,
    const by_code_point<wchar_t>::const_iterator& iterator2
)
noexcept
{
    return
        iterator1.m_current_iterator != iterator2.m_current_iterator
            || iterator1.m_end_iterator != iterator2.m_end_iterator;
} // function -----------------------------------------------------------------

// Private Functions ----------------------------------------------------------

char32_t
by_code_point<wchar_t>::const_iterator::finish_sequence (
    int sequence_length,
    char32_t initial_code_point_value,
    std::wstring_view::const_iterator i
)
const
{
    if (sequence_length == 2) {
        if (i == m_end_iterator) {
            throw iterated_past_end{};
        }
        char16_t code_unit{*(i + 1)};
        if (!is_trailing_surrogate(code_unit)) {
            throw invalid_unicode_encoding{};
        }
        ++i;
        return initial_code_point_value + (code_unit - 0xDC00) + 0x10000;
    } else {
        return initial_code_point_value;
    }
} // function -----------------------------------------------------------------

char32_t
by_code_point<wchar_t>::const_iterator::finish_sequence (
    int sequence_length,
    char32_t initial_code_point_value,
    std::wstring_view::const_iterator& i
) {
    if (sequence_length == 2) {
        if (i == m_end_iterator) {
            throw iterated_past_end{};
        }
        char16_t code_unit{*(i + 1)};
        if (!is_trailing_surrogate(code_unit)) {
            throw invalid_unicode_encoding{};
        }
        ++i;
        return initial_code_point_value + (code_unit - 0xDC00) + 0x10000;
    } else {
        ++i;
        return initial_code_point_value;
    }
} // function -----------------------------------------------------------------

void
by_code_point<wchar_t>::const_iterator::advance ()
{
    if constexpr (sizeof (wchar_t) == 2) {
        char16_t code_unit{*m_current_iterator};
        char32_t code_point;
        auto sequence_length{
            impl::initialize_utf16_sequence(code_unit, code_point)
        };
        code_point = finish_sequence(
            sequence_length,
            code_point,
            m_current_iterator
        );
    } else {
        ++m_current_iterator;
    }
} // function -----------------------------------------------------------------

void
by_code_point<wchar_t>::const_iterator::advance (
    difference_type offset
) {
    if constexpr (sizeof (wchar_t) == 2) {
        while (offset-- > 0) {
            advance();
        }
    } else {
        m_current_iterator += offset;
    }
} // function -----------------------------------------------------------------

void
by_code_point<wchar_t>::const_iterator::retreat ()
{
    if constexpr (sizeof (wchar_t) == 2) {
        char16_t code_unit{*(--m_current_iterator)};
        if (is_trailing_surrogate(code_unit)) {
            --m_current_iterator;
        }
    } else {
        --m_current_iterator;
    }
} // function -----------------------------------------------------------------

void
by_code_point<wchar_t>::const_iterator::retreat (
    difference_type offset
) {
    if constexpr (sizeof (wchar_t) == 2) {
        while (offset-- > 0) {
            advance();
        }
    } else {
        m_current_iterator -= offset;
    }
} // function -----------------------------------------------------------------

// ----------------------------------------------- cmp::by_code_point<wchar_t>

// Constructors and Destructor ------------------------------------------------

by_code_point<wchar_t>::by_code_point (
    std::wstring_view string_to_iterate
)
noexcept
    : m_begin_iterator{string_to_iterate.cbegin()}
    , m_end_iterator{string_to_iterate.cend()}
{
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

by_code_point<wchar_t>::const_iterator
by_code_point<wchar_t>::begin ()
const noexcept
{
    return cbegin();
} // function -----------------------------------------------------------------

by_code_point<wchar_t>::const_iterator
by_code_point<wchar_t>::end ()
const noexcept
{
    return cend();
} // function -----------------------------------------------------------------

by_code_point<wchar_t>::const_iterator
by_code_point<wchar_t>::cbegin ()
const noexcept
{
    return const_iterator{m_begin_iterator, m_end_iterator};
} // function -----------------------------------------------------------------

by_code_point<wchar_t>::const_iterator
by_code_point<wchar_t>::cend ()
const noexcept
{
    return const_iterator{m_end_iterator, m_end_iterator};
} // function -----------------------------------------------------------------

by_code_point<wchar_t>::const_reverse_iterator
by_code_point<wchar_t>::crbegin ()
const noexcept
{
    return const_reverse_iterator{cend()};
} // function -----------------------------------------------------------------

by_code_point<wchar_t>::const_reverse_iterator
by_code_point<wchar_t>::crend ()
const noexcept
{
    return const_reverse_iterator{cbegin()};
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
