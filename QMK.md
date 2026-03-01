# QMK Firmware Setup & Flashing Guide

> Setting up the QMK environment on Pop!\_OS 24.04 and compiling/flashing custom firmware for two Keebio Iris split keyboards — the **Rev. 7** and the **CE Rev. 1**.

---

## Table of Contents

1. [Environment Setup](#environment-setup)
2. [Installing QMK via uv](#installing-qmk-via-uv)
3. [Resolving Install Errors](#resolving-install-errors)
4. [Generating Keymaps](#generating-keymaps)
5. [Compiling Firmware](#compiling-firmware)
6. [Flashing Firmware](#flashing-firmware)

---

## Environment Setup

### A Note on System Safety

Installing QMK globally on Linux can be risky. The typical approach uses `pip` or `pipx`, but this risks overwriting system-managed Python libraries (used by `apt`, `gnome-terminal`, etc.) and potentially breaking the OS. Python's **PEP 668** addresses this by placing an `EXTERNALLY-MANAGED` marker in the system Python directory to prevent accidental overwrites.

To avoid this entirely, I use **[uv](https://github.com/astral-sh/uv)** for all Python project and package management. `uv` creates isolated environments automatically, keeping the system Python completely untouched.

---

## Installing QMK via uv

Install `qmk` as a tool. `uv` will create a dedicated isolated environment, install the QMK package, and add the `qmk` command to your `PATH`.

```bash
uv tool install qmk
```

On first run, `qmk` will clone the firmware repository and run its environment check (`qmk doctor`). On a fresh install, expect two categories of problems:

```
⚠ Missing or outdated udev rules for 'atmel-dfu' boards.
⚠ Missing or outdated udev rules for 'caterina' boards.
⚠ Detected ModemManager without the necessary udev rules.
  ... (repeated for multiple board types)

☒ Can't find arm-none-eabi-gcc in your path.
☒ Can't find avr-gcc in your path.
☒ Can't find avrdude in your path.
☒ Can't find dfu-programmer in your path.
☒ Can't find dfu-util in your path.
☒ Can't find dos2unix in your path.

Ψ Major problems detected, please fix these problems before proceeding.
```

These break down into **missing udev rules** (the OS can't talk to the keyboard over USB) and **missing compilers/tools** (the firmware can't be built or flashed). Both are resolved below.

---

## Resolving Install Errors

### 1. Fix udev Rules

Copy the rules file and reload:

```bash
sudo cp /home/aexx/qmk_firmware/util/udev/50-qmk.rules /etc/udev/rules.d/
sudo udevadm control --reload-rules && sudo udevadm trigger
```

### 2. Install Missing Compilers & Tools

Install the entire toolchain in one go:

```bash
sudo nala install git git-lfs diffutils gcc g++ unzip wget zip \
    binutils-avr avr-libc avrdude dfu-programmer dfu-util \
    gcc-arm-none-eabi binutils-arm-none-eabi libnewlib-arm-none-eabi dos2unix
```

### 3. Verify the Environment

Run the doctor check again:

```bash
qmk doctor
```

All tests should now pass with the message: **`Ψ QMK is ready to go`**

---

## Generating Keymaps

The keymaps for both Iris boards are identical from a layout perspective, with minor differences in `rules.mk` due to underlying hardware differences.

All source code lives in the **[icelandic-keebio-iris-qmk](https://github.com/AegirAexx/icelandic-keebio-iris-qmk)** repository on GitHub. Clone or fork it and modify to your specifications.

### Keymap Directory Structure

When using the QMK CLI, keymaps must be placed under specific paths relative to `~/qmk_firmware/keyboards/keebio/`.

**Iris Rev. 7** — `iris/keymaps/aexx_iris_rev7/`

```
iris/keymaps/aexx_iris_rev7/
├── config.h
├── keymap.c
├── keymap_icelandic.h
└── rules.mk
```

**Iris CE Rev. 1** — `iris_ce/keymaps/aexx_iris_ce/`

```
iris_ce/keymaps/aexx_iris_ce/
├── config.h
├── keymap.c
├── keymap_icelandic.h
└── rules.mk
```

---

## Compiling Firmware

```bash
# Iris Rev. 7
qmk compile -kb keebio/iris/rev7 -km aexx_iris_rev7

# Iris CE Rev. 1
qmk compile -kb keebio/iris_ce/rev1 -km aexx_iris_ce
```

Compiled binaries are output to the root of the QMK directory (`~/qmk_firmware/`).

| Board | Output File |
|---|---|
| Iris Rev. 7 | `keebio_iris_rev7_aexx_iris_rev7.hex` |
| Iris CE Rev. 1 | `keebio_iris_ce_rev1_aexx_iris_ce.uf2` |

---

## Flashing Firmware

### Iris Rev. 7 (`.hex` — command-line flash)

The Rev. 7 uses older hardware and must be flashed via the CLI:

```bash
qmk flash -kb keebio/iris/rev7 -km aexx_iris_rev7
```

The CLI will prompt you to put the keyboard half into **boot mode**, then flash automatically. Repeat for the other half.

### Iris CE Rev. 1 (`.uf2` — drag-and-drop flash)

The CE has newer hardware with a simpler flash process:

1. Connect one half of the keyboard via USB.
2. Put it into **boot mode** — it will appear as a removable drive.
3. Copy the `.uf2` file to the drive.
4. The drive will disappear, indicating a successful flash.
5. Repeat for the other half.
