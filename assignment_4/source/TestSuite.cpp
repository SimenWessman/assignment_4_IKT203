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


// Function for running the different tests:
void test_suite()
{
    // Initializing a test_passed variable to keep track of how many tests have been passed. Resets for every datatype.
    int tests_passed = 0;

    std::ostringstream out;

    // Initializing the different arrays:

    // Integer arrays:
    int int_arr1[5] = {-3, -1, 3, 7, 9};
    int int_arr2[10]= {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    int int_arr3[7] = {0, 1, 2, 3, 4, 5, 6};
    int int_arr4[2] = {1, 3};


    // Float arrays:
    float float_arr1[5] = {-0.2, 1.1, 3.5, 4.4, 7.8};
    float float_arr2[10] = {1.2, 2.3, 2.4, 3.1, 4.7, 5.9, 6.0, 6.2, 9.1, 10.5};
    float float_arr3[7] = {0.3, 1.9, 3.8, 4.6, 5.5, 6.1, 8.4};
    float float_arr4[2] = {2.1, 7.3};


    // String arrays:
    std::string string_arr1[5] = {"Apple", "Banana", "Pineapple", "Queue", "Stop"};
    std::string string_arr2[10] = {"Apartment", "Chair", "Elevator", "Guitar", "Helicopter", "Kite", "Mountain", "Ocean", "Piano", "Train"};
    std::string string_arr3[7] = {"Candle", "Desk", "Envelope", "Guitar", "Kettle", "Monitor", "Pencil"};
    std::string string_arr4[2] = {"Desk", "Guitar"};


    // Defining integer tests, and adding them to a list to iterate over later:
    std::list<Test<int>> Int_Tests =
    {
            {5, 3, 0, 4, int_arr1, 2},
            {10, 2, 0, 9, int_arr2, 0},
            {7, 6, 0, 6, int_arr3, 6},
            {2, 4, 0, 1, int_arr4, -1}
    };

    // Defining float tests, and adding them to a list to iterate over later:
    std::list<Test<float>> Float_Tests =
    {
            {5, 3.5, 0, 4, float_arr1, 2},
            {10, 1.2, 0, 9, float_arr2, 0},
            {7, 8.4, 0, 6, float_arr3, 6},
            {2, 4.2, 0, 1, float_arr4, -1}
    };

    // Defining string tests, and adding them to a list to iterate over later:
    std::list<Test<std::string>> String_Tests =
    {
            {5, "Pineapple", 0, 4, string_arr1, 2},
            {10, "Apartment", 0, 9, string_arr2, 0},
            {7, "Pencil", 0, 6, string_arr3, 6},
            {2, "Elephant", 0, 1, string_arr4, -1}
    };


    // Variable to store the array elements as a string to display them to the user in a user-friendly manner.
    std::string array_elements;

    // Iterating the different tests in the list, and running the InterpolationSearch on them.

    // Iterating the integer tests:
    std::cout << "Testing array of integers:" << std::endl;
    for(const auto& test : Int_Tests)
    {
        // Get the result of the search:
        int result = InterpolationSearch<int>(test._arr, test._size_of_array, test._lo, test._hi, test._value_to_find);

        // Compare the result with the expected value:

        // If it gets the expected result:
        if(result == test._expected_return_value)
        {

            // Add the different elements in the array to the string array_elements to display to the user:
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
            // Increase the tests_passed counter:
            tests_passed++;

            // Display the text to the user:
            std::cout << "Test to find " << test._value_to_find << " in the list [" << array_elements << "] with expected return value " << test._expected_return_value << " passed." << std::endl;
        }

        // If it did not get the expected results:
        else
        {
            std::cout << "Test to find " << test._value_to_find << " in the list [" << array_elements << "] with expected return value " << test._expected_return_value << " failed." << std::endl;
        }

        // Clearing the array elements string:
        array_elements.clear();
    }

    // Telling the user how many tests of the integer tests passed:
    std::cout << "\nPassed " << tests_passed << " / 4" << std::endl;

    // Resetting the counter:
    tests_passed = 0;


    // Iterating the float tests:
   std::cout << "\nTesting array of floats:" << std::endl;
    for(const auto& test : Float_Tests)
    {
        // Get the result of the search:
        int result = InterpolationSearch<float>(test._arr, test._size_of_array, test._lo, test._hi, test._value_to_find);

        // Compare the result with the expected value:

        // If it gets the expected result:
        if(result == test._expected_return_value)
        {

            // Add the different elements in the array to the string array_elements to display to the user:
            for(int i{0}; i < test._size_of_array; ++i)
            {

                if(i+1 == test._size_of_array)
                {

                    // Set precision to only three floating point
                    out << std::fixed << std::setprecision(3) << test._arr[i];
                    array_elements.append(out.str());
                    out.str("");
                    out.clear();
                }
                else
                {
                    out << std::fixed << std::setprecision(3) << test._arr[i];
                    array_elements.append(out.str());
                    array_elements.append(", ");
                    out.str("");
                    out.clear();
                }
            }

            // Increment the tests_passed counter;
            tests_passed++;

            // Display the text to the user:
            std::cout << "Test to find " << test._value_to_find << " in the list [" << array_elements << "] with expected return value " << test._expected_return_value << " passed." << std::endl;
        }

        // If it did not get the expected result:
        else
        {
            std::cout << "Test to find " << test._value_to_find << " in the list [" << array_elements << "] with expected return value " << test._expected_return_value << " failed." << std::endl;
        }

        // Clearing the array elements string
        array_elements.clear();
    }

    // Telling the user how many of the float tests passed:
    std::cout << "\nPassed " << tests_passed << " / 4" << std::endl;

    // Resetting the counter:
    tests_passed = 0;


    // Iterating the string tests:
    std::cout << "\nTesting array of strings:" << std::endl;
    for(const auto& test : String_Tests)
    {

        // Get the result of the search:
        int result = InterpolationSearch<std::string>(test._arr, test._size_of_array, test._lo, test._hi, test._value_to_find);

        // Compare the result with the expected value:

        // If it gets the expected result:
        if(result == test._expected_return_value)
        {

            // Add the different elements in the array to the string array_elements to display to the user:
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

            // Increment the tests_passed counter:
            tests_passed++;

            // Display the text to the user:
            std::cout << "Test to find " << test._value_to_find << " in the list [" << array_elements << "] with expected return value " << test._expected_return_value << " passed." << std::endl;
        }


        // If it did not get the expected result:
        else
        {
            std::cout << "Test to find " << test._value_to_find << " in the list [" << array_elements << "] with expected return value " << test._expected_return_value << " failed." << std::endl;
        }

        // Clear the array elements string:
        array_elements.clear();
    }

    // Telling the user how many of the string tests passed:
    std::cout << "\nPassed " << tests_passed << " / 4" << std::endl;

    // No need to reset counter, because we are done.
}
