#include <exception>
#include <string>
#include <print>
#include <string_view>
#include <unistd.h>
#include <chrono>
#include <thread>
#include "init.h"
#include "data.h"
#include "cmd.h"
#include "log.h"
#include "change_wallpaper.h"
#include "socks.h"

namespace lunawp {
	namespace str {
		std::string substr(const std::string_view& string, const std::string_view& pattern, const std::string_view& pattern2) {
			size_t index = std::min(string.find(pattern), string.size() - (string.empty() == false ? 1 : 0));
			index += index != string.size() - 1 ? pattern.size() : 0;
			return std::string(string.substr(index, std::min(string.find(pattern2, index), string.size() - 1) - index));
		}
	}
}

namespace lunawp {
	namespace sway {
		std::string get_active_workspace(void) {
			std::string command = "swaymsg -t get_workspaces -p";
			auto	    output  = lunawp::cmd(command);
			if (not output) {
				auto _ = lunawp::err_clr();
				std::println("-[X] couldn't execute command '{}', {}", command, output.error().message());
			}

			const std::string& out = output.value();
			std::string	   id  = " (focused)";

			size_t id_index = std::min(out.find(id), out.size() - (out.empty() == false ? 1 : 0));
			size_t begin	= id_index - (out.empty() == false ? 1 : 0);
			for (; begin != 0; begin--) {
				if (out[begin] == ' ') {
					begin++;
					break;
				}
			}

			return out.substr(begin, id_index - begin);
		}
	}

	namespace qtile {
		std::string get_active_workspace(void) {
			std::string command = "qtile cmd-obj -o group -f info";
			auto	    output  = lunawp::cmd(command);
			if (not output) {
				auto _ = lunawp::err_clr();
				std::println("-[X] couldn't execute command '{}', {}", command, output.error().message());
			}

			std::string id = "'label': '";
			return lunawp::str::substr(output.value(), id, "'");
		}
	}
}

namespace lunawp {
	std::expected<std::string, int> get_active_workspace(const std::string_view& wm) {
		std::string num;
		if (wm == "sway")
			num = lunawp::sway::get_active_workspace();
		else if (wm == "qtile")
			num = lunawp::qtile::get_active_workspace();
		else {
			auto _ = lunawp::err_clr();
			std::println("-[X] unsupported window manager '{}'", wm);
			return std::unexpected(1);
		}

		if (num.empty()) {
			std::println("-[X] couldn't get active workspace '{}'", wm);
			return std::unexpected(1);
		}

		return num;
	}

	int run(const std::vector<std::string>& imgs, const std::string_view& wm) {
		std::string temp_active_workspace;
		size_t	    previous_index;
		while (true) {
			auto active_workspace = lunawp::get_active_workspace(wm);
			if (not active_workspace)
				return active_workspace.error();

			if (temp_active_workspace.empty())
				temp_active_workspace = active_workspace.value();
			else if (active_workspace.value() != temp_active_workspace) {
				previous_index = lunawp::change_wallpaper(imgs, previous_index);
				temp_active_workspace.clear();
			}

			std::this_thread::sleep_for(std::chrono::microseconds(lunawp::config::sleep_time));
		}
	}

	bool daemon(void) {
		std::string command = "swww query";
		auto	    output  = lunawp::cmd(command);
		if (not output) {
			auto _ = lunawp::err_clr();
			std::println("-[X] couldn't execute command '{}', {}", command, output.error().message());
			return false;
		}

		if (output.value().find("not found") != output.value().npos)
			return false;

		return true;
	}

	int init(const struct lunawp_data& lunawp_data) {
		bool running = lunawp::daemon();
		if (not running) {
			auto _ = lunawp::err_clr();
			std::println("-[X] swww-daemon not running. run it first with 'swww-daemon'");
			return 1;
		}

		std::vector<std::string> imgs = lunawp::list_images(lunawp_data.imgs_path);
		if (imgs.empty()) {
			auto _ = lunawp::err_clr();
			std::println("-[X] didn't find images");
			return 1;
		}

		if (lunawp_data.wm == "hyprland")
			return lunawp::socks::hyprland::run(imgs);
		else
			return lunawp::run(imgs, lunawp_data.wm);
	}
}
