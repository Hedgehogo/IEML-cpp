#include <iostream>
#include <IEML/node/Node/Node.hpp>
#include <IEML/print/print.hpp>

int main() {
	ieml::Node node{ieml::fromFile("../exampleSrc/test")};
	std::cout << node.get("second", 0u, ieml::clear).ok().as<double>().ok() << "\n";
	std::cout << node;
}
