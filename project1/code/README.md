# Code Instructions

This folder contains the source code for the performance measurement of four search algorithms, along with the data visualization script.

## 1. File List
- **Algorithm Implementations:**
  - `"sequential(iterative).c"`: Iterative Sequential Search implementation.
  - `"sequential(recursive).c"`: Recursive Sequential Search implementation.
  - `"binary(iterative).c"`: Iterative Binary Search implementation.
  - `"binary(recursive).c"`: Recursive Binary Search implementation.
- **Other Files:**
  - `project_test.c`: Integrated testing program (if applicable).
  - `plot_drawing.py`: Python script using Matplotlib to generate the performance curve.
  - `performance_plot.png`: The generated plot output.

## 2. Compilation
Each C file must be compiled separately. You can use GCC or any standard C compiler. Because the filenames contain parentheses `()`, please ensure you include the double quotes `""` around the filenames when compiling.

**Example using GCC:**
```bash
gcc "sequential(iterative).c" -o iter_seq
gcc "sequential(recursive).c" -o recur_seq
gcc "binary(iterative).c" -o iter_bin
gcc "binary(recursive).c" -o recur_bin
```
## 3. Execution
After compilation, run the generated executables from the terminal using the following commands:

```bash
./iter_seq
./recur_seq
./iter_bin
./recur_bin
```
**Input Format:** When executing any of the programs, it will pause and wait for you to input two integers separated by a space:  

- `n`: The size of the array (e.g., `1000`).
- `k`: The number of iterations for the timing loop (e.g., `100000`). 

**Example Run:**
```bash
./iter_bin
1000 100000
```