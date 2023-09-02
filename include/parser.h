#pragma once
#include "./typedefs.h"
#include "./enums.h"
#include <stdexcept>
#include <iostream>
#include <cassert>
#include <cwctype>
#include <optional>
#include <Windows.h>

#if !defined(_WIN32)
#define DIS
#endif

namespace ErrorSpace
{
	static const char* ErrNull = "NULL string";
	static const char* ErrEmpty = "Empty string";
}


using namespace prs;


class HTML_parser
{
public:

	 HTML_parser(CharPtr, bool);
	 HTML_parser(String&, bool);

	 void ReadContent();
	 std::optional<String> GetContent();
	 StringBox GetValuesByAttribute(String&);
	 void SetLangOptions(ConsoleCP, const char* const);
private:

	void SkipComms();
	bool CheckNullable();
	void CallAbort() { std::abort(); }

	bool isParsed = false;
	bool SkipComments = true;
	rdo_string RefString;
	String ParseString;
	CharPtr RawString = nullptr;
	size_t Len = 0;
};