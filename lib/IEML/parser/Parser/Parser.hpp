#pragma once

#include "../../node/Node/Node.hpp"
#include "../../usings/usings.hpp"
#include "../exception/FailedParseException/FailedParseException.hpp"

namespace ieml {
	template<typename Char_>
	struct FileInclude;
	
	template<typename Char_, typename FileInclude_ = FileInclude<Char_>>
	class BasicParser {
	public:
		struct PosInfo {
			BasicStringCIter<Char_> pos;
			Mark mark;
		};
	
	private:
		BasicStringCIter<Char_> pos_;
		BasicStringCIter<Char_> end_;
		Mark mark_;
		RcPtr<BasicAnchorKeeper<Char_>> anchor_keeper_;
		FilePath file_path_;
		
		void parse_file_anchor_map(RcPtr<BasicAnchorKeeper<Char_>> loaded_anchor_keeper, Size indent);
		
		void except(FailedParseException::Reason reason);
		
	public:
		BasicParser(const BasicString<Char_>& input_str, RcPtr<BasicAnchorKeeper<Char_>> anchor_keeper, FilePath file_path = FilePath{});
		
		BasicParser(const BasicString<Char_>& input_str, FilePath file_path = FilePath{}, RcPtr<BasicAnchorKeeper<Char_>> anchor_keeper = make_rc_ptr<BasicAnchorKeeper<Char_>>());
		
		/// @brief Gets a const iterator at the end of the document.
		///
		/// @return Returns a const iterator at the end of the document.
		BasicStringCIter<Char_> end();
		
		/// @brief Gets information about the current position.
		///
		/// @return Returns information about the current position.
		PosInfo get_pos_info();
		
		/// @brief Sets a new position in the document.
		///
		/// @param pos_info Position information.
		void set_pos_info(const PosInfo& pos_info);
		
		/// @brief Parses all input to the node data.
		///
		/// @return Returns node data, the result of parsing.
		BasicNodeData<Char_> parse();
		
		/// @brief Parses the <i>Null</i>.
		///
		/// @param indent The current indentation level.
		///
		/// @return Returns <i>Null</i> data or nothing.
		Option<NullData> parse_null();
		
		/// @brief Parses the <i>Raw data</i>.
		///
		/// @param indent The current indentation level.
		///
		/// @return Returns <i>Raw data</i> or nothing.
		Option<BasicRawData<Char_>> parse_raw();
		
		/// @brief Parses the <i>Line string</i>.
		///
		/// @param indent The current indentation level.
		///
		/// @return Returns <i>String</i> data or nothing.
		Option<BasicStringData<Char_>> parse_line_string();
		
		/// @brief Parses the <i>Not escaped string</i>.
		///
		/// @param indent The current indentation level.
		///
		/// @return Returns <i>String</i> data or nothing.
		Option<BasicStringData<Char_>> parse_not_escaped_string(Size indent);
		
		/// @brief Parses the <i>Classic string</i>.
		///
		/// @param indent The current indentation level.
		///
		/// @return Returns <i>String</i> data or nothing.
		Option<BasicStringData<Char_>> parse_classic_string(Size indent);
		
		/// @brief Parses one of the <i>Scalar</i> data types.
		///
		/// @param indent The current indentation level.
		///
		/// @return Returns node data, the result of the parsing, or throws a FailedParseException if it fails.
		BasicNodeData<Char_> parse_scalar(Size indent);
		
		/// @brief Parses the node data.
		///
		/// @param indent The current indentation level.
		///
		/// @return Returns node data, the result of parsing.
		BasicNodeData<Char_> parse_node(Size indent);
		
		/// @brief Checks for a take <i>Anchor</i> and, if there is one, parses it and the node data.
		///
		/// @param indent The current indentation level.
		///
		/// @return Returns take <i>Anchor</i> data, the result of parsing, or nothing.
		Option<BasicTakeAnchorData<Char_>> parse_take_anchor(Size indent);
		
		/// @brief Checks for a get <i>Anchor</i> and, if there is one, parses it and the node data.
		///
		/// @param indent The current indentation level.
		///
		/// @return Returns get <i>Anchor</i> data, the result of parsing, or nothing.
		Option<BasicGetAnchorData<Char_>> parse_get_anchor(Size indent);
		
		/// @brief Checks for a <i>Tag</i> and, if there is one, parses it and the node data.
		///
		/// @param indent The current indentation level.
		///
		/// @return Returns <i>Tag</i> data, the result of parsing, or nothing.
		Option<BasicTagData<Char_>> parse_tag(Size indent);
		
		/// @brief Parses the <i>List</i>.
		///
		/// @param indent The current indentation level.
		///
		/// @return Returns <i>List</i> data or nothing.
		Option<BasicListData<Char_>> parse_list(Size indent);
		
		/// @brief Parses the <i>List</i> in <i>Short notation</i>.
		///
		/// @param indent The current indentation level.
		///
		/// @return Returns <i>List</i> data or nothing.
		Option<BasicListData<Char_>> parse_short_list();
		
		/// @brief Parses the <i>Map</i>.
		///
		/// @param indent The current indentation level.
		///
		/// @return Returns <i>Map</i> data or nothing.
		Option<BasicMapData<Char_>> parse_map(Size indent);
		
		/// @brief Parses the file path, then includes the node data parsed from the file.
		///
		/// @param indent The current indentation level.
		///
		/// @return Returns node data, the result of the parsing, or throws FailedReadFileException if the file could not be read.
		Option<BasicFileData<Char_>> parse_file(Size indent);
	};
	
	using Parser = BasicParser<Char>;
	
	template<typename Char_>
	struct FileInclude {
		static BasicNodeData<Char_> include(RcPtr<BasicAnchorKeeper<Char_>> anchor_keeper, const FilePath& file_path);
	};
	
	template<typename Char_ = Char>
	BasicNode<Char_> from_file(const FilePath& file_path, RcPtr<BasicAnchorKeeper<Char_>> anchor_keeper = make_rc_ptr<BasicAnchorKeeper<Char_>>());
	
	template<typename Char_ = Char>
	BasicNode<Char_> from(const BasicString<Char_>& input_str, RcPtr<BasicAnchorKeeper<Char_>> anchor_keeper = make_rc_ptr<BasicAnchorKeeper<Char_>>());
}

#include "Parser.inl"