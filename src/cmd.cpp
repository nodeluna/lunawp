#include <cstdio>
#include <string>
#include <string_view>
#include <expected>
#include <array>
#include <system_error>
#include <cerrno>
#include "cmd.h"

namespace lunawp {
	class pipe {
		public:
			pipe(const std::string_view& command, const std::string_view& mode) : p(popen(command.data(), mode.data())) {
			}

			~pipe() {
				if (p != nullptr)
					pclose(p);
			}

			FILE* data(void) {
				return p;
			}

		private:
			FILE* p = nullptr;
	};

	std::expected<std::string, std::error_code> cmd(const std::string_view& command) {
		std::string  output;
		lunawp::pipe pipe(command.data() + std::string(" 2>&1"), "r");
		if (not pipe.data()) {
			std::error_code ec = std::make_error_code(( std::errc ) errno);
			return std::unexpected(ec);
		}

		std::array<char, 1024> buffer;

		while (fgets(buffer.data(), buffer.size(), pipe.data()) != NULL) {
			output.append(buffer.data());
		}

		return output;
	}
}
