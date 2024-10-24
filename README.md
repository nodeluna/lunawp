## lunawp

    a tool that changes your wallpaper if your workspace changes

## installation

    $ make
    # make install

## un-installation

    $ make clean
    # make uninstall

## dependencies

    gcc >= 14 or clang >= 17
    swww
    hyprland, sway or qtile

## usage

    read the man page and/or --help statement

## files

    when running "$ make" compiles the program and the binary is placed in the repo's main directory and build files in ./build
    when running "# make install" the binary file is copied to /usr/bin/lunawp , and the man page to /usr/share/man/man1/lunawp.1

    when running "$ make clean" the ./build is removed. And the binary is removed from the repo's directory but not from /usr/bin/lunawp
    when running "# make uninstall" the binary file is removed from /usr/bin/lunawp as well as /usr/share/man/man1/lunawp.1

## author

    nodeluna - nodeluna@proton.me
