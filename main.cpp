#include <iostream>
#include <optional>
#include "lib/IEML/node/Node/Node.hpp"
#include "lib/IEML/print/print.hpp"

int main() {
	ieml::Node node{ieml::file("../exampleSrc/test.ieml")};
	//std::cout << node["first"][0].as<int>() << "\n";
	std::cout << node;
}
