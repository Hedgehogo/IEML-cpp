#pragma once

#include "../node/Node/Node.hpp"

namespace ieml {
	template<typename Char_>
	struct FileGenerate;
	
	template<typename Char_, typename FileGenerate_ = FileGenerate<Char_>>
	class BasicGenerator {
	public:
		BasicGenerator(std::basic_ostream<Char_>& stream);
		
		void enter(Size indent);
		
		void generate(BasicNode<Char_> const& node, Size indent = 0);
		
		void generateNull(BasicNode<Char_> const& node, Size indent);
		
		void generateRaw(BasicNode<Char_> const& node, Size indent);
		
		void generateString(BasicNode<Char_> const& node, Size indent);
		
		void generateList(BasicNode<Char_> const& node, Size indent);
		
		void generateMap(BasicNode<Char_> const& node, Size indent);
		
		void generateTag(BasicNode<Char_> const& node, Size indent);
		
		void generateFile(BasicNode<Char_> const& node, Size indent);
		
		void generateTakeAnchor(BasicNode<Char_> const& node, Size indent);
		
		void generateGetAnchor(BasicNode<Char_> const& node, Size indent);
		
	private:
		std::basic_ostream<Char_>& stream_;
	};
	
	using Generator = BasicGenerator<Char>;
	
	template<typename Char_>
	struct FileGenerate {
		static void generate(BasicNode<Char_> const& node, const FilePath& filePath);
	};
	
	template<typename Char_ = Char, typename FileGenerate_ = FileGenerate<Char_>>
	void intoFile(const BasicNode<Char_>& node, const FilePath& filePath);
	
	template<typename Char_ = Char, typename FileGenerate_ = FileGenerate<Char_>>
	void into(const BasicNode<Char_>& node, std::basic_ostream<Char_>& stream);
}

#include "Generator.inl"
