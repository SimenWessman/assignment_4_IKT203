#include <iostream>
#include "include/TestSuite.h"

// Max array input size, there is no need for our program at this level to ever work with more than 255 elements.
#define MAX_SIZE     255

// Same function as findpos, but adjusted for strings.
inline auto stringFindPos = [](std::string arr[], std::string &value_to_find, int lo, int hi)
{
    double position = static_cast<double>(value_to_find.compare(arr[lo])) / static_cast<double>(arr[hi].compare(arr[lo]));
    return lo + static_cast<int>((hi - lo) * position);
};


inline auto findpos = [](auto arr[], auto value_to_find, int lo, int hi)
{
    return lo + (((value_to_find - arr[lo]) * (hi - lo)) / (arr[hi] - arr[lo]));
};


// Interpolation Search Function, Takes a datatype typename T.
template<typename T> int InterpolationSearch(T arr[], int size_of_array, int lo, int hi, T value_to_find)
{
    int pos;

    // Sorting array, so we can be sure it's sorted before we work on it.
    std::sort(arr, arr + size_of_array);

    // If the datatype passed to the function is string we do a different comparison to when it's a numerical value:
    if constexpr (std::is_same_v<T, std::string>)
    {
        if (!(lo <= hi && value_to_find.compare(arr[lo]) >= 0 && value_to_find.compare(arr[hi]) <= 0))
        {
            return -1;
        }

    }

    else
    {
        if (!(lo <= hi && value_to_find >= arr[lo] && value_to_find <= arr[hi]))
        {
            return -1;
        }
    }

    if constexpr (std::is_same_v<T, std::string>)
    {
        pos = stringFindPos(arr, value_to_find, lo, hi);
    }

    else
    {
        pos = findpos(arr, value_to_find, lo, hi);
    }

    if (arr[pos] == value_to_find)
    {
        return pos;
    }

    if constexpr (std::is_same_v<T, std::string>)
    {
        if (arr[pos].compare(value_to_find) > 0)
        {
            return InterpolationSearch<T>(arr, size_of_array, lo, pos-1, value_to_find);
        }

        else
        {
            return InterpolationSearch<T>(arr, size_of_array, pos+1, hi, value_to_find);
        }
    }

    else
    {
        if (arr[pos] > value_to_find)
        {
            return InterpolationSearch<T>(arr, size_of_array, lo, pos-1, value_to_find);
        }

        if (arr[pos] < value_to_find)
        {
            return InterpolationSearch<T>(arr, size_of_array, pos+1, hi, value_to_find);
        }
    }

    return -1;
}


// Function to display the menu options to make an interactive UI.
void menu()
{
    std::vector<std::string> choices = {"Run the function manually with custom variables", "Run the test suite", "Exit the program"};

    int iter = 1;
    for(std::string &choice : choices)
    {
        std::cout << iter << ". " << choice << std::endl;
        ++iter;
    }
}


// Template function that runs if the user wishes to type in their own array and values:
template <typename T>
void get_custom_input()
{
    // Element to find is always same type as the array:
    T element_to_find;

    // Get the array from user input:
    std::string input_arr;
    std::cout << "Enter numbers to have in array" << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::getline(std::cin, input_arr);

    std::istringstream iss(input_arr);

    // Initializing an array of type T with MAX_SIZE size.
    T elements[MAX_SIZE];
    int count = 0;

    T element;


    // Append everything entered into the array and ignore spaces.
    while (iss >> element)
    {
        if (count < MAX_SIZE)
        {
            elements[count++] = element;
        }

            // If the input size exceeds 255 elements, ignore everything after the first 255 elements.
        else
        {
            std::cout << "Reached maximum array size. Ignoring extra numbers." << std::endl;
            break;
        }

        // Skip the space (if any)
        if (iss.peek() == ' ')
        {
            iss.ignore();
        }

        // Skip commas if user decides to use comma separated input instead.
        if (iss.peek() == ',')
        {
            iss.ignore();
        }
    }

    // Removing duplicates:
    T* new_end = std::unique(elements, elements + count);

    int new_size = new_end - elements;

    T* new_arr = new T[new_size];

    // Adressing the new array:
    for(int i{0}; i < new_size; ++i)
    {
        new_arr[i] = elements[i];
    }

    std::cout << "Enter the element to find:" << std::endl;
    std::cin >> element_to_find;

    int found_at = InterpolationSearch<T>(new_arr, count, 0, count - 1, element_to_find);

    if(found_at > -1)
    {
        std::cout << "Element " << element_to_find << " found at index: " << found_at  << std::endl;
    }
    else
    {
        std::cout << "\nCouldn't find element in the list" << std::endl;
    }
    delete[] new_arr;
}


int main()
{
    int choice = 0;
    std::string datatype;

    while(true)
    {
        datatype.clear();
        choice = 0;
        std::cout << "\nEnter choice" << std::endl;

        // Display the menu options
        menu();
        std::cin >> choice;

        switch(choice)
        {
            case 1:
                std::cout << "Enter datatype: (int, float, string)" << std::endl;
                std::cin >> datatype;

                if(datatype == "int")
                {
                    get_custom_input<int>();
                }

                else if(datatype == "float")
                {
                    get_custom_input<float>();
                }

                else if(datatype == "string")
                {
                    get_custom_input<std::string>();
                }

                else
                {
                    std::cout << "Invalid datatype input, try again with a valid datatype (int, float string) ..." << std::endl;
                }
                break;

            case 2:
                test_suite();
                break;

            case 3:
                std::cout << "\nExiting the program ..." << std::endl;
                return 0;

            default:
                std::cout << "Unknown menu choice ..." << std::endl;
                break;
        }
    }
}
