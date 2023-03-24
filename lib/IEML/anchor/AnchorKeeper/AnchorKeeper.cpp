#include "AnchorKeeper.hpp"
#include "../../node/Node/Node.hpp"

namespace ieml {
	AnchorKeeper::AnchorKeeper() : parent_() {
	}
	
	AnchorKeeper::AnchorKeeper(Rc<AnchorKeeper> parent) : parent_(parent) {
	}
	
	bool AnchorKeeper::add(const String& key, NodeData value) {
		return anchors_.emplace(key, value).second;
	}
	
	bool AnchorKeeper::add(const String& key, Node value) {
		return anchors_.emplace(key, value.data).second;
	}
	
	NodeData* AnchorKeeper::get(const String& key) {
		if(auto find{anchors_.find(key)}; find != anchors_.end())
			return &find->second;
		if(parent_)
			return parent_->get(key);
		return nullptr;
	}
}
