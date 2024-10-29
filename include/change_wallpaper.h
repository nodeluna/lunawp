#ifndef LUNAWP_CHANGE_WALLPAPER_H
#define LUNAWP_CHANGE_WALLPAPER_H

#include <string>
#include <string_view>
#include <vector>

namespace lunawp {
	std::vector<std::string> list_images(const std::string_view& path);

	size_t change_wallpaper(const std::vector<std::string>& imgs, const size_t& previous);
}

#endif // LUNAWP_CHANGE_WALLPAPER_H
