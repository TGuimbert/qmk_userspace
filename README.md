# QMK Userspace — Miryoku on Ferris Sweep

[Miryoku](https://github.com/manna-harbour/miryoku) layout for the [Ferris Sweep](https://github.com/davidphilipbarr/Sweep) split keyboard, running on the [Blok](https://boardsource.xyz/products/blok-rp2040-keyboard-controller) (RP2040) controller.

## Hardware

- **Keyboard:** Ferris Sweep — 34-key (3×5 + 2 thumbs) wireless-ready split
- **Controller:** Blok (RP2040), one per half

## Layout

[Miryoku](https://github.com/manna-harbour/miryoku) is a 34-key layout built around 10 layers: base alpha, navigation, mouse, media, numbers, symbols, function keys, and more. Layers are accessed via the six thumb keys using hold-tap (home row mods + thumb holds).

See the [Miryoku reference card](https://github.com/manna-harbour/miryoku/tree/master/docs/reference) for the full layer map.

## Prerequisites

Enter the Nix devshell — it installs QMK, the ARM toolchain, and flashing tools, and automatically configures `qmk_home` and the userspace path:

```sh
nix develop
```

The devshell also initializes the `qmk_firmware` submodule on first run if it is not already present.

## Flashing

> **Why these specific commands?**
> This firmware uses `EE_HANDS` to detect which half is left and which is right. Unlike other handedness methods, `EE_HANDS` stores the side in each half's EEPROM. This information is written during flashing via the `-bl uf2-split-left` / `-bl uf2-split-right` bootloader flag. Dragging and dropping a `.uf2` file directly skips this step and leaves both halves with no handedness configured.

### Step 1 — Enter bootloader mode

Double-click the reset button on the half you want to flash. The half will appear as a USB mass-storage device (e.g. `RPI-RP2`).

### Step 2 — Flash

Flash each half separately. Run the appropriate command below, then repeat for the other half.

**Left half:**
```sh
qmk flash -kb ferris/sweep -km miryoku -e CONVERT_TO=blok -bl uf2-split-left
```

**Right half:**
```sh
qmk flash -kb ferris/sweep -km miryoku -e CONVERT_TO=blok -bl uf2-split-right
```

Both halves must be flashed at least once so that their EEPROM contains the correct side information. After that, only reflash both halves when updating firmware.

## Building (optional)

To compile without flashing — useful to verify the firmware builds cleanly:

```sh
qmk userspace-compile
```
