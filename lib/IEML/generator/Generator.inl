//included into Generator.hpp

namespace ieml {
	template<typename Char_, typename FileGenerate_>
	BasicGenerator<Char_, FileGenerate_>::BasicGenerator(std::basic_ostream<Char_>& stream) : stream_(stream) {}
	
	template<typename Char_, typename FileGenerate_>
	void BasicGenerator<Char_, FileGenerate_>::enter(Size indent) {
		stream_ << BasicString<Char_>{toChar<Char_>('\n')} << BasicString<Char_>(indent, toChar<Char_>('\t'));
	}
	
	template<typename Char_, typename FileGenerate_>
	void BasicGenerator<Char_, FileGenerate_>::generate(BasicNode<Char_> const& node, Size indent) {
		auto type{node.getType()};
		switch(type) {
			case NodeType::Null:
				generateNull(node, indent);
				break;
			case NodeType::Raw:
				generateRaw(node, indent);
				break;
			case NodeType::String:
				generateString(node, indent);
				break;
			case NodeType::List:
				generateList(node, indent);
				break;
			case NodeType::Map:
				generateMap(node, indent);
				break;
			case NodeType::Tag:
				generateTag(node, indent);
				break;
			case NodeType::File:
				generateFile(node, indent);
				break;
			case NodeType::TakeAnchor:
				generateTakeAnchor(node, indent);
				break;
			case NodeType::GetAnchor:
				generateGetAnchor(node, indent);
				break;
		}
	}
	
	template<typename Char_, typename FileGenerate_>
	void BasicGenerator<Char_, FileGenerate_>::generateNull(const BasicNode<Char_>& node, Size indent) {
		stream_ << "null";
	}
	
	template<typename Char_, typename FileGenerate_>
	void BasicGenerator<Char_, FileGenerate_>::generateRaw(const BasicNode<Char_>& node, Size indent) {
		stream_ << node.template as<BasicRawData<Char_> >().except().str;
	}
	
	template<typename Char_, typename FileGenerate_>
	void BasicGenerator<Char_, FileGenerate_>::generateString(const BasicNode<Char_>& node, Size indent) {
		BasicString<Char_> str{node.template as<BasicStringData<Char_> >().except()};
		if(auto last{std::find(str.cbegin(), str.cend(), toChar<Char_>('\n'))}; last == str.cend()) {
			stream_ << BasicString<Char_>{toChar<Char_>('>')} + BasicString<Char_>{toChar<Char_>(' ')} + str;
		} else {
			BasicStringCIter<Char_> first{str.cbegin()};
			stream_ << toChar<Char_>('>') << toChar<Char_>('>');
			enter(indent);
			stream_ << BasicString<Char_>{first, last};
			while(last != str.cend()) {
				first = last + 1;
				last = std::find(first, str.cend(), toChar<Char_>('\n'));
				enter(indent);
				stream_ << BasicString<Char_>{first, last};
			}
		}
	}
	
	template<typename Char_, typename FileGenerate_>
	void BasicGenerator<Char_, FileGenerate_>::generateList(const BasicNode<Char_>& node, Size indent) {
		auto& list{node.template as<BasicListData<Char_> const&>().except()};
		for(auto& item: list) {
			enter(indent);
			stream_ << toChar<Char_>('-') << toChar<Char_>(' ');
			generate(item, indent + 1);
		}
	}
	
	template<typename Char_, typename FileGenerate_>
	void BasicGenerator<Char_, FileGenerate_>::generateMap(const BasicNode<Char_>& node, Size indent) {
		auto& map{node.template as<BasicMapData<Char_> const&>().except()};
		for(auto& [key, item]: map) {
			enter(indent);
			stream_ << key << toChar<Char_>(':') << toChar<Char_>(' ');
			generate(item, indent + 1);
		}
	}
	
	template<typename Char_, typename FileGenerate_>
	void BasicGenerator<Char_, FileGenerate_>::generateTag(const BasicNode<Char_>& node, Size indent) {
		stream_ << toChar<Char_>('=') << toChar<Char_>(' ') << node.getTag().except() << toChar<Char_>(':') << toChar<Char_>(' ');
		generate(node.getClearTag(), indent);
	}
	
	template<typename Char_, typename FileGenerate_>
	void BasicGenerator<Char_, FileGenerate_>::generateFile(const BasicNode<Char_>& node, Size indent) {
		auto& filePath{node.getFilePath().except()};
		auto& anchorKeeper{node.getFileAnchorKeeper().except()};
		auto& anchors{anchorKeeper.getFileMap()};
		auto stringFilePath{filePath.template string<Char_>()};
		stringFilePath.resize(stringFilePath.size() - 5);
		stream_ << toChar<Char_>('<') << toChar<Char_>(' ') << stringFilePath;
		for(auto& [name, value]: anchors) {
			enter(indent);
			stream_ << name << toChar<Char_>(':') << toChar<Char_>(' ');
			generate(value, indent + 1);
		}
		FileGenerate_::generate(node.getClearFile(), filePath);
	}
	
	template<typename Char_, typename FileGenerate_>
	void BasicGenerator<Char_, FileGenerate_>::generateTakeAnchor(const BasicNode<Char_>& node, Size indent) {
		stream_ << toChar<Char_>('&') << node.getTakeAnchorName().except() << toChar<Char_>(' ');
		generate(node.getClearTakeAnchor(), indent);
	}
	
	template<typename Char_, typename FileGenerate_>
	void BasicGenerator<Char_, FileGenerate_>::generateGetAnchor(const BasicNode<Char_>& node, Size indent) {
		stream_ << toChar<Char_>('*') << node.getGetAnchorName().except();
	}
	
	template<typename Char_>
	void FileGenerate<Char_>::generate(const BasicNode<Char_>& node, const FilePath& filePath) {
		intoFile(node, filePath);
	}
	
	template<typename Char_, typename FileGenerate_>
	void intoFile(const BasicNode<Char_>& node, const FilePath& filePath) {
		fs::create_directories(filePath.parent_path());
		std::ofstream stream{filePath};
		if(!stream)
			throw FailedOpenFileException{filePath};
		stream.clear();
		BasicGenerator<Char_, FileGenerate_> generator{stream};
		generator.generate(node);
		stream.close();
	}
	
	template<typename Char_, typename FileGenerate_>
	void into(const BasicNode<Char_>& node, std::basic_ostream<Char_>& stream) {
		BasicGenerator<Char_, FileGenerate_> generator{stream};
		generator.generate(node);
	}
}