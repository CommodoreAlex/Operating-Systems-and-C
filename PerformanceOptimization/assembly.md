## **Step 1: C++ Code Example**

We'll write two versions of a simple function that returns the maximum of two integers:
```cpp
// version_if.cpp
int max_if(int a, int b) {
    int result;
    if (a > b) {
        result = a;
    } else {
        result = b;
    }
    return result;
}
```

Using the ternary operator in lieu of a complete IF-ELSE statement:
```cpp
// version_ternary.cpp
int max_ternary(int a, int b) {
    int result = (a > b) ? a : b;
    return result;
}
```

Both are logically equivalent.

---

## **Step 2: Compile to Assembly**

Compile without optimization:
```bash
g++ -O0 -S version_if.cpp -o version_if.s g++ -O0 -S version_ternary.cpp -o version_ternary.s
```

You're compiling `version_if.cpp` using `g++` and generating assembly output (`.s` file) with no optimizations (`-O0`). Here’s a breakdown:

- `g++` → Invokes the GNU C++ compiler.
    
- `-O0` → Disables compiler optimizations, ensuring the generated assembly is as close to the original source code as possible.
    
- `-S` → Produces an assembly file instead of an executable or object file.
    
- `version_if.cpp` → Your source file.
    
- `-o version_if.s` → Specifies the output filename for the assembly file.

Then with optimization:
```bash
g++ -O2 -S version_if.cpp -o version_if_O2.s g++ -O2 -S version_ternary.cpp -o version_ternary_O2.s
```

You're compiling two C++ source files, `version_if.cpp` and `version_ternary.cpp`, into assembly with optimization level `-O2`. Here's what each flag does:

- `g++` → Calls the GNU C++ compiler.
    
- `-O2` → Enables moderate optimizations for better performance while keeping compilation time reasonable.
    
- `-S` → Generates an assembly (`.s`) file instead of an executable.
    
- `<source>.cpp` → The input C++ source files.
    
- `-o <output>.s` → Specifies the output assembly file name.
    

### Key Differences:

Compared to `-O0`, `-O2` performs optimizations like:

- Dead code elimination
    
- Function inlining (when beneficial)
    
- Loop unrolling and vectorization (where applicable)
    
- Improved register allocation
    

Since one file (`version_if.cpp`) likely uses an `if` statement and the other (`version_ternary.cpp`) uses a ternary operator (`? :`), you might find differences in the generated assembly, particularly in branching and conditional evaluations.

---

![image](https://github.com/user-attachments/assets/ce6aa20c-9221-43fd-98d0-33900053aba6)

**Analysis**:

- The ternary version uses a conditional move (`cmovg`), which avoids branching.
    
- Branchless code (ternary) can be faster due to fewer pipeline stalls.
