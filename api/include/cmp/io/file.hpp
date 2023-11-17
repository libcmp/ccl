// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_IO_FILE_HPP_INCLUDED
#define CMP_IO_FILE_HPP_INCLUDED

#include <filesystem>

#include <cmp/io/inclusion_assert.hpp>
#include <cmp/core/platform.hpp>
#include <cmp/io/exceptions.hpp>
#include <cmp/io/general.hpp>
#include <cmp/io/seekable_io_resource.hpp>

namespace cmp {

/**
    Description:
        The <#type>basic_file</#type> class serves as a base class for
        subclasses that implement the platform-specific code for managing
        files. All platform-specific subclasses of <#type>basic_file</#type>
        are called simply <#type>file</#type> so that code that uses them
        stays the same across all platforms. You generally don't want to
        use this class directly in application code. Rather, you use the
        <#type>file</#type> class to read and write files on all supported
        platforms.
*/
class CMP_LIBRARY_NAME basic_file
    : public seekable_io_resource<std::int64_t>
{
public:
    // Constructors and Destructor --------------------------------------------

    /**
        Description:
            Constructs a <#type>basic_file</#type>
            object not associated with any file.
    */
    CMP_CONDITIONAL_INLINE
    basic_file ()
    noexcept;

    /**
        Description:
            Constructs a <#type>basic_file</#type> object associated
            with the given file path and buffer capacity. No file is
            acquired from the operating system, only the path to the
            file and desired access mode are stored.

        Parameters:
            file_path:
                The file path to store in this basic file.
            mode:
                The access mode to store in this basic file.
            buffer_capacity:
                The capacity of the I/O buffer to associate
                with this <#type>basic_file</#type> object.
    */
    CMP_CONDITIONAL_INLINE
    basic_file (
        const std::filesystem::path& file_path,
        access_mode mode,
        std::size_t buffer_capacity = io_buffer::default_buffer_capacity
    );

    // Accessors --------------------------------------------------------------

    /**
        Description:
            Returns true if the file is open. Otherwise, returns false.

            This functionality is platform-dependent and therefore this
            function must be overridden in a platform-specific subclass.
    */
    CMP_CONDITIONAL_INLINE
    virtual
    bool
    is_open ()
    const noexcept = 0;

    /**
        Description:
            Returns the access mode associated with this basic file.
    */
    CMP_CONDITIONAL_INLINE
    access_mode
    get_access_mode ()
    const noexcept;

    /**
        Description:
            Returns true if the file is at its EOF (end-of-file) position.
            Otherwise, returns false.
    */
    CMP_CONDITIONAL_INLINE
    bool
    is_at_end ()
    const noexcept override;

    // Core -------------------------------------------------------------------

    /**
        Description:
            Opens the file at the given path with the given access mode.
            The last argument tells what to do if the specified file doesn't
            already exists, that is, whether to create the file or fail to
            open it. Returns true if opening the file succeeds. Otherwise,
            returns false.

            This functionality is platform-dependent and therefore this
            function must be overridden in a platform-specific subclass.

        Parameters:
            file_path:
                The path to the file to open.
            mode:
                The access mode to open the file in. This tells whether you
                want to just read, just write or both read and write. This
                cannot be changed later unless you close the file and reopen
                it.
            if_file_not_there:
                The action to take if the specified file does not exist. This
                can be <#enumerator>if_not_there::create</#enumerator>, which
                causes the file to be created, or
                <#enumerator>if_not_there::fail</#enumerator>, which causes
                this function to simply return false without taking any
                action.
    */
    CMP_CONDITIONAL_INLINE
    virtual
    bool
    open (
        const std::filesystem::path& file_path,
        access_mode mode,
        if_not_there if_file_not_there
    )
    noexcept = 0;

    /**
        Description:
            Flushes the I/O buffer and closes the file.

            This functionality is platform-dependent and therefore this
            function must be overridden in a platform-specific subclass.
    */
    CMP_CONDITIONAL_INLINE
    virtual
    void
    close ()
    noexcept = 0;

    /**
        Description:
            Reads <#parameter>byte_count</#parameter> bytes
            from <#this/> file and places them in the provided
            <#parameter>data</#parameter> array.

        Parameters:
            data:
                The array into which the read bytes will be placed.
            byte_count:
                The number of bytes to read from <#this/> file.
    */
    CMP_CONDITIONAL_INLINE
    std::size_t
    read (
        std::byte* data,
        std::size_t byte_count
    )
    override;

    /**
        Description:
            Writes <#parameter>byte_count</#parameter> bytes
            from the <#parameter>data</#parameter> array to
            <#this/> file.

        Parameters:
            data:
                The array of bytes that will be written to <#this/> file.
            byte_count:
                The number of bytes to write to <#this/> file.
    */
    CMP_CONDITIONAL_INLINE
    std::size_t
    write (
        const std::byte* data,
        std::size_t byte_count
    )
    override;

protected:
    // Protected Data ---------------------------------------------------------

    std::filesystem::path m_file_path;
    access_mode m_access_mode;
    std::size_t m_last_fill_amount;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#if CMP_CONFIG_HEADER_ONLY == true
#   include <cmp/io/file.cpp>
#endif // CMP_CONFIG_HEADER_ONLY

#if defined(CMP_OS_WINDOWS)
#   include <cmp/io/impl/windows/windows_file.hpp>
#elif defined(CMP_OS_UNIX_LIKE)
#   include <cmp/io/impl/unix_like/unix_like_file.hpp>
#endif

#endif // CMP_IO_FILE_HPP_INCLUDED
