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

#define _PM_ASSERT_COLOR_DEFAULT "\x1B[0m"
#define _PM_ASSERT_COLOR_RED     "\x1B[31m"
#define _PM_ASSERT_COLOR_GREEN   "\x1B[32m"

#define PM_ASSERT(expression) \
    if (!(expression)) { \
		printf(_PM_ASSERT_COLOR_RED); \
        printf("Assertion failed: %s\n", #expression); \
		printf(_PM_ASSERT_COLOR_DEFAULT); \
        return; \
    } else { \
		printf(_PM_ASSERT_COLOR_GREEN); \
		printf("Assertion passed: %s\n", #expression); \
		printf(_PM_ASSERT_COLOR_DEFAULT); \
	}

#define PM_ASSERT_EQ(a, b) PM_ASSERT((a) == (b))

#endif // PIM_TEST_H
