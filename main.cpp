#include <algorithm>
#include <print>
#include <ranges>
#include <string>


// 1. In-Place Reversal
// Reverses the original string directly. Usage when modifying the original string is acceptable.
// Time Complexity: O(n), Tiny temporary extra memory usage, but still O(1)

void reverse_in_place(std::string& word) {
    std::ranges::reverse(word);
}
// Pre-C++20 equivalent, same effect
// void reverse_in_place(std::string& word) {
//     std::reverse(word.begin(), word.end());
// }


// 2. Reversed Copy: Returns a new reversed string while leaving the original string unchanged.
// Time Complexity: O(n). Extra Memory for the copy created: O(n)
// Usage when the original string must remain intact.

std::string reversed_copy(const std::string& word) {
    return {word.rbegin(), word.rend()};
}


// 3. Reversed View (C++20 Ranges). Returns a lazy reverse view of the string.
// No string copy is made. The original string is not modified. Characters are accessed in reverse order on demand.
// Time Complexity: O(n) traversal
// tiny extra memory: O(1)
// Note: The returned view does NOT own the string. The original string must outlive the view.

auto reversed_view(const std::string& word) {
    return word | std::ranges::views::reverse;
}


// 4. Modern Value-Semantics Reversal: Takes the string by value, reverses it in place, and returns the result.
// Benefits: 1. Works with both lvalues and rvalues. 2. Copies lvalues only once.
//           3. Moves rvalues efficiently. 4. Common modern C++ design pattern.
// Time Complexity: O(n). Extra Memory: lvalue argument: O(n) copy. rvalue argument: typically no additional allocation


std::string reversed(std::string word) {
    std::ranges::reverse(word);
    return word;
}


// print array
template <typename T, std::size_t N>
void print_array(const std::array<T, N>& arr) {
    for (std::size_t i = 0; i < N; ++i) {
        std::print("{}", arr[i]);

        if (i != N - 1) {
            std::print(", ");
        }
    }

    std::println();
}

// overload for C-style
template <typename T, std::size_t N>
void print_array(const T (&arr)[N]) {
    for (std::size_t i = 0; i < N; ++i) {
        std::print("{}", arr[i]);

        if (i != N - 1) {
            std::print(", ");
        }
    }

    std::println();
}

// Non-std library implementations

// pass by reference
// Time Complexity: O(n). Extra Memory: O(1) modifies the original string directly.
void reverse_by_ref(std::string &word)
{
    std::size_t left = 0;
    std::size_t right = !word.empty() ? word.size() - 1 : 0;

    // Swap characters from both ends toward the middle(two pointer approach).
    while (left < right)
    {
        const char temp = word[left];
        word[left] = word[right];
        word[right] = temp;

        left++;
        right--;
    }
}

// pass by value
// Reverses a copy of the string, and returns it. Original string (if lvalue was passed) is left untouched.
// Time Complexity: O(n). Extra Memory: O(n) copy for lvalues, move for rvalues.
std::string reversed_by_value_1(std::string word)
{
    std::size_t left = 0;
    std::size_t right = !word.empty() ? word.size() - 1 : 0;

    while (left < right)
    {
        const char temp = word[left];
        word[left] = word[right];
        word[right] = temp;

        left++;
        right--;
    }

    return word;
}

// Technically, pass by value does not need full re-implementation, just pass the argument by value, and use the pass by reference function
std::string reversed_by_value_2(std::string word) {
    reverse_by_ref(word);
    return word;
}



int main() {

    std::println("\nString Reversal Examples");

    // 1. In-Place Reversal
    std::string word = "complete";

    std::println("\n1. In-Place Reversal");
    std::println("Original : {}", word);

    reverse_in_place(word);

    std::println("Reversed : {}", word);


    // 2. Reversed Copy
    std::string word_1 = "important";

    std::println("\n2. Reversed Copy");
    std::println("Original : {}", word_1);

    auto copy = reversed_copy(word_1);

    std::println("Original : {}", word_1);
    std::println("Copy     : {}", copy);


    // 3. Reversed View
    std::string word_2 = "recursion";

    std::println("\n3. Reversed View");
    std::println("Original : {}", word_2);

    auto view = reversed_view(word_2);

    std::print("View     : ");

    for (char c : view) {
        std::print("{}", c);
    }

    std::println();


    // 4. Modern Value-Semantics Reversal
    std::string word_3 = "responsible";

    std::println("\n4. Modern Value-Semantics Reversal");
    std::println("Original : {}", word_3);

    auto result = reversed(word_3);

    std::println("Original : {}", word_3);
    std::println("Result   : {}", result);


    // Efficient usage with rvalue
    auto temporary = reversed("temporary");

    std::println("\nRvalue Example");
    std::println("Result   : {}", temporary);

    // 1 and 4 for general usage and best utility depending on desired outcome, modify original(1), or create copy(4)

    // Array elements modification
    // 1
    std::array<std::string, 4> fruits = {"apple", "banana", "orange", "grape"};

    std::println("\n1. reverse_in_place()");

    std::println("Before:");
    print_array(fruits);

    for (auto& fruit : fruits) {
        reverse_in_place(fruit);
    }

    std::println("\nAfter(Modified):");
    print_array(fruits);

    // 4
    std::array<std::string, 4> animals = {"hippopotamus", "tiger", "polar bear", "wolverine"};

    std::println("\n4. reversed() \nBefore:");
    print_array(animals);

    std::println("\nReversed Copies:");
    for (const auto& animal : animals) {
        std::print("{}, ", reversed(animal));
    }
    std::println();

    std::println("\nOriginal Array Reversal(intact):");
    print_array(animals);

    // Non-library implementation usage
    std::println("\nRaw String Reversal Examples");

    // pass by reference
    std::string word_4 = "practice";

    std::println("\n5.Pass by reference In-Place Reversal");
    std::println("Original : {}", word_4);

    reverse_by_ref(word_4);

    std::println("Reversed : {}", word_4);
    std::println("Original : {}", word_4);


    // Raw Value-Semantics Reversal (pass by value)
    std::string word_5 = "buffer";

    std::println("\n6.Value-Semantics Reversal");
    std::println("Original : {}", word_5);

    auto result_raw = reversed_by_value_1(word_5);

    std::println("Result   : {}", result_raw);
    std::println("Original : {}", word_5);

    // second pass by value function
    std::string word_6 = "relax";

    std::println("\n6.Value-Semantics Reversal(short hand functon)");
    std::println("Original : {}", word_6);

    result_raw = reversed_by_value_2(word_6);

    std::println("Result   : {}", result_raw);
    std::println("Original : {}", word_6);

    // Rvalue usage
    auto temp_raw = reversed_by_value_1("rvalue_test");

    std::println("\nRvalue Example (raw)");
    std::println("Result   : {}", temp_raw);


    // Edge cases
    std::string empty_str;
    std::string single_char = "x";

    reverse_by_ref(empty_str);
    reverse_by_ref(single_char);

    std::println("\nEdge Cases");
    std::println("Empty (reversed)      : \"{}\"", empty_str);
    std::println("Single char (reversed): \"{}\"", single_char);

    return 0;
}