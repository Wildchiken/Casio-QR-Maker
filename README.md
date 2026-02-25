# Casio QR Maker

A standalone QR code generator for the Casio fx-9750GIII (SH4).

Single add-in.  
Runs entirely on-device.  
QR encoder embedded.

---

## Preview

<p align="center">
  <img src="https://github.com/user-attachments/assets/ae605996-9e54-4493-8e2b-5e389759bb43" width="480" />
</p>
<p align="center"><sub>Icon</sub></p>

<p align="center">
  <img src="https://github.com/user-attachments/assets/4d115c51-bff3-4376-ab51-8e3fb1237305" width="430" />
  <img src="https://github.com/user-attachments/assets/6fe4fcaa-617b-4b2c-ac0d-06393ec75f07" width="430" />
</p>
<p align="center"><sub>Main menu / Text input</sub></p>

<p align="center">
  <img src="https://github.com/user-attachments/assets/5acfe5bf-22e9-45ae-926a-d3aa5c56cbba" width="480" />
</p>
<p align="center"><sub>QR output</sub></p>

---

## Functionality

- Generate QR codes directly on the calculator
- Built-in text input with auto line wrap
- F1 — case toggle
- F2 — URL-friendly symbol cycling
- Embedded QR encoder (`qrcodegen`)

Default input length: 60 characters (adjustable in source).

---

## Installation

1. Connect the calculator via USB  
2. Press F1 on the calculator to enter USB mode  
3. Drag `QRCode.G1A` into the root directory  
4. Safely eject  

---

## Build

Open `QRCode.g1w` in the official fx-9860G SDK and select **Build All**.

---

## Source Layout

- `main.c` — UI, input handling, rendering  
- `qrcodegen.c` — QR encoding implementation  
- `qrcodegen.h` — encoder interface  

---

## License

MIT License.

QR encoding is based on Project Nayuki’s implementation.

---

## 中文说明

这是一个运行在 fx-9750GIII（SH4）上的离线二维码生成器（Add-in）。

特点：
- 完全本机运行
- 内置二维码编码器
- 支持大小写切换与常用符号输入
- 默认长度 60（可在源码中修改）

安装方式：USB 连接 → 计算器按 F1 → 拖入 `QRCode.G1A` → 弹出即可。
