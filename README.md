## ⌨ Typing Trainer

A terminal-based typing practice program written in C. Built for Linux systems with clean ANSI output and precise typing statistics.
The program focuses on speed, accuracy, and a distraction-free typing flow.

---

## ✨ Features

- Written fully in standard C
- Runs on Linux and Termux environments
- Supports true-color ANSI rendering (RGB)
- Custom text color and background color support
- Word-aware line splitting without breaking words
- Terminal width aware with auto-detection or manual config
- Accurate typing statistics including WPM, accuracy, and time
- Optional case-sensitive or case-insensitive typing mode
- Smart text normalization that removes unsupported or non-ASCII characters
- Safe exit handling with proper cleanup 

---

## 🛠️ Install / Build

Requirements:
- `gcc` compiler 
- POSIX-compatible system (Linux / Termux)

Clone or download the repository:
```sh
git clone https://github.com/code5x/typing_trainer.git
```

Move into the project directory:
```sh
cd typing_trainer
```

Build the program using make:
```sh
make
```

---

## 🚀 Run

```sh
./typing
```

The program will prompt:
> Enter the text file name: 

Example inputs:
`src2/demo1.txt`
or
`/home/username/Downloads/text_file.txt`

---

## ⚙️ Configuration

All configuration options are available inside `include/config.h`
```text
Case sensitivity options  
Terminal width handling  
RGB text colors  
Background color setup  
Automatic terminal width detection
```

---

## 🖼️ Example (Screenshots)

![Demo Screenshot 1](https://github.com/code5x/typing_trainer/blob/main/images/screenshot_001.jpg)
![Demo Screenshot 2](https://github.com/code5x/typing_trainer/blob/main/images/screenshot_002.jpg)

---

## 📝 Notes

Typing results and statistics appear after completion or safe Ctrl+C exit.
Demo text files are included and custom text files are supported.
Text lines are split to fit terminal width, not auto-wrapped.
Words are never split across lines.
Don't change terminal size when typing in progress.
Ctrl+C exits cleanly and safely.
