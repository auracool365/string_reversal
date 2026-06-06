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


int main() {

    std::println("\n=== String Reversal Examples ===");

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

    return 0;
}