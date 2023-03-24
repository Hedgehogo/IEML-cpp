#include "../Parser.hpp"
#include "../../../helpers/readFile/readFile.hpp"
#include "../../preprocess/preprocess.hpp"
#include "../../helpers/match/match.hpp"
#include "../../helpers/emptyLines/emptyLines.hpp"

namespace ieml {
	static constexpr auto reFile = ctll::fixed_string{R"(< [^\n]*)"};
	
	FilePath getFilePath(const FilePath& parentFilePath, const FilePath& newFilePath) {
		FilePath normalFilePath{newFilePath.lexically_normal().make_preferred()};
		FilePath relativeFilePath{FilePath{parentFilePath}.remove_filename() / normalFilePath};
		if(fs::exists(relativeFilePath))
			return relativeFilePath.lexically_normal();
		return normalFilePath;
	}
	
	void Parser::parseFileAnchorMap(Rc<AnchorKeeper> loadedAnchorKeeper, Size indent) {
		if(pos_ != end()) {
			Mark mark{mark_};
			String::const_iterator pos{pos_};
			skipBlankLines(pos_, end(), mark_);
			Size currentIndent{matchAndMove<reTabs>(pos_, end(), mark_).size()};
			if(currentIndent == indent) {
				if(auto map{parseMap(indent)}) {
					for(auto& [key, value]: map.value()) {
						loadedAnchorKeeper->add(key, *value);
					}
					return;
				}
			}
			pos_ = pos;
			mark_ = mark;
		}
	}
	
	Option<FileData> Parser::parseFile(Size indent) {
		if(auto find{matchAndMove<reFile>(pos_, end(), mark_)}) {
			Rc<AnchorKeeper> loadedAnchorKeeper{std::make_shared<AnchorKeeper>(anchorKeeper_)};
			FilePath loadedFilePath{getFilePath(filePath_, fs::u8path(find.begin() + 2, find.end()))};
			parseFileAnchorMap(loadedAnchorKeeper, indent);
			Parser loadedParser{preprocess(readFile<char>(loadedFilePath)), loadedAnchorKeeper};
			return FileData{loadedParser.parse(), loadedFilePath};
		}
		return {};
	}
}