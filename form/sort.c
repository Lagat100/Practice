#include <stdio.h>


void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void bubble_sort(int *array, size_t size)
{
	for (size_t i = 0; i < size - 1; ++i)
	{
		for (size_t j = 0; j < size - 1 - i; ++j)
		{
			if (array[j] > array[j + 1])
			{
				swap(&array[j], &array[j + 1]);

				// Print the array after each swap
				printf("After swap: ");
				for (size_t k = 0; k < size; ++k)
				{
					printf("%d ", array[k]);
				}
				printf("\n");
			}
		}
	}
}

int main()
{
	int arr[] = {64, 25, 12, 22, 11};
	size_t n = sizeof(arr) / sizeof(arr[0]);

	printf("Original array: ");
	for (size_t i = 0; i < n; ++i)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");

	bubble_sort(arr, n);

	printf("Sorted array: ");
	for (size_t i = 0; i < n; ++i)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");

	return 0;
}

