//included into AnchorKeeper.hpp

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
	bool BasicAnchorKeeper<Char_>::addToFile(const BasicString<Char_>& key, BasicNode<Char_> value) {
		return fileAnchors_.emplace(key, value).second;
	}
	
	template<typename Char_>
	BasicNode<Char_>* BasicAnchorKeeper<Char_>::get(const BasicString<Char_>& key) {
		if(auto find{fileAnchors_.find(key)}; find != fileAnchors_.end())
			return &find->second;
		if(auto find{anchors_.find(key)}; find != anchors_.end())
			return &find->second;
		if(!parent_.expired()) {
			auto shared{parent_.lock()};
			if(shared)
				return shared->get(key);
		}
		return nullptr;
	}
	
	template<typename Char_>
	typename BasicAnchorKeeper<Char_>::AnchorMap const& BasicAnchorKeeper<Char_>::getMap() const {
		return anchors_;
	}
	
	template<typename Char_>
	typename BasicAnchorKeeper<Char_>::AnchorMap const& BasicAnchorKeeper<Char_>::getFileMap() const {
		return fileAnchors_;
	}
}
