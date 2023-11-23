// Copyright (C) 2022 Daniel T. McGinnis
// SPDX-License-Identifier: BSL-1.0

#ifndef CMP_CORE_TEST_MODULE_HPP_INCLUDED
#define CMP_CORE_TEST_MODULE_HPP_INCLUDED

#include <cstring>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

namespace cmp {

/**
    Description:
        The <#type>test_module</#type> class template represents a test module.

        A test module is an object containing functions that exercise, or
        <#emphasis>test</#emphasis> some piece of code, most commonly a class.

        The general approach to testing adopted in CCL is to subclass
        <#type>test_module</#type> and implement one member function per
        unit test, construct this <#type>test_module</#type> subclass with
        an initializer list of function pointers referencing each member
        function containing a unit test, and then call the
        <#function>run_tests</#function> function to run all the tests. The
        return value of <#function>run_tests</#function> is then returned by
        the main function of the test program. If the return value is zero,
        all tests succeeded, otherwise the return value is the number of
        unit tests that failed.
*/
template <
    typename T
>
class test_module {
public:
    // Types ------------------------------------------------------------------

    /**
        Description:
            A <#type>dummy</#type> is simply an object that records when
            a special member function is called, making it easy to test
            code with.
    */
    class dummy {
    public:
        // Types --------------------------------------------------------------

        /**
            Description:
                The type of test module that owns
                <#this/> <#type>dummy</#type> object.
        */
        using owning_test_module_type = test_module<T>;

        // Constants ----------------------------------------------------------

        static const int default_value{0};

        // Constructors and Destructor ----------------------------------------

        /**
            Description:
                Constructs a <#type>dummy</#type> with the given
                test module as its owner, and an initial value.
        */
        explicit
        dummy (
            owning_test_module_type* owning_test_module,
            int initial_value = default_value
        )
        noexcept;

        ~dummy ()
        noexcept;

        // Copy Operations ----------------------------------------------------

        /**
            Description:
                Copy-constructs a <#type>dummy</#type> from an existing one.

            Parameters:
                other:
                    The <#type>dummy</#type> to copy from.
        */
        dummy (
            const dummy& other
        )
        noexcept;

        // Move Operations ----------------------------------------------------

        /**
            Description:
                Move-constructs a <#type>dummy</#type> from an existing one.

            Parameters:
                other:
                    The <#type>dummy</#type> to move from.
        */
        dummy (
            dummy&& other
        )
        noexcept;

        // Accessors ----------------------------------------------------------

        /**
            Description:
                Returns <#this/> <#type>dummy</#type>'s value.
        */
        int
        get_value ()
        const noexcept;

        /**
            Description:
                Sets <#this/> <#type>dummy</#type>'s value
                to <#parameter>new_value</#parameter>.

            Parameters:
                new_value:
                    The new value of <#this/> <#type>dummy</#type>.
        */
        void
        set_value (
            int new_value
        )
        noexcept;

    private:
        // Private Data -------------------------------------------------------

        test_module<T>* m_owning_test_module;
        int m_value;
    }; // class ---------------------------------------------------------------

    /**
        Description:
            The inner test module type, that is,
            the <#type>test_module</#type> subclass.
    */
    using inner_test_module_type = T;

    /**
        Description:
            Gives a name to the signature of a test function so that
            corresponding function pointers can be written more clearly.
    */
    using test_function_pointer = bool (inner_test_module_type::*)();

    /**
        Description:
            The type of message that can be kept in the message queue.
    */
    enum class message {
        empty,
        constructor_called,
        copy_constructor_called,
        move_constructor_called,
        destructor_called
    };

    // Constructors and Destructor --------------------------------------------

    /**
        Description:
            Constructs a test module aware of the provided test functions.

        Parameters:
            test_functions:
                The pointers to the test functions that this
                <#type>test_module</#type> will run when
                <#function>run_tests</#function> is called.
    */
    explicit
    test_module (
        std::vector<test_function_pointer> test_functions
    )
    noexcept;

    ~test_module ()
    noexcept = default;

    // Accessors --------------------------------------------------------------

    /**
        Description:
            Returns the number of messages in the message queue.
    */
    unsigned int
    get_message_count ()
    const noexcept;

    // Core -------------------------------------------------------------------

    /**
        Description:
            Runs all registered tests in this test module
            and returns the number of tests that failed.
    */
    int
    run_tests ()
    noexcept;

    /**
        Description:
            Announces the test that is just starting

        Parameters:
            test_name:
                The name of the test that is just starting.
    */
    void
    start_test (
        const char* test_name
    )
    noexcept;

    /**
        Description:
            Prints a message to standard output stating
            that the current stage succeeded.
    */
    void
    end_stage ()
    noexcept;

    /**
        Description:
            Pushes a message onto the message queue.

        Parameters:
            message_value:
                The message to push onto the message queue.
    */
    void
    push_message (
        message message_value
    )
    noexcept;

    /**
        Description:
            Pops a message from the message queue and returns it. If
            the message queue was empty, an empty message is returned.
    */
    message
    pop_message ()
    noexcept;

    /**
        Description:
            Removes all messages in the message queue.
    */
    void
    clear_message_queue ()
    noexcept;

    /**
        Description:
            Returns an output stream that can be
            used to log informational messages.
    */
    std::ostream&
    log_info ()
    const noexcept;


    /**
        Description:
            Returns an output stream that can
            be used to log error messages.
    */
    std::ostream&
    log_error ()
    const noexcept;

private:
    // Private Data -----------------------------------------------------------

    const char* m_current_test_name;
    unsigned short m_current_test_index;
    unsigned short m_current_stage_index;
    unsigned short m_successful_tests;
    std::vector<std::tuple<unsigned short, const char*, unsigned short>>
        m_failed_tests;
    std::vector<test_function_pointer> m_test_functions;
    std::queue<int> m_message_queue;

    // Private Functions ------------------------------------------------------

    /**
        Description:
            Returns the number of digits in the input integer.

        Parameters:
            integer:
                The integer to count digits in.
    */
    unsigned int
    count_digits (
        int integer
    )
    noexcept;

    /**
        Description:
            Returns a string containing the given unsigned integer
            zero-padded based on the number of test functions.

        Parameters:
            number:
                The number to zero-pad.
    */
    std::string
    zero_pad (
        unsigned int number
    )
    noexcept;

    /**
        Description:
            Prints whether the test succeeded or failed to standard output
            and keeps track of how many tests succeeded and failed.

        Parameters:
            test_succeeded:
                A boolean value that indicates whether the test succeeded.
                True means the test succeeded and false means it failed.
    */
    void
    end_test (
        bool test_succeeded
    )
    noexcept;

    /**
        Description:
            Prints the number and name of the failed test.

        Parameters:
            failed_test:
                The failed test to report.
    */
    void
    report_failed_test (
        std::tuple<unsigned short, const char*, unsigned short> failed_test
    )
    const noexcept;
}; // class -------------------------------------------------------------------

} // namespace ----------------------------------------------------------------

#include <cmp/core/test_module.ipp>

#endif // CMP_CORE_TEST_MODULE_HPP_INCLUDED
