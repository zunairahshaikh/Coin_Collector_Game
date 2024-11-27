# Semester Project 💻

A graphical grid game built in C using MSVC compiler. The game displays a grid with a player, coins, and obstacles, allowing for interactive gameplay directly in the Windows Terminal.

## Contributors:

- Zunairah Aziz Shaikh (24k-0986) -Team Lead

- Laiba Khan (24k-0644)

- Abeeha Binte Aamer (24k-0940)

- Aamna Rizwan (24k-0695)

## Requirements

1. **Windows Terminal**  
   Install from the Microsoft Store:  
   [Windows Terminal](https://apps.microsoft.com/detail/9n0dx20hk701?hl=en-US&gl=US)

2. **MSVC Compiler (Microsoft C/C++ Compiler)**  
   You need the MSVC compiler to build and run the game. There are two options for setting it up:  
   - **Option 1**: Install **Build Tools for Visual Studio Code**:  
     [Download Build Tools](https://visualstudio.microsoft.com/downloads/#remote-tools-for-visual-studio-2022)
   - **Option 2**: Download and install **Visual Studio for C++ developers**:  
     [Visual Studio for C++ Developers](https://visualstudio.microsoft.com/vs/)
     
---

## Setup Instructions

### 1. Install MSVC and Setup Developer Environment
- Follow the instructions on this page to ensure that the compiler and command prompt are installed properly
  [Visual Studio Code - MSVC onfiguration](https://code.visualstudio.com/docs/cpp/config-msvc)
  

### 2. Open Developer Command Prompt for Visual Studio
1. Open the **Windows Terminal**.
2. Select the **Developer Command Prompt for VS** profile (it’s automatically available if MSVC is installed).
   - Alternatively, search for "Developer Command Prompt for VS" in the Windows Start menu and open it in the Windows Terminal.

### 3. Navigate to the Project Directory
Move to the directory where your project files are located by using the `cd` command in the Developer Command Prompt.

For example:
```bash
cd path\to\your\project
```

---

## Build and Run Instructions

Run the following commands one by one in the **Developer Command Prompt for VS**:

1. Compile the source file:
   ```bash
   cl /utf-8 main.c
   ```
   This generates the `main.exe` executable file.

2. Change the terminal code page to UTF-8 to support emojis:
   ```bash
   chcp 65001
   ```

3. Run the game:
   ```bash
   main.exe
   ```

---

## Gameplay Controls
- Use **W for up, A for left, S for down, and D for right** to move.
- Press **Q** to quit the game.
- You 🦊 have 30 seconds and three lives to collect as many coins 🟡 as you can while avoiding the obstacles 🔺.
- Once the time is over or you lose all lives, the game ends.

---

## Game Preview
![image](https://github.com/user-attachments/assets/b5b0302a-c12c-4e8e-a1f2-d93e67360d00)

---

## Troubleshooting

1. **Command Not Found Error**:  
   Ensure you are running the commands in the **Developer Command Prompt for VS**.

2. **MSVC Not Installed**:  
   Reinstall the Visual Studio Build Tools or Desktop Development for C++ Developers.

3. **Icons/Emojis Not Displayed Correctly**:  
   Ensure you changed the code page to UTF-8 using `chcp 65001` before running the game.

Hope you enjoy the game! 😊
