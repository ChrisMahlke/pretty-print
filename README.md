## PrettyPrint

A program to optimally format text from an input file so that the words fit within specified line lengths. The goal is to minimize the "ugliness" or penalty, which is based on the number of spaces left at the end of each line.

This C program is a text formatter that applies a justified formatting strategy on input text. It organizes words into lines, where each line's length does not exceed a maximum line length provided as input.

The program has three main parts:

Reading from an input file: The program takes two command-line arguments: the name of a text file, and an integer representing the maximum line length. The program reads words from the file and stores them in an array. If the file can't be opened, the program prints an error message and exits. If the line length isn't provided or isn't an integer, the program also exits.

Word and line formatting: Using the words from the input file, the program organizes the words into lines. It uses dynamic programming to determine the optimal way to break up the text into lines, minimizing the penalty associated with each line. The penalty of a line is calculated as the cube of the number of extra spaces at the end of the line. However, if a line's words don't fit within the maximum line length, the penalty is considered as infinite, and if it's the last line, the penalty is 0.

Output: After formatting the text, the program prints the minimum total penalty and the formatted text. Each line in the output includes its number, its length, and its contents.

This is a standard problem in the area of dynamic programming and text formatting, often known as the text justification or word wrap problem. It optimizes line breaks in a way to reduce the raggedness of the right margin when text is flush-left formatted.

## Features
* Dynamic programming for efficient optimal text formatting.
* Penalty function to evaluate the cost of a line's formatting.
* Supports up to 2048 words, each of a maximum length of 30 characters.
* Defaults to a maximum line width of 80 characters (standard telnet screen size) but can be adjusted as needed.

## Runtime Analysis

The runtime of this program is primarily determined by the format function. Given num words, for every word j, it tries to combine it with previous words (i through j). Thus, its time complexity is O(nM) where n is the number of words and M is the maximum line length. The rest of the operations, such as reading the file or computing penalties, are linear in nature.

## Instructions for Use

1) Compile the program using:
   `gcc -o prettyprint prettyprint.c`

2) Run the program with two arguments: the path to the input file and the maximum line length:
   `./prettyprint sampledata.txt 80`

3) Run the program, passing the path to the input file and the desired maximum line length as arguments.

## Results

**Neat Printing of Paragraphs**

**Problem Description**: 
Imagine having a paragraph made up of words with lengths l1, l2, …, ln. Our task is to print this paragraph neatly onto a page where the maximum permissible line length is M (given that each word length li < M).

**Neatness Measure**:
The neatness of a printed line is inversely proportional to the "extra space" left on it. Specifically, the extra space on a line that contains words from li to lj is calculated as:
Extra Space = M - j + i - sum of the lengths of all words from i to j.

The "penalty" associated with a line is the cube of its extra space. Interestingly, using the cubic measure has been empirically observed to provide a good heuristic for neatness. However, we exclude the last line from this penalty calculation.

**Goal**: 
Our primary aim is to devise a dynamic programming solution to determine the neatest way to print the paragraph. The expected output is twofold: 
1. The paragraph split into optimal lines.
2. The total penalty (neatness measure) of the printed paragraph.

In this context, a "word" denotes any continuous sequence of characters excluding blank spaces.

**Efficient Penalty Calculation**:
An efficient way to compute the penalty is through a dynamic approach:

1. **Storage**: I've implemented a temporary array L[0, …, n], where L[i] accumulates the lengths of words from 1 through i: 
L[i] = L[i – 1] + li
Thus, the penalty between words i and j can be reformulated as:
penalty(i, j) = (M – j + i – (L[j] - L[i – 1])) cubed.

2. **Time & Space Complexity**: Each value in our penalty array requires n calculations as we iterate through all possible starting words. Therefore, the algorithm operates in O(n^2) time and uses O(n) space, given our array storage.

**Recursive Definition**:
To devise a solution, we can recursively define the value of our optimal solution:
Let p(j) signify the optimal cost of neatly printing words 1 through j. If i is the index of the first word on the last line of our optimal solution, our recurrence relation becomes:
p(j) = p(i-1) + penalty(i,j)
However, the optimal starting word i is unknown, leading us to the following formula:
p(j) = minimum value of (p(i-1) + penalty(i,j) for all i).


