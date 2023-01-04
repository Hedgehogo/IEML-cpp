#pragma once
#include <map>

namespace ieml {
	class Node;
	
	/// @brief Structure to implement the conversion functions from a node to T
	template<typename T>
	struct Decode;
	
	template<typename T>
	struct AsIf {
	private:
		const Node* node;
		
	public:
		AsIf(const Node& node);
		
		T operator()();
	};
	
	template<>
	struct AsIf<std::string> {
	private:
		const Node* node;
		
	public:
		AsIf(const Node& node);
		
		std::string operator()();
	};
}
