#include <exception>
#include <expected>
#include <print>
#include "cliargs.h"
#include "about.h"
#include "config.h"
#include "log.h"

namespace lunawp {
	bool next_arg_exist(const int& argc, char* argv[], const int& index) {
		if (index == (argc - 1)) {
			auto _ = lunawp::err_clr();
			std::println("-[X] argument for option '{}' isn't provided", argv[index]);
			return false;
		}

		return true;
	}

	std::expected<struct lunawp_data, int> cliargs(const int& argc, char* argv[]) {
		struct lunawp_data lunawp_data;

		for (int i = 1; i < argc; i++) {
			std::string option = argv[i];
			if (option == "-c") {
				if (not next_arg_exist(argc, argv, i))
					return std::unexpected(1);
				lunawp_data.wm = argv[++i];
			} else if (option == "-d") {
				if (not next_arg_exist(argc, argv, i))
					return std::unexpected(1);
				lunawp_data.imgs_path = argv[++i];
			} else if (option == "--help" || option == "-h") {
				std::println("{}", lunawp::about::help);
				return std::unexpected(0);
			} else if (option == "--license") {
				std::println("{}", lunawp::about::license);
				return std::unexpected(0);
			} else if (option == "--author") {
				std::println("{}", lunawp::about::author);
				return std::unexpected(0);
			} else if (option == "--version" || option == "-V") {
				std::println("{}", lunawp::about::version);
				return std::unexpected(0);
			} else {
				std::println("-[X] unkwown option '{}'", option);
				return std::unexpected(1);
			}
		}

		if (lunawp_data.wm.empty()) {
			auto _ = lunawp::err_clr();
			std::println("-[X] compositor/window-manager isn't provided");
			return std::unexpected(1);
		} else if (lunawp_data.imgs_path.empty()) {
			auto _ = lunawp::err_clr();
			std::println("-[X] images path isn't provided");
			return std::unexpected(1);
		}

		return lunawp_data;
	}
}
