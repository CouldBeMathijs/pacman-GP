{
        description = "The Pacman Project for the Advanced Programming course at the University of Antwerp";

        inputs = {
                nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
                flake-utils.url = "github:numtide/flake-utils";
        };

        outputs = { self, nixpkgs, flake-utils }:
                flake-utils.lib.eachDefaultSystem (system:
                        let
                                pkgs = import nixpkgs {
                                        inherit system;
                                        # config.allowUnfree = true;
                                };

                                # Explicitly choose the compiler
                                compiler = pkgs.clang;
                                sfml_2 = pkgs.sfml_2;

                                # Package list for the development shell
                                sfml-dev-pkgs = with pkgs; [
                                        compiler
                                        cmake      # Provided as requested
                                        meson
                                        ninja
                                        pkg-config # Essential for Meson
                                        gdb
                                        sfml_2
                                        valgrind
                                        clang-uml
                                ];

                                # Helper to create a derivation using Meson
                                mkPacmanDerivation = { optimization, debug, version }: pkgs.stdenv.mkDerivation {
                                        pname = "pacman";
                                        inherit version;
                                        src = ./.;

                                        nativeBuildInputs = with pkgs; [ 
                                                meson 
                                                ninja 
                                                pkg-config 
                                                compiler 
                                        ];

                                        buildInputs = [ sfml_2 ];

                                        # We set these instead of buildtype to avoid conflicts with Nix defaults
                                        mesonFlags = [
                                                "-Doptimization=${optimization}"
                                                "-Ddebug=${if debug then "true" else "false"}"
                                        ];

                                        # Meson build happens in a subdirectory; we copy results to $out
                                        installPhase = ''
                                        runHook preInstall
                                        echo "Installing Pacman to $out..."
                                        mkdir -p $out

                                        # Copy the binary (assumed to be named 'pacman' in meson.build)
                                        # We use a find command to be safe regardless of where Meson puts it
                                        find . -name pacman -type f -executable -exec cp {} $out/ \;

                                        # Copy assets
                                        if [ -d "$src/assets" ]; then
                                          cp -r $src/assets $out/
                                        fi

                                        echo "Installation complete."
                                        runHook postInstall
                                        '';
                                };

                                # Define the two main package variants
                                cppGamePackage = mkPacmanDerivation { 
                                        optimization = "3"; 
                                        debug = false;
                                        version = "0.1.0-release"; 
                                };

                                cppGamePackageDebug = mkPacmanDerivation { 
                                        optimization = "0"; 
                                        debug = true;
                                        version = "0.1.0-debug"; 
                                };

                        in {
                                # 'nix build'
                                packages = {
                                        default = cppGamePackage;
                                        pacman-release = cppGamePackage;
                                        pacman-debug = cppGamePackageDebug;
                                };

                                # 'nix develop'
                                devShells.default = pkgs.mkShell {
                                        buildInputs = sfml-dev-pkgs;

                                        shellHook = ''
                                        export LD_LIBRARY_PATH=${pkgs.lib.makeLibraryPath [ sfml_2 ]}:$LD_LIBRARY_PATH

                                        # Environment variables to keep CMake happy within the dev shell
                                        export CMAKE_PREFIX_PATH=${sfml_2}:$CMAKE_PREFIX_PATH
                                        export SFML_DIR=${sfml_2}/lib/cmake/SFML

                                        echo "--------------------------------------------------------"
                                        echo "Pacman Dev Environment (Meson + CMake + Clang)"
                                        echo "--------------------------------------------------------"
                                        echo "To build with Meson:"
                                        echo "  meson setup build && meson compile -C build"
                                        echo ""
                                        echo "To build with CMake:"
                                        echo "  cmake -B build-cmake . && cmake --build build-cmake"
                                        echo "--------------------------------------------------------"
                                        '';
                                };

                                # 'nix run'
                                apps.default = {
                                        type = "app";
                                        program = "${cppGamePackage}/pacman";
                                };
                        }
                );
}
