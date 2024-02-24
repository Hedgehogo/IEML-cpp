//included into ../Parser.hpp
#include "IEML/helpers/read_file/read_file.hpp"
#include "../../helpers/match/match.hpp"
#include "../../helpers/blank_lines/blank_lines.hpp"

namespace ieml {
	static constexpr auto re_file = ctll::fixed_string{R"(< [^\n]*)"};
	
	namespace detail {
		template<typename FileInclude_>
		static auto has_custom_file_path_helper(FileInclude_&&) ->
		decltype(FileInclude_::get_file_path(std::declval<FilePath>(), std::declval<FilePath>()), std::true_type{});
		
		static std::false_type has_custom_file_path_helper(...);
		
		template<typename FileInclude_>
		constexpr auto has_custom_file_path = std::is_same_v<decltype(has_custom_file_path_helper(std::declval<FileInclude_>())), std::true_type>;
	}
	
	template<typename Char_>
	BasicNodeData<Char_> FileInclude<Char_>::include(RcPtr<BasicAnchorKeeper<Char_> > anchor_keeper, const FilePath& file_path) {
		BasicString<Char_> input_str{read_file<Char_>(file_path)};
		BasicParser<Char_> parser{input_str, anchor_keeper};
		return parser.parse();
	}
	
	template<typename FileInclude_>
	FilePath get_file_path(const FilePath& parent_file_path, FilePath&& new_file_path) {
		if constexpr(detail::has_custom_file_path<FileInclude_>) {
			return FileInclude_::get_file_path(parent_file_path, std::forward<FilePath>(new_file_path));
		} else {
			FilePath normal_file_path{new_file_path.concat(".ieml").lexically_normal().make_preferred()};
			FilePath relative_file_path{FilePath{parent_file_path}.remove_filename() / normal_file_path};
			if(fs::exists(relative_file_path))
				return relative_file_path.lexically_normal();
			return normal_file_path;
		}
	}
	
	template<typename Char_, typename FileInclude_>
	void BasicParser<Char_, FileInclude_>::parse_file_anchor_map(RcPtr<BasicAnchorKeeper<Char_> > loaded_anchor_keeper, Size indent) {
		if(pos_ != end()) {
			PosInfo pos_info{get_pos_info()};
			skip_blank_lines_ln<Char_>(pos_, end(), mark_);
			if(match_indent<Char_>(pos_, end(), mark_, indent)) {
				for(auto& map: parse_map(indent)) {
					for(auto& [key, value]: map) {
						loaded_anchor_keeper->add_to_file(key, value);
					}
					return;
				}
			}
			set_pos_info(pos_info);
		}
	}
	
	template<typename Char_, typename FileInclude_>
	Option<BasicFileData<Char_> > BasicParser<Char_, FileInclude_>::parse_file(Size indent) {
		Mark mark{mark_};
		if(auto find{match_and_move<re_file, Char_>(pos_, end(), mark_)}) {
			RcPtr<BasicAnchorKeeper<Char_> > loaded_anchor_keeper{make_rc_ptr<BasicAnchorKeeper<Char_> >(anchor_keeper_)};
			FilePath new_file_path{BasicString<Char_>{find.begin() + 2, find.end()}};
			FilePath loaded_file_path{get_file_path<FileInclude_>(file_path_, std::move(new_file_path))};
			parse_file_anchor_map(loaded_anchor_keeper, indent);
			
			return {
				BasicFileData<Char_>{
					BasicNode<Char_>{FileInclude_::include(loaded_anchor_keeper, loaded_file_path), mark},
					loaded_file_path,
					loaded_anchor_keeper
				}
			};
		}
		return {};
	}
}