//included into Node.hpp

namespace ieml {
	template<typename Char_>
	BaseMetaData<Char_>::BaseMetaData(BoxPtr<BasicNode<Char_>> node) : node_(std::move(node)) {
	}
	
	template<typename Char_>
	BaseMetaData<Char_>::BaseMetaData(const BasicNode<Char_>& node) : node_(makeBoxPtr<BasicNode<Char_>>(node)) {
	}
	
	template<typename Char_>
	BaseMetaData<Char_>::BaseMetaData(BaseMetaData<Char_>&& other) : node_(std::move(other.node_)) {
	}
	
	template<typename Char_>
	BaseMetaData<Char_>::BaseMetaData(const BaseMetaData<Char_>& other) : node_(makeBoxPtr<BasicNode<Char_>>(*other.node_)) {
	}
	
	template<typename Char_>
	BaseMetaData<Char_>& BaseMetaData<Char_>::operator=(const BaseMetaData& other) {
		node_.reset(new BasicNode<Char_>{*other.node_});
		return *this;
	}
	
	template<typename Char_>
	BasicTagData<Char_>::BasicTagData(BoxPtr<BasicNode<Char_>> node, const BasicTag<Char_>& tag) : BaseMetaData<Char_>(std::move(node)), tag_(tag) {
	}
	
	template<typename Char_>
	BasicTagData<Char_>::BasicTagData(const BasicNode<Char_>& node, const BasicTag<Char_>& tag) : BaseMetaData<Char_>(node), tag_(tag) {
	}
	
	template<typename Char_>
	BasicFileData<Char_>::BasicFileData(BoxPtr<BasicNode<Char_>> node, const FilePath& filePath) : BaseMetaData<Char_>(std::move(node)), filePath_(filePath) {
	}
	
	template<typename Char_>
	BasicFileData<Char_>::BasicFileData(const BasicNode<Char_>& node, const FilePath& filePath) : BaseMetaData<Char_>(node), filePath_(filePath) {
	}
	
	template<typename Char_>
	BasicRawData<Char_>::operator BasicString<Char_>() const {
		return str;
	}
}
