
#include <iostream>
#include <sstream>



int main()
{
  std::stringstream ss;
  std::string myString = "a string";

  // basic string
  std::cout << "This is myString, " << myString << std::endl;

  // stringstream with number converted to int
//  ss.str("2021");
  ss << "2021";
  int myInt;
  ss >> myInt;

  std::cout << "Convert contents of ss, " << ss.str() << ", to an int resulted in " << myInt << std::endl;

  // append to stringstream
  ss.str(ss.str() + " appended this");
  std::cout << "Append to ss resulted in " << ss.str() << std::endl;

  // reset stringstream
  const static std::stringstream initial;
  ss.str(std::string());
  ss.clear();
  ss.copyfmt(initial);
  ss << "new string content";
  std::cout << "Reset ss resulted in " << ss.str() << std::endl;
}
