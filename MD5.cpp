#include "stdafx.h"
#include "MD5.h"


MD5::MD5()
{
}


MD5::~MD5()
{
}

int MD5::Main(std::vector<std::wstring> &args)
{
	if (args.size() < 3)
	{
		std::wcout << std::wstring(L"Not enough arguments!") << std::endl;
		return -1;
	}

	std::wstring filePath = args[0];
	std::wstring tempFile = args[1];
	std::wstring fileName = args[2];

	std::wstring md5 = GetMD5(fileName);

	if (md5 == L"")
	{
		std::wcout << std::wstring(L"Empty MD5!!!") << std::endl;
		return -1;
	}

	try
	{
		File::WriteAllText(tempFile, md5);
	}
	catch (std::exception &ex)
	{
		std::wcout << ex.what() << std::endl;
		return -1;
	}
	//Console.WriteLine(md5);

	return 0;
}


std::wstring MD5::GetMD5(const std::wstring &filename)
{
	int score = 0;
	unsigned char b;
	std::vector<unsigned char> bytes(41);
	std::vector<unsigned char> MD5bytes(16);

	try
	{
		//load file into string
		//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
		//ORIGINAL LINE: using (FileStream f = new FileStream(filename, FileMode.Open, FileAccess.Read, FileShare.Read, 8))
		{
			FileStream *f = new FileStream(filename, FileMode::Open, FileAccess::Read, FileShare::Read, 8);
			//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
			//ORIGINAL LINE: using (BinaryReader readStream = new BinaryReader(f))
			{
				BinaryReader *readStream = new BinaryReader(f);

				while (true) //readStream.PeekChar()>-1)
				{
					b = readStream->ReadByte();
					switch (b)
					{
					case 0x50:
						if (score == 0)
						{
							score = 1;
						}
						else
						{
							score = 0;
						}
						break;
					case 0x52:
						if (score == 1)
						{
							score = 2;
						}
						else if (score == 4)
						{
							score = 5;
						}
						else
						{
							score = 0;
						}
						break;
					case 0x4F:
						if (score == 2)
						{
							score = 3;
						}
						else
						{
							score = 0;
						}
						break;
					case 0x47:
						if (score == 3)
						{
							score = 4;
						}
						else
						{
							score = 0;
						}
						break;
					case 0x45:
						if (score == 5)
						{
							score = 6;
						}
						else
						{
							score = 0;
						}
						break;
					case 0x53:
						if (score == 6)
						{
							score = 7;
						}
						else if (score == 7)
						{
							score = 8;
						}
						else
						{
							score = 0;
						}
						break;
					default:
						score = 0;
						break;
					}
					if (score == 8)
					{
						bytes = readStream->ReadBytes(41);
						break;
					}
				}
				readStream->Close();
				delete readStream;
			}
			delete f;
		}
	}
	catch (std::exception &ex)
	{
		std::wcout << ex.what() << std::endl;
		return L"";
	}

	//no MD5 found?
	if (score != 8)
	{
		return L"";
	}

	Array::Copy(bytes, 25, MD5bytes, 0, 16);

	return ToHexString(MD5bytes);
}

std::vector<wchar_t> MD5::hexDigits = { L'0', L'1', L'2', L'3', L'4', L'5', L'6', L'7', L'8', L'9', L'A', L'B', L'C', L'D', L'E', L'F' };

std::wstring MD5::ToHexString(std::vector<unsigned char> &bytes)
{
	std::vector<wchar_t> chars(bytes.size() * 2);
	for (int i = 0; i < bytes.size(); i++)
	{
		int b = bytes[i];
		chars[i * 2] = hexDigits[b >> 4];
		chars[i * 2 + 1] = hexDigits[b & 0xF];
	}
	return std::wstring(chars);
}