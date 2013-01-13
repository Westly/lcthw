// Normal header files
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void die(const char *message)
{
	if(errno) {
		perror(message);
	} else {
		printf("ERROR: %s\n", message);
	}

	exit(1);
}

// a typedef creates a fake type, in this case for a function pointer
// a typedef is a Sype deffinition, like int = integer(s), char = character(s)
typedef int (*compare_cb)(int a, int b);

/**
 * A classic bubble sort function that uses the
 * compare_cb to do the sorting
 */
// Function called bubble sort, that takes an array of numbers, count, and the typedef?
int *bubble_sort(int *numbers, int count, compare_cb cmp)
{
	int temp = 0;
	int i = 0;
	int j = 0;
	// Variable target allocates memory for the number of ints * the size of an int.
	int *target = malloc(count * sizeof(int));

	// If target is not set, memory error.
	if (!target) die("Memory Error.");
	
	// void *memcpy(void *str1, const void *str2, size_t n); 
	// Put all the numbers into target 
	memcpy(target, numbers, count * sizeof(int));

	// For all the numebrs in target
	for(i = 0; i < count; i++) {
		// Loop though again, the -1 is important.
		for(j = 0; j < count - 1; j++) {
			// cmp points to the typedef made
			// if the int has a positive value
			if(cmp(target[j], target[j+1]) > 0) {
				// assign to temp
				temp = target[j+1];
				// Change the possition
				target[j+1] = target[j];
				// Then set it in the other spot
				target[j] = temp;
			}
		}
	}

	return target;
}

int sorted_order(int a, int b)
{
	return a - b;
}

int reverse_order(int a, int b)
{
	return b - a;
}

int strange_order(int a, int b)
{
	if(a == 0 || b == 0) {
		return 0;
	} else {
		return a % b;
	}
}

/**
 * Used to test that we are sorting things correctly
 * by doing the sort and printing it out
 * */
void test_sorting(int *numbers, int count, compare_cb cmp)
{
	int i = 0;
	int *sorted = bubble_sort(numbers, count, cmp);

	if(!sorted) die("Failerd to sort as requested");
	
	for(i = 0; i < count; i++) {
		printf("%d ", sorted[i]);
	}
	printf("\n");

	// Remove from memory
	free(sorted);
}

int main(int argc, char * argv[])
{
	if (argc < 2) die("USAGE: ex18 4 3 1 5 6");

	int count = argc - 1;
	int i = 0;
	// ** means an array you can modify?
	char **inputs = argv + 1;

	// Allocate memory for the numebers, if it cant be done, exit
	int *numbers = malloc(count * sizeof(int));
	if(!numbers) die("Memory error.");

	// for each number in in inputs, add to numbers after we use atoi to make sure its an int
	for (i = 0; i < count; i++) {
		numbers[i] = atoi(inputs[i]);
	}

	// Change the order of the numbers and run the test.
	test_sorting(numbers, count, sorted_order);
	test_sorting(numbers, count, reverse_order);
	test_sorting(numbers, count, strange_order);

	// always free malloc
	free(numbers);

	return 0;
}





