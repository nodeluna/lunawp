#ifndef LUNAWP_CMD_H
#define LUNAWP_CMD_H

#include <string>
#include <string_view>
#include <expected>
#include <system_error>

namespace lunawp {
	std::expected<std::string, std::error_code> cmd(const std::string_view& command);
}

#endif // LUNAWP_CMD_H
