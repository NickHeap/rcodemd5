#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
class MD5
{
public:
	MD5();
	~MD5();

	static int Main(std::vector<std::wstring> &args);


private:
	static std::wstring GetMD5(const std::wstring &filename);


	static std::vector<wchar_t> hexDigits;

public:
	static std::wstring ToHexString(std::vector<unsigned char> &bytes);

};

