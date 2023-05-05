//included into Node.hpp

namespace ieml {
	template<typename Char_>
	BaseMetaData<Char_>::BaseMetaData(BoxPtr<BasicNode<Char_>> data) : data(std::move(data)) {
	}
	
	template<typename Char_>
	BaseMetaData<Char_>::BaseMetaData(const BasicNode<Char_>& data) : data(makeBoxPtr<BasicNode<Char_>>(data)) {
	}
	
	template<typename Char_>
	BaseMetaData<Char_>::BaseMetaData(BaseMetaData<Char_>&& other) : data(std::move(other.data)) {
	}
	
	template<typename Char_>
	BaseMetaData<Char_>::BaseMetaData(const BaseMetaData<Char_>& other) : data(makeBoxPtr<BasicNode<Char_>>(*other.data)) {
	}
	
	template<typename Char_>
	BaseMetaData<Char_>& BaseMetaData<Char_>::operator=(const BaseMetaData& other) {
		data.reset(new BasicNode<Char_>{*other.data});
		return *this;
	}
	
	template<typename Char_>
	BasicTagData<Char_>::BasicTagData(BoxPtr<BasicNode<Char_>> data, const BasicTag<Char_>& tag) : BaseMetaData<Char_>(std::move(data)), tag(tag) {
	}
	
	template<typename Char_>
	BasicTagData<Char_>::BasicTagData(const BasicNode<Char_>& data, const BasicTag<Char_>& tag) : BaseMetaData<Char_>(data), tag(tag) {
	}
	
	template<typename Char_>
	BasicFileData<Char_>::BasicFileData(BoxPtr<BasicNode<Char_>> data, const FilePath& filePath) : BaseMetaData<Char_>(std::move(data)), filePath(filePath) {
	}
	
	template<typename Char_>
	BasicFileData<Char_>::BasicFileData(const BasicNode<Char_>& data, const FilePath& filePath) : BaseMetaData<Char_>(data), filePath(filePath) {
	}
	
	template<typename Char_>
	BasicRawData<Char_>::operator BasicString<Char_>() const {
		return str;
	}
}
