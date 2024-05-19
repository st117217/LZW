#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

int main(int argc, char* argv[])
{
	std::locale::global(std::locale("ru_RU.UTF-8"));
	

	return EXIT_SUCCESS;
}

std::vector<int> encode(std::string s1)
{
	std::locale::global(std::locale("ru_RU.UTF-8"));

	std::unordered_map<std::string, int> dictionary;
	for (int i = 0; i <= 255; ++i) {
		std::string ch = "";
		ch += char(i);
		dictionary[ch] = i;
	}
	std::string a = "";
	std::string b = "";
	a += s1[0];
	int code = 256;
	std::vector<int> output_code;
	for (int i = 0; i < s1.length(); ++i)
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
			++code;
			a = b;
		}
		b = "";
	}
	output_code.push_back(dictionary[a]);
	return output_code;
}
std::string decode(std::vector<int> op)
{
	
	std::locale::global(std::locale("ru_RU.UTF-8"));


	std::unordered_map<int, std::string> dictionary;
	for (int i = 0; i <= 255; ++i) {
		std::string ch = "";
		ch += char(i);
		dictionary[i] = ch;
	}
	int old = op[0];
	int n = 0;
	std::string s = dictionary[old];
	std::string c = "";
	std::string output = "";
	c += s[0];
	output += s;
	int count = 256;
	for (int i = 0; i < op.size() - 1; ++i) {
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
		++count;
		old = n;
	}
	return output;
}

std::string readTextFromFile()
{
	std::ifstream file("text.txt");


	std::string str;
	std::string s;
	while (!file.eof()) {
		getline(file, s);
		str += s + '\n';
	}

	file.close();

	return str;
}

void printText()
{
	std::string str;
	str = readTextFromFile();
	std::cout << str;
}
void writeVectorToFile(std::vector<int> numbers)
{
	std::ofstream output_file("vector.txt");
	std::ostream_iterator<int> output_iterator(output_file, " ");
	std::copy(numbers.begin(), numbers.end(), output_iterator);
	output_file.close();
}
void printVector(std::vector<int> numbers)
{
	std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<int>(std::cout, " "));
}
void printDecodingText(std::vector<int> numbers)
{
	std::cout << decode(numbers);
}

void writeDecodingTextInFile(std::string s1)
{
	std::ofstream outFile("output.txt");
	outFile << s1;
	outFile.close();
}

std::vector<int> readVectorFromFile()
{
	std::ifstream inFile("vector.txt");

	std::vector<int> numbers;

	std::string line;
	while (std::getline(inFile, line)) 
	{
		std::stringstream ss(line);

		int number;
		while (ss >> number) 
		{
			numbers.push_back(number);
		}
	}
	inFile.close();

	return numbers;
}

void decodingfile()
{
	std::vector<int> numbers=readVectorFromFile();
	writeDecodingTextInFile(decode(numbers));
}
void encodingfile()
{
	std::string text = readTextFromFile();
	writeVectorToFile(encode(text));
}