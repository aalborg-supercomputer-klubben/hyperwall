{
  description = "Hyperwall ASCK";

  inputs = {
    nixpkgs.url = "nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs }: let
    system = "x86_64-linux";
    pkgs = import nixpkgs { inherit system; };
  in {
    devShells.${system}.default = pkgs.mkShellNoCC {
      packages = with pkgs; [
        opencv
        ffmpeg
      ];
    };
  };
}
