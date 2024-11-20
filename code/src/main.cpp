#include <iostream>

#include <EngineBravo.h>

int main()
{
    std::cout << "Hello, World!" << std::endl;
    EngineBravo::getInstance().initialize();
    EngineBravo::getInstance().run();
    return 0;
}