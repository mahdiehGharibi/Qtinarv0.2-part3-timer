# QtinarOS v0.2 — Timer + Keyboard Interrupts

QtinarOS v0.2 is a small educational 32‑bit operating system built from scratch. This version introduces hardware interrupt handling, a working PIT timer, and a functional keyboard driver. It runs in protected mode, uses a custom GDT and IDT, and boots via GRUB.

This project is part of a learning journey into low‑level OS development, focusing on clarity, correctness, and clean modular design.



## ✨ What’s implemented in v0.2 (part 3)

- Protected Mode Kernel  
- Global Descriptor Table (GDT)  
- Interrupt Descriptor Table (IDT)  
- CPU exception handlers (ISR 0–31)  
- Hardware IRQ handling (IRQ 0–15)  
- PIC remapping (0x20–0x2F)  
- PIT timer driver (IRQ0)  
- Keyboard driver (IRQ1)  
- Basic input system  
- VGA text‑mode screen driver  
- Simple shell prompt  

This version focuses on interrupt correctness and stable hardware input.



## 📁 Project Structure
```
src/
├── cpu/        # GDT, IDT, ISR, IRQ, PIC, ports, timer
├── drivers/    # screen, keyboard, integer printing
├── kernel/     # kernel_main, input system, commands
└── libc/       # minimal string & memory utilities
```



## 🚀 Running QtinarOS

QtinarOS boots using GRUB and runs in QEMU.

After building the kernel and ISO (using your local build scripts or Makefile), run:

```
qemu-system-i386 -cdrom os.iso
```
You will see:

- A boot banner

- A shell prompt

- Working keyboard input

- Timer interrupts running in the background

## 🧠 Learning Goals of This Version
v0.2 is designed to teach:

- How hardware interrupts work

- How to remap the PIC

- How to write interrupt stubs in assembly

- How to build a minimal IDT

- How to handle keyboard scancodes

- How to structure a small kernel cleanly

This version is intentionally simple and readable.


