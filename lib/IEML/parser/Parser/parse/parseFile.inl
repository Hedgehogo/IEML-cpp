//included into ../Parser.hpp
#include "../../../helpers/readFile/readFile.hpp"
#include "../../helpers/match/match.hpp"
#include "../../helpers/blankLines/blankLines.hpp"

namespace ieml {
	static constexpr auto reFile = ctll::fixed_string{R"(< [^\n]*)"};
	
	template<typename Char_>
	NodeData FileInclude<Char_>::include(Rc<AnchorKeeper> anchorKeeper, FilePath filePath) {
		String inputStr{readFile<String::value_type>(filePath)};
		Parser parser{inputStr, anchorKeeper};
		return parser.parse();
	}
	
	template<typename Char_>
	FilePath getFilePath(const FilePath& parentFilePath, FilePath&& newFilePath) {
		FilePath normalFilePath{newFilePath.concat(".ieml").lexically_normal().make_preferred()};
		FilePath relativeFilePath{FilePath{parentFilePath}.remove_filename() / normalFilePath};
		if(fs::exists(relativeFilePath))
			return relativeFilePath.lexically_normal();
		return normalFilePath;
	}
	
	template<typename Char_, typename FileInclude_>
	void Parser<Char_, FileInclude_>::parseFileAnchorMap(Rc<AnchorKeeper> loadedAnchorKeeper, Size indent) {
		if(pos_ != end()) {
			PosInfo posInfo{getPosInfo()};
			skipBlankLinesLn(pos_, end(), mark_);
			if(matchIndent(pos_, end(), mark_, indent)) {
				if(auto map{parseMap(indent)}) {
					for(auto& [key, value]: map.value()) {
						loadedAnchorKeeper->add(key, *value);
					}
					return;
				}
			}
			setPosInfo(posInfo);
		}
	}
	
	template<typename Char_, typename FileInclude_>
	Option<FileData> Parser<Char_, FileInclude_>::parseFile(Size indent) {
		if(auto find{matchAndMove<reFile>(pos_, end(), mark_)}) {
			Rc<AnchorKeeper> loadedAnchorKeeper{makeRc<AnchorKeeper>(anchorKeeper_)};
			FilePath loadedFilePath{getFilePath<Char_>(filePath_, fs::u8path(find.begin() + 2, find.end()))};
			parseFileAnchorMap(loadedAnchorKeeper, indent);
			return FileData{FileInclude_::include(loadedAnchorKeeper, loadedFilePath), loadedFilePath};
		}
		return {};
	}
}