/*
 * matter.h
 *
 *  Created on: 17 Dec 2017
 *      Author: root
 */

#include <stddef.h>

#ifndef MATTE_H_
#define MATTE_H_

typedef struct {
	size_t dimensions;			// Amount of dimensions in tensor.
	size_t *shape;				// Shape of tensor.
	size_t *indices;			// Used to convert multiple indices into a single one.

	float *values;				// Actual values in tensor.
	size_t valuesLength;		// How many values there are.
} tensor;

tensor *matte_allocate_tensor(size_t *shape, size_t dimensions);
void matte_free_tensor(tensor *toFree);

tensor *matte_clone_tensor(tensor *cpy);
tensor *matte_clone_tensor_shape(tensor *cpy);

void matte_set_tensor_from_tensor(tensor *a, tensor *b);
void matte_set_tensor_from_scalar(tensor *a, float b);

void matte_add_tensor_from_tensor(tensor *a, tensor *b);
void matte_add_tensor_from_scalar(tensor *a, float b);

tensor *matte_add_tensor_and_tensor(tensor *a, tensor *b);
tensor *matte_add_tensor_and_scalar(tensor *a, float b);

void matte_subtract_tensor_from_tensor_to_a(tensor *a, tensor *b);
void matte_subtract_tensor_from_tensor_to_b(tensor *a, tensor *b);
void matte_subtract_tensor_from_scalar(tensor *a, float b);
void matte_subtract_scalar_from_tensor(float b, tensor *a);

tensor *matte_subtract_tensor_and_tensor(tensor *a, tensor *b);
tensor *matte_subtract_tensor_and_scalar(tensor *a, tensor *b);
tensor *matte_subtract_scalar_and_tensor(tensor *a, tensor *b);

void matte_multiply_tensor_from_tensor(tensor *a, tensor *b);
void matte_multiply_tensor_from_scalar(tensor *a, float b);

tensor *matte_multiply_tensor_and_tensor(tensor *a, tensor *b);
tensor *matte_multiply_tensor_and_scalar(tensor *a, float b);

void matte_divide_tensor_from_tensor_to_a(tensor *a, tensor *b);
void matte_divide_tensor_from_tensor_to_b(tensor *a, tensor *b);
void matte_divide_tensor_from_scalar(tensor *a, float b);
void matte_divide_scalar_from_tensor(float b, tensor *a);

tensor *matte_divide_tensor_and_tensor(tensor *a, tensor *b);
tensor *matte_divide_tensor_and_scalar(tensor *a, tensor *b);
tensor *matte_divide_scalar_and_tensor(tensor *a, tensor *b);

float matte_max(tensor *value);
float matte_min(tensor *value);

#endif
