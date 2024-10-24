#include <string>
#include <expected>
#include <print>
#include "cliargs.h"
#include "init.h"
#include "about.h"

int main(int argc, char* argv[]) {
	auto rv = lunawp::cliargs(argc, argv);
	if (not rv) {
		if (rv.error() == 1)
			std::println("{}", lunawp::about::help);
		return rv.error();
	}

	return lunawp::init(rv.value());
}
