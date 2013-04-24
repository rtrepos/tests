
#include "mainCorrPlugin.hpp"
#include <mydll.hpp>
#include <iostream>
#include <windows.h>

MainPlugin::MainPlugin()
{
}
void MainPlugin::start()
{
    std::cout << " MainPlugin::start " << std::endl;
    MyDll mydll;
    mydll.f();
}




