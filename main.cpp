#include <iostream>
#include <variant>
#include <cmath>
#include <optional>

std::variant<std::monostate, double, std::pair<double, double>> solveSquareEquation(double a, double b, double c) {
    double d = b * b - 4 * a * c;
    if (d < 0) {
        return std::monostate();
    } else if (d == 0) {
        return -b / (2 * a);
    } else {
        return std::make_pair((-b + sqrt(d)) / (2 * a), (-b - sqrt(d)) / (2 * a));
    }
}

std::optional<int> parseArgs(int argc, char* argv[]) {
    int sum = 0;
    for (int i = 1; i < argc; ++i) {
        try {
            sum += std::stoi(argv[i]);
        } catch (std::invalid_argument& e) {
            return std::nullopt;
        }
    }
    return sum;
}

int main(int argc, char* argv[]) {
    std::cout << "Enter a, b, c: ";
    double a, b, c;
    std::cin >> a >> b >> c;
    auto result = solveSquareEquation(a, b, c);
    if (std::holds_alternative<std::monostate>(result)) {
        std::cout << "No roots" << std::endl;
    } else if (std::holds_alternative<double>(result)) {
        std::cout << "Root: " << std::get<double>(result) << std::endl;
    } else {
        auto [x1, x2] = std::get<std::pair<double, double>>(result);
        std::cout << "Roots: " << x1 << "; " << x2 << std::endl;
    }

    auto sum = parseArgs(argc, argv);
    if (sum) {
        std::cout << "Sum: " << *sum << std::endl;
    } else {
        std::cout << "Invalid arguments" << std::endl;
    }
    return 0;
}
