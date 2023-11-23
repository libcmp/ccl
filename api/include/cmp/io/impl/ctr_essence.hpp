// Copyright (C) 2023 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_IO_CTR_ESSENCE_HPP_INCLUDED
#define CMP_IO_CTR_ESSENCE_HPP_INCLUDED

#include <string>

#include <cmp/io/inclusion_assert.hpp>
#include <cmp/io/seekable_input_resource.hpp>

namespace cmp {

namespace impl {

template <
    typename Container
>
class ctr_essence
{
public:
    // Constructors and Destructor --------------------------------------------

    explicit
    ctr_essence (
        const Container* initial_content_ptr
    );

    ~ctr_essence ()
    noexcept = default;

protected:
    // Protected Data ---------------------------------------------------------

    void* m_content_ptr;
    std::int64_t m_position;
    std::size_t m_last_fill_amount;

    // Protected Functions ----------------------------------------------------

    Container*
    get_content_ptr ()
    noexcept;

    const Container*
    get_const_content_ptr ()
    const noexcept;

    bool
    is_at_end (
        const io_buffer& buffer
    )
    const noexcept;

    std::int64_t
    get_position (
        const io_buffer& m_buffer
    )
    const noexcept;

    void
    set_position_raw (
        std::int64_t new_position,
        position_reference pr
    )
    noexcept;

    std::size_t
    read_raw (
        std::byte* data,
        std::size_t byte_count,
        read_request rr,
        seekable_input_resource<std::int64_t>& resource
    );

    std::size_t
    write_raw (
        const std::byte* data,
        std::size_t byte_count
    );
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#include <cmp/io/impl/ctr_essence.ipp>

#endif // CMP_IO_CTR_ESSENCE_HPP_INCLUDED
