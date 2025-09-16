#ifndef ARRAY_LIST_H 
#define ARRAY_LIST_H

#include <stdlib.h>
#include "../types.h"

/*
 * A dynamic array structure that can hold items of any type.
 *
 * defined as an opaque type which must be accessed through the function
 * implementations
 */
typedef struct array_list array_list;

/*
 * Creates an array list via malloc that stores the item size and initial
 * capacity.
 *
 * item_size		-> size of the item in bytes
 * initial_capacity	-> initial capacity for declaring an array_list
 * 
 * Returns a pointer to an allocated array_list struct.
 */
array_list *array_list_create(usize item_size, usize initial_capacity);

/*
 * Appends an item to the end of the array list
 * reallocates memory to the array if its capacity was reached
 * if it does reallocate memory, it doubles the capacity
 *
 * arr	-> a pointer to an array list allocated by array_list_create()
 * item	-> the item to append to the array list
 * 
 * Return the index of the appended item
 */
usize array_list_append(array_list *arr, const void *item);

/*
 * Returns a pointer to the item at the given index in the array list.
 *
 * arr		-> a pointer to an array list allocated by array_list_create()
 * index	-> index of the item to return (0 <= index < length of array)
 * 
 * Returns a void pointer to the item which should be casted.
 */
void *array_list_get(const array_list *arr, u32 index);

/*
 * Returns the current length of the array list.
 *
 * arr		-> a pointer to an array list allocated by array_list_create()
 * 
 * Returns the current length of the array list.
 */
usize array_list_length(const array_list *arr);


/*
 * Removes an item at the given index in the array list. Subsequent items
 * are then shifted down.
 *
 * arr	-> a pointer to an array list allocated by array_list_create()
 */
void array_list_remove(array_list *arr, u32 index);

/*
 * Frees up memory of the allocated array_list struct and the memory block
 * allocated to it.
 *
 * arr -> a pointer to an array list allocated by array_list_create()
 */
void array_list_free(array_list *arr);

#endif
