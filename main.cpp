#include <iostream>
#include <IEML/parser.hpp>
#include <IEML/generator.hpp>
#include <IEML/debug.hpp>

struct FileGenerate {
	static void generate(ieml::Node const&, ieml::FilePath const&) {}
};

int main() {
	ieml::Node node{ieml::from_file("../example-src/test")};
	std::cout << node.get_as<double>("second", 0, ieml::clear).except() << "\n";
	ieml::debug(node);
	std::cout << "\n";
	ieml::into<ieml::Char, FileGenerate>(node.get_clear_file(), std::cout);
}
