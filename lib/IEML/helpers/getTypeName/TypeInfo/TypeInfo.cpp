#include "TypeInfo.hpp"

namespace ieml {
	TypeInfo::operator const std::type_info&() const {
		return getInfo();
	}
}