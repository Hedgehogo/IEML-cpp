//included into Node.hpp

namespace ieml {
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
		if(node_ != nullptr) {
			delete node_;
		}
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
	BasicTagData<Char_>::BasicTagData(BasicNode<Char_>&& node, const BasicTag<Char_>& tag) : BaseMetaData<Char_>(std::forward<BasicNode<Char_> >(node)), tag_(tag) {
	}
	
	template<typename Char_>
	BasicTagData<Char_>::BasicTagData(const BasicNode<Char_>& node, const BasicTag<Char_>& tag) : BaseMetaData<Char_>(node), tag_(tag) {
	}
	
	template<typename Char_>
	BasicFileData<Char_>::BasicFileData(BasicNode<Char_>&& node, const FilePath& filePath, RcPtr<BasicAnchorKeeper<Char_>> anchorKeeper) :
		BaseMetaData<Char_>(std::forward<BasicNode<Char_> >(node)), filePath_(filePath), anchorKeeper_(anchorKeeper) {
	}
	
	template<typename Char_>
	BasicFileData<Char_>::BasicFileData(const BasicNode<Char_>& node, const FilePath& filePath, RcPtr<BasicAnchorKeeper<Char_>> anchorKeeper) :
		BaseMetaData<Char_>(node), filePath_(filePath), anchorKeeper_(anchorKeeper) {
	}
	
	template<typename Char_>
	BasicRawData<Char_>::operator BasicString<Char_>() const {
		return str;
	}
}
