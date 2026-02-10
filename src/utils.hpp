#pragma once

#include <string>
#include <vector>
#include <chrono>

namespace wttrbar::utils
{
	struct Response
	{
		int status;
		std::string body;
	};

	Response request(
		const std::string& url,
		const std::string& method = "GET",
		const std::vector<std::string>& headers = {},
		const std::string& body = ""
	);

	bool isCacheRecent(const std::string& cache_file_path);

	std::chrono::sys_time<std::chrono::seconds> chronoDateFromString(const std::string& datetime_str, const std::string& format);

	std::chrono::hh_mm_ss<std::chrono::seconds> chronoTimeFromString(const std::string& time_str, const std::string& format);
}
