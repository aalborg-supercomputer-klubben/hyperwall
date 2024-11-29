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
      packages = let
          opencvGtk = pkgs.opencv.override (old : { enableGtk2 = true; });
      in with pkgs; [
        opencvGtk
        ffmpeg
        cmake
        spdlog
        argparse
        catch2_3
      ];
    };
  };
}
