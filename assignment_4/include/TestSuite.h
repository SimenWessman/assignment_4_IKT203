//
// Created by Simen Wessman on 17/10/2023.
//

#ifndef ASSIGNMENT_4_TESTSUITE_H
#define ASSIGNMENT_4_TESTSUITE_H

#include <iostream>
#include <sstream>
#include <list>
#include <iomanip>
#include <algorithm>
#include <type_traits>
#include <string>

// Extern for the InterpolationSearch function present in main.cpp
// The extern tag tells the compiler that the function is defined elsewhere, but that it HAS been defined.
// Allowing it to be used in current scope without needing to be included.
template<typename T>
extern int InterpolationSearch(T arr[], int size_of_array, int lo, int hi, T value_to_find);

void test_suite();

#endif //ASSIGNMENT_4_TESTSUITE_H
