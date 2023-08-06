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

Suppose we want to print a paragraph neatly on a page. The paragraph consists of words of length l1,l2,…,ln.The maximum line length is M. (Assume li < M always.) We define a measure of neatness as follows. The extra space on a line (using one space between words) containing words li through lj  is 
M – j + i - ∑jk=1 l..

The penalty is the sum over all lines except the last of the cube of the extra space at the end of the line. This has been proven to be an effective heuristic for neatness in practice. We want to find a dynamic programming algorithm to determine the neatest way to print a paragraph. The algorithm prints an optimal division of words into lines. The output is the text split into lines appropriately, and the numerical value of the penalty. A word in this context is any contiguous sequence of characters not including blank spaces.

Efficient algorithm to compute the penalty:

Since each p(k) for 1 ≤ k < j will be available the time p(j) is computed, we calculate the values of the array p from index 1 to n.  We need a method for recording the optimal arrangement of words, so we store an array c, where c(k) is the I which led to the optimal p(k).  Compute the arrays for p and c, and the optimal cost will be p(n) and optimal solution will be found by working from the bottom up by printing words c(n) through n on the last line, and then words c(c(n)-1) through c(n) – 1 on the next line up, and so on.  I created a temporary array L[0, …, n], where L[i] is the cumulative sum of the lengths of words 1 through i:  L[i] = L[i – 1] + li ≡ ∑jk=1 l k .  In order to compute the penalty(i, j) we simply modify the formula: penalty(i, j) = (M – j + i – (L[j] - L[i – 1]))3 .  Since each value of p requires n calculations as each i is considered it runs in O(n2) time, and uses O(n) space for the arrays.

To prove a recursive definition of the value of the optimal solution:

We let p(j) be the optimal cost of printing words 1 through j.  If i is the index of the first word printed on the last line of an optima solution then p(j) = p(i-1) + penalty(i,j).  We do not know which i is optimal, so we recurse through: p(j) = min (p(i-1) + penalty(i,j)). 

