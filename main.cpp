#include "lib/IEML/toNumber/toNumber.hpp"
#include "lib/IEML/isValue/isValue.hpp"
#include <iostream>

int main() {
	std::string str{"1.0"};
	std::cout << std::boolalpha << ieml::isDouble(str.begin(), str.end()) << std::endl;
	std::cout << std::to_string(ieml::toDouble(str)) << std::endl;
}
