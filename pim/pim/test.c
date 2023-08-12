#include "test.h"

#include <stdio.h>

Test test(char* name, TestFunction function) {
	Test test;
	test.name = name;
	test.function = function;
	return test;
}

TestSuite test_suite(char* name, Test tests[]) {
	TestSuite test_suite;
	test_suite.name = name;
	test_suite.tests = tests;
	return test_suite;
}

void _run_test(Test test) {
	printf("%s\n", test.name);
	test.function();
}

void test_suite_run(TestSuite suite, const int tests_length) {
	printf("%s\n\n", suite.name);

	for (int i = 0; i < tests_length; i++) {
		Test test = suite.tests[i];
		_run_test(test);
	}

	printf("\n");
}
