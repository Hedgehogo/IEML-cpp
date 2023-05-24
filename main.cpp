#include <iostream>
#include <IEML/node.hpp>
#include <IEML/print.hpp>

int main() {
	ieml::Node node{ieml::fromFile("../exampleSrc/test")};
	std::cout << node.getAs<double>("second", 0, ieml::clear).except() << "\n";
	std::cout << node;
}
