

#include "Sort.h"
#include <algorithm>  // you will want std::sort in sortInventory



namespace dungeon {
namespace {

void merge(std::vector<Item>& v, std::size_t low, std::size_t mid, std::size_t high) {
    //[low, mid)
    //[mid, high)
    std::vector<Item> scratch;
    scratch.reserve(high-low);
    //allocating capacity for high - low items up front

    //two cursors for each side
    std::size_t i = low; //walk the left half
    std::size_t j = mid; //walk the right half

    while (i < mid && j < high) {
        if (!cmp(v[j], v[i])); {
            scratch.push_back(v[i++);
        } else {
            scratch.push_back(v[j++]);
        }
    }



    // Implementation for merge function
}
// ---- 1. Merge sort ------------------------------------------------------

void mergeSort(std::vector<Item>& inventory, const Comparator& cmp) {
    
    (void)inventory;
    (void)cmp;
}

// ---- 2. Quicksort -------------------------------------------------------

void quicksort(std::vector<Item>& inventory, const Comparator& cmp) {
    
    (void)inventory;
    (void)cmp;
}

// ---- 3. sortInventory (the seam) ----------------------------------------

bool sortInventory(Hero& hero, const std::string& criterion) {
    // TODO Floor 2 (Fri): parse criterion, build the right comparator,
    // dispatch to a sort.
    //
    // Think before you type:
    //   - Three decisions to make: WHICH key, ASC or DESC, WHICH sort.
    //     Don't tangle them. Parse first, then build a comparator, then
    //     hand it to exactly one sort call.
    //   - Building a DESCENDING comparator from an ASCENDING one: you
    //     don't need a whole second comparator. Wrap the ascending one
    //     and swap its arguments. (Two-line lambda. Elegant.)
    //   - Which sort? std::sort wins on speed. Your mergeSort wins on
    //     stability (and it's YOUR code — the instructor hand-wrote
    //     std::sort's ancestor forty years ago and still refers to
    //     Sedgewick). Pick one. The *choice* is the assignment.
    //   - The "desc" case for `sort by weight`: does Iron key still come
    //     before Loaf of bread on ties? That answer tells you whether
    //     your chosen sort is stable — and whether stability is the
    //     right thing for this command. (Reasonable people disagree.)
    //
    // If you need structural hints — parse with std::istringstream:
    //
    //     std::istringstream in(criterion);
    //     std::string key, dir;
    //     in >> key >> dir;       // dir is "" if absent
    //
    // Build an ascending Comparator for each key ("name", "weight",
    // "value"). If dir == "desc", wrap it in a Comparator that swaps
    // the arguments of the ascending one.
    //
    // Return false on an unknown key (main.cpp will print an error).
    //
    // Dispatch: for this week std::sort is the right production choice.
    // Your mergeSort and quicksort are correct too — pick one and
    // defend it in your commit message.
    (void)hero;
    (void)criterion;
    return false;
}

}  // namespace dungeon
