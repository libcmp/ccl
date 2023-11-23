// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_IO_IO_BUFFER_HPP_INCLUDED
#define CMP_IO_IO_BUFFER_HPP_INCLUDED

#include <cstring>
#include <vector>

#include <cmp/io/inclusion_assert.hpp>

namespace cmp {

class CMP_LIBRARY_NAME io_buffer {
public:
    // Constants --------------------------------------------------------------

    static constexpr std::size_t default_buffer_capacity{
        CMP_CONFIG_DEFAULT_BUFFER_CAPACITY
    };

    // Constructors and Destructor --------------------------------------------

    /**
        Description:
            Constructs an I/O buffer with the given capacity.

        Parameters:
            buffer_capacity:
                The capacity to use for the I/O buffer.
    */
    CMP_CONDITIONAL_INLINE
    explicit
    io_buffer (
        std::size_t buffer_capacity = default_buffer_capacity
    );

    CMP_CONDITIONAL_INLINE
    ~io_buffer ()
    noexcept = default;

    // Accessors --------------------------------------------------------------

    /**
        Description:
            Returns the capacity of <#this/> I/O buffer.
    */
    CMP_CONDITIONAL_INLINE
    std::size_t
    get_capacity ()
    const noexcept;

    /**
        Description:
            Returns the size of <#this/> I/O buffer.
    */
    CMP_CONDITIONAL_INLINE
    std::size_t
    get_size ()
    const noexcept;

    /**
        Description:
            Sets the size of <#this/> I/O buffer.

        Parameters:
            new_size:
                The new size of <#this/> I/O buffer.
    */
    CMP_CONDITIONAL_INLINE
    void
    set_size (
        std::size_t new_size
    )
    noexcept;

    /**
        Description:
            Returns the position of <#this/> I/O buffer.
    */
    CMP_CONDITIONAL_INLINE
    std::size_t
    get_position ()
    const noexcept;

    /**
        Description:
            Sets the position of <#this/> I/O buffer.

        Parameters:
            new_position:
                The new position of <#this/> I/O buffer.
    */
    CMP_CONDITIONAL_INLINE
    void
    set_position (
        std::size_t new_position
    )
    noexcept;

    /**
        Description:
            Returns a pointer to the beginning of <#this/> I/O buffer's data.
    */
    CMP_CONDITIONAL_INLINE
    std::byte*
    get_data ()
    noexcept;

    /**
        Description:
            Returns true if <#this/> I/O buffer is read-dirty.
            Otherwise, returns false.
    */
    CMP_CONDITIONAL_INLINE
    bool
    is_read_dirty ()
    const noexcept;

    /**
        Description:
            Sets whether <#this/> I/O buffer is read-dirty.

        Parameters:
            new_read_dirty_flag:
                The new read-dirty flag for <#this/> I/O buffer.
    */
    CMP_CONDITIONAL_INLINE
    void
    set_read_dirty (
        bool new_read_dirty_flag
    )
    noexcept;

    /**
        Description:
            Returns true if <#this/> I/O buffer is write-dirty.
            Otherwise, returns false.
    */
    CMP_CONDITIONAL_INLINE
    bool
    is_write_dirty ()
    const noexcept;

    /**
        Description:
            Sets whether <#this/> I/O buffer is write-dirty.

        Parameters:
            new_write_dirty_flag:
                The new write-dirty flag for <#this/> I/O buffer.
    */
    CMP_CONDITIONAL_INLINE
    void
    set_write_dirty (
        bool new_write_dirty_flag
    )
    noexcept;

    // Core -------------------------------------------------------------------

    /**
        Description:
            Reads <#parameter>byte_count</#parameter> bytes
            from <#this/> I/O buffer and places them in the
            provided <#parameter>data</#parameter> array.

        Parameters:
            data:
                The array into which the read bytes will be placed.
            byte_count:
                The number of bytes to read from <#this/> I/O buffer.
    */
    CMP_CONDITIONAL_INLINE
    std::size_t
    read (
        std::byte* data,
        std::size_t byte_count
    );

    /**
        Description:
            Writes <#parameter>byte_count</#parameter> bytes
            from the <#parameter>data</#parameter> array to
            <#this/> I/O buffer.

        Parameters:
            data:
                The array of bytes that will be written to <#this/> I/O buffer.
            byte_count:
                The number of bytes to write to <#this/> I/O buffer.
    */
    CMP_CONDITIONAL_INLINE
    std::size_t
    write (
        const std::byte* data,
        std::size_t byte_count
    );

private:
    // Private Data -----------------------------------------------------------

    std::size_t m_size;
    std::size_t m_position;
    std::vector<std::byte> m_data;
    bool m_read_dirty_flag;
    bool m_write_dirty_flag;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#if CMP_CONFIG_HEADER_ONLY == true
#   include <cmp/io/io_buffer.cpp>
#endif // CMP_CONFIG_HEADER_ONLY

#endif // CMP_IO_IO_BUFFER_HPP_INCLUDED
