#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_list.h"
#include "../util/style.h"

/*
 * len			-> current number of elements in the array
 * capacity		-> allocated capacity (max number of elements the array can hold)
 * item_size	-> size in bytes of each item
 * data			-> pointer to the memory block storing the items
 */
struct array_list {
	size_t len;
	size_t capacity;
	size_t item_size;
	void *data;
};

// clamp to 8
static inline size_t grow_capacity(size_t capacity)
{
	return (capacity < 8 ? 8 : capacity * 2);
}

/*
 * index addressing:
 *
 * result = base + index * element size
 *
 * casting to char * ensures that the pointer arithmetic moves one byte at
 * a time and casting it back to void * ensures it's generic
 */
static inline void *array_list_offset(array_list *arr, size_t index)
{
	return (void *) ((char *) arr->data + (index * arr->item_size));

}

array_list *array_list_create(size_t item_size, size_t initial_capacity)
{
	array_list *arr;

	arr = (array_list *) malloc(sizeof(array_list));
	if (arr == NULL) {
		fprintf(stderr, LERR "Failed to allocate memory for array list\n");
		perror("malloc");
		exit(1);
	}

	arr->capacity = initial_capacity;
	arr->item_size = item_size;
	arr->len = 0;
	arr->data = malloc(item_size * initial_capacity);

	if (arr->data == NULL) {
		fprintf(
			stderr,
			LERR "Failed to allocate memory for the data in array list\n"
		);
		perror("malloc");
		free(arr);
		exit(1);
	}

	return arr;
}

size_t array_list_append(array_list *arr, void *item)
{
	if (arr->len == arr->capacity) {
		arr->capacity = grow_capacity(arr->capacity);
		void *data = realloc(arr->data, arr->item_size * arr->capacity);
		if (!data) {
			fprintf(stderr, LERR "Failed to realloc memory for array list\n");
			perror("realloc");
			exit(1);
		}

		arr->data = data;
	}

	// index to be stored (on a free space to the right of last appeneded)
	size_t index = arr->len;
	arr->len++;

	memcpy(
		array_list_offset(arr, index),
		item,
		arr->item_size
	);

	return index;
}

void *array_list_get(array_list *arr, u32 index)
{
	if (index >= arr->len) {
		fprintf(stderr, LERR "Attempted to index out of bounds of an array\n");
		exit(1);
	}

	return array_list_offset(arr, index);
}

size_t array_list_length(array_list *arr)
{
	return arr->len;
}

void array_list_remove(array_list *arr, u32 index)
{
	if (arr->len == 0) {
		fprintf(
			stderr, LERR "Attempted to delete an element in an empty array\n"
		);
		exit(1);
	}

	if (index >= arr->len) {
		fprintf(
			stderr,
			LERR "Attempted to delete an element out of bounds of an array\n"
		);
	}

	arr->len--;

	void *item_ptr = array_list_offset(arr, index);
	void *end_ptr = array_list_offset(arr, arr->len);
	memcpy(item_ptr, end_ptr, arr->item_size);
}

void array_list_free(array_list *arr)
{
	free(arr->data);
	free(arr);
}

