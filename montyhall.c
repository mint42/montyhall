#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define DEFAULT_SIZE 10000
#define RED    "\e[1;35m"
#define GREEN  "\e[1;32m"
#define WHITE  "\e[m"

void		print_usage(void)
{
	printf("\n");
	printf("*************************************************\n");
	printf("*  usage: ./montyhall [iterations]              *\n");
	printf("*  next time try giving a sample size!          *\n");
	printf("*  (or change the DEFAULT_SIZE in montyhall.c)  *\n");
	printf("*************************************************\n");
}

void		get_percentages(unsigned int sample_size, unsigned int *with, unsigned int *without)
{
	unsigned int	door;
	unsigned int	bad_door;
	unsigned int	choice;

	srand(time(0));
	for (unsigned int i = 0; i < sample_size; i++)
	{
		door = (rand() % 3) + 1;
		choice = (rand() % 3) + 1;
		bad_door = 1;
		if (bad_door == choice || bad_door == door)
		{
			++bad_door;
			if (bad_door == choice || bad_door == door)
				++bad_door;
		}
		if (choice == door)
			++*without;
		choice = (choice == 3) ? 1 : choice + 1; 
		if (choice == bad_door)
			choice = (choice == 3) ? 1 : choice + 1; 
		if (choice == door)
			++*with;
	}
}

int		main(int argc, char **argv)
{
	unsigned int	sample_size;
	unsigned int	correct_with_change = 0;
	unsigned int	correct_without_change = 0;

	if (argc > 2)
	{
		printf("please give only one sample size\n");
		print_usage();
		return (1);
	}
	sample_size = (argc == 2) ? atoi(argv[1]) : DEFAULT_SIZE;
	get_percentages(sample_size, &correct_with_change, &correct_without_change);
	printf("Without Change:  %s%.2f%%\n", RED, ((float)((float)correct_without_change / (float)sample_size)) * 100);
	printf(WHITE);
	printf("With Change:     %s%.2f%%\n", GREEN, ((float)((float)correct_with_change / (float)sample_size)) * 100);
	printf(WHITE);
	if (argc == 1)
		print_usage();
	return (0);
}
