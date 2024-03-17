# Chapter 10, Exercise 10
Discussion on how to use text files to test the Calculator program.

## Recap of 7.3 Error handling
Once the first working version of a program has been implemented, it wise to proceed to testing.

This essentially consists of systematically attempting to produce and locate bugs.

Feeding the program a large variety of input, both good and bad, is an effective starting-point.

Know that the number and causes of bugs can be surprising and overwhelming.

The process can be made less demotivating by challenging oneself to outsmart the program by hunting down as many bugs as possible.

There is no one-size-fits-all approach to systematically testing a program and identifying all errors.

And while systematic testing can get you a long way, it is also important to perform tests using unpredictable input.

For example, testing an arithmetic expression parser using random HTML source files scraped from the web may seem unconventional, but it could help uncover unexpected bugs.

## Systematic vs. Fuzz testing
### Systematic testing
> Provides the program with specific input, expects a specific output or behavior. Used to verify correctness according to specifications.

### Fuzz testing
> Provides a program with unconventional input, uncovers errors and sometimes vulnerabilities. Used to test the ability to handle unexpected input and recover from error states.

These types of testing complement each other and can improve the overall quality of a program.

## Approach

1. Use the 'from x' and 'to y' commands to read in expressions from a text file, and output the results to another text file.
2. I have some qualms about the security of this thing:
    A. Without comprehensive checks, I think it would be unwise to allow the user to enter the file path themselves for these commands.
    B. I would like to prevent the use of these commands if they themselves are contained in the text file being loaded, to prevent infinite recursion and similar (Also because of point A, if and when custom file paths are allowed).
3. To prevent these potential vulnerabilities listed above:
    A. Hardcode the file paths into the program for now.
    B. In the implementation of 'from x', check which input stream is in use, throw error if not of type std::cin.
    It would go something like this:
    ```c++
    class Parser {
    public:
        void reset_is() { is = std::cin; }
    private:
        std::istream& is = std::cin; // cin by default

    }
    
    void read_from_file(Parser& p)
    try {
        if (&is != &std::cin) {
            throw std::runtime_error("Cannot read from file from within a text file");
        }
        std::ifstream input_file("file.txt");
        p.is = input_file;
        /* process text file */
        p.reset_is();
    } catch (...) {
        p.reset_is;
        throw;
    }
    ```
4. Also add a a kill switch to both functions, when the number of loaded / written characters exceeds a certain limit, to prevent infinite recursion and similar.
5. Allow the user to test the 'from x' and 'to y', commands with the limited functionality outlined above.
6. Use the functions that implement the commands for running a series of tests:
    6.1. Systematic testing, load in a file of predefined expressions, output the results to another file.
    6.2. Compare the results written to disk with another file of predefined expected outcomes.
    6.3. Fuzz testing, load in a file of some scraped web data or similar, expect it to gracefully handle all errors, output the "logs" to disk. (Really 'barebones' at the moment)