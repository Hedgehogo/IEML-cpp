//included into Node.hpp

namespace ieml {
	template<typename Char_>
	BasicTagData<Char_>::BasicTagData(Box<BasicNodeData<Char_>> data, const BasicTag<Char_>& tag) : data(std::move(data)), tag(tag) {
	}
	
	template<typename Char_>
	BasicTagData<Char_>::BasicTagData(const BasicNodeData<Char_>& data, const BasicTag<Char_>& tag) : data(makeBox<BasicNodeData<Char_>>(data)), tag(tag) {
	}
	
	template<typename Char_>
	BasicTagData<Char_>::BasicTagData(const BasicTagData<Char_>& other) : data(makeBox<BasicNodeData<Char_>>(*other.data)), tag(other.tag) {
	}
	
	template<typename Char_>
	BasicTagData<Char_>& BasicTagData<Char_>::operator=(const BasicTagData<Char_>& other) {
		data = makeBox<BasicNodeData<Char_>>(*other.data);
		tag = other.tag;
		return *this;
	}
	
	template<typename Char_>
	BasicFileData<Char_>::BasicFileData(Box<BasicNodeData<Char_>> data, const FilePath& filePath) : data(std::move(data)), filePath(filePath) {
	}
	
	template<typename Char_>
	BasicFileData<Char_>::BasicFileData(const BasicNodeData<Char_>& data, const FilePath& filePath) : data(makeBox<BasicNodeData<Char_>>(data)), filePath(filePath) {
	}
	
	template<typename Char_>
	BasicFileData<Char_>::BasicFileData(const BasicFileData<Char_>& other) : data(makeBox<BasicNodeData<Char_>>(*other.data)), filePath(other.filePath) {
	}
	
	template<typename Char_>
	BasicFileData<Char_>& BasicFileData<Char_>::operator=(const BasicFileData<Char_>& other) {
		data = makeBox<BasicNodeData<Char_>>(*other.data);
		filePath = other.filePath;
		return *this;
	}
	
	template<typename Char_>
	BasicRawData<Char_>::operator BasicString<Char_>() const {
		return str;
	}
}
