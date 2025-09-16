#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#include "array_list.h"
#include "../logging/log.h"

/*
 * len			-> current number of elements in the array
 * capacity		-> allocated capacity (max number of elements the array can hold)
 * item_size	-> size in bytes of each item
 * data			-> pointer to the memory block storing the items
 */
struct array_list {
	usize len;
	usize capacity;
	usize item_size;
	void *data;
};

// clamp to 8
static inline usize grow_capacity(usize capacity)
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
static inline void *array_list_offset(const array_list *arr, usize index)
{
	return (void *) ((char *) arr->data + (index * arr->item_size));

}

array_list *array_list_create(usize item_size, usize initial_capacity)
{
	array_list *arr = NULL;

	arr = (array_list *) malloc(sizeof(array_list));
	if (arr == NULL) {
		LOG_ERR("malloc failed to allocate memory for the array list");
		exit(1);
	}

	arr->capacity = initial_capacity;
	arr->item_size = item_size;
	arr->len = 0;
	arr->data = malloc(item_size * initial_capacity);

	if (arr->data == NULL) {
		LOG_ERR("malloc failed to allocate memory block for the array list");
		free(arr);
		exit(1);
	}

	return arr;
}

usize array_list_append(array_list *arr, const void *item)
{
	if (arr->len == arr->capacity) {
		arr->capacity = grow_capacity(arr->capacity);
		void *data = realloc(arr->data, arr->item_size * arr->capacity);
		if (!data) {
			LOG_ERR("realloc failed to realloc the memory block for the array");
			exit(1);
		}
		arr->data = data;
	}

	usize index = arr->len;
	arr->len++;
	memcpy(array_list_offset(arr, index), item, arr->item_size);
	return index;
}

void *array_list_get(const array_list *arr, u32 index)
{
	if (index >= arr->len) {
		LOG_ERR("Attempted out of bounds indexing for the array list");
		exit(1);
	}

	return array_list_offset(arr, index);
}

usize array_list_length(const array_list *arr)
{
	return arr->len;
}

void array_list_remove(array_list *arr, u32 index)
{
	if (arr->len == 0) {
		LOG_ERR("Attempted to delete from an empty array list");
		exit(1);
	}

	if (index >= arr->len) {
		LOG_ERR("Attempted to delete an element from out of bounds of an array");
		exit(1);
	}

	arr->len--;
	void *item_ptr = array_list_offset(arr, index);
	void *end_ptr = array_list_offset(arr, arr->len);
	memcpy(item_ptr, end_ptr, arr->item_size);
}

void array_list_free(array_list *arr)
{
	free(arr->data);
	arr->data = NULL;
	free(arr);
}

