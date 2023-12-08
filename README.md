# LL1-Parser
The code provides a functional implementation of an LL(1) parsing table generator for a context-free grammar.

## Report on the Given Code

The provided C code appears to be an implementation of an LL(1) parsing table generator for a context-free grammar. The code calculates the First and Follow sets for each non-terminal in the grammar, and then constructs the LL(1) parsing table based on these sets. Finally, it prints the LL(1) parsing table.

### Code Structure

1. **Data Structures:**
   - The code uses two main data structures: `struct rightNode` and `struct production`.
     - `struct rightNode` represents a right-hand side of a production, containing a string (`rname`) and a pointer to the next rightNode (`rnext`).
     - `struct production` represents a production rule, containing a left-hand side (`lname`), a pointer to the first rightNode (`rnode`), First and Follow sets, LL(1) parsing table entries, and links to the next production rule (`prodNext`).

2. **Functions:**
   - `isNonTerminal(char ch)`: Determines whether a character is a non-terminal in the production rules.
   - `isPresent(char* string, char ch)`: Checks if a character is present in a string.
   - `calculatingFirst(struct production* tempProd)`: Calculates the First set for a given production rule.
   - `calculatingFollow(struct production* tempProd)`: Calculates the Follow set for a given production rule.
   - `gatherTerminal(char ch)`: Collects the terminals from the grammar rules.
   - `isExist(char ch)`: Determines whether a character is a terminal.
   
3. **Main Logic:**
   - The code reads the grammar rules, builds the corresponding data structures, and calculates the First and Follow sets for each non-terminal in two separate loops.
   - It then constructs the LL(1) parsing table based on the First and Follow sets.

### Functionality

1. **Grammar Input:**
   - The user is prompted to enter the size (number) of production rules.
   - For each production rule, the user inputs the rule in the form of `A -> XYZ`.

2. **First and Follow Set Calculation:**
   - The code calculates the First set for each non-terminal in the grammar.
   - It calculates the Follow set for each non-terminal, considering the `#` (epsilon) symbol in the First set calculation.

3. **Terminal Collection:**
   - The code collects the terminals from the grammar rules, including the `$` symbol.

4. **LL(1) Parsing Table Construction:**
   - The code constructs the LL(1) parsing table by considering the First and Follow sets.
   - It handles epsilon productions and errors appropriately.

5. **Output:**
   - The code prints the LL(1) parsing table, displaying the entries for each non-terminal and terminal pair.

### Suggestions for Improvement:

1. **User Input Validation:**
   - The code assumes correct user input. It would be beneficial to include input validation to handle potential errors gracefully.

2. **Memory Management:**
   - The code uses dynamic memory allocation with `malloc`. It's essential to free allocated memory using `free` to avoid memory leaks.

3. **Code Comments:**
   - Adding comments to explain the purpose and functionality of each section of the code can improve code readability and understanding.

4. **Error Handling:**
   - The code does not handle potential errors, such as division by zero or invalid input. Including error-checking mechanisms would enhance the robustness of the code.

5. **Optimization:**
   - The code could potentially be optimized for efficiency, but this depends on specific requirements and constraints.
