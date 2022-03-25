
#include "c_is_easy.hpp"

const std::string c_is_easy::getenv(const std::string env_name)
{
#ifdef _WIN32

	char* buf = nullptr;
	size_t sz = 0;
	std::string value = "";

	if (_dupenv_s(&buf, &sz, env_name.c_str()) == 0 && buf != nullptr)
	{
		value = std::move(std::string(buf));
		free(buf);
	}
	return (value);

#elif __linux__

	const char const* env_value = std::getenv(env_name.c_str());
	return env_value == nullptr ? std::string() : std::string(env_value);

#endif
}
