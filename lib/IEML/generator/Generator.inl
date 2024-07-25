//included into Generator.hpp

namespace ieml {
	template<typename Char_, typename FileGenerate_>
	BasicGenerator<Char_, FileGenerate_>::BasicGenerator(std::basic_ostream<Char_>& stream) : stream_(stream) {}
	
	template<typename Char_, typename FileGenerate_>
	void BasicGenerator<Char_, FileGenerate_>::enter(Size indent) {
		stream_ << BasicString<Char_>{to_char<Char_>('\n')} << BasicString<Char_>(indent, to_char<Char_>('\t'));
	}
	
	template<typename Char_, typename FileGenerate_>
	void BasicGenerator<Char_, FileGenerate_>::generate(BasicNode<Char_> const& node, Size indent) {
		auto type{node.get_type()};
		switch(type) {
			case NodeType::Null:
				generate_null(node, indent);
				break;
			case NodeType::Raw:
				generate_raw(node, indent);
				break;
			case NodeType::String:
				generate_string(node, indent);
				break;
			case NodeType::List:
				generate_list(node, indent);
				break;
			case NodeType::Map:
				generate_map(node, indent);
				break;
			case NodeType::Tag:
				generate_tag(node, indent);
				break;
			case NodeType::File:
				generate_file(node, indent);
				break;
			case NodeType::TakeAnchor:
				generate_take_anchor(node, indent);
				break;
			case NodeType::GetAnchor:
				generate_get_anchor(node, indent);
				break;
		}
	}
	
	template<typename Char_, typename FileGenerate_>
	void BasicGenerator<Char_, FileGenerate_>::generate_null(const BasicNode<Char_>& node, Size indent) {
		stream_ << "null";
	}
	
	template<typename Char_, typename FileGenerate_>
	void BasicGenerator<Char_, FileGenerate_>::generate_raw(const BasicNode<Char_>& node, Size indent) {
		stream_ << node.template as<BasicRawData<Char_> >().except().str;
	}
	
	template<typename Char_, typename FileGenerate_>
	void BasicGenerator<Char_, FileGenerate_>::generate_string(const BasicNode<Char_>& node, Size indent) {
		BasicString<Char_> str{node.template as<BasicStringData<Char_> >().except()};
		if(auto last{std::find(str.cbegin(), str.cend(), to_char<Char_>('\n'))}; last == str.cend()) {
			stream_ << BasicString<Char_>{to_char<Char_>('>')} + BasicString<Char_>{to_char<Char_>(' ')} + str;
		} else {
			BasicStringCIter<Char_> first{str.cbegin()};
			stream_ << to_char<Char_>('>') << to_char<Char_>('>');
			enter(indent);
			stream_ << BasicString<Char_>{first, last};
			while(last != str.cend()) {
				first = last + 1;
				last = std::find(first, str.cend(), to_char<Char_>('\n'));
				enter(indent);
				stream_ << BasicString<Char_>{first, last};
			}
		}
	}
	
	template<typename Char_, typename FileGenerate_>
	void BasicGenerator<Char_, FileGenerate_>::generate_list(const BasicNode<Char_>& node, Size indent) {
		auto& list{node.template as<BasicListData<Char_> const&>().except()};
		for(auto& item: list) {
			enter(indent);
			stream_ << to_char<Char_>('-') << to_char<Char_>(' ');
			generate(item, indent + 1);
		}
	}
	
	template<typename Char_, typename FileGenerate_>
	void BasicGenerator<Char_, FileGenerate_>::generate_map(const BasicNode<Char_>& node, Size indent) {
		auto& map{node.template as<BasicMapData<Char_> const&>().except()};
		for(auto& [key, item]: map) {
			enter(indent);
			stream_ << key << to_char<Char_>(':') << to_char<Char_>(' ');
			generate(item, indent + 1);
		}
	}
	
	template<typename Char_, typename FileGenerate_>
	void BasicGenerator<Char_, FileGenerate_>::generate_tag(const BasicNode<Char_>& node, Size indent) {
		stream_ << to_char<Char_>('=') << to_char<Char_>(' ') << node.get_tag().except() << to_char<Char_>(':') << to_char<Char_>(' ');
		generate(node.get_clear_tag(), indent);
	}
	
	template<typename Char_, typename FileGenerate_>
	void BasicGenerator<Char_, FileGenerate_>::generate_file(const BasicNode<Char_>& node, Size indent) {
		auto& file_path{node.get_file_path().except()};
		auto& anchor_keeper{node.get_file_anchor_keeper().except()};
		auto& anchors{anchor_keeper.get_file_map()};
		auto string_file_path{file_path.template string<Char_>()};
		string_file_path.resize(string_file_path.size() - 5);
		stream_ << to_char<Char_>('<') << to_char<Char_>(' ') << string_file_path;
		for(auto& [name, value]: anchors) {
			enter(indent);
			stream_ << name << to_char<Char_>(':') << to_char<Char_>(' ');
			generate(value, indent + 1);
		}
		FileGenerate_::generate(node.get_clear_file(), file_path);
	}
	
	template<typename Char_, typename FileGenerate_>
	void BasicGenerator<Char_, FileGenerate_>::generate_take_anchor(const BasicNode<Char_>& node, Size indent) {
		stream_ << to_char<Char_>('@') << node.get_take_anchor_name().except() << to_char<Char_>(':') << to_char<Char_>(' ');
		generate(node.get_clear_take_anchor(), indent);
	}
	
	template<typename Char_, typename FileGenerate_>
	void BasicGenerator<Char_, FileGenerate_>::generate_get_anchor(const BasicNode<Char_>& node, Size) {
		stream_ << to_char<Char_>('@') << node.get_get_anchor_name().except();
	}
	
	template<typename Char_>
	void FileGenerate<Char_>::generate(const BasicNode<Char_>& node, const FilePath& file_path) {
		into_file(node, file_path);
	}
	
	template<typename Char_, typename FileGenerate_>
	void into_file(const BasicNode<Char_>& node, const FilePath& file_path) {
		fs::create_directories(file_path.parent_path());
		std::ofstream stream{file_path};
		if(!stream)
			throw FailedOpenFileException{file_path};
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