/*
 * chapter03_BoostScopeExit.hpp
 *
 *  Created on: Jan. 14th, 2018
 *      Author: Pyrad
 */

#ifndef CHAPTER03_BOOSTSCOPEEXIT_HPP_
#define CHAPTER03_BOOSTSCOPEEXIT_HPP_

#include <iostream>
#include <utility>

#include <boost/scope_exit.hpp>

namespace C03 {

// ============================================================
// Example 3.1. Using BOOST_SCOPE_EXIT
// ============================================================
// 
int *run_03_01_foo() {
    int *i = new int{10};
    BOOST_SCOPE_EXIT(&i) {
        delete i;
        i = 0;
    } BOOST_SCOPE_EXIT_END
    std::cout << *i << '\n';
    return i;
}

void run_03_01() {
    int *j = run_03_01_foo();
    // Notice that the output below is not '0'
    // Since in run_03_01_foo, 'i' is set to 0
    // after it is returned.
    // So it is too late to set 'i' to '0'
    std::cout << j << '\n';
}


// ============================================================
// Example Example 3.2. Boost.ScopeExit with C++11 lambda functions
// ============================================================
//
// #include <iostream>
// #include <utility>
template <typename T>
struct scope_exit {
    scope_exit(T &&t) : t_{std::move(t)} {}
    ~scope_exit() { t_(); }
    T t_;
};

template <typename T>
scope_exit<T> make_scope_exit(T &&t) {
    return scope_exit<T>{ std::move(t) };
}

int *run_03_02_foo() {
    int *i = new int{10};
    // a lambda function is passed to 'make_scope_exit'
    // lambda function here is: [&i]() mutable { delete i; i = 0; }
    auto cleanup = make_scope_exit([&i]() mutable { delete i; i = 0; });
    std::cout << *i << '\n';
    return i;
}

void run_03_02() {
    int *j = run_03_02_foo();
    std::cout << j << '\n';
}

// ============================================================
// Example 3.3. Peculiarities of BOOST_SCOPE_EXIT
// ============================================================
//
// #include <boost/scope_exit.hpp>
// #include <iostream>
struct x {
    int i;
    // When BOOST_SCOPE_EXIT is used to define more than one block in a scope
    // then blocks are executed in reverse order
    void foo() {
        i = 10;
        // If no variables will be passed to BOOST_SCOPE_EXIT
        // you need to specify void.
        // !!! The parentheses must not be empty.
        BOOST_SCOPE_EXIT(void) {
            std::cout << "last\n";
        } BOOST_SCOPE_EXIT_END

        // If you use BOOST_SCOPE_EXIT in a member function
        // and you need to pass a pointer to the current object, you must use this_, not this
        BOOST_SCOPE_EXIT(this_) {
            this_->i = 20;
            std::cout << "first\n";
        } BOOST_SCOPE_EXIT_END
    }
};

void run_03_03() {
    x obj;
    obj.foo();
    std::cout << obj.i << '\n';
}



void run_all() {
	run_03_01();
	run_03_02();
	run_03_03();
	// run_03_04();
	// run_03_05();
	// run_03_06();
	// run_03_07();
	// run_03_08();
	// run_03_09();
}



} // namespace C03



#endif /* CHAPTER03_BOOSTSCOPEEXIT_HPP_ */
