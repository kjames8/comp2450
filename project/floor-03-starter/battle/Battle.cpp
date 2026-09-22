// Battle.h contains the declarations associated with this implementation,
// including Hero, BattleOutcome, BattleException, and runWardenBattle().
#include "Battle.h"

// Standard-library headers used in this file.
#include <algorithm>  // std::min and std::max
#include <iostream>   // std::cout and std::cin
#include <string>     // std::string, std::getline, std::stoi

// Project-specific headers from neighboring directories.
#include "../bestiary/Search.h"     // findByName<T>()
#include "../hero/Bag.h"             // Bag<T>
#include "../hero/BagException.h"   // BagException
#include "../hero/Item.h"            // Item
#include "../hero/Sort.h"            // sortInventory()

namespace dungeon {

namespace {

    // constexpr means these values are compile-time constants
    // k prefix --> means constant
    constexpr int kPlayerStartHP = 30;
    constexpr int kWardenStartHP = 50;
    constexpr int kPlayerAttackDmg = 6;
    constexpr int kWardenAttackDmg = 4;

    // enum creates a set of named choices
    // enum class keeps our names scoped
    enum class MenuAction {
        Attack,
        UseItem,
        Inspect,
        Flee
    };

    struct MenuOption {
        int number;          // number typed by the player
        std::string label;  // text displayed by the menu
        MenuAction action;  // action performed by our program
    };

    void printMenu(
        Bag<MenuOption>& menu,
        int playerHP,
        int wardenHP
    ) {
        std::cout << "\n -- Your turn -- your hp " << playerHP
                  << "     Warden hp " << wardenHP << "\n";

        for (std::size_t i = 0; i < menu.size(); ++i) {
            std::cout << "     "
                      << menu[i].number
                      << ". "
                      << menu[i].label
                      << "\n";
        }

        std::cout << " > ";
    }

    // Read the user's input and convert that into a MenuAction.
    MenuAction readMenuChoice(const Bag<MenuOption>& menu) {
        std::string line;

        // getline will get the entire line up to the enter key.
        if (!std::getline(std::cin, line)) {
            return MenuAction::Flee;
        }

        int n = -1;

        try {
            // "2" --> 2
            n = std::stoi(line);
        }
        catch (...) {
            throw BattleException(
                "'" + line + "' is not a menu number (enter 1 to "
                + std::to_string(menu.size()) + ")"
            );
        }

        // Search our menu for an option whose displayed number
        // matches the number entered by the player.
        for (std::size_t i = 0; i < menu.size(); ++i) {
            if (menu[i].number == n) {
                return menu[i].action;
            }
        }

        // The input was numeric but it did not match a menu option.
        throw BagException(
            static_cast<std::size_t>(n),
            menu.size()
        );
    }

    // Handle the player's "use item" action.
    void useItem(Hero& hero, int& playerHP) {

        // Handle empty inventory case.
        if (hero.inventory.empty()) {
            std::cout << "Your satchel is empty.\n";
            return;
        }

        // Sort hero's inventory from highest to lowest.
        sortInventory(hero, "value desc");

        std::cout << "Choose an item by name:\n";
        printInventory(hero);
        std::cout << " > ";

        std::string name;

        if (!std::getline(std::cin, name) || name.empty()) {
            std::cout << "You hesitated.\n";
            return;
        }

        // Find the item by name.
        const Item* it = findByName<Item>(hero.inventory, name);

        // A nullptr converts to false.
        if (!it) {
            throw BattleException(
                "no item found '" + name + "' in your satchel"
            );
        }

        // If you say Potion or Healing Potion.
        if (it->name.find("otion") != std::string::npos) {

            // Heal 12 HP, but do not exceed maximum health.
            playerHP = std::min(
                playerHP + 12,
                kPlayerStartHP
            );

            std::cout << "You drink "
                      << it->name
                      << ". HP -> "
                      << playerHP
                      << ".\n";
        }
        else {
            std::cout << "You ready "
                      << it->name
                      << " - but it is not a consumable.\n";
        }
    }

} // namespace

BattleOutcome runWardenBattle(Hero& hero) {

    // Create two variables for the player and
    // warden health; represent the state.
    int playerHP = kPlayerStartHP;
    int wardenHP = kWardenStartHP;

    // Create a bag specialized to store MenuOption objects.
    Bag<MenuOption> menu;

    menu.push_back({ 1, "Attack", MenuAction::Attack });
    menu.push_back({ 2, "Use item", MenuAction::UseItem });
    menu.push_back({ 3, "Inspect warden", MenuAction::Inspect });
    menu.push_back({ 4, "Flee", MenuAction::Flee });

    // Continue the battle ONLY while both participants
    // are alive.
    while (playerHP > 0 && wardenHP > 0) {

        try {
            printMenu(menu, playerHP, wardenHP);

            // readMenuChoice returns a MenuAction.
            switch (readMenuChoice(menu)) {

            case MenuAction::Attack: {

                // Subtract player's damage from warden's HP.
                wardenHP -= kPlayerAttackDmg;

                std::cout << "You strike for "
                          << kPlayerAttackDmg
                          << ". Warden HP -> "
                          << std::max(wardenHP, 0)
                          << ".\n";

                // If the warden is still alive, it attacks.
                if (wardenHP > 0) {

                    playerHP -= kWardenAttackDmg;

                    std::cout << "The warden retaliates for "
                              << kWardenAttackDmg
                              << ". Your HP -> "
                              << std::max(playerHP, 0)
                              << ".\n";
                }

                // Break exits the switch case, not the while loop.
                break;
            }

            case MenuAction::UseItem: {

                // Use an item.
                useItem(hero, playerHP);

                // Using an item consumes the player's turn.
                // The warden attacks if both are still alive.
                if (wardenHP > 0 && playerHP > 0) {

                    playerHP -= kWardenAttackDmg;

                    std::cout
                        << "The warden strikes while you fumble. "
                        << "Your HP -> "
                        << std::max(playerHP, 0)
                        << ".\n";
                }

                break;
            }

            case MenuAction::Inspect: {

                std::cout << "Warden of the Foundations. HP -> "
                          << wardenHP
                          << " / "
                          << kWardenStartHP
                          << ". No visible weakness (free action).\n";

                break;
            }

            case MenuAction::Flee: {

                // Return immediately exits the function.
                return BattleOutcome::Fled;
            }

            } // end switch
        } // end try

        catch (const std::exception& e) {

            // BattleException and BagException will inherit
            // from std::exception.
            std::cout << e.what()
                      << " - try again.\n";
        }
    }

    // condition ? value_if_true : value_if_false
    return wardenHP <= 0
        ? BattleOutcome::Victory
        : BattleOutcome::Defeat;
}

} // namespace dungeon