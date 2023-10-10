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
		
		void generate_null(BasicNode<Char_> const& node, Size indent);
		
		void generate_raw(BasicNode<Char_> const& node, Size indent);
		
		void generate_string(BasicNode<Char_> const& node, Size indent);
		
		void generate_list(BasicNode<Char_> const& node, Size indent);
		
		void generate_map(BasicNode<Char_> const& node, Size indent);
		
		void generate_tag(BasicNode<Char_> const& node, Size indent);
		
		void generate_file(BasicNode<Char_> const& node, Size indent);
		
		void generate_take_anchor(BasicNode<Char_> const& node, Size indent);
		
		void generate_get_anchor(BasicNode<Char_> const& node, Size indent);
		
	private:
		std::basic_ostream<Char_>& stream_;
	};
	
	using Generator = BasicGenerator<Char>;
	
	template<typename Char_>
	struct FileGenerate {
		static void generate(BasicNode<Char_> const& node, const FilePath& file_path);
	};
	
	template<typename Char_ = Char, typename FileGenerate_ = FileGenerate<Char_>>
	void into_file(const BasicNode<Char_>& node, const FilePath& file_path);
	
	template<typename Char_ = Char, typename FileGenerate_ = FileGenerate<Char_>>
	void into(const BasicNode<Char_>& node, std::basic_ostream<Char_>& stream);
}

#include "Generator.inl"
