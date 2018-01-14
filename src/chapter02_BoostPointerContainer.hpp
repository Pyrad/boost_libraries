/*
 * chapter02_BoostPointerContainer.hpp
 *
 *  Created on: Jan. 14th, 2018
 *      Author: Pyrad
 */

#ifndef CHAPTER02_BOOSTPOINTERCONTAINER_HPP_
#define CHAPTER02_BOOSTPOINTERCONTAINER_HPP_

#include <iostream>
#include <set>
#include <memory>
#include <functional>
#include <array>
#include <algorithm>

#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/ptr_container/ptr_set.hpp>
#include <boost/ptr_container/indirect_fun.hpp>
#include <boost/ptr_container/ptr_inserter.hpp>

namespace C02 {

// ============================================================
// 
// ============================================================
// 
// #include <boost/ptr_container/ptr_vector.hpp>
// #include <iostream>
void run_02_01() {
    boost::ptr_vector<int> v;
    v.push_back(new int{1});
    v.push_back(new int{2});
    std::cout << v.back() << '\n';
}


// ============================================================
// 
// ============================================================
// 
// #include <boost/ptr_container/ptr_set.hpp>
// #include <boost/ptr_container/indirect_fun.hpp>
// #include <set>
// #include <memory>
// #include <functional>
// #include <iostream>

/*
 * All ptr_XXX
 *  boost::ptr_vector
 *  boost::ptr_set
 *  boost::ptr_deque
 *  boost::ptr_list
 *  boost::ptr_map
 *  boost::ptr_unordered_set
 *  boost::ptr_unordered_map
*/
void run_02_02() {
    boost::ptr_set<int> s;
    s.insert(new int{2});
    s.insert(new int{1});
    std::cout << *s.begin() << '\n';

    std::set<std::unique_ptr<int>, boost::indirect_fun<std::less<int>>> v;
    v.insert(std::unique_ptr<int>(new int{2}));
    v.insert(std::unique_ptr<int>(new int{1}));
    std::cout << **v.begin() << '\n';
}

// ============================================================
// 
// ============================================================
// 
// #include <boost/ptr_container/ptr_vector.hpp>
// #include <boost/ptr_container/ptr_inserter.hpp>
// #include <array>
// #include <algorithm>
// #include <iostream>

void run_02_03() {
  boost::ptr_vector<int> v;
  std::array<int, 3> a{{0, 1, 2}};
  std::copy(a.begin(), a.end(), boost::ptr_container::ptr_back_inserter(v));
  std::cout << v.size() << '\n';
}

void run_all() {
	run_02_01();
	run_02_02();
	run_02_03();
	// run_02_04();
	// run_02_05();
	// run_02_06();
	// run_02_07();
	// run_02_08();
	// run_02_09();
} /* void run_all() */

} // namespace C02



#endif /* CHAPTER02_BOOSTPOINTERCONTAINER_HPP_ */
