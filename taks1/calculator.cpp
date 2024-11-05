#include <iostream>
#include <limits>  // To handle invalid input

using namespace std;

// Function prototypes
double add(double x, double y);
double subtract(double x, double y);
double multiply(double x, double y);
double divide(double x, double y);

int main() {
    double num1, num2;
    int choice;

    // Display available operations
    cout << "Select operation:" << endl;
    cout << "1. Add" << endl;
    cout << "2. Subtract" << endl;
    cout << "3. Multiply" << endl;
    cout << "4. Divide" << endl;

    // Get user input for operation choice
    cout << "Enter choice (1/2/3/4): ";
    cin >> choice;

    // Input validation for choice
    if (cin.fail() || choice < 1 || choice > 4) {
        cout << "Invalid input! Please enter a valid choice (1-4)." << endl;
        return 1;  // Exit the program with an error code
    }

    // Get user input for two numbers
    cout << "Enter first number: ";
    cin >> num1;
    cout << "Enter second number: ";
    cin >> num2;

    // Perform the selected operation
    switch (choice) {
        case 1:
            cout << "Result: " << add(num1, num2) << endl;
            break;
        case 2:
            cout << "Result: " << subtract(num1, num2) << endl;
            break;
        case 3:
            cout << "Result: " << multiply(num1, num2) << endl;
            break;
        case 4:
            if (num2 == 0) {
                cout << "Error! Division by zero." << endl;
            } else {
                cout << "Result: " << divide(num1, num2) << endl;
            }
            break;
        default:
            cout << "Invalid operation choice." << endl;
    }

    return 0;
}

// Function definitions
double add(double x, double y) {
    return x + y;
}

double subtract(double x, double y) {
    return x - y;
}

double multiply(double x, double y) {
    return x * y;
}

double divide(double x, double y) {
    if (y == 0) {
        cout << "Error! Division by zero." << endl;
        return std::numeric_limits<double>::quiet_NaN(); // Return NaN to indicate an error
    }
    return x / y;
}
