/*
 * matter.c
 *
 *  Created on: 17 Dec 2017
 *      Author: root
 */

#include "matte.h"

#include <stdlib.h>

struct tensor* create_tensor(unsigned int* shape, unsigned int dimensions) {
	struct tensor* t = malloc(sizeof* t); // Create a tensor struct
	t->shape = (unsigned int*) malloc(sizeof(int) * dimensions); // Create an array for the shape
	t->valuesLength = 1; // Work out the size of the values
	for (unsigned int i = 0; i < dimensions; i++) {
		t->valuesLength *= shape[i];
		t->shape[i] = shape[i];
	}
	t->dimension = (unsigned int*) malloc(sizeof(int) * dimensions); // Create dimensions
	int multiply = 1;
	for (int i = dimensions; i--;) {
		t->dimension[i] = multiply;
		if (i) {
			multiply *= t->shape[i];
		}
	}
	t->values = (float*) malloc(sizeof(float) * t->valuesLength); // Create space for values
	return t;
}

struct tensor* create_tensor_no_shape_copy(unsigned int* shape, unsigned int dimensions) {
	struct tensor* t = malloc(sizeof* t); // Create a tensor struct
	t->shape = shape;
	t->valuesLength = 1; // Work out the size of the values
	for (unsigned int i = 0; i < dimensions; i++) {
		t->valuesLength *= shape[i];
	}
	t->dimension = (unsigned int*) malloc(sizeof(int) * dimensions); // Create dimensions
	int multiply = 1;
	for (int i = dimensions - 1; i >= 0; i--) {
		t->dimension[i] = multiply;
		if (i) {
			multiply *= t->shape[i];
		}
	}
	t->values = (float*) malloc(sizeof(float) * t->valuesLength); // Create space for values
	return t;
}

void delete_tensor(struct tensor* t) {
	free(t->dimension);
	free(t->shape);
	free(t->values);
	free(t);
}

struct tensor* copy_tensor_shape(struct tensor* from) {
	struct tensor* t = malloc(sizeof* t);
	t->valuesLength = from->valuesLength;
	t->dimensions = from->dimensions;
	t->valuesLength = from->valuesLength;
	t->shape = (unsigned int*) malloc(sizeof(int) * from->dimensions);
	t->dimension = (unsigned int*) malloc(sizeof(int) * t->dimensions);
	for (unsigned int i = 0; i < from->dimensions; i++) {
		t->shape[i] = from->shape[i];
		t->dimension[i] = from->dimension[i];
	}
	t->values = (float*) malloc(sizeof(float) * t->valuesLength);
	return t;
}

struct tensor* copy_tensor(struct tensor* tensor) {
	struct tensor* cpy = create_tensor(tensor->shape, tensor->dimensions);
	fill_tensor(cpy, tensor->values);
	return cpy;
}

void fill_value(struct tensor* tensor, float value) {
	memset(tensor->values, value, tensor->valuesLength);
}

void fill_tensor(struct tensor* tensor, struct tensor* value) {
	unsigned int a = 0;
	unsigned int b = 0;
}

void fill_tensor_no_broadcast(struct tensor* tensor, struct tensor* value) {
	memcpy(tensor->values, value->values, tensor->valuesLength);
}

float get_value_from_index(struct tensor* tensor, unsigned int index) {
	return tensor->values[index];
}

float get_value_from_indices(struct tensor* tensor, unsigned int* indices) {
	return tensor->values[get_index_from_indices(tensor, indices)];
}

void set_value_from_index(struct tensor* tensor, unsigned int index, float value) {
	tensor->values[index] = value;
}
void set_value_from_indices(struct tensor* tensor, unsigned int indices, float value) {
	tensor->values[get_index_from_indices(tensor, indices)] = value;
}

unsigned int get_index_from_indices(struct tensor* tensor, unsigned int* indices) {
	int index = 0;
	int dim;
	for (dim = tensor->dimensions; dim--;) {
		index += indices[dim] * tensor->dimension[dim];
	}
	return index;
}

struct tensor* add_value(struct tensor* a, struct tensor* b) {
	if (a->dimensions > b->dimensions) {
	} else if (a->dimensions == b->dimensions) {
		int dim;
		for (dim = a->dimensions; dim--;) {
			if (a->shape[dim] != b->shape[dim]) {
				goto equal_diff;
			}
		}
		{
			struct tensor* result = copy_tensor_shape(b);
			for (int i = a->valuesLength; i--;) {
				result->shape[i] = a->shape[i] + b->shape[i];
			}
			return result;
		}
		equal_diff: {
//			unsigned int
			unsigned int aI = 0;
			unsigned int bI = 0;
			unsigned int outputIndices[a->dimensions];
			for (unsigned int i = 0; i < b->valuesLength; i++) {
//				for (unsigned int j = 0;)
			}
		}
	} else /*if (a->dimensions < b->dimensions)*/ {
	}
}

void add_value_same_shape(struct tensor* from, struct tensor* to) {
	for (int i = from->valuesLength; i--;) {
		to->values[i] += from->values[i];
	}
}
