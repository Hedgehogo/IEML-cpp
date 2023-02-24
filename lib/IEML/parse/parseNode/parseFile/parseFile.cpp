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
	
	void parseFileRefMap(std::string::const_iterator& pos, std::string::const_iterator end, const fs::path& filePath, RefKeeper& refKeeper, Mark& mark, size_t indent) {
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
	
	Option<FileData> parseFile(std::string::const_iterator& pos, std::string::const_iterator end, const fs::path& filePath, RefKeeper& refKeeper, Mark& mark, size_t indent) {
		if(auto find{matchAndMove<reFile>(mark, pos, end)}) {
			Mark loadedMark{0, 0};
			RefKeeper loadedRefKeeper{refKeeper};
			FilePath loadedFilePath{fs::u8path(find.begin() + 2, find.end())};
			parseFileRefMap(pos, end, filePath, loadedRefKeeper, mark, indent + 1);
			NodeData loadedData(parse(preprocess(readFile<char>(loadedFilePath)), loadedMark, loadedRefKeeper, loadedFilePath));
			return FileData{new NodeData{loadedData}, loadedFilePath};
		}
		return {};
	}
}