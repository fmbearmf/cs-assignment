{
  description = "Toolchain";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixpkgs-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs =
    {
      self,
      nixpkgs,
      flake-utils,
    }:
    flake-utils.lib.eachDefaultSystem (
      system:
      let
        pkgs = import nixpkgs { inherit system; };

        llvmPackages = pkgs.llvmPackages;

        stdenv = llvmPackages.stdenv;

        mkShell = pkgs.mkShell.override { inherit stdenv; };
      in
      {
        devShells.default = mkShell {
          name = "unit-test-devshell";
          packages = with pkgs; [
            gnumake
            clang-tools
            pkg-config
          ];
        };
      }
    );
}
