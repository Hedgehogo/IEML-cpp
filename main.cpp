#include <iostream>
#include <IEML/parser.hpp>
#include <IEML/generator.hpp>
#include <IEML/debug.hpp>

struct FileGenerate {
	static void generate(ieml::Node const& node, const ieml::FilePath& filePath) {}
};

int main() {
	ieml::Node node{ieml::fromFile("../exampleSrc/test")};
	std::cout << node.getAs<double>("second", 0, ieml::clear).except() << "\n";
	ieml::debug(node);
	std::cout << "\n";
	ieml::into<ieml::Char, FileGenerate>(node.getClearFile(), std::cout);
}
