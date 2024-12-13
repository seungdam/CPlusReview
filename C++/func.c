#include <stdio.h>
#include "func.h"

void print_map(MyPair arr[], int size)
{
	for (int i = 0; i < size; ++i)
	{
		printf("{%d, %d} ", arr[i].key, arr[i].value);
	}
}

void print_arr(int arr[], int size)
{
	for (int i = 0; i < size; ++i)
	{
		printf("%d",arr[i]);
	}
}

