//included into MapException.hpp

namespace ieml {
	namespace detail {
		template<typename Char_>
		String toString(BasicString<Char_> const& other) {
			return String{static_cast<const Char*>(other.c_str())};
		}
	}
	
	template<typename Char_>
	MapException<Char_>::MapException(Mark mark, BasicString<Char_> const& requested_key) :
		NodeException(mark), requested_key_(requested_key) {
	}
	
	template<typename Char_>
	String MapException<Char_>::get_description() const {
		return String{"A key named '"} + detail::toString<Char_>(requested_key_) + String {"' does not exist in the map."};
	}
	
	template<typename Char_>
	BasicStringView<Char_> MapException<Char_>::get_requested_key() const {
		return requested_key_;
	}
	
	template<typename Char_>
	MapException<Char_>* MapException<Char_>::clone() const {
		return new MapException<Char_>{*this};
	}
}