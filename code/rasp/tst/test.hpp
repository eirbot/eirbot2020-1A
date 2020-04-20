#ifndef __TEST_H_
#define __TEST_H_

#include <vector>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <array>
#include <cfloat>
#include <cstring>
#include <assert.h>
#include <string.h>

#define SHELL_SUCCESS "\e[32m"
#define SHELL_INFO "\e[34m"
#define SHELL_END "\e[0m"
#define TEST_BEGIN printf("\n\033[34mRunning test %s()...\033[0m\n", __func__)
#define TEST_END printf("\033[34mEnding test %s()\033[0m \t%sSUCCESS%s\n \n",__func__, SHELL_SUCCESS, SHELL_END)
#define TEST_SKIPPED printf("\t%sSKIPPED\n%s", SHELL_INFO, SHELL_END)

int main(int argc, char *argv[]);

#endif // __TEST_H_
