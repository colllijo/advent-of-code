#include "AoCCookie.hpp"

#include <filesystem>
#include "AoCException.hpp"

#include <curl/curl.h>

#ifdef SQLITE3_FOUND
#include <sqlite3.h>
#endif

AoCCookie::AoCCookie(const std::shared_ptr<AoCCache>& aocCache) : cache(aocCache) {}

std::string AoCCookie::getSession()
{
	std::optional<std::string> session = cache->get("caoc_session");
	if (session.has_value() && isValidSession(session.value())) return session.value();

	session = loadSessionFromBrowser();
	if (session.has_value())
	{
		cache->set("caoc_session", session.value());
		return session.value();
	}

	char* cookie = getenv("CAOC_AUTH");
	if (cookie == nullptr)
    throw AoCException("Authorisation cookie not set.\nPlease set the `CAOC_AUTH` environment variable.");

	return std::string(cookie);
}

std::optional<std::string> AoCCookie::loadSessionFromBrowser()
{
#ifdef SQLITE3_FOUND
	const char* home = getenv("HOME");
	if (!home) return std::nullopt;;

	std::optional<std::string> session;
	
	session = loadSessionFromFirefox(fs::path(home) / ".zen");
	if (session.has_value()) return session;

	session = loadSessionFromFirefox(fs::path(home) / ".mozilla/firefox");

	return session;
#else
	return std::nullopt;
#endif
}

std::optional<std::string> AoCCookie::loadSessionFromFirefox(const fs::path& profileDir)
{
	if (!fs::exists(profileDir) || !fs::is_directory(profileDir)) return std::nullopt;

	for (const auto& entry : std::filesystem::directory_iterator(profileDir))
	{
		if (entry.is_directory() && std::filesystem::exists(entry.path() / "cookies.sqlite"))
		{
			std::optional<std::string> session = readCookieFromSQLite(entry.path() / "cookies.sqlite");
			if (session && isValidSession(session.value()))
			{
				return session;
			}
		}
	}

	return std::nullopt;
}

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	((std::string *)userp)->append((char *)contents, size * nmemb);
	return size * nmemb;
}

bool AoCCookie::isValidSession(const std::string& session)
{
	std::string url = "https://adventofcode.com/";
	std::string readBuffer;

	CURL *curl = curl_easy_init();
	if (!curl)
	{
		fprintf(stderr, "Could not initialize curl\n");
		return false;
	}

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_COOKIE, ("session=" + session).c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

	CURLcode res = curl_easy_perform(curl);
	if (res != CURLE_OK)
	{
		curl_easy_cleanup(curl);
    throw AoCException("Failed to download: " + std::string(curl_easy_strerror(res)));
	}

	// Cleanup
	curl_easy_cleanup(curl);

	readBuffer = readBuffer.substr(readBuffer.find("<nav>") + 5, readBuffer.find("</nav>") - readBuffer.find("<nav>") - 5);
	return readBuffer.find("[Log Out]") != std::string::npos;
}

std::optional<std::string> AoCCookie::readCookieFromSQLite(const fs::path& path) 
{
#ifdef SQLITE3_FOUND
	fs::path tmpDir = fs::temp_directory_path();
	fs::path dbFile = tmpDir / "aoc_cookies.sqlite";
	fs::copy_file(path, dbFile, fs::copy_options::overwrite_existing);

	sqlite3* db;

	if (sqlite3_open(dbFile.c_str(), &db) != SQLITE_OK)
	{
		sqlite3_close(db);
		return std::nullopt;
	}

	sqlite3_stmt* stmt;
	const char* sql = "SELECT value FROM moz_cookies WHERE name = 'session' AND host = '.adventofcode.com'";

	if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
	{
		sqlite3_close(db);
		return std::nullopt;
	}

	std::string session;

	if (sqlite3_step(stmt) == SQLITE_ROW) session = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	if (!session.empty()) return session;
	return std::nullopt;
#else
  return std::nullopt;
#endif
}
