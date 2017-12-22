/*
 * matter.h
 *
 *  Created on: 17 Dec 2017
 *      Author: root
 */

#ifndef MATTE_H_
#define MATTE_H_

struct tensor {
	float* values; // Array of floats for values
	unsigned int valuesLength; // Length of values
	unsigned int* shape; // Shape of tensor
	unsigned int* dimension; // Array to convert a list of dimensions to an index
	unsigned int dimensions;
};

struct tensor* create_tensor(unsigned int* shape, unsigned int dimensions);
struct tensor* create_tensor_no_shape_copy(unsigned int* shape, unsigned int dimensions);
void delete_tensor(struct tensor* t);

struct tensor* copy_tensor(struct tensor* tensor);

void fill_value(struct tensor* tensor, float value);
void fill_tensor(struct tensor* tensor, struct tensor* value);

float get_value_from_index(struct tensor* tensor, unsigned int index);
float get_value_from_indices(struct tensor* tensor, unsigned int* indices);

void set_value_from_index(struct tensor* tensor, unsigned int index, float value);
void set_value_from_indices(struct tensor* tensor, unsigned int indices, float value);

unsigned int get_index_from_indices(struct tensor* tensor, unsigned int* indices);

struct tensor* add_value(struct tensor* from, struct tensor* to);
void add_value_same_shape(struct tensor* from, struct tensor* to);

#endif
