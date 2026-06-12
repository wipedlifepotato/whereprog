#include<iostream>
//#include<fstream>
#include<regex>
#include<sstream>
//#include<string>

std::string get_env(std::string what, const char** env, const char delitor='=') 
{

	std::smatch matches;
//	auto sre = std::regex("(\\w+)\=([\\.:\\/a-zA-Z0-9]+)");
	using namespace std;
	//char **sPointer = env;
	while(*env)
	{
//		std::cout << *env << std::endl;
	/*	if(!std::regex_match(std::string(*env), matches, sre) && matches.size() >=2) 
		{
			std::cerr << "Bad enviroment: " << *env << std::endl;
		} else 
		{
			if ( std::string(matches[0]) == what )
			{
				return std::string( matches.suffix() );
			}
		}
	*/
		std::ostringstream name;
		std::ostringstream val;
		bool isname = true;
		char * pS = (char*)*env;
		while(*pS)
		{
			if (*pS == delitor)
			{
				isname = false;
				pS++;
				continue;
			}
			if (isname)
				name<<*pS;
			else
				val<<*pS;
			pS++;
		}
		if(name.str() == what)
		{
			return val.str();
		}
		(env++);
	}
	//env = static_cast<char**>(sPointer);
	throw std::runtime_error("Not found env val");
}
std::vector<std::string> split_str(std::string & str, char delimiter)
{
	std::ostringstream tmp;
	std::vector<std::string> ret;
	for(auto ch : str)
	{
		if (ch != delimiter)
		{
			tmp<<ch;
		}
		else 
		{
			ret.push_back(tmp.str());
			tmp.str("");
			tmp.clear();
		}
	}
	tmp.str("");
	tmp.clear();
	return ret;
}
#include<filesystem>
std::string search_program(std::string name, std::string path)
{
//	try {
	auto p = std::filesystem::path{path};
	if(!std::filesystem::exists(p) || !std::filesystem::is_directory(p))
	{
	//	std::cout << p << " is not exists" << std::endl;
	//	std::cout << path << std::endl << "~~~~" << std::endl;
		return std::string{};
	}
	//std::cout << "search in " << p << std::endl;
	for(auto & el : std::filesystem::directory_iterator(p))
	{
		//std::cout << el << std::endl;
		if (name == el.path().filename())
		{
			return el.path();	
		} else {
	//		std::cerr << "not found: " << el << std::endl;
		}
	}
	return std::string{};
//	} catch(std::exception & err)
//	{
//		std::cerr << err.what() << std::endl;
//	}catch(std::filesystem::filesystem_error const & err) 
//	{
//		std::cerr << err.what() << std::endl;
//	}

}

int main(const int c, const char * argv[], const char * env[]) 
{
	//auto path = get_env("PATH",env);
	//std::cout <<  path << std::endl;
	//auto splitted = split_str(path, ':');
	//std::cout << search_program("a.out", ".") << std::endl;
	if(c < 2)
	{
		std::cerr << argv[0] << " filename" << std::endl;
		return 1;
	}
	auto path = get_env("PATH",env);
	auto splitted = split_str(path, ':');
	for(auto p: splitted)
	{
		auto r = search_program(argv[1], p);
		if(r.size())
		{
			std::cout << "Found:" << r << std::endl;
		}
	}
}
