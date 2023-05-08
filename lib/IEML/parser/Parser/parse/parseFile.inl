//included into ../Parser.hpp
#include "../../../helpers/readFile/readFile.hpp"
#include "../../helpers/match/match.hpp"
#include "../../helpers/blankLines/blankLines.hpp"

namespace ieml {
	static constexpr auto reFile = ctll::fixed_string{R"(< [^\n]*)"};
	
	template<typename Char_>
	BasicNodeData<Char_> FileInclude<Char_>::include(RcPtr<BasicAnchorKeeper<Char_>> anchorKeeper, FilePath filePath) {
		BasicString<Char_> inputStr{readFile<Char_>(filePath)};
		BasicParser<Char_> parser{inputStr, anchorKeeper};
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
	void BasicParser<Char_, FileInclude_>::parseFileAnchorMap(RcPtr<BasicAnchorKeeper<Char_>> loadedAnchorKeeper, Size indent) {
		if(pos_ != end()) {
			PosInfo posInfo{getPosInfo()};
			skipBlankLinesLn<Char_>(pos_, end(), mark_);
			if(matchIndent<Char_>(pos_, end(), mark_, indent)) {
				if(auto map{parseMap(indent)}) {
					for(auto& [key, value]: map.some()) {
						loadedAnchorKeeper->add(key, value);
					}
					return;
				}
			}
			setPosInfo(posInfo);
		}
	}
	
	template<typename Char_, typename FileInclude_>
	Option<BasicFileData<Char_>> BasicParser<Char_, FileInclude_>::parseFile(Size indent) {
		Mark mark{mark_};
		if(auto find{matchAndMove<reFile, Char_>(pos_, end(), mark_)}) {
			RcPtr<BasicAnchorKeeper<Char_>> loadedAnchorKeeper{makeRcPtr<BasicAnchorKeeper<Char_>>(anchorKeeper_)};
			FilePath loadedFilePath{getFilePath<Char_>(filePath_, {find.begin() + 2, find.end()})};
			parseFileAnchorMap(loadedAnchorKeeper, indent);
			return {BasicFileData<Char_>{BasicNode<Char_>{FileInclude_::include(loadedAnchorKeeper, loadedFilePath), mark}, loadedFilePath}};
		}
		return {};
	}
}