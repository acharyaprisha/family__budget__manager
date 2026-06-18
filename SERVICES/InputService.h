#ifndef INPUTSERVICE_H
#define INPUTSERVICE_H

#include<string>

using namespace std;

/**
 * @class InputService
 * @brief Provides utility functions
 * for console-based user input.
 */
class InputService{

    public:

    /**
     * @brief Read a PIN from the console
     * while masking entered characters.
     *
     * @return The PIN entered by the user.
     */
    static string inputPin();
};
#endif