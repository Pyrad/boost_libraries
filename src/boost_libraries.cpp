//============================================================================
// Name        : boost_libraries.cpp
// Author      : Pyrad
// Version     :
// Copyright   : All Rights Reserved
// Description : Programs based on the book online:
//               https://theboostcpplibraries.com/
//============================================================================
// Online book
// https://theboostcpplibraries.com/

#include <iostream>

#include "chapter01_smartpointers.hpp"
#include "chapter02_BoostPointerContainer.hpp"
#include "chapter03_BoostScopeExit.hpp"
#include "chapter04_BoostPool.hpp"

#include "cpp11_style_tester.hpp"

int main() {
	//std::cout << "Good day today" << std::endl; // prints Good day today

    /* PART I. RAII and Memory Management */
	// chapter 01 - Smart pointers
	C01::run_all();
	// chapter 02 - Smart pointer container
	C02::run_all();
	// chapter 03 - Scope exit
	C03::run_all();
	// chapter 04 - Boost pool
	C04::run_all();


	// Additional testers
	std::cout << "\n\nADDITIONAL TESTS OUTPUT" << std::endl;
	namespace CPP11 = CPP11TESTER;
	CPP11::cpp11_lambda_tester();
	return 0;
}
