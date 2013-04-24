
#ifndef MyDll_HPP
#define MyDll_HPP

#ifdef MYDLL_EXPORTS
  #define MYDLL_API __declspec(dllexport)
#else
  #define MYDLL_API
#endif

using namespace std;

class MYDLL_API MyDll
{
public:
	MyDll();

	void f();
};

#endif
