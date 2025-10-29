{
        description = "A C++ project";

        inputs = {
                # Get the systems from the flake's utility functions
                nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
                flake-utils.url = "github:numtide/flake-utils";
        };

        outputs = { self, nixpkgs, flake-utils }:
                # Use flake-utils to iterate over common systems
                flake-utils.lib.eachDefaultSystem 
                (system: # <--- system variable is now passed in
                        let
                                pkgs = import nixpkgs {
                                        inherit system;
                                        config.allowUnfree = true;
                                };

                                compiler = pkgs.clang;

                                # Use the specific SFML 2.6.2 package
                                sfml_2 = pkgs.sfml_2;
                                sfml-pkgs = with pkgs; [ compiler cmake gdb sfml_2 valgrind];

                                cpp-env = pkgs.mkShell {
                                        buildInputs = sfml-pkgs;
                                        shellHook = ''
          export LD_LIBRARY_PATH=${pkgs.lib.makeLibraryPath [ sfml_2 ]}:$LD_LIBRARY_PATH
          export CMAKE_PREFIX_PATH=${sfml_2}:$CMAKE_PREFIX_PATH

          # Manual fix for SFML 2.6 CMake targets
          export SFML_DIR=${sfml_2}/lib/cmake/SFML

          echo "Entering C++ development environment."
          echo "Please run your IDE from within this env to make sure all dependencies are present."
                                        '';
                                };
                        in {
                                devShells = {
                                        default = cpp-env;
                                };
                        }
                );
}
