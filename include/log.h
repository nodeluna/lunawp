#ifndef LUNAWP_LOG_H
#define LUNAWP_LOG_H

#include <string>
#include <print>
#include "config.h"

namespace lunawp {
	class err_clr {
		public:
			err_clr(void) {
				std::print("{}", lunawp::config::color_error);
			}

			~err_clr(void) {
				std::print("{}", lunawp::config::reset_color);
			}
	};
}

#endif // LUNAWP_LOG_H
