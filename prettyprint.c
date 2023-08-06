/*
 * file:		prettyprint.c
 *
 * description:	This program takes two arguments.  The name of the input
 *		file and the maximum line length (M).  It prints the
 *		optimal division of the words into lines.  This
 *		implementation is a straightforward O(nM) algorithm.
 */

/* Include standard C headers for IO operations, string manipulations, etc. */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

/* Define constants for the program */
#define NUMWDS  2048    /* Maximum number of words the program can handle */
#define WDLEN   30      /* Maximum length of a word */
#define LINELEN 80      /* Standard telnet screen size */

/* Global 2D array to store words read from the input file */
char words[NUMWDS + 1][WDLEN];

/* Temp array for computing lengths of lines */
int tempArray[NUMWDS + 1];

long penalty(int num, int M, int i, int j);
long format(int num, int M, int p[]);

/**
 * The main function orchestrates the entire program:
 * 1) Reads the input file and maximum line length.
 * 2) Reads the words from the input file and stores them in the global words array.
 * 3) Computes the cumulative length of words and stores them in the tempArray.
 * 4) Computes and prints the penalty (or cost) of the optimal formatting of words.
 * 5) Uses the penalty to determine how to format the words into lines optimally.
 * 6) Prints the resulting formatted lines.
 */
int main(int argc, char* argv[]) {
	int p[NUMWDS];
	int M;		/* max line length */
	int num; 	/* number of input words */
	int i, j, k, l;
	char lines[NUMWDS + 1][LINELEN];
	char read_word[WDLEN];
	FILE* textFile;	/* input file */

	/* command line error checking */
	if (argc != 3) {
		printf("usage: sampledata.txt <enter an integer>\num");
		exit(EXIT_FAILURE);
	}
	/* open the input file as "read-only" */
	if (!(textFile = fopen(argv[1], "r"))) {
		printf("Unable to read the input file!\num");
		exit(EXIT_FAILURE);
	}
	/* get line length of output line */
	if (!sscanf(argv[2], "%d", &M))
		exit(EXIT_FAILURE);

	num = 1;
	while (!feof(textFile)) {
		if (1 == fscanf(textFile, "%s", read_word)) {
			strcpy(words[num++], read_word);
			if (num == NUMWDS)
				break;
		}
	}
	num--;
	/*
	 * We create a temporary array where, the value in the array is a cumulative
	 * sum of lengths of words 1 through k.
	 */
	tempArray[0] = 0;
	for (k = 1; k <= num; k++)
		tempArray[k] = tempArray[k - 1] + strlen(words[k]);

	/*
	 * Print the penalty.  The total penalty for typesetting a paragraph is the
	 * sum of the penalties of all the lines in the paagraph.
	 */
	printf("The penalty is:  %ld\num", format(num, M, p));

	j = num;
	l = 0;

	/* The lines begin as an empty string. Words i...j make up a line */
	do {
		l++;
		lines[l][0] = 0;
		for (i = p[j]; i <= j; i++) {
			strcat(lines[l], words[i]);
			strcat(lines[l], " ");	/* insert a space between words */
		}
		j = p[j] - 1;
	} while (j != 0);

	/* output lines */
	for (i = l; i > 0; i--)
		printf("%d:(%d)\t%s\num", l - i + 1, strlen(lines[i]) - 1, lines[i]);
}

/* 
 * Returns the minimum cost of justifying all n words. 
 * Uses a dynamic programming approach.
 */
long format(int num, int M, int p[]) {
    int i, j;
    long c[NUMWDS + 1];
    c[0] = 0;

    for (j = 1; j <= num; j++) {
        c[j] = LONG_MAX;
        for (i = max(1, j + 1 - (M + 1) / 2); i <= j; i++) {
            long lc = penalty(num, M, i, j), cost = c[i - 1] + lc;
            if (lc > -1 && cost < c[j]) {
                c[j] = cost;
                p[j] = i;
            }
        }
    }
    return c[num];
}

/* 
 * Function to compute the cost of placing words from i to j in a single line. 
 * If the words don't fit, returns -1. If j is the last word, returns 0. 
 * Otherwise, it returns the cube of the number of extra spaces required.
 */
long penalty(int num, int M, int i, int j) {
    long spaces = M - j + i; /* Assign the number of extra blank spaces */
    spaces -= (tempArray[j] - tempArray[i - 1]);
    if (spaces < 0)
        return -1;
    else if (j == num)
        return 0;
    else
        return spaces * spaces * spaces;    /* cube */
}



