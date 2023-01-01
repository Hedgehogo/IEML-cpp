#include <iostream>
#include "lib/IEML/preprocess/preprocess.hpp"

int main() {
	std::string string{"ahsgdjbs #asfh \n > asfasas \n \"asfasf\" #agsdj "};
	std::cout << string << "\n";
	std::cout << ieml::preprocess(string);
}
