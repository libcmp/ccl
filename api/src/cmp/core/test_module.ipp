// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#include <cmp/core/test_module.hpp>

namespace cmp {

// ------------------------------------------------ cmp::test_module<T>::dummy

// Constructors and Destructor ------------------------------------------------

template <
    typename T
>
test_module<T>::dummy::dummy (
    owning_test_module_type* owning_test_module,
    int initial_value
)
noexcept
    : m_owning_test_module{owning_test_module}
    , m_value{initial_value}
{
    m_owning_test_module->push_message(
        owning_test_module_type::message::constructor_called
    );
} // function -----------------------------------------------------------------

template <
    typename T
>
test_module<T>::dummy::~dummy ()
{
    m_owning_test_module->push_message(
        owning_test_module_type::message::destructor_called
    );
} // function -----------------------------------------------------------------

// Copy Operations ------------------------------------------------------------

template <
    typename T
>
test_module<T>::dummy::dummy (
    const dummy& other
)
    : m_owning_test_module{other.m_owning_test_module}
    , m_value{other.m_value}
{
    m_owning_test_module->push_message(
        owning_test_module_type::message::copy_constructor_called
    );
} // function -----------------------------------------------------------------

// Move Operations ------------------------------------------------------------

template <
    typename T
>
test_module<T>::dummy::dummy (
    dummy&& other
)
noexcept
    : m_owning_test_module{other.m_owning_test_module}
    , m_value(other.m_value)
{
    m_owning_test_module->push_message(
        owning_test_module_type::message::move_constructor_called
    );

    other.m_value = default_value;
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

template <
    typename T
>
int
test_module<T>::dummy::get_value ()
const noexcept
{
    return m_value;
} // function -----------------------------------------------------------------

template <
    typename T
>
void
test_module<T>::dummy::set_value (
    int new_value
)
noexcept
{
    m_value = new_value;
} // function -----------------------------------------------------------------

// ------------------------------------------------------- cmp::test_module<T>

// Constructors ---------------------------------------------------------------

template <
    typename T
>
test_module<T>::test_module (
    std::vector<test_function_pointer> test_functions
)
noexcept
    : m_current_test_name{"<uninitialized>"}
    , m_current_test_index{0}
    , m_current_stage_index{0}
    , m_successful_tests{0}
    , m_test_functions{test_functions}
{
    /*
        Allocate enough space for all tests in the m_failed_tests
        vector so that it is guaranteed that a reallocation will
        never be necessary.
    */
    m_failed_tests.reserve(m_test_functions.size());
} // function -----------------------------------------------------------------

// Accessors ------------------------------------------------------------------

template <
    typename T
>
unsigned int
test_module<T>::get_message_count ()
const noexcept
{
    return m_message_queue.size();
} // function -----------------------------------------------------------------

// Core -----------------------------------------------------------------------

template <
    typename T
>
int
test_module<T>::run_tests ()
noexcept
{
    /*
        For each test function, run it and record
        whether the test succeeded or failed.
    */
    for (const auto& current_test_function : m_test_functions) {
        end_test((static_cast<T*>(this)->*current_test_function)());
    }

    /*
        Report how many tests succeeded and how many failed.
    */
    std::cout << "Successful tests: " << m_successful_tests << '\n';
    std::cout << "Failed tests: " << m_failed_tests.size() << '\n';
    std::cout << std::endl;

    /*
        Report back each failed test, including its
        number, name and the stage it failed on.
    */
    if (!m_failed_tests.empty()) {
        for (const auto& current_failed_test : m_failed_tests) {
            report_failed_test(current_failed_test);
        }
    }

    return static_cast<int>(m_failed_tests.size());
} // function -----------------------------------------------------------------

template <
    typename T
>
void
test_module<T>::start_test (
    const char* test_name
)
noexcept
{
    std::string zero_padded_test_index{zero_pad(++m_current_test_index)};

    /*
        Display a message stating the number and
        name of the test that is just starting.
    */
    std::cout << "Test #"
              << zero_padded_test_index
              << " - '"
              << test_name
              << "' starting."
              << std::endl;

    /*
        Store the name of the current test so that
        the next call to end_test can report it again.
    */
    m_current_test_name = test_name;

    /*
        Each time a test starts, we must reset the
        current stage to 0 so that calls to end_stage
        report the correct stage number for the test
        currently being executed.
    */
    m_current_stage_index = 0;
} // function -----------------------------------------------------------------

template <
    typename T
>
void
test_module<T>::end_stage ()
noexcept
{
    /*
        Display a message stating the number of
        the stage that just ended successfully.
    */
    std::cout << "Stage "
              << (++m_current_stage_index)
              << " completed successfully."
              << std::endl;
} // function -----------------------------------------------------------------

template <
    typename T
>
void
test_module<T>::push_message (
    typename test_module<T>::message message_value
)
noexcept
{
    m_message_queue.push(static_cast<int>(message_value));
} // function -----------------------------------------------------------------

template <
    typename T
>
typename test_module<T>::message
test_module<T>::pop_message ()
noexcept
{
    message message_value{message::empty};
    if (!m_message_queue.empty()) {
        message_value = static_cast<message>(m_message_queue.front());
        m_message_queue.pop();
    }
    return message_value;
} // function -----------------------------------------------------------------

template <
    typename T
>
void
test_module<T>::clear_message_queue ()
noexcept
{
    while (!m_message_queue.empty()) {
        m_message_queue.pop();
    }
} // function -----------------------------------------------------------------

template <
    typename T
>
std::ostream&
test_module<T>::log_info ()
const noexcept
{
    std::cout << "info: ";
    return std::cout;
} // function -----------------------------------------------------------------

template <
    typename T
>
std::ostream&
test_module<T>::log_error ()
const noexcept
{
    std::cerr << "error: ";
    return std::cerr;
} // function -----------------------------------------------------------------

// Private Functions ----------------------------------------------------------

template <
    typename T
>
unsigned int
test_module<T>::count_digits (
    int integer
)
noexcept
{
    unsigned int digit_count{0};
    do {
        ++digit_count;
        integer /= 10;
    } while (integer);
    return digit_count;
} // function -----------------------------------------------------------------

template <
    typename T
>
std::string
test_module<T>::zero_pad (
    unsigned int number
)
noexcept
{
    /*
        Get the number of digits in the input number.
    */
    unsigned int input_number_digit_count{
        count_digits(number)
    };

    /*
        Get the number of digits in the total number of tests.
    */
    unsigned int total_number_digit_count{
        count_digits(m_test_functions.size())
    };

    unsigned int digit_difference{
        total_number_digit_count - input_number_digit_count
    };

    unsigned int string_length{total_number_digit_count};
    std::string zero_padded_number(string_length, '\0');

    unsigned int zero_pad_index{0};
    while (digit_difference--) {
        zero_padded_number[zero_pad_index++] = '0';
    }

    unsigned int digit_index{1};
    do {
        zero_padded_number[string_length - digit_index++]
            = (number % 10) + '0';
        number /= 10;
    } while (number);

    return zero_padded_number;
} // function -----------------------------------------------------------------

template <
    typename T
>
void
test_module<T>::end_test (
    bool test_succeeded
)
noexcept
{
    std::string zero_padded_test_index{zero_pad(m_current_test_index)};

    std::cout << "Test #"
              << zero_padded_test_index
              << " - '"
              <<
              m_current_test_name
              << "' "
              << (test_succeeded ? "succeeded" : "failed")
              << " with "
              << m_current_stage_index
              << (m_current_stage_index == 1
                    ? " successful stage."
                    : " successful stages.")
              << '\n';

    std::size_t equal_signs_to_print{
        std::strlen("Test #") + zero_padded_test_index.length()
    };

    for (
        std::size_t equal_signs_printed{0};
        equal_signs_printed < equal_signs_to_print;
        ++equal_signs_printed
    ) {
        std::cout << '=';
    }

    std::cout << std::endl;

    if (test_succeeded) {
        ++m_successful_tests;
    } else {
        m_failed_tests.emplace_back(
            m_current_test_index,
            m_current_test_name,
            m_current_stage_index + 1
        );
    }

    clear_message_queue();
} // function -----------------------------------------------------------------

template <
    typename T
>
void
test_module<T>::report_failed_test (
    std::tuple<unsigned short, const char*, unsigned short> failed_test
)
const noexcept
{
    std::cout << "Test #"
              << std::get<0>(failed_test)
              << " - '"
              << std::get<1>(failed_test)
              << "' failed on stage "
              << std::get<2>(failed_test)
              << std::endl;
} // function -----------------------------------------------------------------

} // namespace ----------------------------------------------------------------
