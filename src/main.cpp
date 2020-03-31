#include <iostream>
#include <config.h>

int func();

int main()
{
	func();
	std::cout << "Starting " << PACKAGE_STRING << std::endl;
	return 0;
}

