
#include <iostream>
#include <windows.h>


template < typename __v_result >
__v_result functionCast(void* x)
{
    union __vle_pointer_to_function
    {
        __v_result f;
        void* r;
    };

    __vle_pointer_to_function tmp;
    tmp.r = x;
    return tmp.f;
}

int main(int argc, char** argv)
{
	std::cout << "main startsss " << std::endl;

	//TODO modify path

	typedef int(*appliFctSignature)(int, char**);



	HMODULE handle = ::LoadLibrary("c:\\tests\\mingw_libs_conflict\\installwin\\lib\\libmainCorrPlugin.dll");

	void* symbol = (void*)::GetProcAddress(handle, "start");

	appliFctSignature appliFct = functionCast < appliFctSignature >(symbol);

    int plug = appliFct(argc, argv);


	return 0;
}

