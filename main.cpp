#include "HaphaiTest.h"
#include "test.h"

int *correct_answer;

TEST(foo_2) { ASSERT_EQUAL(foo(2), correct_answer[0]); }

TEST(foo_3) { ASSERT_EQUAL(foo(3), correct_answer[1]); }

TEST(foo_4) { ASSERT_EQUAL(foo(4), correct_answer[2]); }

TEST(foo_5) { ASSERT_EQUAL(foo(5), correct_answer[3]); }

TEST(throw_test) { ASSERT_THROW(foo(5), std::logic_error); }

TEST(wrong_throw) { ASSERT_THROW(foo(5), std::runtime_error); }

TEST(manual_fail) { FAIL(); }

TEST(force_succeed) { SUCCEED(); FAIL(); }

SETUP() {
    correct_answer = new int[4];
    for (int i = 2; i <= 5; ++i) correct_answer[i - 2] = correct_foo(i);
}

TEARDOWN() {
    delete[] correct_answer;
}

int main() { RUN(); }