

#include "Sort.h"
#include <algorithm> 
#include <sstream> // you will want std::sort in sortInventory



namespace dungeon {
namespace {

void merge(std::vector<Item>& v, std::size_t low, std::size_t mid, std::size_t high, const Comparator& cmp){
    //[low, mid)
    //[mid, high)
    std::vector<Item> scratch;
    scratch.reserve(high-low);
    //allocating capacity for high - low items up front

    //two cursors for each side
    std::size_t i = low; //walk the left half
    std::size_t j = mid; //walk the right half

    while (i < mid && j < high) {
        if (!cmp(v[j], v[i])) {
            scratch.push_back(v[i++]);
        } else {
            scratch.push_back(v[j++]);
         }
    }
        //one half is drained but the other still has items
while (i < mid) scratch.push_back(v[i++]);
while (j < high) scratch.push_back(v[j++]);

//copy the nerged result back into the v at positions [low, high)
for (std::size_t k = 0; k < scratch.size(); ++k){
    v[low + k] = std::move(scratch[k]);
}
}
    
void mergeSortImpl(std::vector<Item>& v, std::size_t low, std::size_t high, const Comparator& cmp) {
if (high - low < 2) return;
//recursion!
std::size_t mid = low + (high - low) / 2;
mergeSortImpl(v, low, mid, cmp);
mergeSortImpl(v, mid, high, cmp);
merge(v, low, mid, high, cmp);
}

std::size_t partition(std::vector<Item>& v, std::size_t low, std::size_t high, const Comparator& cmp) {
    // high is our last index (inclusive)
    // 1.) pick the pivot
    std::size_t mid = low + (high - low) / 2;
    std::swap(v[mid], v[high]);
    const Item pivot = v[high];
    // comput middle index
    // std::swap exchanges two items w/o copying the whole struct
    // In Lomuto, assumes the pivot lives at high, so by moving our pivot there, we can follow classic Lomuto

    // lomuto scan
    std::size_t store = low;
    for (std::size_t i = low; i < high; ++i) {
        if (cmp(v[i], pivot)) {
            std::swap(v[i], v[store]);
            ++store;
        }
    }
    std::swap(v[store], v[high]);
    return store;
}

void quicksortImpl(std::vector<Item>& v, std::size_t low, std::size_t high, const Comparator& cmp) {
    if (low >= high) return;
    std::size_t p = partition(v, low, high, cmp);
    if(p > 0) quicksortImpl(v, low, p - 1, cmp);
    quicksortImpl(v, p + 1, high, cmp);
}
Comparator makeComparator(const std::string& key, bool descending){
    Comparator cmp;
    if (key == "name") {
        cmp = [](const Item& a, const Item& b) { return a.name <
    b.name; };
        } else if (key == "weight") {
        cmp = [](const Item& a, const Item& b) { return a.weight < b.weight; };
    } else if (key == "value") {
        cmp = [](const Item& a, const Item& b) { return a.value < b.value; };
    } else {
        return nullptr;
        }
        if (descending){
            Comparator asc = cmp;
            cmp = [asc](const Item& a, const Item& b) {
                return asc(b, a); 
            };
        }
        return cmp;
}
}
// ---- 1. Merge sort ------------------------------------------------------

void mergeSort(std::vector<Item>& inventory, const Comparator& cmp) {
    mergeSortImpl(inventory, 0, inventory.size(), cmp);
    (void)inventory;
    (void)cmp;
}

// ---- 2. Quicksort -------------------------------------------------------

void quicksort(std::vector<Item>& inventory, const Comparator& cmp) {
    if (inventory.size() < 2) return;
    quicksortImpl(inventory, 0, inventory.size() - 1, cmp);


    (void)inventory;
    (void)cmp;
}

// ---- 3. sortInventory (the seam) ----------------------------------------

bool sortInventory(Hero& hero, const std::string& criterion) {
   std::istringstream in(criterion);
    std::string key;
    std::string dir;
    in >> key >> dir;
    
    
    bool descending = (dir == "desc");
    Comparator cmp = makeComparator(key, descending);
    if(!cmp) return false;
    std::sort(hero.inventory.begin(), hero.inventory.end(), cmp);
    return true;
}

}


