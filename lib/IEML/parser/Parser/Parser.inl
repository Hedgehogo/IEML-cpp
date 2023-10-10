//included into Parser.hpp

#include "../helpers/to_char/to_char.hpp"

namespace ieml {
	template<typename Char_, typename FileInclude_>
	BasicParser<Char_, FileInclude_>::BasicParser(const BasicString<Char_>& input_str, RcPtr<BasicAnchorKeeper<Char_>> anchor_keeper, FilePath file_path) :
		pos_(input_str.cbegin()), end_(input_str.cend()), mark_(), anchor_keeper_(anchor_keeper), file_path_(file_path) {
	}
	
	template<typename Char_, typename FileInclude_>
	BasicParser<Char_, FileInclude_>::BasicParser(const BasicString<Char_>& input_str, FilePath file_path, RcPtr<BasicAnchorKeeper<Char_>> anchor_keeper) :
		pos_(input_str.cbegin()), end_(input_str.cend()), mark_(), anchor_keeper_(anchor_keeper), file_path_(file_path) {
	}
	
	template<typename Char_, typename FileInclude_>
	BasicStringCIter<Char_> BasicParser<Char_, FileInclude_>::end() {
		return end_;
	}
	
	template<typename Char_, typename FileInclude_>
	typename BasicParser<Char_, FileInclude_>::PosInfo BasicParser<Char_, FileInclude_>::get_pos_info() {
		return PosInfo{pos_, mark_};
	}
	
	template<typename Char_, typename FileInclude_>
	void BasicParser<Char_, FileInclude_>::set_pos_info(const PosInfo& pos_info) {
		pos_ = pos_info.pos;
		mark_ = pos_info.mark;
	}
	
	template<typename Char_, typename FileInclude_>
	void BasicParser<Char_, FileInclude_>::except(FailedParseException::Reason reason) {
		throw FailedParseException{file_path_, reason, mark_};
	}
	
	template<typename Char_>
	BasicNode<Char_> from_file(const FilePath& file_path, RcPtr<BasicAnchorKeeper<Char_>> anchor_keeper) {
		FilePath normal_file_path{FilePath{file_path}.concat(".ieml").lexically_normal().make_preferred()};
		BasicString<Char_> input_str{read_file<Char_>(normal_file_path)};
		BasicParser<Char_> parser{input_str, normal_file_path, anchor_keeper};
		return BasicNode<Char_>{parser.parse()};
	}
	
	template<typename Char_>
	BasicNode<Char_> from(const BasicString<Char_>& input_str, RcPtr<BasicAnchorKeeper<Char_>> anchor_keeper) {
		BasicParser<Char_> parser{input_str, anchor_keeper};
		return BasicNode<Char_>{parser.parse()};
	}
}

#include "parse/parse_null.inl"
#include "parse/parse_raw.inl"
#include "parse/parse_line_string.inl"
#include "parse/parse_not_escaped_string.inl"
#include "parse/parse_classic_string.inl"
#include "parse/parse_scalar.inl"
#include "parse/parse_node.inl"
#include "parse/parse_anchor.inl"
#include "parse/parse_tag.inl"
#include "parse/parse_list.inl"
#include "parse/parse_short_list.inl"
#include "parse/parse_map.inl"
#include "parse/parse_file.inl"
#include "parse/parse.inl"