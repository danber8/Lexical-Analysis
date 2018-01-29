# Lexical-Analysis

Problem Description

In this problem, you should implement thelexical  analysistask for a limited version(i.e., the depth of the nested loops) of a programming language. Lexical analysis is thefirst stage that compilers parse and detect the possible syntax errors.

Ideally, any new (programming) languages can be designed and analyzed in the similarmanner.  You will need to analyze a Pascal-and-C-like language in this programmingassignment.

Given a segment of the source code, your C++ code should analyze the code andextract all tokens, which include:

•Keywords:keywords are the words reserved by the language. They are all upper-case. In the case of this simplified language, the keywords are restricted to the set{”BEGIN”, ”END”, ”FOR”}

•Identifiers:An identifier is used to describe the variables, which are all lower-case•Constants:Numbers like 10, ... .

•Operators:all arithmetic operations (i.e., +, -, *, and /), ”++” and ”=”

•Delimiters:like ”,” and ”;”

Your C++ code should input a text file from user, which contains the expressionhe/she wants the compilers to analyze. Then, your code should parse the input, detectthe tokens, classify them, and print out the results.

With this assignment, you will get practice with the stack implementation which isone of the most widely used data structures. Besides, you will be familiar with stringprocessing and input parsing, which are of crucial importance in most C++ projects.

Details

1. (Data Structures:) You need to implement a stack data structure to keep track of theprocessing and compute the depth of the nested loops. Adding elements to the stack
(push) and removing objects from it (pop) are two essential methods that must beimplemented. You can use any data structure to implement the stack, e.g., arrays,linked-lists, etc.

2. (Algorithms:) Once the input expression is given, your program should decide whichcharacter should be inserted to the stack, and when the result needs to be computed.You need to detect the possible syntax errors while tracing the depth of the nestedloops.
