#include <iostream>
#include "include/TestSuite.h"

// Max array input size, there is no need for our program at this level to ever work with more than 255 elements.
#define MAX_SIZE     255

// Function to validate user input:
template <typename T>
bool validate_input(const std::string& str)
{

    std::istringstream iss(str);
    std::string token;

    // If the datatype of the input is supposed to be an integer
    if constexpr (std::is_same_v<T, int>)
    {
        // Iterate over every character
        for (char c : str)
        {
            // If it's not a digit
            if (!std::isdigit(c) && c != ',' && c != ' ' && c != '-')
            {
                // Return false (The user input is not valid)
                return false;
            }
        }
    }


    else if constexpr (std::is_same_v<T, float>)
    {

        // Read the entire string
        while (getline(iss, token, ','))
        {
            // Separate into parts
            std::string trimmed_token = token;

            // Removing everything we don't want like whitespaces and such.
            trimmed_token.erase(trimmed_token.begin(), std::find_if(trimmed_token.begin(), trimmed_token.end(), [](unsigned char ch)
            {
                return !std::isspace(ch);
            }));

            bool has_dot = false;

            for (char c : trimmed_token)
            {
                if (c == '.')
                {
                    if (has_dot) return false; // multiple dots in one token are not allowed
                    has_dot = true;

                }

                // If its not a character, not a dash, not a space, and not a comma
                else if (!std::isdigit(c) && c != '-' && c != ' ' && c != ',')
                {
                    return false;
                }
            }
        }
    }

    // Don't need to cover the case of a string, because anything can be converted to a string.

    return true;
}

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

    // If the datatype is a numerical value, we can follow standard procedure:
    else
    {
        if (!(lo <= hi && value_to_find >= arr[lo] && value_to_find <= arr[hi]))
        {
            return -1;
        }
    }

    // Different call to probe function if the datatype is a string:
    if constexpr (std::is_same_v<T, std::string>)
    {
        pos = stringFindPos(arr, value_to_find, lo, hi);
    }

    // Standard probe function if datatype is numerical:
    else
    {
        pos = findpos(arr, value_to_find, lo, hi);
    }

    // If the current value is the value we are looking for:
    if (arr[pos] == value_to_find)
    {
        // We are done, return the index we found it at.
        return pos;
    }

    // If datatype is a string, we compare the string we are looking for with the string at the current index, using .compare().
    // .compare() returns 0 if equal
    // positive integer (>0): current string is larger than the string we are looking for
    // negative integer (<0): current string is smaller than the string we are looking for

    if constexpr (std::is_same_v<T, std::string>)
    {
        // If current string is larger than string we are looking for, divide the array and look at first subset
        if (arr[pos].compare(value_to_find) > 0)
        {
            return InterpolationSearch<T>(arr, size_of_array, lo, pos-1, value_to_find);
        }

        // If current string is smaller than string we are looking for, divide the array and look at the second subset.
        else
        {
            return InterpolationSearch<T>(arr, size_of_array, pos+1, hi, value_to_find);
        }
    }

    // If it's not a string follow standard procedure
    else
    {
        // Compare
        if (arr[pos] > value_to_find)
        {
            return InterpolationSearch<T>(arr, size_of_array, lo, pos-1, value_to_find);
        }

        if (arr[pos] < value_to_find)
        {
            return InterpolationSearch<T>(arr, size_of_array, pos+1, hi, value_to_find);
        }
    }

    // If it never finds anything, happens when the sub array has a size of 0, it returns -1.
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
    std::cout << "Enter elements to have in array" << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::getline(std::cin, input_arr);

    std::istringstream iss(input_arr);

    // Initializing an array of type T with MAX_SIZE size.
    T elements[MAX_SIZE];
    int count = 0;

    T element;

    // Validating the input:
    if(!validate_input<T>(input_arr))
    {
        std::cout << "Invalid input for chosen datatype" << std::endl;
        return;
    }

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

    // Creating a dynamic array to account for portability of variable sized array declaration.
    T* new_arr = new T[new_size];

    // Addressing the new array:
    for(int i{0}; i < new_size; ++i)
    {
        new_arr[i] = elements[i];
    }

    // Get element_to_find input from user:
    std::cout << "Enter the element to find:" << std::endl;
    std::cin >> element_to_find;


    // Pass all the required arguments to the InterpolationSearch function and store the return value in found_at
    int found_at = InterpolationSearch<T>(new_arr, count, 0, count - 1, element_to_find);

    // If found_at is greater than -1, its 0 or higher. Which means it was found in the list.
    if(found_at > -1)
    {
        std::cout << "Element " << element_to_find << " found at index: " << found_at  << std::endl;
    }

    // Else, it was not found because return value was -1, signifying no such value found.
    else
    {
        std::cout << "\nCouldn't find element in the list" << std::endl;
    }

    // Free up the memory used by the array
    delete[] new_arr;
}

int main()
{
    int choice = 0;
    std::string datatype;

    // While loop containing program. Runs as long as the user doesn't choose option 3.
    while(true)
    {
        // Clearing previous datatype input and choice input.
        datatype.clear();
        choice = 0;

        // Querying the user to choose an option
        std::cout << "\nEnter choice" << std::endl;

        // Display the menu options
        menu();
        std::cin >> choice;

        // What to do based on the users input.
        switch(choice)
        {
            case 1:
                // Only support int, float and string.
                // Program is scalable, so allowing for double and long is easily done.
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

                // If any other datatype is written, the program notifies the user of invalid input, but doesn't crash.
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
