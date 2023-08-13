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

#define _PM_ASSERT(expression, format, ...) \
    do { \
        if (!(expression)) { \
            printf(_PM_ASSERT_COLOR_RED); \
            printf("Failed: "); \
            printf(format, __VA_ARGS__); \
            printf(_PM_ASSERT_COLOR_DEFAULT); \
            printf("\n"); \
            return; \
        } \
        printf(_PM_ASSERT_COLOR_GREEN); \
        printf("Passed: "); \
        printf(format, __VA_ARGS__); \
        printf(_PM_ASSERT_COLOR_DEFAULT); \
        printf("\n"); \
    } while (0) // Use a do-while(0) loop to make the macro a single statement

#define PM_ASSERT(expression) _PM_ASSERT(expression, "%s", #expression)

#define PM_ASSERT_EQ(a, b) _PM_ASSERT((a) == (b), "%s should be %d", #a, b)

#define PM_ASSERT_EQ_STR(a, b) _PM_ASSERT(strcmp(a, b) == 0, "%s should match \"%s\"", #a, b);

#endif // PIM_TEST_H
