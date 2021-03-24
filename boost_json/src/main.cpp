
#include <boost/json.hpp>
#include <iostream>
#include <fstream>
#include <string>


void usage()
{
  std::cout << "JSON parse parameters required." << std:: endl;
  std::cout << "  main JSON_FILENAME" << std::endl;
}


boost::json::value parse_file(char const* filename)
{
  std::ifstream f(filename, std::ios::in);
  boost::json::stream_parser p;
  boost::json::error_code ec;
  const size_t BUFFER_SIZE = 25;
  char buf[BUFFER_SIZE];
  do
  {
    f.read(buf, BUFFER_SIZE);
    p.write(buf, f.gcount(), ec);
    if (ec)
      throw std::runtime_error("JSON parse error, " + ec.message() + " : " + std::string(buf, f.gcount()).c_str());
  }
  while(!f.eof());
  f.close();
  if (ec) return nullptr;
  return p.release();
}



void pretty_print( std::ostream& os, boost::json::value const& jv, std::string* indent = nullptr )
{
    std::string indent_;
    if(! indent)
        indent = &indent_;
    switch(jv.kind())
    {
    case boost::json::kind::object:
    {
        os << "{\n";
        indent->append(4, ' ');
        auto const& obj = jv.get_object();
        if(! obj.empty())
        {
            auto it = obj.begin();
            for(;;)
            {
                os << *indent << boost::json::serialize(it->key()) << " : ";
                pretty_print(os, it->value(), indent);
                if(++it == obj.end())
                    break;
                os << ",\n";
            }
        }
        os << "\n";
        indent->resize(indent->size() - 4);
        os << *indent << "}";
        break;
    }

    case boost::json::kind::array:
    {
        os << "[\n";
        indent->append(4, ' ');
        auto const& arr = jv.get_array();
        if(! arr.empty())
        {
            auto it = arr.begin();
            for(;;)
            {
                os << *indent;
                pretty_print( os, *it, indent);
                if(++it == arr.end())
                    break;
                os << ",\n";
            }
        }
        os << "\n";
        indent->resize(indent->size() - 4);
        os << *indent << "]";
        break;
    }

    case boost::json::kind::string:
    {
        os << boost::json::serialize(jv.get_string());
        break;
    }

    case boost::json::kind::uint64:
        os << jv.get_uint64();
        break;

    case boost::json::kind::int64:
        os << jv.get_int64();
        break;

    case boost::json::kind::double_:
        os << jv.get_double();
        break;

    case boost::json::kind::bool_:
        if(jv.get_bool())
            os << "true";
        else
            os << "false";
        break;

    case boost::json::kind::null:
        os << "null";
        break;
    }

    if(indent->empty())
        os << "\n";
}


int main(int argc, char * argv[])
{
  if (argc < 2) {
    usage();
    return 1;
  }

  try
  {
    auto const jv = parse_file(argv[1]);
    pretty_print(std::cout, jv);
  }
  catch (std::exception &e)
  {
    std::cout << "Exception: " << e.what() << std::endl << std::endl;
    return 1;
  }


  return 0;
}
