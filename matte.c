/*
 * matte.c
 *
 *  Created on: 22 Dec 2017
 *      Author: root
 */

#include <stdlib.h>
#include <string.h>
#include "matte.h"

tensor *matte_allocate_tensor(size_t *shape, size_t dimensions) {
	tensor *output = malloc(sizeof(tensor));
	output->dimensions = dimensions;
	output->shape = malloc(sizeof(size_t) * dimensions);
	output->indices = malloc(sizeof(size_t) * dimensions);
	size_t valuesLength = 1;
	size_t mult = 1;
	for (size_t i = dimensions; i--;) {
		valuesLength *= (output->shape[i] = shape[i]);
		output->indices[i] = mult;
		if (i) {
			mult *= shape[i];
		}
	}
	output->values = malloc(sizeof(float) * valuesLength);
	output->valuesLength = valuesLength;
	return output;
}

void matte_free_tensor(tensor *toFree) {
	free(toFree->indices);
	free(toFree->shape);
	free(toFree->values);
	free(toFree);
}

tensor *matte_clone_tensor(tensor *cpy) {
	tensor *t = malloc(sizeof(tensor));
	t->valuesLength = cpy->valuesLength;
	t->dimensions = cpy->dimensions;
	t->shape = malloc(sizeof(size_t) * cpy->dimensions);
	memcpy(t->shape, cpy->shape, sizeof(size_t) * cpy->dimensions);
	t->indices = malloc(sizeof(size_t) * cpy->dimensions);
	memcpy(t->indices, cpy->indices, sizeof(size_t) * cpy->dimensions);
	t->values = malloc(sizeof(float) * cpy->valuesLength);
	memcpy(t->values, cpy->values, sizeof(float) * cpy->valuesLength);
	return t;
}

tensor *matte_clone_tensor_shape(tensor *cpy) {
	tensor *t = malloc(sizeof(tensor));
	t->valuesLength = cpy->valuesLength;
	t->dimensions = cpy->dimensions;
	t->shape = malloc(sizeof(size_t) * cpy->dimensions);
	memcpy(t->shape, cpy->shape, sizeof(size_t) * cpy->dimensions);
	t->indices = malloc(sizeof(size_t) * cpy->dimensions);
	memcpy(t->indices, cpy->indices, sizeof(size_t) * cpy->dimensions);
	t->values = malloc(sizeof(float) * cpy->valuesLength);
	return t;
}

void matte_set_tensor_from_tensor(tensor *a, tensor *b) {
}

void matte_set_tensor_from_scalar(tensor *a, float b) {
}

void matte_add_tensor_from_tensor(tensor *a, tensor *b) {
	for (size_t i = a->valuesLength; i--;) {
		a->values[i] += b->values[i];
	}
}

void matte_add_tensor_from_scalar(tensor *a, float b) {
	for (size_t i = a->valuesLength; i--;) {
		a->values[i] += b;
	}
}

tensor *matte_add_tensor_and_tensor(tensor *a, tensor *b) {
}
tensor *matte_add_tensor_and_scalar(tensor *a, float b) {
}

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
