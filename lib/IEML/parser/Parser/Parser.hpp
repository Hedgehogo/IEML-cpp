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
		
		BasicNodeData<Char_> parseNode(Size indent);
		
		/// @brief Checks for a tag and parses it, then parses the node data.
		///
		/// @param indent The current indentation level.
		/// @param lineBegin Whether the virtual cursor is at the beginning of the line at the moment (Not just at the beginning of the document).
		///
		/// @return Returns node data, the result of parsing.
		Option<BasicTagData<Char_>> parseTag(Size indent);
		
		Option<BasicNodeData<Char_>> parseAnchor(Size indent);
		
		BasicNodeData<Char_> parseScalar(Size indent);
		
		Option<BasicStringData<Char_>> parseClassicString(Size indent);
		
		Option<NullData> parseNull();
		
		Option<BasicRawData<Char_>> parseRaw();
		
		Option<BasicStringData<Char_>> parseNotEscapedString(Size indent);
		
		Option<BasicFileData<Char_>> parseFile(Size indent);
		
		Option<BasicNodeData<Char_>> parseNotScalar(Size indent);
		
		Option<BasicListData<Char_>> parseList(Size indent);
		
		Option<BasicListData<Char_>> parseShortList(Size indent);
		
		Option<BasicMapData<Char_>> parseMap(Size indent);
	};
	
	using Parser = BasicParser<Char>;
	
	template<typename Char_>
	struct FileInclude {
		static BasicNodeData<Char_> include(Rc<BasicAnchorKeeper<Char_>> anchorKeeper, FilePath filePath);
	};
}

#include "Parser.inl"