#ifndef HAPHAITEST_HAPHAITEST_H
#define HAPHAITEST_HAPHAITEST_H

#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <exception>

namespace HaphaiTest {

    std::vector<std::string> nameList;
    std::vector<void (*)()> codeList;

    void checkValid() {
        assert(nameList.size() == codeList.size()); // The two sizes should always be same.
    }

    void regTestCase(const std::string &name, void(*code)()) {
        checkValid();
        nameList.push_back(name);
        codeList.push_back(code);
    }

    std::size_t size() {
        checkValid();
        return nameList.size();
    }

    void (*setup)() = nullptr;

    void (*teardown)() = nullptr;

    class FailException : public std::exception {
    };

    void runTest() {
        std::cout << "[   Running HaphaiTest     ] " << std::endl;
        std::cout << "[ Copyright Haphaistos2333 ] " << std::endl;
        std::cout << std::endl;

        if (setup) {
            setup();
            std::cout << "[ Setup      ] " << std::endl;
        }
        int passedTest = 0;
        for (int i = 0; i < size(); ++i) {
            try {
                std::cout << "[ Testing    ] " << nameList[i] << std::endl;
                codeList[i]();
                std::cout << "[         Ok ] " << std::endl;
                ++passedTest;
            } catch (const FailException &f) {
                std::cout << "[       Fail ] " << std::endl;
            } catch (const std::exception &e) {
                std::cout << "[  Exception ] " << e.what() << std::endl;
            }
        }
        if (teardown) {
            teardown();
            std::cout << "[ Teardown   ] " << std::endl;
        }

        std::cout << std::endl;
        std::cout << "Tested " << __FILE__ << "." << std::endl;
        std::cout << "Passed " << passedTest << " of " << size();
    }
}

#define TEST(test_name) \
    namespace HaphaiTest{ \
        void test_name(); \
        int test_name##_reg = [](){ \
            HaphaiTest::regTestCase(#test_name, HaphaiTest::test_name); \
            return 0; \
        }(); \
    } \
    void HaphaiTest::test_name()

#define SETUP() \
    namespace HaphaiTest{ \
        void customized_setup(); \
        int setup_reg = [](){ \
            setup = customized_setup; \
            return 0; \
        }(); \
    } \
    void HaphaiTest::customized_setup()

#define TEARDOWN() \
    namespace HaphaiTest{ \
        void customized_teardown(); \
        int teardown_reg = [](){ \
            teardown = customized_teardown; \
            return 0; \
        }(); \
    } \
    void HaphaiTest::customized_teardown()

#define SUCCEED() return
#define FAIL() throw HaphaiTest::FailException()

#define ASSERT_EQUAL(a, b) \
    if(a != b)\
        FAIL();

#define ASSERT_THROW(a, e) \
    try{ \
        a; \
        FAIL(); \
    } \
    catch(const e& _){} \
    catch(const std::exception &_){ FAIL(); }\

#define RUN() HaphaiTest::runTest()

#endif //HAPHAITEST_HAPHAITEST_H
