#pragma once

#include "../../node/NodeData/NodeData.hpp"
#include "../../anchor/AnchorKeeper/AnchorKeeper.hpp"
#include "../../usings/usings.hpp"
#include "../exception/FailedParseException/FailedParseException.hpp"

namespace ieml {
	template<typename Char_>
	struct FileInclude;
	
	template<typename Char_, typename FileInclude_ = FileInclude<Char_>>
	class BasicParser {
	private:
		struct PosInfo {
			BasicStringCIter<Char_> pos;
			Mark mark;
		};
		
		BasicStringCIter<Char_> pos_;
		BasicStringCIter<Char_> end_;
		Mark mark_;
		Rc<BasicAnchorKeeper<Char_>> anchorKeeper_;
		FilePath filePath_;
		
		BasicStringCIter<Char_> end();
		
		PosInfo getPosInfo();
		
		void setPosInfo(const PosInfo& posInfo);
		
		Option<BasicTakeAnchorData<Char_>> parseTakeAnchor(Size indent);
		
		Option<BasicGetAnchorData<Char_>> parseGetAnchor(Size indent);
		
		void parseFileAnchorMap(Rc<BasicAnchorKeeper<Char_>> loadedAnchorKeeper, Size indent);
		
		void except(FailedParseException::Reason reason);
		
		void exceptWithCheckSpace(FailedParseException::Reason reason);
		
	public:
		BasicParser(const BasicString<Char_>& inputStr, Rc<BasicAnchorKeeper<Char_>> anchorKeeper, FilePath filePath = FilePath{});
		
		BasicParser(const BasicString<Char_>& inputStr, FilePath filePath = FilePath{}, Rc<BasicAnchorKeeper<Char_>> anchorKeeper = makeRc<BasicAnchorKeeper<Char_>>());
		
		/// @brief Parses all input to the node data.
		///
		/// @return Returns node data, the result of parsing.
		BasicNodeData<Char_> parse();
		
		/// @brief Parses the node data.
		///
		/// @param indent The current indentation level.
		///
		/// @return Returns node data, the result of parsing.
		BasicNodeData<Char_> parseNode(Size indent);
		
		/// @brief Checks for a <i>Tag</i> and, if there is one, parses it and the node data.
		///
		/// @param indent The current indentation level.
		///
		/// @return Returns <i>Tag</i> data, the result of parsing, or nothing.
		Option<BasicTagData<Char_>> parseTag(Size indent);
		
		/// @brief Checks for a <i>Anchor</i> and, if there is one, parses it and the node data.
		///
		/// @param indent The current indentation level.
		///
		/// @return Returns <i>Anchor</i> data, the result of parsing, or nothing.
		Option<BasicNodeData<Char_>> parseAnchor(Size indent);
		
		/// @brief Parses one of the <i>Scalar</i> data types.
		///
		/// @param indent The current indentation level.
		///
		/// @return Returns node data, the result of the parsing, or throws a FailedParseException if it fails.
		BasicNodeData<Char_> parseScalar(Size indent);
		
		/// @brief Parses the <i>Null</i>.
		///
		/// @param indent The current indentation level.
		///
		/// @return Returns <i>Null</i> data or nothing.
		Option<NullData> parseNull();
		
		/// @brief Parses the <i>Raw data</i>.
		///
		/// @param indent The current indentation level.
		///
		/// @return Returns <i>Raw data</i> or nothing.
		Option<BasicRawData<Char_>> parseRaw();
		
		/// @brief Parses the <i>Classic string</i>.
		///
		/// @param indent The current indentation level.
		///
		/// @return Returns <i>String</i> data or nothing.
		Option<BasicStringData<Char_>> parseClassicString(Size indent);
		
		/// @brief Parses the <i>Not escaped string</i>.
		///
		/// @param indent The current indentation level.
		///
		/// @return Returns <i>String</i> data or nothing.
		Option<BasicStringData<Char_>> parseNotEscapedString(Size indent);
		
		/// @brief Parses the file path, then includes the node data parsed from the file.
		///
		/// @param indent The current indentation level.
		///
		/// @return Returns node data, the result of the parsing, or throws FailedReadFileException if the file could not be read.
		Option<BasicFileData<Char_>> parseFile(Size indent);
		
		/// @brief Parses the <i>List</i> or <i>Map</i>.
		///
		/// @param indent The current indentation level.
		///
		/// @return Returns node data or nothing.
		Option<BasicNodeData<Char_>> parseNotScalar(Size indent);
		
		/// @brief Parses the <i>List</i>.
		///
		/// @param indent The current indentation level.
		///
		/// @return Returns <i>List</i> data or nothing.
		Option<BasicListData<Char_>> parseList(Size indent);
		
		/// @brief Parses the <i>List</i> in <i>Short notation</i>.
		///
		/// @param indent The current indentation level.
		///
		/// @return Returns <i>List</i> data or nothing.
		Option<BasicListData<Char_>> parseShortList(Size indent);
		
		/// @brief Parses the <i>Map</i>.
		///
		/// @param indent The current indentation level.
		///
		/// @return Returns <i>Map</i> data or nothing.
		Option<BasicMapData<Char_>> parseMap(Size indent);
	};
	
	using Parser = BasicParser<Char>;
	
	template<typename Char_>
	struct FileInclude {
		static BasicNodeData<Char_> include(Rc<BasicAnchorKeeper<Char_>> anchorKeeper, FilePath filePath);
	};
}

#include "Parser.inl"