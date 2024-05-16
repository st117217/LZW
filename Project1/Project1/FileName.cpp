#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include<sstream>

class LZW
{
public:
	LZW();
	~LZW();
	std::vector<int> encode(std::string s1);
	std::string decode(std::vector<int> op);
	std::string getTextInString();

	void printText();
	void vectorToFile(std::vector<int> numbers);
	void printVector(std::vector<int> numbers);
	void printDecodingText(std::vector<int> numbers);

private:
};


int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");

	LZW lzw;

	std::cout << std::endl;
	std::cout << "исходный текст" << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	lzw.printText();
	std::vector<int> numbers = lzw.encode(lzw.getTextInString());

	std::cout << std::endl;
	lzw.vectorToFile(numbers);
	std::cout << "закодированный текст" << std::endl;
	std::cout << std::endl;
	lzw.printVector(numbers);
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "декодированный текст" << std::endl;
	std::cout << std::endl;

	lzw.printDecodingText(numbers);

	return EXIT_SUCCESS;
}

LZW::LZW() {}

LZW::~LZW() {}


std::vector<int> LZW::encode(std::string s1)
{
	std::unordered_map<std::string, int> dictionary;
	for (int i = 0; i <= 255; ++i) {
		std::string ch = "";
		ch += char(i);
		dictionary[ch] = i;
	}
	std::string a = "", b = "";
	a += s1[0];
	int code = 256;
	std::vector<int> output_code;
	for (int i = 0; i < s1.length(); i++)
	{
		if (i != s1.length() - 1)
		{
			b += s1[i + 1];
		}
		if (dictionary.find(a + b) != dictionary.end()) {
			a = a + b;
		}
		else {
			output_code.push_back(dictionary[a]);
			dictionary[a + b] = code;
			code++;
			a = b;
		}
		b = "";
	}
	output_code.push_back(dictionary[a]);
	return output_code;
}
std::string LZW::decode(std::vector<int> op)
{
	std::unordered_map<int, std::string> dictionary;
	for (int i = 0; i <= 255; i++) {
		std::string ch = "";
		ch += char(i);
		dictionary[i] = ch;
	}
	int old = op[0], n;
	std::string s = dictionary[old];
	std::string c = "";
	std::string output = "";
	c += s[0];
	output += s;
	int count = 256;
	for (int i = 0; i < op.size() - 1; i++) {
		n = op[i + 1];
		if (dictionary.find(n) == dictionary.end()) {
			s = dictionary[old];
			s = s + c;
		}
		else {
			s = dictionary[n];
		}
		output += s;
		c = "";
		c += s[0];
		dictionary[count] = dictionary[old] + c;
		count++;
		old = n;
	}
	return output;
}
std::string LZW::getTextInString()
{
	std::ifstream file("text.txt");

	if (!file.is_open()) {
		std::cerr << "Невозможно открыть файл text.txt" << std::endl;
		return "1";
	}

	std::string str;
	std::string s;
	while (!file.eof()) {
		getline(file, s);
		str += s + '\n';
	}

	file.close();

	return str;
}

void LZW::printText()
{
	std::string str;
	str = getTextInString();
	std::cout << str;
}
void LZW::vectorToFile(std::vector<int> numbers)
{
	std::ofstream output_file("vector.txt");
	std::ostream_iterator<int> output_iterator(output_file, " ");
	std::copy(numbers.begin(), numbers.end(), output_iterator);
	output_file.close();
}
void LZW::printVector(std::vector<int> numbers)
{
	std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<int>(std::cout, " "));
}
void LZW::printDecodingText(std::vector<int> numbers)
{
	std::cout << decode(numbers);
}