#include <string>
#include <vector>
#include <print>
#include <thread>
#include <chrono>
#include <cstring>
#include <cerrno>
#include <sys/un.h>
#include <sys/socket.h>
#include <unistd.h>
#include "data.h"
#include "log.h"
#include "change_wallpaper.h"
#include "config.h"

namespace lunawp {
	namespace socks {
		namespace hyprland {
			std::string get_active_workspace(const std::string& msg) {
				std::string	  active;
				const std::string event = "workspace>>";
				if (size_t i = msg.find(event); i != msg.npos && i == 0)
					active = msg.substr(i + event.size(), msg.find('\n') - (i + event.size()));
				else
					return "";

				return active;
			}

			int run(const std::vector<std::string>& imgs) {
				char* xdg_runtime_dir		  = getenv("XDG_RUNTIME_DIR");
				char* hyprland_instance_signature = getenv("HYPRLAND_INSTANCE_SIGNATURE");
				if (xdg_runtime_dir == nullptr || hyprland_instance_signature == nullptr) {
					auto _ = lunawp::err_clr();
					std::println("-[X] couldnt get environment variable {}",
					    xdg_runtime_dir == nullptr ? "XDG_RUNTIME_DIR" : "HYPRLAND_INSTANCE_SIGNATURE");
					return 1;
				}

				std::string socket_path =
				    std::string(xdg_runtime_dir) + "/hypr/" + std::string(hyprland_instance_signature) + "/.socket2.sock";

				int sock = socket(AF_UNIX, SOCK_STREAM, 0);
				if (sock < 0) {
					auto _ = lunawp::err_clr();
					std::println("-[X] couldn't open a socket, {}", std::strerror(errno));
					return 1;
				}

				struct sockaddr_un socket_addr;
				socket_addr.sun_family = AF_UNIX;
				strncpy(socket_addr.sun_path, socket_path.c_str(), socket_path.size());

				if (connect(sock, reinterpret_cast<struct sockaddr*>(&socket_addr), sizeof(socket_addr)) < 0) {
					auto _ = lunawp::err_clr();
					std::println("-[X] couldn't connect to {} socket, {}", socket_path, std::strerror(errno));
					return 1;
				}

				std::array<char, 16384> buffer;
				int			bytes_read;
				std::string		active_workspace;

				while (true) {
					bytes_read = read(sock, buffer.data(), buffer.size());
					if (bytes_read < 0) {
						auto _ = lunawp::err_clr();
						std::println("-[X] failed to read from socket {} , {}", socket_path, std::strerror(errno));
						return 1;
					} else if (bytes_read == 0) {
						auto _ = lunawp::err_clr();
						std::println("-[X] socket {} closed", socket_path);
						return 1;
					}

					active_workspace =
					    lunawp::socks::hyprland::get_active_workspace(std::string(buffer.data(), bytes_read));
					if (not active_workspace.empty())
						lunawp::change_wallpaper(imgs);

					std::this_thread::sleep_for(std::chrono::microseconds(100));
				}

				return 0;
			}
		}

	}
}
