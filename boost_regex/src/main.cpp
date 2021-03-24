
#include <boost/regex.hpp>
#include <iostream>
#include <string>

int main()
{
	std::string line;
	boost::regex pat( "^Subject: (Re: |Aw: )*(.*)" );

	while (std::cin)
	{
		std::getline(std::cin, line);
		boost::smatch matches;
		if (boost::regex_match(line, matches, pat))
			std::cout << "Found match: " << matches[2] << std::endl;
    else
      std::cout << "No match in " << line << std::endl;
	}
}
