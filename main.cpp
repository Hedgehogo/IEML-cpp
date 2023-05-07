#include <iostream>
#include <IEML/node/Node/Node.hpp>
#include <IEML/print/print.hpp>

int main() {
	ieml::Node node{ieml::fromFile("../exampleSrc/test")};
	std::cout << node.at("second").at(0).getClear().as<double>() << "\n";
	std::cout << node;
}
