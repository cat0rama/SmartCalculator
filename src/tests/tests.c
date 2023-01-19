#include <stdio.h>
#include <check.h>

#include "../backend/include/parse_infix.h"
#include "../backend/include/defines.h"
#include "../backend/include/executer.h"
#include "../backend/include/utils.h"
#include "../backend/include/stack.h"

START_TEST(test1) {
    const char* expr = "acos(cos(sin(atan(ln(sqrt((8 * ((1 + 2 + 4 * 3 - 3 * 7) / 4)) + 133))))))";
    const char* to_out = 0;
    int buf_counter = 0;
    double result = 0;

    parse_string(expr, &to_out, &buf_counter);
    calc_expression(to_out, &result, 2, buf_counter);

    ck_assert_double_eq_tol(result, 0.922, 1e-3);
}
END_TEST

START_TEST(test2) {
    const char* expr = "cos(2)";
    const char* to_out = 0;
    int buf_counter = 0;
    double result = 0;

    parse_string(expr, &to_out, &buf_counter);
    calc_expression(to_out, &result, 2, buf_counter);

    ck_assert_double_eq_tol(result, -0.416147, 1e-3);
}
END_TEST

START_TEST(test3) {
    const char* expr = "(-4 + 32) * 32";
    const char* to_out = 0;
    int buf_counter = 0;
    double result = 0;

    parse_string(expr, &to_out, &buf_counter);
    calc_expression(to_out, &result, 2, buf_counter);

    ck_assert_float_eq(896, result);
}
END_TEST

START_TEST(test4) {
    const char* expr = "(1 + 2 + 4 * 3 - 3 * 7) / 4";
    const char* to_out = 0;
    int buf_counter = 0;
    double result = 0;

    parse_string(expr, &to_out, &buf_counter);
    calc_expression(to_out, &result, 2, buf_counter);

    ck_assert_float_eq(-1.5, result);
}
END_TEST

START_TEST(test5) {
    const char* expr = "())";

    bool flag = validate_parentheses(expr);

    ck_assert_int_eq(0, flag);
}
END_TEST

START_TEST(test6) {
    const char* expr = "6.25 mod 3";
    const char* to_out = 0;
    int buf_counter = 0;
    double result = 0;

    parse_string(expr, &to_out, &buf_counter);
    calc_expression(to_out, &result, 2, buf_counter);

    ck_assert_float_eq(0.25, result);
}
END_TEST


START_TEST(test7) {
    const char* expr = "sin(sqrt(4))";
    const char* to_out = 0;
    int buf_counter = 0;
    double result = 0;

    parse_string(expr, &to_out, &buf_counter);
    calc_expression(to_out, &result, 2, buf_counter);

    ck_assert_double_eq_tol(result, 0.909, 1e-3);
}
END_TEST

START_TEST(test8) {
    const char* expr = "24^2";
    const char* to_out = 0;
    int buf_counter = 0;
    double result = 0;

    parse_string(expr, &to_out, &buf_counter);
    calc_expression(to_out, &result, 2, buf_counter);

    ck_assert_double_eq(576, result);
}
END_TEST

START_TEST(test9) {
    stack st;
    enum eError err = 0;
    char elem = 0;
    
    create_stack(&st, 20, T_CHAR);
    create_stack(NULL, 0, 34);

    push_stack(&st, 'd');
    push_stack(&st, 'c');
    push_stack(NULL, '/');

    pop_stack(&st, &elem);
    pop_stack(&st, &elem);
    err = pop_stack(NULL, NULL);

    ck_assert_int_eq(err, -2);

    destroy_stack(&st);
}
END_TEST

START_TEST(test10) {
    destroy_stack(NULL);
}
END_TEST

START_TEST(test11) {
    stack st;
    enum eError err = 0;
    int elem = 0;
    
    create_stack(&st, 20, T_INT);

    push_stack(&st, 123);
    push_stack(&st, 943);
    push_stack(NULL, 854);

    pop_stack(&st, &elem);
    pop_stack(&st, &elem);
    pop_stack(NULL, NULL);

    ck_assert_int_eq(err, 0);

    destroy_stack(&st);
}
END_TEST

START_TEST(test12) {
    stack st;
    enum eError err = 0;
    int elem = 0;
    
    create_stack(&st, 20, T_INT);

    push_stack(&st, 123);
    push_stack(&st, 943);
    push_stack(NULL, 854);

    pop_stack(&st, &elem);
    pop_stack(&st, &elem);
    pop_stack(&st, &elem);
    err = pop_stack(&st, &elem);

    get_char_top(NULL);
    get_char_top(&st);


    ck_assert_int_eq(err, -4);

    destroy_stack(&st);
}
END_TEST

START_TEST(test13) {
    const char* expr = "sin(x)";
    const char* to_out = 0;
    int buf_counter = 0;
    double result = 0;

    parse_string(expr, &to_out, &buf_counter);
    calc_expression(to_out, &result, 10, buf_counter);

    get_op_priority(123123);

    ck_assert_double_eq_tol(result, -0.544, 1e-3);
}
END_TEST

Suite *smart_calc() {
    Suite *s;
    TCase *tc_tests;
  
    s = suite_create("tests");
    tc_tests = tcase_create("TESTS");

    tcase_add_test(tc_tests, test1);
    tcase_add_test(tc_tests, test2);
    tcase_add_test(tc_tests, test3);
    tcase_add_test(tc_tests, test4);
    tcase_add_test(tc_tests, test5);
    tcase_add_test(tc_tests, test6);
    tcase_add_test(tc_tests, test7);
    tcase_add_test(tc_tests, test8);
    tcase_add_test(tc_tests, test9);
    tcase_add_test(tc_tests, test10);
    tcase_add_test(tc_tests, test11);
    tcase_add_test(tc_tests, test12);
    tcase_add_test(tc_tests, test13);


    suite_add_tcase(s, tc_tests);

    return s;
}

int main() {
    Suite *s;
    SRunner *runner;

    s = smart_calc();
    runner = srunner_create(s);

    srunner_run_all(runner, CK_VERBOSE);
    srunner_ntests_failed(runner);
    srunner_free(runner);

  return 0;
}
