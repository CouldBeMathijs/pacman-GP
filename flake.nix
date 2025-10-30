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

                                # Packages needed for development shell
                                sfml-dev-pkgs = with pkgs; [ compiler cmake gdb sfml_2 valgrind];

                                # --- 1. PACKAGE DEFINITION (Build Shell) ---
                                # Defines how to build and install the C++ project
                                cppGamePackage = pkgs.stdenv.mkDerivation {
                                        pname = "Pacman";
                                        version = "0.1.0";

                                        src = ./.; # Source code is in the current flake directory

                                        # Dependencies required for linking and runtime (SFML libraries)
                                        buildInputs = [ sfml_2 ];

                                        # Dependencies required for the build process (e.g., CMake, compiler)
                                        nativeBuildInputs = [ pkgs.cmake pkgs.clang ];

                                        # Set up the CMake flags
                                        cmakeFlags = [
                                                "-DCMAKE_BUILD_TYPE=Release"
                                                # Explicitly tell CMake where to find the SFML package configuration
                                                "-DSFML_DIR=${sfml_2}/lib/cmake/SFML"
                                        ];

                                        installPhase = ''
                                                echo "Running custom install phase..."
                                                # Create the standard output directory for binaries
                                                mkdir -p $out/bin

                                                # Copy the built executable (named 'pacman' based on your log) to $out/bin
                                                cp pacman $out/bin/

                                                # If your project uses assets (images, fonts, etc.), you must copy them here as well.
                                                # Example for assets:
                                                # mkdir -p $out/share/pacman/
                                                # cp -r assets/* $out/share/pacman/

                                                echo "Executable copied to $out/bin/"
                                        '';

                                        # The installPhase now overrides the default 'make install' phase.
                                };

                                # --- 2. DEVELOPMENT SHELL DEFINITION ---
                                # Defines the environment for development
                                cpp-env = pkgs.mkShell {
                                        buildInputs = sfml-dev-pkgs;
                                        shellHook = ''
                                                export LD_LIBRARY_PATH=${pkgs.lib.makeLibraryPath [ sfml_2 ]}:$LD_LIBRARY_PATH
                                                export CMAKE_PREFIX_PATH=${sfml_2}:$CMAKE_PREFIX_PATH

                                                # Manual fix for SFML 2.6 CMake targets
                                                export SFML_DIR=${sfml_2}/lib/cmake/SFML

                                                echo "Entering C++ development environment."
                                                echo "Run 'cmake . && make' to build, or 'nix build' outside this shell."
                                                echo "Please run your IDE from within this env to make sure all dependencies are present."
                                        '';
                                };
                        in {
                                # Make the C++ package available via `nix build` or `nix install`
                                packages = {
                                        default = cppGamePackage;
                                        sfml-cpp-project = cppGamePackage;
                                };

                                devShells = {
                                        default = cpp-env;
                                };
                        }
                );
}

