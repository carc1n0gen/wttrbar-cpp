#include "utils.hpp"

#include <regex>
#include <format>
#include <chrono>
#include <stdexcept>
#include <filesystem>

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/error.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <boost/algorithm/string/predicate.hpp>

namespace wttrbar::utils
{
	namespace beast = boost::beast;
	namespace net = boost::asio;
	using tcp = net::ip::tcp;
	namespace ssl = net::ssl;

	// Helper to parse URL into scheme, host, port, target
	struct url_parts
	{
		std::string scheme, host, port, target;
	};

	static url_parts parse_url(const std::string& url)
	{
		// Basic regex for http(s)://host[:port]/path
		std::regex url_regex(R"((http|https)://([^/:]+)(:([0-9]+))?(/.*)?)");
		std::smatch match;
		if (!std::regex_match(url, match, url_regex))
		{
			throw std::invalid_argument("Invalid URL: " + url);
		}
		url_parts parts;
		parts.scheme = match[1].str();
		parts.host = match[2].str();
		parts.port = match[4].matched ? match[4].str() : (parts.scheme == "https" ? "443" : "80");
		parts.target = match[5].matched ? match[5].str() : "/";
		return parts;
	}

	Response request(
		const std::string& url,
		const std::string& method,
		const std::vector<std::string>& headers,
		const std::string& body)
	{
		url_parts parts = parse_url(url);
		net::io_context ioc;
		beast::flat_buffer buffer;
		Response resp;

		// Common lambda for request/response logic
		auto perform_request = [&](auto& stream) -> void
		{
			boost::beast::http::request<boost::beast::http::string_body> req{boost::beast::http::string_to_verb(method), parts.target, 11};
			req.set(boost::beast::http::field::host, parts.host);
			req.set(boost::beast::http::field::user_agent, BOOST_BEAST_VERSION_STRING);
			for (const auto& h : headers)
			{
				auto pos = h.find(":");
				if (pos != std::string::npos)
				{
					req.set(h.substr(0, pos), h.substr(pos + 1));
				}
			}
			if (!body.empty())
			{
				req.body() = body;
				req.prepare_payload();
			}
			boost::beast::http::write(stream, req);
			boost::beast::http::response<boost::beast::http::string_body> res;
			boost::beast::http::read(stream, buffer, res);
			resp.status = static_cast<int>(res.result_int());
			resp.body = std::move(res.body());
		};

		if (parts.scheme == "https")
		{
			ssl::context ctx(ssl::context::sslv23_client);
			ctx.set_default_verify_paths();
			beast::ssl_stream<tcp::socket> stream(ioc, ctx);
			tcp::resolver resolver(ioc);
			auto const results = resolver.resolve(parts.host, parts.port);
			net::connect(stream.next_layer(), results.begin(), results.end());
            // Set SNI hostname (required by many servers)
            if(!SSL_set_tlsext_host_name(stream.native_handle(), parts.host.c_str()))
            {
                throw boost::system::system_error(
                    ::ERR_get_error(),
                    boost::asio::error::get_ssl_category());
            }
            stream.handshake(ssl::stream_base::client);
			perform_request(stream);
			beast::error_code ec;
			stream.shutdown(ec); // ignore shutdown errors
		}
		else if (parts.scheme == "http")
		{
			tcp::resolver resolver(ioc);
			beast::tcp_stream stream(ioc);
			auto const results = resolver.resolve(parts.host, parts.port);
			stream.connect(results);
			perform_request(stream);
			beast::error_code ec;
			stream.socket().shutdown(tcp::socket::shutdown_both, ec);
		}
		else
		{
			throw std::invalid_argument("Unsupported scheme: " + parts.scheme);
		}
		return resp;
	}

	bool isCacheRecent(const std::string& cache_file_path)
	{
		if (std::filesystem::exists(cache_file_path))
        {
            auto last_write_time = std::filesystem::last_write_time(cache_file_path);
            auto now = std::filesystem::file_time_type::clock::now();
            return (now - last_write_time) < std::chrono::minutes(10);
        }
        return false;
	}

	std::chrono::sys_time<std::chrono::seconds> chronoDateFromString(const std::string& datetime_str, const std::string& format)
	{
		std::istringstream iss(datetime_str);
		std::chrono::sys_time<std::chrono::seconds> tp;
		iss >> std::chrono::parse(format, tp);
		if (iss.fail())
		{
			throw std::runtime_error(std::format("Failed to parse datetime: {}, provided format: {}", datetime_str, format));
		}
		return tp;
	}

	std::chrono::hh_mm_ss<std::chrono::seconds> chronoTimeFromString(const std::string& time_str, const std::string& format)
	{
		std::istringstream iss(time_str);
		std::chrono::seconds dur{};
		iss >> std::chrono::parse(format, dur);
		if (iss.fail())
		{
			throw std::runtime_error(std::format("Failed to parse time: {}, provided format: {}", time_str, format));
		}
		return std::chrono::hh_mm_ss<std::chrono::seconds>{dur};
	}
}
