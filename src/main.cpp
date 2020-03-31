#include <iostream>
#include <config.h>

#include "Renderer.hpp"

int main()
{
	std::cout << "Starting " << PACKAGE_STRING << std::endl;
	Renderer r;
	r.OpenWindow();
	return 0;
}

