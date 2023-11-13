// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_UNICODE_BY_CODE_POINT_HPP_INCLUDED
#define CMP_UNICODE_BY_CODE_POINT_HPP_INCLUDED

#include <string>

#include <cmp/unicode/inclusion_assert.hpp>
#include <cmp/core/config.hpp>
#include <cmp/unicode/examiners.hpp>
#include <cmp/unicode/exceptions.hpp>
#include <cmp/unicode/impl/impl.hpp>

namespace cmp {

template <
    typename CodeUnit
>
class by_code_point {
}; // class -------------------------------------------------------------------

template <>
class CMP_LIBRARY_NAME by_code_point<char> {
public:
    // Types ------------------------------------------------------------------

    class CMP_LIBRARY_NAME const_iterator {
    public:
        // Types --------------------------------------------------------------

        using difference_type = std::ptrdiff_t;

        using value_type = char;

        using reference = std::iterator_traits<
            std::string_view::const_iterator
        >::reference;

        using iterator_category = std::bidirectional_iterator_tag;

        using iterator_concept = std::bidirectional_iterator_tag;

        // Constructors and Destructor ----------------------------------------

        CMP_CONDITIONAL_INLINE
        const_iterator ()
        noexcept = default;

        CMP_CONDITIONAL_INLINE
        const_iterator (
            std::string_view::const_iterator initial_current_iterator,
            std::string_view::const_iterator initial_end_iterator
        )
        noexcept;

        CMP_CONDITIONAL_INLINE
        ~const_iterator ()
        = default;

        // Copy Operations ----------------------------------------------------

        CMP_CONDITIONAL_INLINE
        const_iterator (
            const const_iterator& other
        )
        = default;

        CMP_CONDITIONAL_INLINE
        const_iterator&
        operator = (
            const const_iterator& other
        )
        = default;

        // Move Operations ----------------------------------------------------

        CMP_CONDITIONAL_INLINE
        const_iterator (
            const_iterator&& other
        )
        noexcept = default;

        CMP_CONDITIONAL_INLINE
        const_iterator&
        operator = (
            const_iterator&& other
        )
        noexcept = default;

        // Operator Overloads -------------------------------------------------

        CMP_CONDITIONAL_INLINE
        reference
        operator * ()
        const;

        CMP_CONDITIONAL_INLINE
        const_iterator&
        operator ++ ();

        CMP_CONDITIONAL_INLINE
        const_iterator
        operator ++ (
            int
        );

        CMP_CONDITIONAL_INLINE
        const const_iterator&
        operator += (
            difference_type offset
        );

        CMP_CONDITIONAL_INLINE
        const_iterator&
        operator -- ()
        noexcept;

        CMP_CONDITIONAL_INLINE
        const_iterator
        operator -- (
            int
        )
        noexcept;

        CMP_CONDITIONAL_INLINE
        const const_iterator&
        operator -= (
            difference_type offset
        )
        noexcept;

        // Friends ------------------------------------------------------------

        CMP_CONDITIONAL_INLINE
        CMP_LIBRARY_NAME
        friend
        const_iterator
        operator + (
            const const_iterator& iterator,
            difference_type offset
        )
        noexcept;

        CMP_CONDITIONAL_INLINE
        CMP_LIBRARY_NAME
        friend
        const_iterator
        operator + (
            difference_type offset,
            const const_iterator& iterator
        )
        noexcept;

        CMP_CONDITIONAL_INLINE
        CMP_LIBRARY_NAME
        friend
        const_iterator
        operator - (
            const const_iterator& iterator,
            difference_type offset
        )
        noexcept;

        CMP_CONDITIONAL_INLINE
        CMP_LIBRARY_NAME
        friend
        const_iterator
        operator - (
            difference_type offset,
            const const_iterator& iterator
        )
        noexcept;

        CMP_CONDITIONAL_INLINE
        CMP_LIBRARY_NAME
        friend
        bool
        operator == (
            const const_iterator& iterator1,
            const const_iterator& iterator2
        )
        noexcept;

        CMP_CONDITIONAL_INLINE
        CMP_LIBRARY_NAME
        friend
        bool
        operator != (
            const const_iterator& iterator1,
            const const_iterator& iterator2
        )
        noexcept;

    private:
        // Private Data -------------------------------------------------------

        std::string_view::const_iterator m_current_iterator;
        std::string_view::const_iterator m_end_iterator;
    }; // class ---------------------------------------------------------------

    using iterator = const_iterator;

    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    using reverse_iterator = const_reverse_iterator;

    // Constructors and Destructor --------------------------------------------

    CMP_CONDITIONAL_INLINE
    by_code_point ()
    noexcept = default;

    /**
        Description:
            Constructs a <#type>by_code_point</#type> from the given string.

        Parameters:
            string_to_iterate:
                The string to iterate over by code point.
    */
    CMP_CONDITIONAL_INLINE
    explicit
    by_code_point (
        std::string_view string_to_iterate
    )
    noexcept;

    CMP_CONDITIONAL_INLINE
    ~by_code_point ()
    = default;

    // Copy Operations --------------------------------------------------------

    /**
        Description:
            Copy-constructs a <#type>by_code_point</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>by_code_point</#type> to copy from.
    */
    CMP_CONDITIONAL_INLINE
    by_code_point (
        const by_code_point& other
    )
    = default;

    /**
        Description:
            Copy-assigns a <#type>by_code_point</#type> into <#this/> one.

        Parameters:
            other:
                The <#type>by_code_point</#type> to copy from.
    */
    CMP_CONDITIONAL_INLINE
    by_code_point&
    operator = (
        const by_code_point& other
    )
    = default;

    // Move Operations --------------------------------------------------------

    /**
        Description:
            Move-constructs a <#type>by_code_point</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>by_code_point</#type> to move from.
    */
    CMP_CONDITIONAL_INLINE
    by_code_point (
        by_code_point&& other
    )
    noexcept = default;

    /**
        Description:
            Move-assigns a <#type>by_code_point</#type> into <#this/> one.

        Parameters:
            other:
                The <#type>by_code_point</#type> to move from.
    */
    CMP_CONDITIONAL_INLINE
    by_code_point&
    operator = (
        by_code_point&& other
    )
    noexcept = default;

    // Core -------------------------------------------------------------------

    /**
        Description:
            Returns a constant iterator to the beginning.
    */
    CMP_CONDITIONAL_INLINE
    const_iterator
    begin ()
    const noexcept;

    /**
        Description:
            Returns a constant iterator to the end.
    */
    CMP_CONDITIONAL_INLINE
    const_iterator
    end ()
    const noexcept;

    /**
        Description:
            Returns a constant iterator to the beginning.
    */
    CMP_CONDITIONAL_INLINE
    const_iterator
    cbegin ()
    const noexcept;

    /**
        Description:
            Returns a constant iterator to the end.
    */
    CMP_CONDITIONAL_INLINE
    const_iterator
    cend ()
    const noexcept;

    /**
        Description:
            Returns a constant reverse iterator to the beginning.
    */
    CMP_CONDITIONAL_INLINE
    const_reverse_iterator
    crbegin ()
    const noexcept;

    /**
        Description:
            Returns a constant reverse iterator to the end.
    */
    CMP_CONDITIONAL_INLINE
    const_reverse_iterator
    crend ()
    const noexcept;

private:
    // Private Data -----------------------------------------------------------

    std::string_view::const_iterator m_begin_iterator;
    std::string_view::const_iterator m_end_iterator;
}; // class -------------------------------------------------------------------

template <>
class CMP_LIBRARY_NAME by_code_point<char8_t> {
public:
    // Types ------------------------------------------------------------------

    class CMP_LIBRARY_NAME const_iterator {
    public:
        // Types --------------------------------------------------------------

        using difference_type = std::ptrdiff_t;

        using value_type = char32_t;

        class CMP_LIBRARY_NAME reference {
        public:
            // Constructors and Destructor ------------------------------------

            CMP_CONDITIONAL_INLINE
            reference (
                std::u8string_view::const_iterator initial_current_iterator,
                std::u8string_view::const_iterator initial_end_iterator
            )
            noexcept;

            CMP_CONDITIONAL_INLINE
            ~reference ()
            noexcept = default;

            // Operator Overloads ---------------------------------------------

            CMP_CONDITIONAL_INLINE
            operator char32_t ()
            const;

        private:
            // Private Data ---------------------------------------------------

            std::u8string_view::const_iterator m_current_iterator;
            std::u8string_view::const_iterator m_end_iterator;

            // Private Functions ----------------------------------------------

            CMP_CONDITIONAL_INLINE
            char32_t
            finish_sequence (
                int sequence_length,
                char32_t initial_code_point_value,
                std::u8string_view::const_iterator i
            )
            const;
        }; // class -----------------------------------------------------------

        using iterator_category = std::bidirectional_iterator_tag;

        using iterator_concept = std::bidirectional_iterator_tag;

        // Constructors and Destructor ----------------------------------------

        CMP_CONDITIONAL_INLINE
        const_iterator ()
        noexcept = default;

        CMP_CONDITIONAL_INLINE
        const_iterator (
            std::u8string_view::const_iterator initial_current_iterator,
            std::u8string_view::const_iterator initial_end_iterator
        )
        noexcept;

        CMP_CONDITIONAL_INLINE
        ~const_iterator ()
        = default;

        // Copy Operations ----------------------------------------------------

        CMP_CONDITIONAL_INLINE
        const_iterator (
            const const_iterator& other
        )
        = default;

        CMP_CONDITIONAL_INLINE
        const_iterator&
        operator = (
            const const_iterator& other
        )
        = default;

        // Move Operations ----------------------------------------------------

        CMP_CONDITIONAL_INLINE
        const_iterator (
            const_iterator&& other
        )
        noexcept = default;

        CMP_CONDITIONAL_INLINE
        const_iterator&
        operator = (
            const_iterator&& other
        )
        noexcept = default;

        // Operator Overloads -------------------------------------------------

        CMP_CONDITIONAL_INLINE
        reference
        operator * ()
        const;

        CMP_CONDITIONAL_INLINE
        const_iterator&
        operator ++ ();

        CMP_CONDITIONAL_INLINE
        const_iterator
        operator ++ (
            int
        );

        CMP_CONDITIONAL_INLINE
        const const_iterator&
        operator += (
            difference_type offset
        );

        CMP_CONDITIONAL_INLINE
        const_iterator&
        operator -- ()
        noexcept;

        CMP_CONDITIONAL_INLINE
        const_iterator
        operator -- (
            int
        )
        noexcept;

        CMP_CONDITIONAL_INLINE
        const const_iterator&
        operator -= (
            difference_type offset
        )
        noexcept;

        // Friends ------------------------------------------------------------

        CMP_CONDITIONAL_INLINE
        CMP_LIBRARY_NAME
        friend
        const_iterator
        operator + (
            const const_iterator& iterator,
            difference_type offset
        )
        noexcept;

        CMP_CONDITIONAL_INLINE
        CMP_LIBRARY_NAME
        friend
        const_iterator
        operator + (
            difference_type offset,
            const const_iterator& iterator
        )
        noexcept;

        CMP_CONDITIONAL_INLINE
        CMP_LIBRARY_NAME
        friend
        const_iterator
        operator - (
            const const_iterator& iterator,
            difference_type offset
        )
        noexcept;

        CMP_CONDITIONAL_INLINE
        CMP_LIBRARY_NAME
        friend
        const_iterator
        operator - (
            difference_type offset,
            const const_iterator& iterator
        )
        noexcept;

        CMP_CONDITIONAL_INLINE
        CMP_LIBRARY_NAME
        friend
        bool
        operator == (
            const const_iterator& iterator1,
            const const_iterator& iterator2
        )
        noexcept;

        CMP_CONDITIONAL_INLINE
        CMP_LIBRARY_NAME
        friend
        bool
        operator != (
            const const_iterator& iterator1,
            const const_iterator& iterator2
        )
        noexcept;

    private:
        // Private Data -------------------------------------------------------

        std::u8string_view::const_iterator m_current_iterator;
        std::u8string_view::const_iterator m_end_iterator;

        // Private Functions --------------------------------------------------

        CMP_CONDITIONAL_INLINE
        char32_t
        finish_sequence (
            int sequence_length,
            char32_t initial_code_point_value,
            std::u8string_view::const_iterator i
        )
        const;

        CMP_CONDITIONAL_INLINE
        char32_t
        finish_sequence (
            int sequence_length,
            char32_t initial_code_point_value,
            std::u8string_view::const_iterator& i
        );

        CMP_CONDITIONAL_INLINE
        void
        advance ();

        CMP_CONDITIONAL_INLINE
        void
        advance (
            difference_type offset
        );

        CMP_CONDITIONAL_INLINE
        void
        retreat ();

        CMP_CONDITIONAL_INLINE
        void
        retreat (
            difference_type offset
        );
    }; // class ---------------------------------------------------------------

    using iterator = const_iterator;

    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    using reverse_iterator = const_reverse_iterator;

    // Constructors and Destructor --------------------------------------------

    CMP_CONDITIONAL_INLINE
    by_code_point ()
    noexcept = default;

    /**
        Description:
            Constructs a <#type>by_code_point</#type> from the given string.

        Parameters:
            string_to_iterate:
                The string to iterate over by code point.
    */
    CMP_CONDITIONAL_INLINE
    explicit
    by_code_point (
        std::u8string_view string_to_iterate
    )
    noexcept;

    CMP_CONDITIONAL_INLINE
    ~by_code_point ()
    = default;

    // Copy Operations --------------------------------------------------------

    /**
        Description:
            Copy-constructs a <#type>by_code_point</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>by_code_point</#type> to copy from.
    */
    CMP_CONDITIONAL_INLINE
    by_code_point (
        const by_code_point& other
    )
    = default;

    /**
        Description:
            Copy-assigns a <#type>by_code_point</#type> into <#this/> one.

        Parameters:
            other:
                The <#type>by_code_point</#type> to copy from.
    */
    CMP_CONDITIONAL_INLINE
    by_code_point&
    operator = (
        const by_code_point& other
    )
    = default;

    // Move Operations --------------------------------------------------------

    /**
        Description:
            Move-constructs a <#type>by_code_point</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>by_code_point</#type> to move from.
    */
    CMP_CONDITIONAL_INLINE
    by_code_point (
        by_code_point&& other
    )
    noexcept = default;

    /**
        Description:
            Move-assigns a <#type>by_code_point</#type> into <#this/> one.

        Parameters:
            other:
                The <#type>by_code_point</#type> to move from.
    */
    CMP_CONDITIONAL_INLINE
    by_code_point&
    operator = (
        by_code_point&& other
    )
    noexcept = default;

    // Core -------------------------------------------------------------------

    /**
        Description:
            Returns a constant iterator to the beginning.
    */
    CMP_CONDITIONAL_INLINE
    const_iterator
    begin ()
    const noexcept;

    /**
        Description:
            Returns a constant iterator to the end.
    */
    CMP_CONDITIONAL_INLINE
    const_iterator
    end ()
    const noexcept;

    /**
        Description:
            Returns a constant iterator to the beginning.
    */
    CMP_CONDITIONAL_INLINE
    const_iterator
    cbegin ()
    const noexcept;

    /**
        Description:
            Returns a constant iterator to the end.
    */
    CMP_CONDITIONAL_INLINE
    const_iterator
    cend ()
    const noexcept;

    /**
        Description:
            Returns a constant reverse iterator to the beginning.
    */
    CMP_CONDITIONAL_INLINE
    const_reverse_iterator
    crbegin ()
    const noexcept;

    /**
        Description:
            Returns a constant reverse iterator to the end.
    */
    CMP_CONDITIONAL_INLINE
    const_reverse_iterator
    crend ()
    const noexcept;

private:
    // Private Data -----------------------------------------------------------

    std::u8string_view::const_iterator m_begin_iterator;
    std::u8string_view::const_iterator m_end_iterator;
}; // class -------------------------------------------------------------------

template <>
class CMP_LIBRARY_NAME by_code_point<char16_t> {
public:
    // Types ------------------------------------------------------------------

    class CMP_LIBRARY_NAME const_iterator {
    public:
        // Types --------------------------------------------------------------

        using difference_type = std::ptrdiff_t;

        using value_type = char32_t;

        class CMP_LIBRARY_NAME reference {
        public:
            // Constructors and Destructor ------------------------------------

            CMP_CONDITIONAL_INLINE
            explicit
            reference (
                std::u16string_view::const_iterator initial_current_iterator,
                std::u16string_view::const_iterator initial_end_iterator
            )
            noexcept;

            CMP_CONDITIONAL_INLINE
            ~reference ()
            noexcept = default;

            // Operator Overloads ---------------------------------------------

            CMP_CONDITIONAL_INLINE
            operator char32_t ()
            const;

        private:
            // Private Data ---------------------------------------------------

            std::u16string_view::const_iterator m_current_iterator;
            std::u16string_view::const_iterator m_end_iterator;

            // Private Functions ----------------------------------------------

            CMP_CONDITIONAL_INLINE
            char32_t
            finish_sequence (
                int sequence_length,
                char32_t initial_code_point_value,
                std::u16string_view::const_iterator i
            )
            const;
        }; // class -----------------------------------------------------------

        using iterator_category = std::bidirectional_iterator_tag;

        using iterator_concept = std::bidirectional_iterator_tag;

        // Constructors and Destructor ----------------------------------------

        CMP_CONDITIONAL_INLINE
        const_iterator ()
        noexcept = default;

        CMP_CONDITIONAL_INLINE
        const_iterator (
            std::u16string_view::const_iterator initial_current_iterator,
            std::u16string_view::const_iterator initial_end_iterator
        )
        noexcept;

        CMP_CONDITIONAL_INLINE
        ~const_iterator ()
        = default;

        // Copy Operations ----------------------------------------------------

        CMP_CONDITIONAL_INLINE
        const_iterator (
            const const_iterator& other
        )
        = default;

        CMP_CONDITIONAL_INLINE
        const_iterator&
        operator = (
            const const_iterator& other
        )
        = default;

        // Move Operations ----------------------------------------------------

        CMP_CONDITIONAL_INLINE
        const_iterator (
            const_iterator&& other
        )
        noexcept = default;

        CMP_CONDITIONAL_INLINE
        const_iterator&
        operator = (
            const_iterator&& other
        )
        noexcept = default;

        // Operator Overloads -------------------------------------------------

        CMP_CONDITIONAL_INLINE
        reference
        operator * ()
        const;

        CMP_CONDITIONAL_INLINE
        const_iterator&
        operator ++ ();

        CMP_CONDITIONAL_INLINE
        const_iterator
        operator ++ (
            int
        );

        CMP_CONDITIONAL_INLINE
        const const_iterator&
        operator += (
            difference_type offset
        );

        CMP_CONDITIONAL_INLINE
        const_iterator&
        operator -- ()
        noexcept;

        CMP_CONDITIONAL_INLINE
        const_iterator
        operator -- (
            int
        )
        noexcept;

        CMP_CONDITIONAL_INLINE
        const const_iterator&
        operator -= (
            difference_type offset
        )
        noexcept;

        // Friends ------------------------------------------------------------

        CMP_CONDITIONAL_INLINE
        CMP_LIBRARY_NAME
        friend
        const_iterator
        operator + (
            const const_iterator& iterator,
            difference_type offset
        )
        noexcept;

        CMP_CONDITIONAL_INLINE
        CMP_LIBRARY_NAME
        friend
        const_iterator
        operator + (
            difference_type offset,
            const const_iterator& iterator
        )
        noexcept;

        CMP_CONDITIONAL_INLINE
        CMP_LIBRARY_NAME
        friend
        const_iterator
        operator - (
            const const_iterator& iterator,
            difference_type offset
        )
        noexcept;

        CMP_CONDITIONAL_INLINE
        CMP_LIBRARY_NAME
        friend
        const_iterator
        operator - (
            difference_type offset,
            const const_iterator& iterator
        )
        noexcept;

        CMP_CONDITIONAL_INLINE
        CMP_LIBRARY_NAME
        friend
        bool
        operator == (
            const const_iterator& iterator1,
            const const_iterator& iterator2
        )
        noexcept;

        CMP_CONDITIONAL_INLINE
        CMP_LIBRARY_NAME
        friend
        bool
        operator != (
            const const_iterator& iterator1,
            const const_iterator& iterator2
        )
        noexcept;

    private:
        // Private Data -------------------------------------------------------

        std::u16string_view::const_iterator m_current_iterator;
        std::u16string_view::const_iterator m_end_iterator;

        // Private Functions --------------------------------------------------

        CMP_CONDITIONAL_INLINE
        char32_t
        finish_sequence (
            int sequence_length,
            char32_t initial_code_point_value,
            std::u16string_view::const_iterator i
        )
        const;

        CMP_CONDITIONAL_INLINE
        char32_t
        finish_sequence (
            int sequence_length,
            char32_t initial_code_point_value,
            std::u16string_view::const_iterator& i
        );

        CMP_CONDITIONAL_INLINE
        void
        advance ();

        CMP_CONDITIONAL_INLINE
        void
        advance (
            difference_type offset
        );

        CMP_CONDITIONAL_INLINE
        void
        retreat ();

        CMP_CONDITIONAL_INLINE
        void
        retreat (
            difference_type offset
        );
    }; // class ---------------------------------------------------------------

    using iterator = const_iterator;

    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    using reverse_iterator = const_reverse_iterator;

    // Constructors and Destructor --------------------------------------------

    CMP_CONDITIONAL_INLINE
    by_code_point ()
    noexcept = default;

    /**
        Description:
            Constructs a <#type>by_code_point</#type> from the given string.

        Parameters:
            string_to_iterate:
                The string to iterate over by code point.
    */
    CMP_CONDITIONAL_INLINE
    explicit
    by_code_point (
        std::u16string_view string_to_iterate
    )
    noexcept;

    CMP_CONDITIONAL_INLINE
    ~by_code_point ()
    = default;

    // Copy Operations --------------------------------------------------------

    /**
        Description:
            Copy-constructs a <#type>by_code_point</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>by_code_point</#type> to copy from.
    */
    CMP_CONDITIONAL_INLINE
    by_code_point (
        const by_code_point& other
    )
    = default;

    /**
        Description:
            Copy-assigns a <#type>by_code_point</#type> into <#this/> one.

        Parameters:
            other:
                The <#type>by_code_point</#type> to copy from.
    */
    CMP_CONDITIONAL_INLINE
    by_code_point&
    operator = (
        const by_code_point& other
    )
    = default;

    // Move Operations --------------------------------------------------------

    /**
        Description:
            Move-constructs a <#type>by_code_point</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>by_code_point</#type> to move from.
    */
    CMP_CONDITIONAL_INLINE
    by_code_point (
        by_code_point&& other
    )
    noexcept = default;

    /**
        Description:
            Move-assigns a <#type>by_code_point</#type> into <#this/> one.

        Parameters:
            other:
                The <#type>by_code_point</#type> to move from.
    */
    CMP_CONDITIONAL_INLINE
    by_code_point&
    operator = (
        by_code_point&& other
    )
    noexcept = default;

    // Core -------------------------------------------------------------------

    /**
        Description:
            Returns a constant iterator to the beginning.
    */
    CMP_CONDITIONAL_INLINE
    const_iterator
    begin ()
    const noexcept;

    /**
        Description:
            Returns a constant iterator to the end.
    */
    CMP_CONDITIONAL_INLINE
    const_iterator
    end ()
    const noexcept;

    /**
        Description:
            Returns a constant iterator to the beginning.
    */
    CMP_CONDITIONAL_INLINE
    const_iterator
    cbegin ()
    const noexcept;

    /**
        Description:
            Returns a constant iterator to the end.
    */
    CMP_CONDITIONAL_INLINE
    const_iterator
    cend ()
    const noexcept;

    /**
        Description:
            Returns a constant reverse iterator to the beginning.
    */
    CMP_CONDITIONAL_INLINE
    const_reverse_iterator
    crbegin ()
    const noexcept;

    /**
        Description:
            Returns a constant reverse iterator to the end.
    */
    CMP_CONDITIONAL_INLINE
    const_reverse_iterator
    crend ()
    const noexcept;

private:
    // Private Data -----------------------------------------------------------

    std::u16string_view::const_iterator m_begin_iterator;
    std::u16string_view::const_iterator m_end_iterator;
}; // class -------------------------------------------------------------------

template <>
class CMP_LIBRARY_NAME by_code_point<char32_t> {
public:
    // Types ------------------------------------------------------------------

    class CMP_LIBRARY_NAME const_iterator {
    public:
        // Types --------------------------------------------------------------

        using difference_type = std::ptrdiff_t;

        using value_type = char32_t;

        using reference = std::iterator_traits<
            std::u32string_view::const_iterator
        >::reference;

        using iterator_category = std::bidirectional_iterator_tag;

        using iterator_concept = std::bidirectional_iterator_tag;

        // Constructors and Destructor ----------------------------------------

        CMP_CONDITIONAL_INLINE
        const_iterator ()
        noexcept = default;

        CMP_CONDITIONAL_INLINE
        const_iterator (
            std::u32string_view::const_iterator initial_current_iterator,
            std::u32string_view::const_iterator initial_end_iterator
        )
        noexcept;

        CMP_CONDITIONAL_INLINE
        ~const_iterator ()
        = default;

        // Copy Operations ----------------------------------------------------

        CMP_CONDITIONAL_INLINE
        const_iterator (
            const const_iterator& other
        )
        = default;

        CMP_CONDITIONAL_INLINE
        const_iterator&
        operator = (
            const const_iterator& other
        )
        = default;

        // Move Operations ----------------------------------------------------

        CMP_CONDITIONAL_INLINE
        const_iterator (
            const_iterator&& other
        )
        noexcept = default;

        CMP_CONDITIONAL_INLINE
        const_iterator&
        operator = (
            const_iterator&& other
        )
        noexcept = default;

        // Operator Overloads -------------------------------------------------

        CMP_CONDITIONAL_INLINE
        reference
        operator * ()
        const;

        CMP_CONDITIONAL_INLINE
        const_iterator&
        operator ++ ();

        CMP_CONDITIONAL_INLINE
        const_iterator
        operator ++ (
            int
        );

        CMP_CONDITIONAL_INLINE
        const const_iterator&
        operator += (
            difference_type offset
        );

        CMP_CONDITIONAL_INLINE
        const_iterator&
        operator -- ()
        noexcept;

        CMP_CONDITIONAL_INLINE
        const_iterator
        operator -- (
            int
        )
        noexcept;

        CMP_CONDITIONAL_INLINE
        const const_iterator&
        operator -= (
            difference_type offset
        )
        noexcept;

        // Friends ------------------------------------------------------------

        CMP_CONDITIONAL_INLINE
        CMP_LIBRARY_NAME
        friend
        const_iterator
        operator + (
            const const_iterator& iterator,
            difference_type offset
        )
        noexcept;

        CMP_CONDITIONAL_INLINE
        CMP_LIBRARY_NAME
        friend
        const_iterator
        operator + (
            difference_type offset,
            const const_iterator& iterator
        )
        noexcept;

        CMP_CONDITIONAL_INLINE
        CMP_LIBRARY_NAME
        friend
        const_iterator
        operator - (
            const const_iterator& iterator,
            difference_type offset
        )
        noexcept;

        CMP_CONDITIONAL_INLINE
        CMP_LIBRARY_NAME
        friend
        const_iterator
        operator - (
            difference_type offset,
            const const_iterator& iterator
        )
        noexcept;

        CMP_CONDITIONAL_INLINE
        CMP_LIBRARY_NAME
        friend
        bool
        operator == (
            const const_iterator& iterator1,
            const const_iterator& iterator2
        )
        noexcept;

        CMP_CONDITIONAL_INLINE
        CMP_LIBRARY_NAME
        friend
        bool
        operator != (
            const const_iterator& iterator1,
            const const_iterator& iterator2
        )
        noexcept;

    private:
        // Private Data -------------------------------------------------------

        std::u32string_view::const_iterator m_current_iterator;
        std::u32string_view::const_iterator m_end_iterator;
    }; // class ---------------------------------------------------------------

    using iterator = const_iterator;

    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    using reverse_iterator = const_reverse_iterator;

    // Constructors and Destructor --------------------------------------------

    CMP_CONDITIONAL_INLINE
    by_code_point ()
    noexcept = default;

    /**
        Description:
            Constructs a <#type>by_code_point</#type> from the given string.

        Parameters:
            string_to_iterate:
                The string to iterate over by code point.
    */
    CMP_CONDITIONAL_INLINE
    explicit
    by_code_point (
        std::u32string_view string_to_iterate
    )
    noexcept;

    CMP_CONDITIONAL_INLINE
    ~by_code_point ()
    = default;

    // Copy Operations --------------------------------------------------------

    /**
        Description:
            Copy-constructs a <#type>by_code_point</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>by_code_point</#type> to copy from.
    */
    CMP_CONDITIONAL_INLINE
    by_code_point (
        const by_code_point& other
    )
    = default;

    /**
        Description:
            Copy-assigns a <#type>by_code_point</#type> into <#this/> one.

        Parameters:
            other:
                The <#type>by_code_point</#type> to copy from.
    */
    CMP_CONDITIONAL_INLINE
    by_code_point&
    operator = (
        const by_code_point& other
    )
    = default;

    // Move Operations --------------------------------------------------------

    /**
        Description:
            Move-constructs a <#type>by_code_point</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>by_code_point</#type> to move from.
    */
    CMP_CONDITIONAL_INLINE
    by_code_point (
        by_code_point&& other
    )
    noexcept = default;

    /**
        Description:
            Move-assigns a <#type>by_code_point</#type> into <#this/> one.

        Parameters:
            other:
                The <#type>by_code_point</#type> to move from.
    */
    CMP_CONDITIONAL_INLINE
    by_code_point&
    operator = (
        by_code_point&& other
    )
    noexcept = default;

    // Core -------------------------------------------------------------------

    /**
        Description:
            Returns a constant iterator to the beginning.
    */
    CMP_CONDITIONAL_INLINE
    const_iterator
    begin ()
    const noexcept;

    /**
        Description:
            Returns a constant iterator to the end.
    */
    CMP_CONDITIONAL_INLINE
    const_iterator
    end ()
    const noexcept;

    /**
        Description:
            Returns a constant iterator to the beginning.
    */
    CMP_CONDITIONAL_INLINE
    const_iterator
    cbegin ()
    const noexcept;

    /**
        Description:
            Returns a constant iterator to the end.
    */
    CMP_CONDITIONAL_INLINE
    const_iterator
    cend ()
    const noexcept;

    /**
        Description:
            Returns a constant reverse iterator to the beginning.
    */
    CMP_CONDITIONAL_INLINE
    const_reverse_iterator
    crbegin ()
    const noexcept;

    /**
        Description:
            Returns a constant reverse iterator to the end.
    */
    CMP_CONDITIONAL_INLINE
    const_reverse_iterator
    crend ()
    const noexcept;

private:
    // Private Data -----------------------------------------------------------

    std::u32string_view::const_iterator m_begin_iterator;
    std::u32string_view::const_iterator m_end_iterator;
}; // class -------------------------------------------------------------------

template <>
class CMP_LIBRARY_NAME by_code_point<wchar_t> {
public:
    // Types ------------------------------------------------------------------

    class CMP_LIBRARY_NAME const_iterator {
    public:
        // Types --------------------------------------------------------------

        using difference_type = std::ptrdiff_t;

        using value_type = char32_t;

        class CMP_LIBRARY_NAME reference {
        public:
            // Constructors and Destructor ------------------------------------

            CMP_CONDITIONAL_INLINE
            explicit
            reference (
                std::wstring_view::const_iterator initial_current_iterator,
                std::wstring_view::const_iterator initial_end_iterator
            )
            noexcept;

            CMP_CONDITIONAL_INLINE
            ~reference ()
            noexcept = default;

            // Operator Overloads ---------------------------------------------

            CMP_CONDITIONAL_INLINE
            operator char32_t ()
            const;

        private:
            // Private Data ---------------------------------------------------

            std::wstring_view::const_iterator m_current_iterator;
            std::wstring_view::const_iterator m_end_iterator;

            // Private Functions ----------------------------------------------

            CMP_CONDITIONAL_INLINE
            char32_t
            finish_sequence (
                int sequence_length,
                char32_t initial_code_point_value,
                std::wstring_view::const_iterator i
            )
            const;
        }; // class -----------------------------------------------------------

        using iterator_category = std::bidirectional_iterator_tag;

        using iterator_concept = std::bidirectional_iterator_tag;

        // Constructors and Destructor ----------------------------------------

        CMP_CONDITIONAL_INLINE
        const_iterator ()
        noexcept = default;

        CMP_CONDITIONAL_INLINE
        const_iterator (
            std::wstring_view::const_iterator initial_current_iterator,
            std::wstring_view::const_iterator initial_end_iterator
        )
        noexcept;

        CMP_CONDITIONAL_INLINE
        ~const_iterator ()
        = default;

        // Copy Operations ----------------------------------------------------

        CMP_CONDITIONAL_INLINE
        const_iterator (
            const const_iterator& other
        )
        = default;

        CMP_CONDITIONAL_INLINE
        const_iterator&
        operator = (
            const const_iterator& other
        )
        = default;

        // Move Operations ----------------------------------------------------

        CMP_CONDITIONAL_INLINE
        const_iterator (
            const_iterator&& other
        )
        noexcept = default;

        CMP_CONDITIONAL_INLINE
        const_iterator&
        operator = (
            const_iterator&& other
        )
        noexcept = default;

        // Operator Overloads -------------------------------------------------

        CMP_CONDITIONAL_INLINE
        reference
        operator * ()
        const;

        CMP_CONDITIONAL_INLINE
        const_iterator&
        operator ++ ();

        CMP_CONDITIONAL_INLINE
        const_iterator
        operator ++ (
            int
        );

        CMP_CONDITIONAL_INLINE
        const const_iterator&
        operator += (
            difference_type offset
        );

        CMP_CONDITIONAL_INLINE
        const_iterator&
        operator -- ()
        noexcept;

        CMP_CONDITIONAL_INLINE
        const_iterator
        operator -- (
            int
        )
        noexcept;

        CMP_CONDITIONAL_INLINE
        const const_iterator&
        operator -= (
            difference_type offset
        )
        noexcept;

        // Friends ------------------------------------------------------------

        CMP_CONDITIONAL_INLINE
        CMP_LIBRARY_NAME
        friend
        const_iterator
        operator + (
            const const_iterator& iterator,
            difference_type offset
        )
        noexcept;

        CMP_CONDITIONAL_INLINE
        CMP_LIBRARY_NAME
        friend
        const_iterator
        operator + (
            difference_type offset,
            const const_iterator& iterator
        )
        noexcept;

        CMP_CONDITIONAL_INLINE
        CMP_LIBRARY_NAME
        friend
        const_iterator
        operator - (
            const const_iterator& iterator,
            difference_type offset
        )
        noexcept;

        CMP_CONDITIONAL_INLINE
        CMP_LIBRARY_NAME
        friend
        const_iterator
        operator - (
            difference_type offset,
            const const_iterator& iterator
        )
        noexcept;

        CMP_CONDITIONAL_INLINE
        CMP_LIBRARY_NAME
        friend
        bool
        operator == (
            const const_iterator& iterator1,
            const const_iterator& iterator2
        )
        noexcept;

        CMP_CONDITIONAL_INLINE
        CMP_LIBRARY_NAME
        friend
        bool
        operator != (
            const const_iterator& iterator1,
            const const_iterator& iterator2
        )
        noexcept;

    private:
        // Private Data -------------------------------------------------------

        std::wstring_view::const_iterator m_current_iterator;
        std::wstring_view::const_iterator m_end_iterator;

        // Private Functions --------------------------------------------------

        CMP_CONDITIONAL_INLINE
        char32_t
        finish_sequence (
            int sequence_length,
            char32_t initial_code_point_value,
            std::wstring_view::const_iterator i
        )
        const;

        CMP_CONDITIONAL_INLINE
        char32_t
        finish_sequence (
            int sequence_length,
            char32_t initial_code_point_value,
            std::wstring_view::const_iterator& i
        );

        CMP_CONDITIONAL_INLINE
        void
        advance ();

        CMP_CONDITIONAL_INLINE
        void
        advance (
            difference_type offset
        );

        CMP_CONDITIONAL_INLINE
        void
        retreat ();

        CMP_CONDITIONAL_INLINE
        void
        retreat (
            difference_type offset
        );
    }; // class ---------------------------------------------------------------

    using iterator = const_iterator;

    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    using reverse_iterator = const_reverse_iterator;

    // Constructors and Destructor --------------------------------------------

    CMP_CONDITIONAL_INLINE
    by_code_point ()
    noexcept = default;

    /**
        Description:
            Constructs a <#type>by_code_point</#type> from the given string.

        Parameters:
            string_to_iterate:
                The string to iterate over by code point.
    */
    CMP_CONDITIONAL_INLINE
    explicit
    by_code_point (
        std::wstring_view string_to_iterate
    )
    noexcept;

    CMP_CONDITIONAL_INLINE
    ~by_code_point ()
    = default;

    // Copy Operations --------------------------------------------------------

    /**
        Description:
            Copy-constructs a <#type>by_code_point</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>by_code_point</#type> to copy from.
    */
    CMP_CONDITIONAL_INLINE
    by_code_point (
        const by_code_point& other
    )
    = default;

    /**
        Description:
            Copy-assigns a <#type>by_code_point</#type> into <#this/> one.

        Parameters:
            other:
                The <#type>by_code_point</#type> to copy from.
    */
    CMP_CONDITIONAL_INLINE
    by_code_point&
    operator = (
        const by_code_point& other
    )
    = default;

    // Move Operations --------------------------------------------------------

    /**
        Description:
            Move-constructs a <#type>by_code_point</#type>
            from an existing one.

        Parameters:
            other:
                The <#type>by_code_point</#type> to move from.
    */
    CMP_CONDITIONAL_INLINE
    by_code_point (
        by_code_point&& other
    )
    noexcept = default;

    /**
        Description:
            Move-assigns a <#type>by_code_point</#type> into <#this/> one.

        Parameters:
            other:
                The <#type>by_code_point</#type> to move from.
    */
    CMP_CONDITIONAL_INLINE
    by_code_point&
    operator = (
        by_code_point&& other
    )
    noexcept = default;

    // Core -------------------------------------------------------------------

    /**
        Description:
            Returns a constant iterator to the beginning.
    */
    CMP_CONDITIONAL_INLINE
    const_iterator
    begin ()
    const noexcept;

    /**
        Description:
            Returns a constant iterator to the end.
    */
    CMP_CONDITIONAL_INLINE
    const_iterator
    end ()
    const noexcept;

    /**
        Description:
            Returns a constant iterator to the beginning.
    */
    CMP_CONDITIONAL_INLINE
    const_iterator
    cbegin ()
    const noexcept;

    /**
        Description:
            Returns a constant iterator to the end.
    */
    CMP_CONDITIONAL_INLINE
    const_iterator
    cend ()
    const noexcept;

    /**
        Description:
            Returns a constant reverse iterator to the beginning.
    */
    CMP_CONDITIONAL_INLINE
    const_reverse_iterator
    crbegin ()
    const noexcept;

    /**
        Description:
            Returns a constant reverse iterator to the end.
    */
    CMP_CONDITIONAL_INLINE
    const_reverse_iterator
    crend ()
    const noexcept;

private:
    // Private Data -----------------------------------------------------------

    std::wstring_view::const_iterator m_begin_iterator;
    std::wstring_view::const_iterator m_end_iterator;
}; // class -------------------------------------------------------------------

by_code_point(std::string_view) -> by_code_point<char>;
by_code_point(std::u8string_view) -> by_code_point<char8_t>;
by_code_point(std::u16string_view) -> by_code_point<char16_t>;
by_code_point(std::u32string_view) -> by_code_point<char32_t>;
by_code_point(std::wstring_view) -> by_code_point<wchar_t>;

} // namespace ----------------------------------------------------------------

template <>
inline constexpr bool
std::ranges::enable_view<cmp::by_code_point<char>>
    = true;

template <>
inline constexpr bool
std::ranges::enable_borrowed_range<cmp::by_code_point<char>>
    = true;

template <>
inline constexpr bool
std::ranges::enable_view<cmp::by_code_point<char8_t>>
    = true;

template <>
inline constexpr bool
std::ranges::enable_borrowed_range<cmp::by_code_point<char8_t>>
    = true;

template <>
inline constexpr bool
std::ranges::enable_view<cmp::by_code_point<char16_t>>
    = true;

template <>
inline constexpr bool
std::ranges::enable_borrowed_range<cmp::by_code_point<char16_t>>
    = true;

template <>
inline constexpr bool
std::ranges::enable_view<cmp::by_code_point<char32_t>>
    = true;

template <>
inline constexpr bool
std::ranges::enable_borrowed_range<cmp::by_code_point<char32_t>>
    = true;

template <>
inline constexpr bool
std::ranges::enable_view<cmp::by_code_point<wchar_t>>
    = true;

template <>
inline constexpr bool
std::ranges::enable_borrowed_range<cmp::by_code_point<wchar_t>>
    = true;

#if CMP_CONFIG_HEADER_ONLY == true
#   include <cmp/unicode/by_code_point.cpp>
#endif // CMP_CONFIG_HEADER_ONLY

#endif // CMP_UNICODE_BY_CODE_POINT_HPP_INCLUDED
