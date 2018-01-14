/*
 * chapter04_BoostPool.hpp
 *
 *  Created on: Jan. 14th, 2018
 *      Author: Pyrad
 */

#ifndef CHAPTER04_BOOSTPOOL_HPP_
#define CHAPTER04_BOOSTPOOL_HPP_

#include <boost/pool/simple_segregated_storage.hpp>
#include <boost/pool/object_pool.hpp>
#include <boost/pool/singleton_pool.hpp>
#include <boost/pool/pool_alloc.hpp>

#include <vector>
#include <cstddef>
#include <list>

// Macros
#define BOOST_POOL_NO_MT

namespace C04 {



// ============================================================
// Example 4.1. Using boost::simple_segregated_storage
// ============================================================
// 
// #include <boost/pool/simple_segregated_storage.hpp>
// #include <vector>
// #include <cstddef>

// Just a demo, don't use 'boost::simple_segregated_storage' in practice
void run_04_01() {
    boost::simple_segregated_storage<std::size_t> storage;
    // Total 1024 bytes
    std::vector<char> v(1024);
    // 1024 bytes will be separated by 4 segregation
    // each one is 256 bytes
    storage.add_block(&v.front(), v.size(), 256);

    int *i = static_cast<int*>(storage.malloc());
    *i = 1;

    int *j = static_cast<int*>(storage.malloc_n(1, 512));
    j[10] = 2;

    storage.free(i);
    storage.free_n(j, 1, 512);
}
// ============================================================
// Example 4.2. Using boost::object_pool
// ============================================================
// 
// #include <boost/pool/object_pool.hpp>
void run_04_02() {
    boost::object_pool<int> pool;

    int *i = pool.malloc();
    *i = 1;

    int *j = pool.construct(2);

    pool.destroy(i);
    pool.destroy(j);
}

// ============================================================
// Example 4.3. Changing the segment size with boost::object_pool
// ============================================================
// 
// #include <boost/pool/object_pool.hpp>
// #include <iostream>

void run_04_03() {
    boost::object_pool<int> pool{32, 0};
    pool.construct();
    std::cout << pool.get_next_size() << '\n';
    pool.set_next_size(8);
}


// ============================================================
// Example 4.4. Using boost::singleton_pool
// ============================================================
// 
// #include <boost/pool/singleton_pool.hpp>

struct int_pool {};
// typedef boost::singleton_pool<int_pool, sizeof(int)> singleton_int_pool;
typedef boost::singleton_pool<int_pool, sizeof(int)> SIP;

void run_04_04() {
    int *i = static_cast<int*>(SIP::malloc());
    *i = 1;

    int *j = static_cast<int*>(SIP::ordered_malloc(10));
    j[9] = 2;

    SIP::release_memory();
    SIP::purge_memory();
}

// ============================================================
// Example 4.5. Using boost::pool_allocator
// ============================================================
// 
// #include <boost/pool/pool_alloc.hpp>
// #include <vector>

void run_04_05() {
    std::vector<int, boost::pool_allocator<int>> v;
    for (int i = 0; i < 1000; ++i) {
        v.push_back(i);
    }

    // Should call clear before purge_memory
    // Or, use release_memory instead, and thus there's no need
    // to v.clear() since release_memory only release the idle memories
    // the memories in use are not freed
    v.clear();
    boost::singleton_pool<boost::pool_allocator_tag, sizeof(int)>::purge_memory();
}

// ============================================================
// Example 4.6. Using boost::fast_pool_allocator
// ============================================================
// 
// #define BOOST_POOL_NO_MT
// #include <boost/pool/pool_alloc.hpp>
// #include <list>

// Usage, grossly simplified:
// You use boost::pool_allocator for std::vector and,
// You use boost::fast_pool_allocator for std::list.
void run_04_06() {
    typedef boost::fast_pool_allocator<int,
            boost::default_user_allocator_new_delete,
            boost::details::pool::default_mutex,
            64, 128> allocator;

    std::list<int, allocator> l;
    for (int i = 0; i < 1000; ++i) {
        l.push_back(i);
    }

    l.clear();
    boost::singleton_pool<boost::fast_pool_allocator_tag, sizeof(int)>::purge_memory();
}

void run_all() {
	run_04_01();
	run_04_02();
	run_04_03();
	run_04_04();
	run_04_05();
	run_04_06();
	// run_04_07();
	// run_04_08();
	// run_04_09();
} /* void run_all() */

} // namespace C04



#endif /* CHAPTER04_BOOSTPOOL_HPP_ */
