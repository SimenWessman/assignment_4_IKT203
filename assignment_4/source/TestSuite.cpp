//
// Created by Simen Wessman on 10/10/2023.
//
#include "../include/TestSuite.h"


// Structure for a test
template <typename T>
struct Test
{
    int _size_of_array;
    T _value_to_find;
    int _lo;
    int _hi;
    T *_arr;
    int _expected_return_value;

    Test(int size_of_array, T value_to_find, int lo, int hi, T *arr, int expected_return_value)
    {
        _size_of_array = size_of_array;
        _value_to_find = value_to_find;
        _lo = lo;
        _hi = hi;
        _arr = new T[size_of_array];
        for(int i{0}; i < size_of_array; ++i)
        {
            _arr[i] = arr[i];
        }
        _expected_return_value = expected_return_value;
    }
};


void test_suite()
{
    int tests_passed = 0;


    std::ostringstream out;
    int int_arr1[5] = {-3, -1, 3, 7, 9};
    int int_arr2[10]= {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    int int_arr3[7] = {0, 1, 2, 3, 4, 5, 6};
    int int_arr4[2] = {1, 3};

    float float_arr1[5] = {-0.2, 1.1, 3.5, 4.4, 7.8};
    float float_arr2[10] = {1.2, 2.3, 2.4, 3.1, 4.7, 5.9, 6.0, 6.2, 9.1, 10.5};
    float float_arr3[7] = {0.3, 1.9, 3.8, 4.6, 5.5, 6.1, 8.4};
    float float_arr4[2] = {2.1, 7.3};

    std::string string_arr1[5] = {"Apple", "Banana", "Pineapple", "Queue", "Stop"};
    std::string string_arr2[10] = {"Apartment", "Chair", "Elevator", "Guitar", "Helicopter", "Kite", "Mountain", "Ocean", "Piano", "Train"};
    std::string string_arr3[7] = {"Candle", "Desk", "Envelope", "Guitar", "Kettle", "Monitor", "Pencil"};
    std::string string_arr4[2] = {"Desk", "Guitar"};


    // Some integer tests:

    std::list<Test<int>> Int_Tests =
    {
            {5, 3, 0, 4, int_arr1, 2},
            {10, 2, 0, 9, int_arr2, 0},
            {7, 6, 0, 6, int_arr3, 6},
            {2, 4, 0, 1, int_arr4, -1}
    };

    std::list<Test<float>> Float_Tests =
    {
            {5, 3.5, 0, 4, float_arr1, 2},
            {10, 1.2, 0, 9, float_arr2, 0},
            {7, 8.4, 0, 6, float_arr3, 6},
            {2, 4.2, 0, 1, float_arr4, -1}
    };

    std::list<Test<std::string>> String_Tests =
    {
            {5, "Pineapple", 0, 4, string_arr1, 2},
            {10, "Apartment", 0, 9, string_arr2, 0},
            {7, "Pencil", 0, 6, string_arr3, 6},
            {2, "Elephant", 0, 1, string_arr4, -1}
    };

    std::string array_elements;

    std::cout << "Testing array of integers:" << std::endl;
    for(const auto& test : Int_Tests)
    {
        int result = InterpolationSearch(test._arr, test._size_of_array, test._lo, test._hi, test._value_to_find);

        if(result == test._expected_return_value)
        {
            for(int i{0}; i < test._size_of_array; ++i)
            {
                if(i+1 == test._size_of_array)
                {
                    array_elements.append(std::to_string(test._arr[i]));
                }
                else
                {
                    array_elements.append(std::to_string(test._arr[i]));
                    array_elements.append(", ");
                }
            }
            tests_passed++;
            std::cout << "Test to find " << test._value_to_find << " in the list " << array_elements << " with expected return value " << test._expected_return_value << " passed." << std::endl;
        }

        else
        {
            std::cout << "Test to find " << test._value_to_find << " in the list " << array_elements << " with expected return value " << test._expected_return_value << " failed." << std::endl;
        }
        array_elements.clear();
    }

    std::cout << "\nPassed " << tests_passed << " / 4" << std::endl;
    tests_passed = 0;

   std::cout << "\nTesting array of floats:" << std::endl;
    for(const auto& test : Float_Tests)
    {
        int result = InterpolationSearch(test._arr, test._size_of_array, test._lo, test._hi, test._value_to_find);

        if(result == test._expected_return_value)
        {
            for(int i{0}; i < test._size_of_array; ++i)
            {

                if(i+1 == test._size_of_array)
                {
                    out << std::fixed << std::setprecision(1) << test._arr[i];
                    array_elements.append(out.str());
                    out.str("");
                    out.clear();
                }
                else
                {
                    out << std::fixed << std::setprecision(1) << test._arr[i];
                    array_elements.append(out.str());
                    array_elements.append(", ");
                    out.str("");
                    out.clear();
                }
            }
            tests_passed++;
            std::cout << "Test to find " << test._value_to_find << " in the list " << array_elements << " with expected return value " << test._expected_return_value << " passed." << std::endl;
        }

        else
        {
            std::cout << "Test to find " << test._value_to_find << " in the list " << array_elements << " with expected return value " << test._expected_return_value << " failed." << std::endl;
        }
        array_elements.clear();
    }

    std::cout << "\nPassed " << tests_passed << " / 4" << std::endl;
    tests_passed = 0;

    std::cout << "\nTesting array of strings:" << std::endl;
    for(const auto& test : String_Tests)
    {
        int result = InterpolationSearch(test._arr, test._size_of_array, test._lo, test._hi, test._value_to_find);

        if(result == test._expected_return_value)
        {
            for(int i{0}; i < test._size_of_array; ++i)
            {
                if(i+1 == test._size_of_array)
                {
                    array_elements.append(test._arr[i]);
                }
                else
                {
                    array_elements.append(test._arr[i]);
                    array_elements.append(", ");
                }
            }
            tests_passed++;
            std::cout << "Test to find " << test._value_to_find << " in the list " << array_elements << " with expected return value " << test._expected_return_value << " passed." << std::endl;
        }

        else
        {
            std::cout << "Test to find " << test._value_to_find << " in the list " << array_elements << " with expected return value " << test._expected_return_value << " failed." << std::endl;
        }
        array_elements.clear();
    }

    std::cout << "\nPassed " << tests_passed << " / 4" << std::endl;
    tests_passed = 0;
}
