//included into Node.hpp

namespace ieml {
	template<typename Char_>
	BasicRawData<Char_>::operator BasicString<Char_>() const {
		return str;
	}
	
	template<typename Char_>
	bool BasicRawData<Char_>::operator==(const BasicRawData<Char_>& other) const {
		return str == other.str;
	}
	
	template<typename Char_>
	bool operator==(BasicListData<Char_> const& first, BasicListData<Char_> const& second) {
		if(first.size() != second.size()) {
			return false;
		}
		
		for(Size i = 0; i < first.size(); ++i) {
			if(first[i] != second[i]) {
				return false;
			}
		}
		
		return true;
	}
	
	template<typename Char_>
	bool operator==(BasicMapData<Char_> const& first, BasicMapData<Char_> const& second) {
		if(first.size() != second.size()) {
			return false;
		}
		
		for(auto& [key, value] : first) {
			if(auto find{second.find(key)}; find == second.end() || find->second != value) {
				return false;
			}
		}
		
		return true;
	}
	
	template<typename Char_>
	BaseMetaData<Char_>::BaseMetaData(BasicNode<Char_>&& node) : node_(new BasicNode<Char_>{std::move(node)}) {
	}
	
	template<typename Char_>
	BaseMetaData<Char_>::BaseMetaData(const BasicNode<Char_>& node) : node_(new BasicNode<Char_>{node}) {
	}
	
	template<typename Char_>
	BaseMetaData<Char_>::BaseMetaData(BaseMetaData<Char_>&& other) : node_(other.node_) {
		other.node_ = nullptr;
	}
	
	template<typename Char_>
	BaseMetaData<Char_>::BaseMetaData(const BaseMetaData<Char_>& other) : node_(new BasicNode<Char_>(*other.node_)) {
	}
	
	template<typename Char_>
	BaseMetaData<Char_>::~BaseMetaData() {
		delete node_;
	}
	
	template<typename Char_>
	BaseMetaData<Char_>& BaseMetaData<Char_>::operator=(const BaseMetaData& other) {
		if(node_ != nullptr) {
			delete node_;
		}
		node_ = new BasicNode<Char_>{*other.node_};
		return *this;
	}
	
	template<typename Char_>
	bool BaseMetaData<Char_>::operator==(const BaseMetaData<Char_>& other) const {
		return *node_ == *other.node_;
	}
	
	template<typename Char_>
	BasicTagData<Char_>::BasicTagData(BasicNode<Char_>&& node, const BasicTag<Char_>& tag) : BaseMetaData<Char_>(std::forward<BasicNode<Char_> >(node)), tag_(tag) {
	}
	
	template<typename Char_>
	bool BasicTagData<Char_>::operator==(const BasicTagData<Char_>& other) const {
		return tag_ == other.tag_ && BaseMetaData<Char_>::operator==(other);
	}
	
	template<typename Char_>
	BasicTagData<Char_>::BasicTagData(const BasicNode<Char_>& node, const BasicTag<Char_>& tag) : BaseMetaData<Char_>(node), tag_(tag) {
	}
	
	template<typename Char_>
	BasicFileData<Char_>::BasicFileData(BasicNode<Char_>&& node, const FilePath& file_path, RcPtr<BasicAnchorKeeper<Char_>> anchor_keeper) :
		BaseMetaData<Char_>(std::forward<BasicNode<Char_> >(node)), file_path_(file_path), anchor_keeper_(anchor_keeper) {
	}
	
	template<typename Char_>
	BasicFileData<Char_>::BasicFileData(const BasicNode<Char_>& node, const FilePath& file_path, RcPtr<BasicAnchorKeeper<Char_>> anchor_keeper) :
		BaseMetaData<Char_>(node), file_path_(file_path), anchor_keeper_(anchor_keeper) {
	}
	
	template<typename Char_>
	bool BasicFileData<Char_>::operator==(const BasicFileData<Char_>& other) const {
		return
			file_path_ == other.file_path_ &&
			anchor_keeper_->get_map() == other.anchor_keeper_->get_map() &&
			anchor_keeper_->get_file_map() == other.anchor_keeper_->get_file_map() &&
			BaseMetaData<Char_>::operator==(other);
	}
	
	template<typename Char_>
	bool BaseAnchorData<Char_>::operator==(const BaseAnchorData<Char_>& other) const {
		return this->name_ == other.name_;
	}
	
	template<typename Char_>
	bool BasicNodeData<Char_>::operator==(const BasicNodeData<Char_>& other) const {
		return data_ == other.data_;
	}
}
