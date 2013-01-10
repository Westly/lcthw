/*
 * Extra credit
 * d or i	Signed decimal integer	392
 * u	Unsigned decimal integer	7235
 * o	Unsigned octal	610
 * x	Unsigned hexadecimal integer	7fa
 * X	Unsigned hexadecimal integer (uppercase)	7FA
 * f	Decimal floating point, lowercase	392.65
 * F	Decimal floating point, uppercase	392.65
 * e	Scientific notation (mantissa/exponent), lowercase	3.9265e+2
 * E	Scientific notation (mantissa/exponent), uppercase	3.9265E+2
 * g	Use the shortest representation: %e or %f	392.65
 * G	Use the shortest representation: %E or %F	392.65
 * a	Hexadecimal floating point, lowercase	-0xc.90fep-2
 * A	Hexadecimal floating point, uppercase	-0XC.90FEP-2
 * */

#include <stdio.h>

int main(int argc, char *argv[]) 
{
	int extra_credit = 10;
	int distance = 100;
	float power = 2.34f;
	double super_power = 56789.5432;
	char initial = 'A';
	char first_name[] = "Zed";
	char last_name[] = "Shaw";

	printf("You are %d miles away.\n", distance);
	printf("You have %f levels of power.\n",  power);
	printf("You have %f awesome powers.\n", super_power);
	printf("I have an initial %c.\n", initial);
	printf("I have a first name %s.\n", first_name);
	printf("I have a last name %s.\n", last_name);
	printf("My whole name is %s %c. %s.\n", first_name, initial, last_name);
	printf("10 as an unassigned octal : %o\n", extra_credit);
	printf("10 as a Hecadecimal : %x\n", extra_credit); 
	printf("10 as Scientific Notation : %e\n", extra_credit); 
	return 0;

	/* Cant print an empty string. Causes error.*/
}
