#include "InputService.h"

#include<conio.h>
#include<iostream>
#include<cctype>

using namespace std;

/**
 * @brief Read a PIN from the console while
 * masking entered characters.
 *
 * Accepts numeric input only and displays
 * an asterisk (*) for each entered digit.
 * Supports backspace for correcting input
 * and terminates when the Enter key is
 * pressed.
 *
 * @return The PIN entered by the user.
 */
string InputService:: inputPin(){

    string pin;

    while(true){

        // Read a single character from the keyboard without echoing it.
        char ch = _getch();

        //Stop accepting input if enter key is pressed.
        if(ch=='\r'){
            break;
        }

        // Remove the last entered digit and
       // update the console display when Backspace is pressed.
        else if (ch=='\b')
        {
            if(!pin.empty())
            {
                pin.pop_back();
                cout<< "\b \b";
            }

        }

        // Accept numeric characters only,
       // store them in the PIN, and display a masking character.
        else if(isdigit(ch))
        {
            pin+=ch;
            cout<<'*';
        }

        else{
            cout<<"Incorrect Input"<<endl;
        }
    }

    // Return the complete PIN entered by the user.
    return pin;
}