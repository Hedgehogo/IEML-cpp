#pragma once

#include "../../node/Node/Node.hpp"
#include "../../anchor/AnchorKeeper/AnchorKeeper.hpp"
#include "../../usings/usings.hpp"
#include "../exception/FailedParseException/FailedParseException.hpp"

namespace ieml {
	class Parser {
	private:
		struct PosInfo {
			String::const_iterator pos;
			Mark mark;
		};
		
		String inputStr_;
		String::const_iterator pos_;
		Mark mark_;
		Rc<AnchorKeeper> anchorKeeper_;
		FilePath filePath_;
		
		String::const_iterator end();
		
		PosInfo getPosInfo();
		
		void setPosInfo(const PosInfo& posInfo);
		
		Option<TakeAnchorData> parseTakeAnchor(Size indent);
		
		Option<GetAnchorData> parseGetAnchor(Size indent);
		
		void parseFileAnchorMap(Rc<AnchorKeeper> loadedAnchorKeeper, Size indent);
		
		void except(FailedParseException::Reason reason);
		
		void exceptWithCheckSpace(FailedParseException::Reason reason);
		
	public:
		Parser(const String& inputStr, Rc<AnchorKeeper> anchorKeeper, FilePath filePath = FilePath{});
		
		Parser(const String& inputStr, FilePath filePath = FilePath{}, Rc<AnchorKeeper> anchorKeeper = makeRc<AnchorKeeper>());
		
		/// @brief Parses all input to the node data.
		///
		/// @return Returns node data, the result of parsing.
		NodeData parse();
		
		NodeData parseNode(Size indent);
		
		/// @brief Checks for a tag and parses it, then parses the node data.
		///
		/// @param indent The current indentation level.
		/// @param lineBegin Whether the virtual cursor is at the beginning of the line at the moment (Not just at the beginning of the document).
		///
		/// @return Returns node data, the result of parsing.
		Option<TagData> parseTag(Size indent);
		
		Option<NodeData> parseAnchor(Size indent);
		
		NodeData parseScalar(Size indent);
		
		Option<StringData> parseClassicString(Size indent);
		
		Option<NullData> parseNull();
		
		Option<RawData> parseRaw();
		
		Option<StringData> parseNotEscapedString(Size indent);
		
		Option<FileData> parseFile(Size indent);
		
		Option<NodeData> parseNotScalar(Size indent);
		
		Option<ListData> parseList(Size indent);
		
		Option<MapData> parseMap(Size indent);
		
		Option<ListData> parseShortList(Size indent);
	};
}
