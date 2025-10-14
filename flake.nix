{
  description = "A C++ project with SFML using Nix flakes";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-25.05";
  };

  outputs = { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = import nixpkgs {
        inherit system;
        config.allowUnfree = true;
      };

      compiler = pkgs.clang;
      # Use the specific SFML 2.6.2 package
      sfml_2 = pkgs.sfml_2;
      sfml-pkgs = with pkgs; [ compiler cmake gdb sfml_2 ];

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

      clion-env = pkgs.mkShell {
        buildInputs = sfml-pkgs;
        shellHook = ''
          export LD_LIBRARY_PATH=${pkgs.lib.makeLibraryPath [ sfml_2 ]}:$LD_LIBRARY_PATH
          export CMAKE_PREFIX_PATH=${sfml_2}:$CMAKE_PREFIX_PATH

          # Manual fix for SFML 2.6 CMake targets
          export SFML_DIR=${sfml_2}/lib/cmake/SFML

          echo "Launching CLion from host system..."
          clion .
        '';
      };

    in {
      devShells.${system} = {
        default = cpp-env;
        clion = clion-env;
      };
    };
}
