# Casio QR Maker

A standalone QR code generator for the Casio fx-9750GIII (SH4).

It runs entirely on the calculator.  
No external libraries, no extra files — just a single add-in.

---

## Preview

<p align="center">
  <img src="https://github.com/user-attachments/assets/ae605996-9e54-4493-8e2b-5e389759bb43" width="500" />
</p>

<p align="center">
  <em>App Icon</em>
</p>

<br>

<p align="center">
  <img src="https://github.com/user-attachments/assets/4d115c51-bff3-4376-ab51-8e3fb1237305" width="450" />
  <img src="https://github.com/user-attachments/assets/6fe4fcaa-617b-4b2c-ac0d-06393ec75f07" width="450" />
</p>

<p align="center">
  <em>Main Menu & Text Input</em>
</p>

<br>

<p align="center">
  <img src="https://github.com/user-attachments/assets/5acfe5bf-22e9-45ae-926a-d3aa5c56cbba" width="500" />
</p>

<p align="center">
  <em>Generated QR Code</em>
</p>

---

## What it does

- Generates QR codes directly on the calculator
- Built-in text editor with auto line wrap
- Case toggle (F1)
- Quick URL symbol cycling (F2)
- Fully offline QR encoding (embedded C implementation)

The default input length is currently set to 60 characters.
You can increase it by modifying the buffer size in the source.

---

## Installation

1. Connect the calculator to your computer via USB.
2. On the calculator, press F1 to enter USB mode.
3. It will appear as a removable drive.
4. Drag `QRCode.G1A` into the root directory.
5. Safely eject.

---

## Build

Open `QRCode.g1w` in the official Casio fx-9860G SDK and click **Build All**.

---

## Project Structure

- `main.c` — UI, input handling, rendering
- `qrcodegen.c` — QR encoding core
- `qrcodegen.h` — encoder interface

---

## License

MIT License.

QR encoding implementation is based on Project Nayuki's QR Code generator.


---

## 中文说明

这是一个运行在 fx-9750GIII (SH4) 上的离线二维码生成器。

特点：
- 完全本机运行
- 内置二维码算法
- 支持大小写切换
- 支持常用 URL 符号快捷输入
- 默认长度 60 字符（可自行修改）

通过 USB 连接，按 F1 进入传输模式，将 .G1A 文件直接拖入根目录即可安装。
