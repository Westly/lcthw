/* 
 *	External Research
 *	http://www.cprogramming.com/tutorial/printf-format-strings.html
 *	%[flag][min width][precision][length modifier][conversion specifier]
 *
 *	f 	Display the floating point number using decimal representation 	3.1415
 *	e 	Display the floating point number using scientific notation with e 	1.86e6 (same as 1,860,000)
 *	E 	Like e, but with a capital E in the output 	1.86E6
 *	g 	Use shorter of the two representations: f or e 	3.1 or 1.86e6
 *	G 	Like g, except uses the shorter of f or E 	3.1 or 1.86E6
 *
 *	The "precision" modifier is written ".number", and has slightly different meanings for the 
 *	different conversion specifiers (like d or g). 
 *
 *
 *     \n (newline)
 *     \t (tab)
 *     \v (vertical tab)
 *     \f (new page)
 *     \b (backspace)
 *     \r (carriage return)
 *
 * */

#include <stdio.h>

// Without arguements. 
int main() 
{
	// Integer. Declare types before using them.
	// age == variable. No $age, just age
	int age = 10;
	int height = 72;

	// %d == double? Decimal? \n for new line
	printf ("I am %d years old.\n", age);
	printf ("I am %d inches tall.\n", height);

	// Returning false ends the program?
	return 0;
}
