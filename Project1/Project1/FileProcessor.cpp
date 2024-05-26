#include"FileProcessor.h"


FileProcessor::FileProcessor(const std::string& filepath) : _filepath(filepath)
{
	readFile();
}

FileProcessor::~FileProcessor() = default;

void FileProcessor::encodeFile()
{
	_encodedText = encode(_text);
	writeVectorToFile(_encodedText);
}

void FileProcessor::decodeFile()
{
	_encodedText = readVectorFromFile();
	_decodingText = decode(_encodedText);
	writeDecodingTextToFile(_decodingText);
}


std::string _text;
std::string _decodingText;
SCode _encodedText;
std::string _filepath;

void FileProcessor::readFile()
{
	std::ifstream file(_filepath);
	if (!file.is_open()) {
		std::cerr << "Файл не открыт, будет закодирован пустой символ" << std::endl;
		_text = "";
		return;
	}

	std::string line;
	while (std::getline(file, line))
	{
		_text += line + '\n';
	}
	file.close();
	std::cout << "Длина исходного текста: " << _text.size() << std::endl;
}

SCode FileProcessor::encode(const std::string& s1)
{
	std::locale::global(std::locale("ru_RU.UTF-8"));
	setlocale(LC_ALL, "ru");

	std::unordered_map<std::string, int> dictionary;
	for (int i = 0; i <= 255; ++i)
	{
		std::string ch = "";
		ch += char(i);
		dictionary[ch] = i;
	}

	SCode output_code;
	std::string a;
	std::string b;
	a += s1[0];
	int code = 256;

	for (int i = 0; i < s1.length(); ++i)
	{
		if (i != s1.length() - 1) {
			b += s1[i + 1];
		}
		if (dictionary.find(a + b) != dictionary.end())
		{
			a = a + b;
		}
		else
		{
			output_code.pushBack(dictionary[a]);
			dictionary[a + b] = code;
			++code;
			a = b;
		}
		b = "";
	}
	output_code.pushBack(dictionary[a]);
	std::cout << "Длина закодированного файла: " << output_code.size() << std::endl;
	return output_code;
}

std::string FileProcessor::decode(const SCode& numbers)
{
	std::locale::global(std::locale("ru_RU.UTF-8"));
	setlocale(LC_ALL, "ru");

	std::unordered_map<int, std::string> dictionary;
	for (int i = 0; i <= 255; ++i)
	{
		std::string ch = "";
		ch += char(i);
		dictionary[i] = ch;
	}

	int old = numbers[0];
	std::string s = dictionary[old];
	std::string c;
	std::string output;
	c += s[0];
	output += s;

	int count = 256;
	for (int i = 0; i < numbers.size() - 1; ++i)
	{
		int n = numbers[i + 1];
		if (dictionary.find(n) == dictionary.end())
		{
			s = dictionary[old] + c;
		}
		else
		{
			s = dictionary[n];
		}
		output += s;
		c = s[0];
		dictionary[count] = dictionary[old] + c;
		++count;
		old = n;
	}
	std::cout << "Длина декодированного текста: " << output.size() << std::endl;
	return output;
}

void FileProcessor::writeVectorToFile(const SCode& numbers)
{
	std::ofstream output_file("encodingText.txt");
	for (int i = 0; i < numbers.size(); ++i)
	{
		output_file << numbers[i] << " ";
	}
	output_file.close();
}

SCode FileProcessor::readVectorFromFile()
{
	std::ifstream inFile("encodingText.txt");
	if (!inFile.is_open())
	{
		std::cerr << "Файл не открыт, декодирован пустой символ" << std::endl;
		SCode err;
		err.pushBack(0);
		return err;
	}

	SCode numbers;
	std::string line;
	while (std::getline(inFile, line))
	{
		std::stringstream ss(line);
		int number;
		while (ss >> number)
		{
			numbers.pushBack(number);
		}
	}
	inFile.close();
	std::cout << "Длина закодированного текста: " << numbers.size() << std::endl;
	return numbers;
}

void FileProcessor::writeDecodingTextToFile(const std::string& s1)
{
	std::ofstream outFile("output.txt");
	outFile << s1;
	outFile.close();
}
