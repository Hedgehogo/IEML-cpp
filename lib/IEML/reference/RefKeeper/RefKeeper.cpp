#include "RefKeeper.hpp"

namespace ieml {
	RefKeeper::RefKeeper() : parent(nullptr) {}
	
	RefKeeper::RefKeeper(RefKeeper &parent) : parent(&parent) {}
	
	void RefKeeper::add(const std::string &key, INodeData *value) {
		refs.emplace(key, PNodeData{value->copy()});
	}
	
	INodeData *RefKeeper::get(const std::string &key) {
		if(auto find{refs.find(key)}; find != refs.end()) return find->second.get();
		if(parent) return parent->get(key);
		return nullptr;
	}
}
