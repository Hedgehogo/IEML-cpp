#include "parseFile.hpp"
#include "../../../node/Node/Node.hpp"
#include "../../../readFile/readFile.hpp"
#include "../../../preprocess/preprocess.hpp"
#include "../../parse.hpp"
#include "../../match/match.hpp"
#include "../../emptyLines/emptyLines.hpp"
#include "../parseNotScalar/parseMap/parseMap.hpp"

namespace ieml {
	static constexpr auto reFile = ctll::fixed_string{R"(< [^\n]*)"};
	
	void parseFileRefMap(std::string::const_iterator& pos, std::string::const_iterator end, const FilePath& filePath, RefKeeper& refKeeper, Mark& mark, size_t indent) {
		if(pos != end) {
			auto currentIndentFind{ctre::starts_with<reTabs>(pos + 1, end)};
			if(currentIndentFind.size() == indent) {
				Mark currentMark{mark.line + 1, indent};
				std::string::const_iterator currentPos{currentIndentFind.end()};
				if(auto map{parseMap(currentPos, end, filePath, refKeeper, currentMark, indent)}) {
					pos = currentPos;
					mark = currentMark;
					for(auto& [key, value]: map.value()) {
						refKeeper.add(key, value);
					}
				}
			}
		}
	}
	
	FilePath getFilePath(const FilePath& parentFilePath, const FilePath& newFilePath) {
		FilePath normalFilePath{newFilePath.lexically_normal().make_preferred()};
		FilePath relativeFilePath{FilePath{parentFilePath}.remove_filename() / normalFilePath};
		if(fs::exists(relativeFilePath))
			return relativeFilePath.lexically_normal();
		return normalFilePath;
	}
	
	Option<FileData> parseFile(std::string::const_iterator& pos, std::string::const_iterator end, const FilePath& filePath, RefKeeper& refKeeper, Mark& mark, size_t indent) {
		if(auto find{matchAndMove<reFile>(mark, pos, end)}) {
			Mark loadedMark{0, 0};
			RefKeeper loadedRefKeeper{refKeeper};
			FilePath loadedFilePath{getFilePath(filePath, fs::u8path(find.begin() + 2, find.end()))};
			parseFileRefMap(pos, end, filePath, loadedRefKeeper, mark, indent + 1);
			NodeData loadedData(parse(preprocess(readFile<char>(loadedFilePath)), loadedMark, loadedRefKeeper, loadedFilePath));
			return FileData{new NodeData{loadedData}, loadedFilePath};
		}
		return {};
	}
}