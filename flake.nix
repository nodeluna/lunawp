{
    description = "a tool that changes your wallpaper if your workspace changes";

    inputs = {
        nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
        utils.url = "github:numtide/flake-utils";
    };

    outputs = { self, nixpkgs, utils}:
        utils.lib.eachDefaultSystem (system:
                let
                pkgs = import nixpkgs{ inherit system; };
                pname = "lunawp";
                version = "0.1.2";
                in
                {

                packages.lunawp = pkgs.stdenvNoCC.mkDerivation {
                inherit pname;
                inherit version;
                src = ./.;
                buildInputs = with pkgs; [ gcc14 gcc14Stdenv pkg-config ];
                nativeBuildInputs = with pkgs; [ gnumake ];
                buildPhase = ''
                make -j
                '';
                installPhase = ''
                make PREFIX=$out install
                '';
                };

                packages.default = self.packages.${system}.lunawp;

                devShells.lunawp = with pkgs; mkShellNoCC {
                    buildInputs = with pkgs; [ gcc14 gcc14Stdenv pkg-config ];
                };
                devShells.default = self.devShells.${system}.lunawp;
                }
    );
}
