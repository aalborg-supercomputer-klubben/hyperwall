{
    description = "Hyperwall ASCK";

    inputs = {
        nixpkgs.url = "nixpkgs/nixos-unstable";
    };

    outputs = { self, nixpkgs }: {
        devShells = builtins.mapAttrs (system: _: let
            pkgs = import nixpkgs { inherit system; };
        in {
            default = pkgs.mkShellNoCC {
                packages = let
                    opencvGtk = pkgs.opencv.override (old: { enableGtk2 = true; });
                in with pkgs; [
                    opencvGtk
                    ffmpeg
                    cmake
                    spdlog
                    argparse
                    catch2_3
                ];
            };
        }) {
            "x86_64-linux" = {};
            "aarch64-linux" = {};
        };
    };
}
