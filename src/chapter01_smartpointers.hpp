/*
 * chapter01_smartpointers.hpp
 *
 *  Created on: Jan. 14th, 2018
 *      Author: Pyrad
 */

#ifndef CHAPTER01_SMARTPOINTERS_HPP_
#define CHAPTER01_SMARTPOINTERS_HPP_

#include <iostream>
#include <typeinfo>
#include <iostream>
#include <ctime>

#include <Windows.h>

#include <boost/smart_ptr.hpp>

#define BOOST_SP_USE_QUICK_ALLOCATOR

namespace C01 {

// ============================================================
// Example 1.1. Using boost::scoped_ptr
// ============================================================
// 
// boost::scoped_ptr
void run_01_01() {
	boost::scoped_ptr<int> p{new int{1}};
	std::cout << *p << '\n';
	p.reset(new int{2});
	std::cout << *p.get() << '\n';
	p.reset();
	std::cout << std::boolalpha << static_cast<bool>(p) << '\n';
} // run_01_01()


// ============================================================
// Example 1.2. Using boost::scoped_array
// ============================================================
// 
// #include <boost/scoped_array.hpp>
// boost::scoped_array
void run_01_02() {
	boost::scoped_array<int> p{new int[2]};
	*p.get() = 1;
	p[1] = 2;
	p.reset(new int[3]);

	p[0] = 7;
	p[1] = 9;
	p[2] = 11;
	std::cout << p[0] << ", " << p[1] << ", " << p[2] << std::endl;
} // run_01_02()

// ============================================================
// Example 1.3. Using boost::shared_ptr
// ============================================================
// 
// #include <boost/shared_ptr.hpp>
// boost::shared_ptr
void run_01_03() {
	boost::shared_ptr<int> p1{new int{1}};
	std::cout << *p1 << '\n';
	boost::shared_ptr<int> p2{p1};
	p1.reset(new int{2});
	std::cout << *p1.get() << '\n';
	p1.reset();
	std::cout << std::boolalpha << static_cast<bool>(p2) << '\n';
}

// ============================================================
// Example 1.4. boost::shared_ptr with a user-defined deleter
// ============================================================
// 
// #include <Windows.h>
// Use a deleter for boost::shared_ptr
void run_01_04() {
	boost::shared_ptr<void> handle(OpenProcess(PROCESS_SET_INFORMATION, FALSE, GetCurrentProcessId()), CloseHandle);
}

// ============================================================
// Example 1.5. Using boost::make_shared
// ============================================================
// 
void run_01_05() {
    auto p1 = boost::make_shared<int>(1);
    std::cout << typeid(p1).name() << '\n';
    auto p2 = boost::make_shared<int[]>(10);
    std::cout << typeid(p2).name() << '\n';
}

// ============================================================
// Example 1.6. Using boost::shared_array
// ============================================================
// 
// boost/shared_array.hpp
void run_01_06() {
    boost::shared_array<int> p1{new int[1]};
    {
        boost::shared_array<int> p2{p1};
        p2[0] = 1;
    }
    std::cout << p1[0] << '\n';
}

// ============================================================
// Example 1.7. boost::shared_ptr with BOOST_SP_USE_QUICK_ALLOCATOR
// ============================================================
// 
// #define BOOST_SP_USE_QUICK_ALLOCATOR
// #include <boost/shared_ptr.hpp>
// #include <iostream>
// #include <ctime>
void run_01_07() {
    boost::shared_ptr<int> p;
    std::time_t then = std::time(nullptr);
    for (int i = 0; i < 1000000; ++i) {
        p.reset(new int{i});
    }
    std::time_t now = std::time(nullptr);
    std::cout << "Time used for allocation: " << now - then << '\n';
}

#if 0
// ============================================================
// Example 1.8. Using boost::weak_ptr
// ============================================================
// 
// #include <boost/shared_ptr.hpp>
// #include <boost/weak_ptr.hpp>
// #include <thread>
// #include <functional>
// #include <iostream>

void run_01_08_reset(boost::shared_ptr<int> &sh) {
    sh.reset();
}

void run_01_08_print(boost::weak_ptr<int> &w) {
    boost::shared_ptr<int> sh = w.lock();
    if (sh) {
        std::cout << *sh << '\n';
    }
}

void run_01_08() {
    boost::shared_ptr<int> sh{new int{99}};
    boost::weak_ptr<int> w{sh};
    std::thread t1{run_01_08_reset, std::ref(sh)};
    std::thread t2{run_01_08_print, std::ref(w)};
    t1.join();
    t2.join();
}
#endif // 0


#if 0
// ============================================================
// Example 1.9. Using boost::intrusive_ptr
// ============================================================
// 
// For COM, so it can only be built on Windows
// #include <boost/intrusive_ptr.hpp>
// #include <atlbase.h>
// #include <iostream>

void intrusive_ptr_add_ref(IDispatch *p) { p->AddRef(); }
void intrusive_ptr_release(IDispatch *p) { p->Release(); }

void run_01_09_check_windows_folder()
{
    CLSID clsid;
    CLSIDFromProgID(CComBSTR{"Scripting.FileSystemObject"}, &clsid);
    void *p;
    CoCreateInstance(clsid, 0, CLSCTX_INPROC_SERVER, __uuidof(IDispatch), &p);
    boost::intrusive_ptr<IDispatch> disp{static_cast<IDispatch*>(p), false};
    CComDispatchDriver dd{disp.get()};
    CComVariant arg{"D:\\Movies"};
    CComVariant ret{false};
    dd.Invoke1(CComBSTR{"FolderExists"}, &arg, &ret);
    std::cout << std::boolalpha << (ret.boolVal != 0) << '\n';
}

void run_01_09() {
    CoInitialize(0);
    check_windows_folder();
    CoUninitialize();
}
#endif // 0


void run_all() {
	run_01_01();
	run_01_02();
	run_01_03();
	run_01_04();
	run_01_05();
	run_01_06();
	run_01_07();
	// run_01_08();
	// run_01_09();
}

} // namespace C01
#endif /* CHAPTER01_SMARTPOINTERS_HPP_ */
