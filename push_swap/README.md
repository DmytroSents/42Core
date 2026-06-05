*This project has been created as part of the 42 curriculum by <dbrusent>.*

# Push_Swap

## Description

**push_swap** is an algorithmic project from the 42 curriculum.  
The goal is to sort a stack of integers using a restricted set of operations  
`sa`, `pb`, `ra`, `rrr` etc. while aiming to minimize the total number of moves.

The program receives an unsorted list of integers as arguments and outputs a sequence
of operations that sorts them in ascending order using two stacks: A and B.

## **Compilation**

To compile the project run:

**make**

ARG=$(shuf -i 1-2147483647 -n 100 | tr '\n' ' '); ./push_swap $ARG | wc -l; ./push_swap $ARG | ./checker_linux $ARG

ARG=$(shuf -i 1-2147483647 -n 500 | tr '\n' ' '); ./push_swap $ARG | wc -l; ./push_swap $ARG | ./checker_linux $ARG

**make t100** & **make t500** were used for testing

./push_swap (your arguments, exmpl: 1 2 4 8 5 4) add "| wc -l" 
 (wc -l at the end to count how many lines/operations were done)

### AI Instructions

-->Imagine, that I have an array of unique integers and I must sort them in the least amount of operations. What algorithm is the most effective from the large variety (I've scrolled list of algo's names on this page en.wikipedia.org/wiki/Sorting_algorithm).
-->it's not about real time efficiency, I must calculate the minimal amount of opperations, I need to use to sort the array.
-->yes, I need to calculate minimal amount of swaps, disregarding the number of comparisons. Which algorithm is the best for this purpose?

Deep_Seek   https://chat.deepseek.com
Theoretical Minimum for Push_Swap:

For a random permutation of N elements:

    Lower bound: Ω(N) operations (must touch each element)

    Upper bound (radix): O(N log N)

    Practical (good alg): ~1.5N × log₂N

Empirical results:

    N=100: 600-700 ops (radix)

    N=500: 4500-5500 ops (optimized radix)

    N=1000: 8500-11000 ops

Recommendation:

    N ≤ 5: Hardcoded optimal sequences

    6 ≤ N ≤ 100: Radix sort (base 2) - simple, meets requirements

    N > 100: Radix sort with 2-bit processing - best operation count

Why not other algorithms?

    QuickSort: Needs many comparisons (not your metric)

    MergeSort: Needs O(N log N) moves but not optimal for 2-stack

    HeapSort: Many swaps

    Bubble/Insertion: O(N²) operations

Bottom line: For push_swap's specific operations and your goal of minimizing operation count, Radix Sort (especially with 2-bit processing) is mathematically optimal given the constraints.

***AI.*** was used primarily for the testing purposes. (And genegate 60% of this Readme, of course.) 
Here I put one of the scripts, prodused by AI, just because I can:


#!/bin/bash

echo "=== Valgrind Test for 500 Numbers ==="

# Generate 500 random numbers
ARG=$(shuf -i 1-2147483647 -n 500 | tr '\n' ' ')

echo "Generated 500 numbers"
echo "First few: $(echo $ARG | cut -d' ' -f1-5) ..."

# Save to file for reuse
echo "$ARG" > /tmp/test_500.txt

echo -e "\n=== 1. Operation Count ==="
./push_swap $ARG | wc -l

echo -e "\n=== 2. Checker Result ==="
./push_swap $ARG | ./checker_linux $ARG

echo -e "\n=== 3. Valgrind Memory Check ==="
valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --error-exitcode=42 \
         ./push_swap $ARG > /dev/null 2>&1

VALGRIND_EXIT=$?

echo -e "\n=== 4. Valgrind Summary ==="
if [ $VALGRIND_EXIT -eq 42 ]; then
    echo -e "\033[31m✗ Memory errors detected\033[0m"
    # Show full valgrind output
    valgrind --leak-check=full --show-leak-kinds=all ./push_swap $ARG 2>&1 | \
        grep -A10 -B5 "ERROR SUMMARY\|LEAK SUMMARY\|definitely lost"
else
    echo -e "\033[32m✓ No memory errors\033[0m"
    # Just show summary
    valgrind --leak-check=full --show-leak-kinds=all ./push_swap $ARG 2>&1 | \
        tail -15
fi

# Cleanup
rm -f /tmp/test_500.txt
