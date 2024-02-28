#include "TypeInfo.hpp"

namespace ieml {
	TypeInfo::operator std::type_info const&() const {
		return get_info();
	}
}