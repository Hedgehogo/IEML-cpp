#include "lib/IEML/toValue/toValue.hpp"
#include <iostream>

int main() {
	std::cout << std::to_string(ieml::toDouble("0p0.1")) << std::endl;
	return 0;
}
