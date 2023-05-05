#include "AnchorKeeper.hpp"

namespace ieml {
	template<typename Char_>
	BasicAnchorKeeper<Char_>::BasicAnchorKeeper() : parent_() {
	}
	
	template<typename Char_>
	BasicAnchorKeeper<Char_>::BasicAnchorKeeper(RcPtr<BasicAnchorKeeper> parent) : parent_(parent) {
	}
	
	template<typename Char_>
	bool BasicAnchorKeeper<Char_>::add(const BasicString<Char_>& key, BasicNode<Char_> value) {
		return anchors_.emplace(key, value).second;
	}
	
	template<typename Char_>
	BasicNode<Char_>* BasicAnchorKeeper<Char_>::get(const BasicString<Char_>& key) {
		if(auto find{anchors_.find(key)}; find != anchors_.end())
			return &find->second;
		if(parent_)
			return parent_->get(key);
		return nullptr;
	}
}
