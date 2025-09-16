# Customised Virtual File System (CVFS)

##  Project Overview

**CVFS** is a custom implementation of a **Virtual File System (VFS)** built entirely in **C**. It simulates the core functionalities of the **Linux File System**, featuring its own **custom shell** for interaction.

This project is designed to provide a practical and deep understanding of:
- System calls
- File handling
- Memory management
- Operating system internals

---

##  Key Features

- ###  Custom Shell Interface
  - Linux-like commands for file operations:
    - `create`, `open`, `read`, `write`, `close`, `delete`, `ls`, etc.

- ###  System Call Simulation
  - Implements core Linux system calls (`open`, `read`, `write`, `lseek`, `close`, `rm`, etc.) using C.

- ###  File System Data Structures
  - **Incore Inode Table**
  - **File Table**
  - **UAREA (User Area)**
  - **User File Descriptor Table**

- ###  Platform Independent
  - Simulates Linux-level file handling on **any OS platform**.

- ###  Database-like Functionality
  - Structured file handling through a **customized database management layer**.

---

##  Learning Outcomes

- Deep understanding of **Linux File System internals**.
- Practical experience with **data structures** used in OS (inode, file tables, UAREA).
- Solid foundation in **systems programming in C**.
- Hands-on knowledge of **shell design** and **command interpretation**.
- Development of **low-level logic building** skills.

---

##  Example Usage

```bash
$ ./Myexe

Marvellous CVFS> create Demo.txt
Marvellous CVFS> write Demo.txt "Jay Ganesh"
Marvellous CVFS> read Demo.txt
Jay Ganesh
Marvellous CVFS> ls
Demo.txt
Marvellous CVFS> rm Demo.txt
Marvellous CVFS> exit
