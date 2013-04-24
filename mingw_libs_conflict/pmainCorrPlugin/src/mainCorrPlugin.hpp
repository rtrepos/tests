#ifndef MainCorr_HPP
#define MainCorr_HPP

#ifdef MAIN_CORR_PLUGIN_EXPORTS
  #define MAIN_CORR_PLUGIN_API __declspec(dllexport)
#else
  #define MAIN_CORR_PLUGIN_API
#endif



#include <iostream>
#include <windows.h>


class MAIN_CORR_PLUGIN_API MainPlugin
{
public:
    MainPlugin();
    void start();
};


extern "C"
{
  MAIN_CORR_PLUGIN_API int start(int argc, char** argv)
  {
      MainPlugin appli;
      appli.start();
      std::cout << " PLUG argc " << argc << std::endl;
      return 0;

  }
}



#endif

