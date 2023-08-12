#ifndef PIM_TEST_H
#define PIM_TEST_H

// A function that does not take arguments and does not return a value.
typedef void (*TestFunction)();

typedef struct Test {
	// The name of the test.
	char* name;

	// The function that this test will run.
	TestFunction function;
} Test;

typedef struct TestSuite {
	// The name of the test suite.
	char* name;

	// The collection of tests that this suite will run.
	Test* tests;
} TestSuite;

// Creates a test.
Test test(char* name, TestFunction function);

// Creates a test suite.
TestSuite test_suite(char* name, Test tests[]);

// Runs a test suite.
void test_suite_run(TestSuite suite, const int tests_length);

#define PM_ASSERT(expression) \
    if (!(expression)) { \
        fprintf(stderr, "Assertion failed: %s, file %s, line %d\n", #expression, __FILE__, __LINE__); \
        return; \
    }

#endif // PIM_TEST_H
