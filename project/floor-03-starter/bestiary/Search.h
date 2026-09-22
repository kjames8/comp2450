#pragma once

#include <cstddef>
#include <string>
#include "../hero/Bag.h"
#include "Monster.h"

namespace dungeon {

// ---- Floor 1 reference: Monster-specific searches ---------------------
//
// Linear scan. Works on any order.    O(n).
const Monster* linearSearch(const Bag<Monster>& bestiary,
                            const std::string&         name);

// Iterative binary search.            O(log n). Pre: sorted.
const Monster* binarySearch(const Bag<Monster>& bestiary,
                            const std::string&         name);

// Recursive binary search.            O(log n). Pre: sorted.
const Monster* binarySearchRecursive(const Bag<Monster>& bestiary,
                                     const std::string&         name);

// The seam Floor 1 introduced: one place the rest of the game calls.
const Monster* findMonster(const Bag<Monster>& bestiary,
                           const std::string&         name);


// ---- Floor 3 (Mon): function template ---------------------------------

template <typename T>
const T* findByName(const Bag<T>& items, const std::string& name) {
    for (const auto& it: items) {
        if (it.name == name) return &it;
    }
    return nullptr;
}

}  // namespace dungeon
