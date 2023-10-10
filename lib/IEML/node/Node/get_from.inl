//included into Node.cpp

namespace ieml {
	template<typename N, typename T>
	struct GetFromStep {};
	
	template<typename Char_, typename N>
	struct GetFromStep<N, BasicTagData<Char_>> {
		static N* get(N& node) {
			if(auto tag_data = std::get_if<BasicTagData<Char_>>(&node.data_.data_))
				return tag_data->node_;
			return nullptr;
		}
	};
	
	template<typename Char_, typename N>
	struct GetFromStep<N, BasicFileData<Char_>> {
		static N* get(N& node) {
			if(auto file_data = std::get_if<BasicFileData<Char_>>(&node.data_.data_))
				return file_data->node_;
			return nullptr;
		}
	};
	
	template<typename Char_, typename N>
	struct GetFromStep<N, BasicTakeAnchorData<Char_>> {
		static N* get(N& node) {
			if(auto take_anchor_data = std::get_if<BasicTakeAnchorData<Char_>>(&node.data_.data_)) {
				auto& keeper{take_anchor_data->keeper_};
				if(!keeper.expired()) {
					auto shared{keeper.lock()};
					if(auto anchor_data{shared->get(take_anchor_data->name_)}) {
						return anchor_data;
					}
				}
			}
			return nullptr;
		}
	};
	
	template<typename Char_, typename N>
	struct GetFromStep<N, BasicGetAnchorData<Char_>> {
		static N* get(N& node) {
			if(auto get_anchor_data = std::get_if<BasicGetAnchorData<Char_>>(&node.data_.data_)) {
				auto& keeper{get_anchor_data->keeper_};
				if(!keeper.expired()) {
					auto shared{keeper.lock()};
					if(auto anchor_data{shared->get(get_anchor_data->name_)}) {
						return anchor_data;
					}
				}
			}
			return nullptr;
		}
	};
	
	template<typename N>
	N* get_from_step(N& data) {
		return nullptr;
	}
	
	template<typename N, typename F, typename... T>
	N* get_from_step(N& data) {
		if(auto get_data = GetFromStep<N, F>::get(data)) {
			return get_data;
		}
		return get_from_step<N, T...>(data);
	}
	
	template<typename N, typename... T>
	N& get_from(N& data) {
		if(auto get_data = get_from_step<N, T...>(data)) {
			return get_from<N, T...>(*get_data);
		}
		return data;
	}
}
