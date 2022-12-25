#pragma once
#include "template_regex/string.hpp"

/// @brief Helper macros to separate string into characters
#define IEML_TEMPLATE_STRING_GET_C1(str, i)  \
    ::template_regex::char_at(str, i)
#define IEML_TEMPLATE_STRING_GET_C2(str, i)  \
    IEML_TEMPLATE_STRING_GET_C1(str, i),  IEML_TEMPLATE_STRING_GET_C1(str, i + 1)
#define IEML_TEMPLATE_STRING_GET_C4(str, i)  \
    IEML_TEMPLATE_STRING_GET_C2(str, i),  IEML_TEMPLATE_STRING_GET_C2(str, i + 2)
#define IEML_TEMPLATE_STRING_GET_C8(str, i)  \
    IEML_TEMPLATE_STRING_GET_C4(str, i),  IEML_TEMPLATE_STRING_GET_C4(str, i + 4)
#define IEML_TEMPLATE_STRING_GET_C16(str, i) \
    IEML_TEMPLATE_STRING_GET_C8(str, i),  IEML_TEMPLATE_STRING_GET_C8(str, i + 8)
#define IEML_TEMPLATE_STRING_GET_C32(str, i) \
    IEML_TEMPLATE_STRING_GET_C16(str, i), IEML_TEMPLATE_STRING_GET_C16(str, i + 16)
#define IEML_TEMPLATE_STRING_GET_C64(str, i) \
    IEML_TEMPLATE_STRING_GET_C32(str, i), IEML_TEMPLATE_STRING_GET_C32(str, i + 32)

/// @brief Default string literal expansion macro.
#ifndef IEML_TEMPLATE_STRING_EXPAND
#define IEML_TEMPLATE_STRING_EXPAND(str) IEML_TEMPLATE_STRING_GET_C64(str, 0)
#endif

/// @brief Detect string character type.
///
/// @param str String literal.
///
/// @return Character type.
#define IEML_TEMPLATE_STRING_CHAR_TYPE(str) decltype(::template_regex::char_at(str, 0))

/// @brief Creates template string object type.
/// This is just a macro that will expand into very ugly code.
///
/// @param str String literal.
///
/// @return String type.
///
/// @note Currently this is based on macro expansion and allows only
/// up to 64 characters strings. If you need create string with more
/// characters define own TEMPLATE_STRING_EXPAND macro.
#define ieml_make_string_t(str) \
    ::template_regex::basic_string_builder<\
        sizeof(str) / sizeof(IEML_TEMPLATE_STRING_CHAR_TYPE(str)) - 1, \
        IEML_TEMPLATE_STRING_CHAR_TYPE(str), \
        ::template_regex::basic_string<IEML_TEMPLATE_STRING_CHAR_TYPE(str)>, \
        IEML_TEMPLATE_STRING_EXPAND(str)\
    >::type

/// @brief Creates template string object.
///
/// @param str String literal.
///
/// @return String object.
///
/// @see `ieml_make_string_t`
#define ieml_make_string(str) ieml_make_string_t(str){}



#include "template_regex/regex.hpp"

/// @brief Create template regular expression type.
///
/// @param str Regular expression string.
///
/// @return Rules type.
#define ieml_make_regex_t(str) \
    ::template_regex::basic_regex_str<IEML_TEMPLATE_STRING_CHAR_TYPE(str), ieml_make_string_t(str)>

/// @brief Create template regular expression object.
///
/// @param str Regular expression string.
///
/// @return Rules object.
#define ieml_make_regex(str) ieml_make_regex_t(str){}

namespace ieml {
	namespace regex {
		/// @brief Perform input range matching.
		///
		/// @tparam Rule     Matching rule.
		/// @tparam Iterator Source sequence iterator type.
		///
		/// @param rule
		/// @param first
		/// @param last
		///
		/// @return If input sequence is matched by rule.
		template<typename Regex, typename Iterator>
		bool match(const Regex& regex, Iterator first, const Iterator last)
		{
			return template_regex::regex_match(regex, first, last);
		}
		
		/// @brief Perform input range matching.
		///
		/// @tparam Rule   Matching rule.
		/// @tparam Source Source sequence.
		///
		/// @param rule
		/// @param source
		///
		/// @return If input sequence is matched by rule.
		template <typename Regex, typename Source>
		bool match(const Regex &regex, Source &&source) {
			return template_regex::regex_match(regex, std::begin(source), std::end(source));
		}
		
		namespace rules {
			using namespace template_regex::rules;
		}
	}
}