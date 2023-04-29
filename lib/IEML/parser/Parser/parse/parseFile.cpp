#include "../Parser.hpp"
#include "../../../helpers/readFile/readFile.hpp"
#include "../../helpers/match/match.hpp"
#include "../../helpers/blankLines/blankLines.hpp"

namespace ieml {
	static constexpr auto reFile = ctll::fixed_string{R"(< [^\n]*)"};
	
	FilePath getFilePath(const FilePath& parentFilePath, FilePath&& newFilePath) {
		FilePath normalFilePath{newFilePath.concat(".ieml").lexically_normal().make_preferred()};
		FilePath relativeFilePath{FilePath{parentFilePath}.remove_filename() / normalFilePath};
		if(fs::exists(relativeFilePath))
			return relativeFilePath.lexically_normal();
		return normalFilePath;
	}
	
	void Parser::parseFileAnchorMap(Rc<AnchorKeeper> loadedAnchorKeeper, Size indent) {
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
	
	Option<FileData> Parser::parseFile(Size indent) {
		if(auto find{matchAndMove<reFile>(pos_, end(), mark_)}) {
			Rc<AnchorKeeper> loadedAnchorKeeper{makeRc<AnchorKeeper>(anchorKeeper_)};
			FilePath loadedFilePath{getFilePath(filePath_, fs::u8path(find.begin() + 2, find.end()))};
			parseFileAnchorMap(loadedAnchorKeeper, indent + 1);
			Parser loadedParser{readFile<String::value_type>(loadedFilePath), loadedAnchorKeeper};
			return FileData{loadedParser.parse(), loadedFilePath};
		}
		return {};
	}
}