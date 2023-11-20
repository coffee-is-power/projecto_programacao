{
  description = "memofante development environment";
  inputs = { nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable"; };
  outputs = { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};
    in {
      devShells.${system}.default = with pkgs;
        mkShell {
            buildInputs = [ premake5 jansson clang ninja pkg-config asciinema curl.dev ];
        };
    };
}
