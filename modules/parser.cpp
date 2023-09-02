#include "../include/parser.h"


bool HTML_parser::CheckNullable()
{
	return (RawString == nullptr || RawString == NULL) ? true : false;
}

 HTML_parser::HTML_parser(CharPtr str, bool SkipCm)
{
	RawString = str;
	assert(!CheckNullable(), ErrorSpace::ErrNull);
	SkipComments = SkipCm;
}

 HTML_parser::HTML_parser(String& str, bool SkipCm)
{
	RawString = str.c_str();
	assert(!CheckNullable(), ErrorSpace::ErrNull);
	SkipComments = SkipCm;

}

 void HTML_parser::SetLangOptions(ConsoleCP cp, const char* const lg)
{
	 SetConsoleOutputCP(static_cast<int>(cp));
	 std::setlocale(LC_ALL, lg);
}

void HTML_parser::ReadContent()
{
	bool NotifyBold = false;
	Len = std::wcslen(RawString);

	for (auto i = 0; i < Len; i++)
	{
		if (RawString[i] == '<') // if <a> or
		{
			RawString[i++];
			if (RawString[i] == '/') // </a>
			{
				for (; RawString[i] != '>'; RawString[++i]);
			}

			if (std::iswalpha(RawString[i]) != 0) // <a>
			{
				String TagBrMaybe;
				auto ps = i;
				while (std::iswalpha(RawString[ps]) != 0)
					TagBrMaybe += RawString[ps++];

				if (TagBrMaybe == L"br")
					ParseString.push_back(L'\n');
				else if (*TagBrMaybe.begin() == 'b')
				{
					ParseString.append(L"\x1b[1m");
					NotifyBold = true;
				}
				for (; RawString[i] != '>'; RawString[i++]);
			}
			
		}
		if (RawString[i] == '>') continue;
		if (NotifyBold)
		{
			ParseString.append(L"\x1b[0m");
			NotifyBold = false;
		}
		ParseString += RawString[i];

	}

	isParsed = true;
}

std::optional<String> HTML_parser::GetContent()
{
	if (isParsed)
	{
		return (ParseString);
	}
	else return {};
}

StringBox HTML_parser::GetValuesByAttribute(String & Attribute)
{
	if (!CheckNullable())
	{
		String tmp{ RawString };
		StringBox RetBox;
		auto pos = tmp.find(Attribute, 0);
		while (pos != String::npos)
		{
			auto TmpIt = pos;
			while (tmp[TmpIt] != '"')
				tmp[TmpIt++];
			String val;
			tmp[TmpIt++];
			while (tmp[TmpIt] != '"')
			{
				val += tmp[TmpIt++];
			}
			RetBox.push_back(std::move(val));
			pos = tmp.find(Attribute, pos + 1);
		}
		return RetBox;
	}
	return StringBox(0);
}