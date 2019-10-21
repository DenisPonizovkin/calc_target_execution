// qqq.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#undef UNICODE
#include <iostream>
#include <windows.h>

#include <bravo/api/calc_target.h>

typedef int(__stdcall* f1)();
typedef int (__stdcall *f2)(int, int[], double[], double[], int, int);

const int n = 27;
int params[1];
double mean[n];
double target[n];
int min_max = 2;

int main()
{
	HMODULE hGetProcIDDLL = LoadLibrary("calc_targets.dll");

	if (!hGetProcIDDLL) {
		std::cout << "could not load the dynamic library" << std::endl;
		return EXIT_FAILURE;
	}

	f2 f = (f2)GetProcAddress(hGetProcIDDLL, "?calc_target@@YAHHQEAHQEAN1HH@Z");

	if (!f) {
		std::cout << "could not locate the function" << std::endl;
		return EXIT_FAILURE;
	}
	f(0, params, mean, target, n, min_max);
	for (int i = 0; i < n; i++) {
		std::cout << std::to_string(i) << std::string(" ") << std::to_string(target[i]) << std::endl;
	}

	return 0;
}