{
  description = "QMK userspace devshell for Ferris Sweep (Blok/RP2040)";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
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
        pkgs = nixpkgs.legacyPackages.${system};
      in
      {
        devShells.default = pkgs.mkShell {
          name = "qmk-ferris-sweep";

          packages = [
            # QMK CLI (pulls in Python + qmk dependencies)
            pkgs.qmk

            # ARM cross-compiler — required for RP2040/Blok firmware build
            pkgs.gcc-arm-embedded

            # RP2040 flashing tool (reads/writes UF2 over USB)
            pkgs.picotool

            # General USB DFU flashing (covers non-RP2040 QMK boards too)
            pkgs.dfu-util

            # Build essentials used by QMK's Makefile
            pkgs.gnumake
            pkgs.git
          ];

          shellHook = ''
            export QMK_USERSPACE="$(pwd)"
            export QMK_HOME="$QMK_USERSPACE/qmk_firmware"

            if [ ! -f "$QMK_HOME/Makefile" ]; then
              echo "Initializing qmk_firmware submodule..."
              git submodule update --init --recursive qmk_firmware
            fi

            qmk config user.qmk_home="$QMK_HOME" > /dev/null

            echo "QMK devshell ready."
            echo "  Userspace : $QMK_USERSPACE"
            echo "  Firmware  : $QMK_HOME"
            echo ""
            echo "Build & flash:"
            echo "  qmk userspace-compile"
            echo "  qmk flash -kb ferris/sweep -km miryoku -e CONVERT_TO=blok -bl uf2-split-left"
            echo "  qmk flash -kb ferris/sweep -km miryoku -e CONVERT_TO=blok -bl uf2-split-right"
          '';
        };
      }
    );
}
