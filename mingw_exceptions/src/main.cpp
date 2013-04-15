
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
		// Pour main-static l'exeption ne sera pas r�cup�r�e (Runtime Error) car la dll est compil�e en static libgcc et libstdc++
	}


	try {
		inst.throwStructExc();
	} catch (const MyExcept& except) {
		std::cout << " struct exception caught " << std::endl;
		std::cout << " => message " << except.error << std::endl;
		// Exception r�cup�r�e par 'main'
	}

	std::cout << "main ends" << std::endl;
	return 0;
}

