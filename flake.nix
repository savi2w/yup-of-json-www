{
  inputs = {
    flake-utils.url = "github:numtide/flake-utils";
    melange.url = "github:melange-re/melange";
    nixpkgs.url = "github:nixos/nixpkgs/nixpkgs-unstable";
  };

  outputs = { self, flake-utils, nixpkgs, ... }@inputs:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = (import nixpkgs { inherit system; }).extend
          inputs.melange.overlays.default;
      in {
        devShells.default = pkgs.mkShell {
          buildInputs = [
            pkgs.ocamlPackages.dune_3
            pkgs.ocamlPackages.melange
            pkgs.ocamlPackages.mel
            pkgs.ocamlPackages.ocaml
            pkgs.nodejs-18_x
            pkgs.reason
          ];
          shellHook =
            ''
              npm install && \
              ln -sfn ${pkgs.ocamlPackages.melange}/lib/melange/runtime node_modules/melange && \
              mel clean && \
              mel build && \
              NODE_ENV=production npx webpack build
            '';
        };
      });
}
