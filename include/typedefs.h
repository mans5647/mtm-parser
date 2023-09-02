#pragma once
#include <string>
#include <cstdint>
#include <vector>
#include <string_view>

namespace prs
{
	using String = std::wstring;
	using Char = wchar_t;
	using StringBox = std::vector<String>;
	using CharPtr = const Char*;
	using rdo_string = std::wstring_view;
}