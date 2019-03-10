
#include <stdio.h>
#include <assert.h>

int test_multByPwr2_leftSide(void);
int test_multByPwr2_rightSide(void);
int test_multByOtherValue_leftSide(void);
int test_multByOtherValue_rightSide(void);

int main(void) {
    assert(test_multByPwr2_leftSide() == 384);
    assert(test_multByPwr2_rightSide() == 3072);
    assert(test_multByOtherValue_leftSide() == 387);
    assert(test_multByOtherValue_rightSide() == 3069);
    return 0;
}

int test_multByPwr2_leftSide(void) {
    int a = 0;
    int b = 3;
    return a = 128 * b;
}

int test_multByPwr2_rightSide(void) {
    int a = 0;
    int b = 3;
    return a = b * 1024;    
}

int test_multByOtherValue_leftSide(void) {
    int a = 0;
    int b = 3;
    return a = 129 * b;
}

int test_multByOtherValue_rightSide(void) {
    int a = 0;
    int b = 3;
    return a = b * 1023;   
}
