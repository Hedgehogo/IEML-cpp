#include "parseFile.hpp"
#include "../../../readFile/readFile.hpp"
#include "../../../preprocess/preprocess.hpp"
#include "../../../node/NodeData/file/FileNodeData.hpp"
#include "../../parse.hpp"
#include "../../match/match.hpp"
#include "../../exceptions/FailedParseException.hpp"

namespace ieml {
	static constexpr auto fileString = ctll::fixed_string{ R"(< [^\"\n>]*?\n)" };
	
	INodeData *parseFile(std::string::const_iterator &pos, std::string::const_iterator end, const fs::path &filePath, RefKeeper &refKeeper, Mark &mark) {
		if(auto find{matchAndEnter<fileString>(mark, pos, end)}; find) {
			Mark loadedMark{0, 0};
			fs::path loadedFilePath{find.begin() + 2, find.end() - 1};
			INodeData *loadedData{parse(preprocess(readFile<char>(loadedFilePath)), loadedMark, refKeeper, loadedFilePath)};
			return new FileNodeData(std::unique_ptr<INodeData>{loadedData}, loadedFilePath);
		}
		throw FailedParseException{filePath, mark};
	}
}