/*
 * test.c
 *
 *  Created on: 21 Dec 2017
 *      Author: root
 */

#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "matte.h"

#define BENCHMARK_REPITIONS 1000000

static void test_allocate_tensor(void **state) {
	size_t shape[] = {6, 5, 7, 3, 4};
	size_t indices[] = {
			shape[1] * shape[2] * shape[3] * shape[4],
			shape[2] * shape[3] * shape[4],
			shape[3] * shape[4],
			shape[4],
			1
	};
	tensor *t = matte_allocate_tensor(shape, 5);
	for (unsigned int i = 0; i < 5; i++) {
		assert_int_equal(shape[i], t->shape[i]);
		assert_int_equal(indices[i], t->indices[i]);
	}
	assert_int_equal(
			t->valuesLength,
			shape[0] * shape[1] * shape[2] * shape[3] * shape[4]
	);
	matte_free_tensor(t);
}

static void test_clone_tensor(void **state) {
	size_t shape[] = {2, 2, 2, 2};
	tensor *t = matte_allocate_tensor(shape, 4);
	for (int i = t->valuesLength; i--;) {
		t->values[i] = i;
	}
	tensor *cpy = matte_clone_tensor(t);
	for (int i = t->dimensions; i--;) {
		assert_true(cpy->shape[i] == t->shape[i]);
		assert_true(cpy->indices[i] == t->indices[i]);
		cpy->shape[i] = 0;
		cpy->indices[i] = 0;
		assert_false(cpy->shape[i] == t->shape[i]);
		assert_false(cpy->indices[i] == t->indices[i]);
	}
	for (int i = t->valuesLength; i--;) {
		assert_true(cpy->values[i] == t->values[i]);
		cpy->values[i] = -1;
		assert_false(cpy->values[i] == t->values[i]);
	}
	matte_free_tensor(cpy);
	matte_free_tensor(t);
}

void test_clone_tensor_shape(void **state) {
	size_t shape[] = {2, 2, 2, 2};
	tensor *t = matte_allocate_tensor(shape, 4);
	for (int i = t->valuesLength; i--;) {
		t->values[i] = 100;
	}
	tensor *cpy = matte_clone_tensor_shape(t);
	for (int i = t->dimensions; i--;) {
		assert_true(cpy->shape[i] == t->shape[i]);
		assert_true(cpy->indices[i] == t->indices[i]);
		cpy->shape[i] = 0;
		cpy->indices[i] = 0;
		assert_false(cpy->shape[i] == t->shape[i]);
		assert_false(cpy->indices[i] == t->indices[i]);
	}
	for (int i = t->valuesLength; i--;) {
		assert_false(cpy->values[i] == t->values[i]);
		cpy->values[i] = t->values[i];
		assert_true(cpy->values[i] == t->values[i]);
	}
	matte_free_tensor(cpy);
	matte_free_tensor(t);
}

static void test_set_tensor(void **state) {
	size_t shape[] = {4, 2, 3};
	tensor *a = matte_allocate_tensor(shape, 3);
	tensor *b = matte_allocate_tensor(shape, 3);
	matte_set_tensor_from_scalar(a, 45.3);
	for (size_t i = a->valuesLength; i--;) {
		assert_true(a->values[i] == 45.3);
		b->values[i] = i;
	}
	matte_set_tensor_from_tensor(a, b);
	for (size_t i = a->valuesLength; i--;) {
		assert_true(a->values[i] == b->values[i]);
	}
	matte_free_tensor(a);
	matte_free_tensor(b);
}

static void test_add(void **state) {
	{
		size_t shape[] = {4, 2, 3};
		tensor *a = matte_allocate_tensor(shape, 3);
		tensor *b = matte_allocate_tensor(shape, 3);
		for (size_t i = a->valuesLength; i--;) {
			a->values[i] = i;
			b->values[i] = i * 3;
		}
		matte_add_tensor_from_scalar(a, 3.5);
		for (size_t i = a->valuesLength; i--;) {
			assert_true(a->values[i] == i + 3.5);
		}
		matte_add_tensor_from_tensor(a, b);
		for (size_t i = a->valuesLength; i--;) {
			assert_true(a->values[i] == i + 3.5 + b->values[i]);
		}
		tensor *c = matte_add_tensor_and_tensor(a, b);
		for (size_t i = a->valuesLength; i--;) {
			assert_true(c->values[i] == a->values[i] + b->values[i]);
		}
		tensor *d = matte_add_tensor_and_scalar(a, 3);
		for (size_t i = d->valuesLength; i--;) {
			assert_true(d->values[i] == a->values[i] + 3);
		}
		matte_free_tensor(a);
		matte_free_tensor(b);
		matte_free_tensor(c);
		matte_free_tensor(d);
	}
	{
		size_t shapeA[] = {2,3,4,2,3};
		size_t shapeB[] = {3,1,2,3};
		tensor *a = matte_allocate_tensor(shapeA, 5);
		tensor *b = matte_allocate_tensor(shapeB, 4);
		for (size_t i = a->valuesLength; i--;) {
			a->values[i] = i;
		}
		for (size_t i = b->valuesLength; i--;) {
			b->values[i] = i * 3;
		}
		float target[] = {0,4,8,12,16,20,6,10,14,18,22,26,12,16,20,24,28,32,18,22,26,30,34,38,42,46,50,54,58,62,48,52,56,60,64,68,54,58,62,66,70,74,60,64,68,72,76,80,84,88,92,96,100,104,90,94,98,102,106,110,96,100,104,108,112,116,102,106,110,114,118,122,72,76,80,84,88,92,78,82,86,90,94,98,84,88,92,96,100,104,90,94,98,102,106,110,114,118,122,126,130,134,120,124,128,132,136,140,126,130,134,138,142,146,132,136,140,144,148,152,156,160,164,168,172,176,162,166,170,174,178,182,168,172,176,180,184,188,174,178,182,186,190,194};
		tensor *c = matte_add_tensor_and_tensor(a, b);
		for (size_t i = c->valuesLength; i--;) {
			assert_true(c->values[i] == target[i]);
		}
		matte_free_tensor(a);
		matte_free_tensor(b);
		matte_free_tensor(c);
	}
}

void bmark_iterate_index() {
	size_t shape[] = {6, 4, 5, 3};
	tensor *a = matte_allocate_tensor(shape, 4);
	float time = 0;
	for (int i = 0; i < BENCHMARK_REPITIONS; i++) {
		float startTime = (float) clock() / CLOCKS_PER_SEC;
		for (size_t j = 0; j++ < a->valuesLength;) {
			a->values[j] = 4;
		}
		time += (float) clock() / CLOCKS_PER_SEC - startTime;
	}
	printf("Iteration\n\tUp\n\t\tUsing index\t:\t%.10f\n", time);
	time = 0;
	for (int i = 0; i < BENCHMARK_REPITIONS; i++) {
		float startTime = (float) clock() / CLOCKS_PER_SEC;
		float *end_ptr = a->values + a->valuesLength - 1;
		for (float *ptr = a->values; ptr != end_ptr; ptr++) {
			*ptr = 4;
		}
		time += (float) clock() / CLOCKS_PER_SEC - startTime;
	}
	printf("\t\tUsing pointer\t:\t%.10f\n", time);
	time = 0;
	for (int i = 0; i < BENCHMARK_REPITIONS; i++) {
		float startTime = (float) clock() / CLOCKS_PER_SEC;
		for (size_t j = a->valuesLength; j--;) {
			a->values[j] = 4;
		}
		time += (float) clock() / CLOCKS_PER_SEC - startTime;
	}
	printf("\tDown\n\t\tUsing index\t:\t%.10f\n", time);
	time = 0;
	for (int i = 0; i < BENCHMARK_REPITIONS; i++) {
		float startTime = (float) clock() / CLOCKS_PER_SEC;
		for (float *ptr = a->values + a->valuesLength; ptr-- != a->values;) {
			*ptr = 4;
		}
		time += (float) clock() / CLOCKS_PER_SEC - startTime;
	}
	printf("\t\tUsing pointer\t:\t%.10f\n", time);
}

void bmark() {
	bmark_iterate_index();
}

int main(void) {
	bmark();
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_allocate_tensor),
		cmocka_unit_test(test_clone_tensor),
		cmocka_unit_test(test_clone_tensor_shape),
		cmocka_unit_test(test_set_tensor),
		cmocka_unit_test(test_add),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
