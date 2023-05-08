#include <iostream>
#include <IEML/node/Node/Node.hpp>
#include <IEML/print/print.hpp>

int main() {
	ieml::Node node{ieml::fromFile("../exampleSrc/test")};
	std::cout << node.at("second").some().at(0).some().getClear().as<double>().ok() << "\n";
	std::cout << node;
}
