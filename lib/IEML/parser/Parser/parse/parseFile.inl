//included into ../Parser.hpp
#include "../../../helpers/readFile/readFile.hpp"
#include "../../helpers/match/match.hpp"
#include "../../helpers/blankLines/blankLines.hpp"

namespace ieml {
	static constexpr auto reFile = ctll::fixed_string{R"(< [^\n]*)"};
	
	namespace detail {
		template<typename FileInclude_>
		static auto hasCustomFilePathHelper(FileInclude_&&) -> decltype(FileInclude_::getFilePath(std::declval<FilePath>(), std::declval<FilePath>()), std::true_type{});
		static std::false_type hasCustomFilePathHelper(...);
		
		template<typename FileInclude_>
		constexpr auto hasCustomFilePath = std::is_same_v<decltype(hasCustomFilePathHelper(std::declval<FileInclude_>())), std::true_type>;
	}
	
	template<typename Char_>
	BasicNodeData<Char_> FileInclude<Char_>::include(RcPtr<BasicAnchorKeeper<Char_>> anchorKeeper, const FilePath& filePath) {
		BasicString<Char_> inputStr{readFile<Char_>(filePath)};
		BasicParser<Char_> parser{inputStr, anchorKeeper};
		return parser.parse();
	}
	
	template<typename FileInclude_>
	FilePath getFilePath(const FilePath& parentFilePath, FilePath&& newFilePath) {
		if constexpr(detail::hasCustomFilePath<FileInclude_>) {
			return FileInclude_::getFilePath(parentFilePath, std::forward<FilePath>(newFilePath));
		} else {
			FilePath normalFilePath{newFilePath.concat(".ieml").lexically_normal().make_preferred()};
			FilePath relativeFilePath{FilePath{parentFilePath}.remove_filename() / normalFilePath};
			if(fs::exists(relativeFilePath))
				return relativeFilePath.lexically_normal();
			return normalFilePath;
		}
		return {};
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
			FilePath newFilePath{BasicString<Char_>{find.begin() + 2, find.end()}};
			FilePath loadedFilePath{getFilePath<FileInclude_>(filePath_, std::move(newFilePath))};
			parseFileAnchorMap(loadedAnchorKeeper, indent);
			return {BasicFileData<Char_>{BasicNode<Char_>{FileInclude_::include(loadedAnchorKeeper, loadedFilePath), mark}, loadedFilePath}};
		}
		return {};
	}
}