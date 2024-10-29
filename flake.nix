{
    description = "A very basic flake";
    inputs = {
        nixpkgs.url = "nixpkgs/nixos-24.05";
    };
    outputs = { self, nixpkgs }: let
        system = "x86_64-linux";
        pkgs = import nixpkgs {inherit system;};
    in {
        devShells.${system}.default = pkgs.mkShellNoCC {
            packages = with pkgs; [
                mediamtx
            ];
        };

        packages.${system}.vm = (nixpkgs.lib.nixosSystem {
            inherit system;
            modules = [(
                {pkgs, lib, config, ...}:

                {
                    system.stateVersion = "24.05";
                    users.users.root.password = "1234";
                    virtualisation.vmVariant = {
                        virtualisation.graphics = false;
                        virtualisation.forwardPorts = (map (port: {
                            from = "host";
                            host.port = port;
                            guest.port = port;
                        }) [8554 2222]);
                    };
                    services.getty.autologinUser = "root";
                    networking.firewall.enable = false;
                    services.openssh.enable = true;
                    services.openssh.ports = [2222];
                    services.openssh.settings.PermitRootLogin = "yes";
                    services.mediamtx = {
                        enable = true;
                        settings = {
                            paths.all_others = {
                            };
                        };
                    };
                    environment.variables = {
                        RTSP_PORT = 8554;
                    };
                }
            )];
        }).config.system.build.vm;
    };
}
