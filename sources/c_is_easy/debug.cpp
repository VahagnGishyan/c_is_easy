
#include "debug.hpp"

void c_is_easy::debug::test_dll_work(std::ostream& file)
{
	file << "c_is_easy is loaded" << std::endl;
}

void c_is_easy::debug::log(const std::string& err, std::ostream& file)
{
#ifdef DEBUG_MODE
	//if (std::string(c_is_easy::getenv(EV_NAME_DEBUG_LOG_SET)) == 
		//std::string(c_is_easy::getenv(EV_VALUE_DEBUG_LOG_ON)))
	{
		file << err << std::endl;
	}
#endif //!DEBUG_MODE
}
