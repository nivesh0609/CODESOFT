#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    // Initialize random seed based on current time
    srand(static_cast<unsigned int>(time(0)));

    // Generate a random number between 1 and 100
    int number_to_guess = rand() % 100 + 1;
    int user_guess;
    int attempts = 0;

    cout << "Welcome to the 'Guess the Number' game!" << endl;
    cout << "I am thinking of a number between 1 and 100. Can you guess what it is?" << endl;

    // Loop until the user guesses correctly
    do {
        cout << "Enter your guess: ";
        cin >> user_guess;
        attempts++;

        if (user_guess < number_to_guess) {
            cout << "Too low! Try again." << endl;
        } else if (user_guess > number_to_guess) {
            cout << "Too high! Try again." << endl;
        } else {
            cout << "Congratulations! You've guessed the correct number!" << endl;
            cout << "It took you " << attempts << " attempts." << endl;
        }

    } while (user_guess != number_to_guess);

    return 0;
}
