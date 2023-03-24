#include <iostream>
#include "lib/IEML/node/Node/Node.hpp"
#include "lib/IEML/print/print.hpp"

int main() {
	ieml::Node node{ieml::fromFile("../exampleSrc/test.ieml")};
	std::cout << node["second"][0].as<double>() << "\n";
	std::cout << node;
}
