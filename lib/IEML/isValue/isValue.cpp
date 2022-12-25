#include "isValue.hpp"
#include "../template_regex/template_regex.hpp"

namespace ieml {
	bool isEnter(std::string::const_iterator first, std::string::const_iterator last) {
		return regex::match(ieml_make_regex(R"( *)"), first, last);
	}
	
	bool isFile(std::string::const_iterator first, std::string::const_iterator last) {
		return regex::match(ieml_make_regex(R"(\< .*)"), first, last);
	}
	
	bool isNull(std::string::const_iterator first, std::string::const_iterator last) {
		return regex::match(ieml_make_regex(R"(null *)"), first, last);
	}
	
	bool isBool(std::string::const_iterator first, std::string::const_iterator last) {
		return regex::match(ieml_make_regex(R"(no *)"), first, last) ||
			   regex::match(ieml_make_regex(R"(yes *)"), first, last) ||
			   regex::match(ieml_make_regex(R"(true *)"), first, last) ||
			   regex::match(ieml_make_regex(R"(false *)"), first, last);
	}
	
	bool isDouble(std::string::const_iterator first, std::string::const_iterator last) {
		return regex::match(ieml_make_regex(R"([0-9]+\.[0-9]*)"), first, last) ||
			   regex::match(ieml_make_regex(R"(0[a-z][0-9A-Pa-p]+\.[0-9A-Pa-p]*)"), first, last);
	}
	
	bool isInt(std::string::const_iterator first, std::string::const_iterator last) {
		return regex::match(ieml_make_regex(R"([0-9]+)"), first, last) ||
			   regex::match(ieml_make_regex(R"(0[a-z][0-9A-Pa-p]+)"), first, last);
	}
}