
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "mydll.hpp"
#include <windows.h>


int main(int argc, char *argv[]) 
{
	std::cout << "main starts " << std::endl;

	MyDll inst;
	try {
		inst.throwSimpleExc();
	} catch (...) {
		std::cout << " simple exception caught " << std::endl;
		// Pour main-static l'exeption ne sera pas récupérée (Runtime Error) car la dll est compilée en static libgcc et libstdc++
	}


	try {
		inst.throwStructExc();
	} catch (const MyExcept& except) {
		std::cout << " struct exception caught " << std::endl;
		std::cout << " => message " << except.error << std::endl;
		// Exception récupérée par 'main'
	}

	std::cout << "main ends" << std::endl;
	return 0;
}

