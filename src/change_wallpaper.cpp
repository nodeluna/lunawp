#include <string>
#include <string_view>
#include <filesystem>
#include <vector>
#include <ranges>
#include <algorithm>
#include <print>
#include <random>
#include <cstring>
#include <cerrno>
#include "change_wallpaper.h"
#include "config.h"
#include "log.h"

namespace fs = std::filesystem;

namespace lunawp {
	bool correct_extension(const std::string_view& path) {
		const auto& extensions = lunawp::config::extensions;

		return std::ranges::any_of(
		    extensions, [&](const std::string_view& extension) { return not std::ranges::find_end(path, extension).empty(); });
	}

	std::vector<std::string> list_images(const std::string_view& path) {
		std::vector<std::string> imgs;
		std::error_code		 ec;

		if (not fs::exists(path, ec) || not fs::is_directory(path, ec)) {
			auto _ = lunawp::err_clr();
			std::println("-[X] path '{}' isn't a directory", path);
			return imgs;
		}
		if (ec.value() != 0) {
			auto _ = lunawp::err_clr();
			std::println("-[X] couldn't check '{}', {}", path, std::strerror(errno));
			return imgs;
		}

		for (const auto& entry : fs::directory_iterator(path, fs::directory_options::skip_permission_denied)) {
			if (correct_extension(entry.path().string()))
				imgs.push_back(entry.path().string());
		}

		return imgs;
	}

	size_t change_wallpaper(const std::vector<std::string>& imgs, const size_t& previous) {
		std::random_device		rand;
		std::mt19937			gen(rand());
		std::uniform_int_distribution<> dis(0, imgs.size() - 1);
		size_t				index = dis(gen);
		if (previous == index)
			index = index / 2;
		std::string command =
		    std::format("swww img '{}' --transition-step 255 --transition-fps 255 1> /dev/null 2> /dev/null", imgs[index]);

		system(command.c_str());

		return index;
	}
}
