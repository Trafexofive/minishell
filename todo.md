

### To-do;

# ----------------

- 
In Bash, curly braces {} serve various purposes, and understanding their usage is essential for effective scripting. Let's explore a few scenarios where curly braces come into play:

    Variable Expansion:
        When expanding variables, curly braces are useful in specific cases:
            Basic Variable Expansion: For simple variable substitution, like echo "$var", the braces are optional.
            Complex Variable Names: When you want to expand a variable within a string, use braces to avoid ambiguity. For example:
                echo "${var}bar" ensures that the variable foo is expanded, not foobar.
            Array Elements: To expand array elements, use braces: ${array[42]}.
            Parameter Expansion: Curly braces are necessary for operations like ${filename%.*} (to remove file extensions).
            Positional Parameters: When expanding positional parameters beyond 9, use braces: "$8 $9 ${10} ${11}".

    Brace Expansion:
        Brace expansion generates strings based on specified patterns:
            {a,b,c} expands to a, b, and c.
            {1..5} expands to 1, 2, 3, 4, and 5.
            {a..z} generates the entire lowercase alphabet.
            {file1,file2}.txt expands to file1.txt and file2.txt.

    Subshell Creation:
        Nesting curly braces can create subshells:
            Processes within the innermost braces run in a separate subshell.
            Useful for scoping and isolating commands.
