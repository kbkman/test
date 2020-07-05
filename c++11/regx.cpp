#include <iostream>
#include <string>
#include <regex>

int main(int argc, char* argv[])
{
	std::smatch m;
	std::regex re("[0-9]{3,100}+");
	std::string s("13795384185d");
	while (std::regex_search(s, m, re))
	{
		std::cout << "reg match" << std::endl;
		for (auto x : m)
		{
			std::cout << x << std::endl;
			s = m.suffix();
			std::cout << "left : " << s << std::endl;
		}
	}

	return 0;
}

