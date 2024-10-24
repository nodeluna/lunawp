#ifndef LUNAWP_CONFIG_H
#define LUNAWP_CONFIG_H

#include <string>
#include <unordered_set>

namespace lunawp {
	namespace config {
		inline std::string		       color_error = "\x1b[1;31m";
		inline std::string		       reset_color = "\x1b[1;0m";
		inline time_t			       sleep_time  = 2000;
		inline std::unordered_set<std::string> extensions  = {"png", "jpeg", "gif", "pnm", "tga", "tiff", "webp", "bmp"};
	}
}

#endif // LUNAWP_CONFIG_H
