//included into ExtraKeyException.hpp

namespace ieml {
	template<typename Char_>
	ExtraKeyException<Char_>::ExtraKeyException(Mark mark, KeyContainer extra_keys) :
		NodeException(mark), extra_keys_(std::move(extra_keys)) {
	}
	
	template<typename Char_>
	String ExtraKeyException<Char_>::get_description() const {
		std::stringstream stream{};
		stream << "These keys are extra in the map: ";
		for(auto item: extra_keys_) {
			stream << "\n - '" << detail::to_string<Char_>(item) << "'";
		}
		return stream.str();
	}
	
	template<typename Char_>
	auto ExtraKeyException<Char_>::get_extra_keys() const -> KeyContainer {
		return extra_keys_;
	}
	
	template<typename Char_>
	ExtraKeyException<Char_>* ExtraKeyException<Char_>::clone() const {
		return new ExtraKeyException<Char_>{*this};
	}
}
