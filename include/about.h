#ifndef LUNAWP_ABOUT_H
#define LUNAWP_ABOUT_H

#include <string>

namespace lunawp {
	namespace about {
		inline std::string version = "\n  -> lunawp 0.1.1";

		inline std::string help = "-> a tool that changes your wallpaper if your workspace changes"
					  "\n"
					  "         _\n"
					  "        | |  _  _   _ _    __ _  __ __ __  _ __ \n"
					  "        | | | || | | ' \\  / _` | \\ V  V / | '_ \\ \n"
					  "        |_|  \\_,_| |_||_| \\__,_|  \\_/\\_/  | .__/\n"
					  "                                          |_|   \n"
					  "\n"
					  "  usage\n"
					  "    $ swww-daemon\n"
					  "    $ lunawp -c hyprland -d /path/to/imgs_dir\n"
					  "\n"
					  "  options\n"
					  "    [-c] <name>\n"
					  "        the name of the compositor/window-manager. hyprland, sway and qtile are supported\n"
					  "\n"
					  "    [-d] <path>\n"
					  "        the directory where the images are\n"
					  "\n"
					  "    [--author]\n"
					  "        print the program's author\n"
					  "\n"
					  "    [--license]\n"
					  "        print the program's license\n"
					  "\n"
					  "    [-V, --version]\n"
					  "        print the program's version\n"
					  "\n"
					  "    [-h, --help]\n"
					  "        print this help statement\n";

		inline std::string license = "\n  -> GPLv3+\n"
					     "  -> This program is distributed in the hope that it will be useful,\n"
					     "       but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
					     "       MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n"
					     "       See the GNU General Public License version 3 for more details.\n"
					     "  -> https://www.gnu.org/licenses/gpl-3.0.en.html";

		inline std::string author = "\n  -> nodeluna - nodeluna@proton.me"
					    "\n  -> https://github.com/nodeluna\n";
	}
}

#endif // LUNAWP_ABOUT_H
