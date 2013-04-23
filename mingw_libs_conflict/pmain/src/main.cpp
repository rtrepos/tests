
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <mydll.hpp>
#include <windows.h>


int main(int /*argc*/, char ** /*argv*/)
{
	std::cout << "main startsss " << std::endl;

	MyDll inst;
	inst.f();
	return 0;
}

