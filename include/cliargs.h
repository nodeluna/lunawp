#ifndef LUNAWP_CLIARGS_H
#define LUNAWP_CLIARGS_H

#include <expected>
#include <string>
#include "data.h"

namespace lunawp {
	std::expected<struct lunawp_data, int> cliargs(const int& argc, char* argv[]);
}

#endif // LUNAWP_CLIARGS_H
