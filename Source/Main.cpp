#include "A5.hpp"

#include <iostream>
using namespace std;

int main( int argc, char **argv )
{

	std::string title("Assignment 5");
	CS488Window::launch(argc, argv, new A5(), 1440,900, title);

	return 0;
}
