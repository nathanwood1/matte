/*
 * test.c
 *
 *  Created on: 21 Dec 2017
 *      Author: root
 */

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "matte.h"

static void test_create_tensor(void **state) {
	(void) state;

	unsigned int shape[5] = {6, 5, 7, 3, 4};
	unsigned int dim_target[5] = {
			shape[1] * shape[2] * shape[3] * shape[4],
			shape[2] * shape[3] * shape[4],
			shape[3] * shape[4],
			shape[4],
			1
	};
	struct tensor* t = create_tensor(shape, 5);
	for (unsigned int i = 0; i < 5; i++) {
		assert_int_equal(shape[i], t->shape[i]);
		assert_int_equal(dim_target[i], t->dimension[i]);
	}
	assert_int_equal(
			t->valuesLength,
			shape[0] * shape[1] * shape[2] * shape[3] * shape[4]
	);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_create_tensor),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
