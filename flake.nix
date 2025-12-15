{
        description = "The Pacman Project for the Advanced Programming course at the University of Antwerp";

        inputs = {
                nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
                flake-utils.url = "github:numtide/flake-utils";
        };

        outputs = { self, nixpkgs, flake-utils }:
                flake-utils.lib.eachDefaultSystem
                (system:
                        let
                                pkgs = import nixpkgs {
                                        inherit system;
                                        config.allowUnfree = true;
                                };

                                compiler = pkgs.clang;
                                sfml_2 = pkgs.sfml_2;
                                valgrind = pkgs.valgrind;

                                # Packages needed for development shell
                                sfml-dev-pkgs = with pkgs; [ compiler cmake gdb sfml_2 valgrind];

                                cppGamePackage = pkgs.stdenv.mkDerivation {
                                        pname = "pacman";
                                        version = "0.1.0-release";

                                        src = ./.; # Source code is in the current flake directory

                                        buildInputs = [ sfml_2 ];
                                        nativeBuildInputs = [ pkgs.cmake pkgs.clang ];

                                        cmakeFlags = [
                                                "-DCMAKE_BUILD_TYPE=Release"
                                                "-DSFML_DIR=${sfml_2}/lib/cmake/SFML"
                                        ];

                                        installPhase = ''
                                                echo "Running custom install phase..."
                                                mkdir -p $out
                                                cp pacman $out/
                                                cp -r $src/assets $out/
                                                echo "Executable copied to $out/"
                                        '';
                                };

                                # --- NEW: Package for Debug Build (for Valgrind) ---
                                cppGamePackageDebug = pkgs.stdenv.mkDerivation {
                                        pname = "pacman";
                                        version = "0.1.0-debug";

                                        src = ./.;

                                        buildInputs = [ sfml_2 ];
                                        # Use clang for nativeBuildInputs
                                        nativeBuildInputs = [ pkgs.cmake pkgs.clang ];

                                        cmakeFlags = [
                                                # Build with Debug symbols for useful Valgrind output
                                                "-DCMAKE_BUILD_TYPE=Debug" 
                                                "-DSFML_DIR=${sfml_2}/lib/cmake/SFML"
                                        ];

                                        installPhase = ''
                                                echo "Running custom install phase for DEBUG build..."
                                                mkdir -p $out
                                                cp pacman $out/
                                                cp -r $src/assets $out/
                                                echo "Debug executable copied to $out/"
                                        '';
                                };

                                cpp-env = pkgs.mkShell {
                                        buildInputs = sfml-dev-pkgs;
                                        shellHook = ''
                                                export LD_LIBRARY_PATH=${pkgs.lib.makeLibraryPath [ sfml_2 ]}:$LD_LIBRARY_PATH
                                                export CMAKE_PREFIX_PATH=${sfml_2}:$CMAKE_PREFIX_PATH
                                                export SFML_DIR=${sfml_2}/lib/cmake/SFML

                                                echo "Entering C++ development environment."
                                                echo "Run 'cmake . && make' to build, or 'nix build' outside this shell."
                                                echo "Please run your IDE from within this env to make sure all dependencies are present."
                                        '';
                                };
                        in {
                                packages = {
                                        default = cppGamePackage;
                                        sfml-cpp-project = cppGamePackage;
                                        pacman-debug = cppGamePackageDebug;
                                };

                                devShells = {
                                        default = cpp-env;
                                };

                                apps.default = {
                                        type = "app";
                                        program = "${cppGamePackage}/pacman";
                                };
                        }
                );
}
