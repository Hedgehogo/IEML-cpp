#include "RefKeeper.hpp"

namespace ieml {
	RefKeeper::RefKeeper() : parent(nullptr) {}
	
	RefKeeper::RefKeeper(RefKeeper &parent) : parent(&parent) {}
	
	void RefKeeper::add(const std::string &key, INodeData *value) {
		refs.emplace(key, PNodeData{value->copy()});
	}
	
	RefKeeper::NodeDataMap::iterator RefKeeper::find(const std::string &key) {
		if(auto find{refs.find(key)}; find != refs.end()) return refs.find(key);
		if(parent) if(auto find{parent->find(key)}; find != parent->end()) return refs.find(key);
		return refs.end();
	}
	
	RefKeeper::NodeDataMap::iterator RefKeeper::end() {
		return refs.end();
	}
}
