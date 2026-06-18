#ifndef MENU_H
#define MENU_H

/**
 * @class Menu
 * @brief Handles menu display operations.
 *
 * Provides functions for displaying the main menu,
 * member menu, and default screen selection menu.
 */
class Menu
{
    public:

/**
 * @brief Displays the main application menu.
 *
 * Presents the available options to create an account,
 * log in, or exit the application and returns the
 * selected option.
 *
 * @return User's selected menu option.
 */
    int showMainMenu();

/**
 * @brief Displays the member operations menu.
 *
 * Presents the available account operations
 * that can be performed after login.
 */
    void showMemberMenu();

/**
 * @brief Display the menu available after a user logs in.
 *
 * Presents the actions that can be performed
 * by an authenticated user, including account
 * management, transaction operations, filtering,
 * default screen customization, and logout.
 */
    void showLoginMenu();
    
/**
 * @brief Displays the default screen selection menu.
 *
 * Allows the user to choose a preferred screen
 * that will automatically open after login.
 *
 * @return Character representing the selected screen.
 */
    char showDefaultScreenMenu();
};

#endif

