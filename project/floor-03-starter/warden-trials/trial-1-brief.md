# Trial I — *The Foundations Brief*

*Warden of the Foundations · Midterm 1 · 15 %*

Four short answers, one from each floor above. **50–100 words per answer.** No code on this trial (except the lambdas in Q3); just clear thinking.

AI is welcome to *check* your answers; it is not welcome to *write your sentences*. These answers are short enough that an LLM voice is recognisable.

---

## 1. Floor 0 — ADT

> Your battle's "Use item" menu shows the *currently usable* items in your hero's inventory on this turn. Name the right ADT for that menu. Defend the choice against its closest neighbour (e.g., why `bag` instead of `set`, or `list` instead of `bag`).

I think that a list is the right answer. I would say list because with a bag you can't pull from a certain order because it's ransomized, meaning you can't call the same thing over, and with a set you can only pull or take away from the top. Therefore, a list is the correct answer.

---

## 2. Floor 1 — search & Big-O

> Your inventory is kept sorted by healing power (in this codebase an item's `value` measures its potency, so `value` plays the healing-power role). The player types `use Healing potion`. Linear or binary search to find it by name? Justify, and give the Big-O for each.

You would use linear search. You would use linear over binary because they are sorted by value, not by name so you wouldn't know if one is above or below the box you opened.

---

## 3. Floor 2 — sort & comparators

> Your "Use item" menu must be displayable sorted *either* by healing power (meaning `value`) *or* by weight. Show a one-line comparator (lambda) for each. One sentence on what language feature makes one `std::sort` call serve both orders.

*Note: `Item` has no healing field — an item's `value` measures its potency, so `value` plays the healing-power role here and in your battle.*

```cpp
// by healing power — i.e. by value
auto byValue  = /* your lambda */;

// by weight
auto byWeight = /* your lambda */;
```

auto comp = [](const Item& a, cont Item& b) {return a.value < b.value;};

---

## 4. Floor 3 — templates & exceptions

> Why does `Bag<T>` live in `Bag.h` instead of `Bag.cpp`? And: when the player types `9` for a 4-option menu, where in your code should the validation **throw**, and where should it **catch**?

Bag<T> lives in Bag.h because Bag.h holds all of the "beefy" stuff, while Bag.cpp is where everything is called. .h and .cpp are seperate because then you can compile in .h whereas you can call in .cpp and it's easier to read.
