#ifdef MYDLL_EXPORTS
  #define MYDLL_API __declspec(dllexport)
#else
  #define MYDLL_API
#endif


#ifndef MyDll_HPP
#define MyDll_HPP

#include <iostream>;

using namespace std;

class MYDLL_API MyExcept
{
public:
	MyExcept() : code(98), error(" Struct error ")
	{
	}
	int code;
	std::string error;
};

class MYDLL_API MyDll
{
public:
	MyDll();

	void throwSimpleExc();
	void throwStructExc()
	{
		throw MyExcept();
	}
};

#endif
