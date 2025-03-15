# Debug Logger with ANSI Colors and Precise Timing

This project provides a **lightweight debug logging library** for C applications, featuring:

- **Color-coded log levels** with ANSI escape sequences.
- **High-resolution timing** for precise debugging.
- **Cross-platform support** for Windows (≥ 10), Linux, and macOS.
- **Flexible formatting**, including multiline and aligned log messages.
- **Future-proof design** for easy customization and enhancements.

## Table of Contents
- [Installation](#installation)
- [Compilation](#compilation)
- [Usage](#usage)
- [Log Output Format](#log-output-format)
- [Project Structure](#project-structure)
- [Customization](#customization)
- [Future Improvements](#future-improvements)

## Installation

Clone the repository:

```sh
git clone https://github.com/ljgonzalez1/C-debug-prints
cd C-debug-prints
```

## Compilation

Compile the example using the provided `Makefile`:

This generates a binary named `test_debug_binary` in the root directory.

Run the example:
```bash
./test_debug_binary
```

Clean the compiled files:
```bash
make clean
```

## Usage

### Initialization

Initialize debug functionality at the start of your `main` function:

```h
#include "debug/debug.h"

int main(void) {
    init_debug();
    // ... your code
}
```

### Logging Messages

Use the message function to print logs with specific severity levels:

```c
message(DEBUG_INFO, "This is an informational message", "Optional detail");
message(DEBUG_WARN, "This is a warning", "Additional context");
message(DEBUG_ERROR, "An error occurred", "Detailed description");
```

Time: Elapsed since program start, shown with exactly 6 decimal places.

Log Level: Types are formatted uniformly:

- `DEBUG:` (cyan)
- `INFO :` (green)
- `WARN :` (yellow)
- `ERR  :` (red)
- `FATAL:` (magenta)

Messages with details show additional lines aligned precisely under the main message, with details printed in italics.

## Code Structure

```
C-debug-prints
├── LICENSE
├── Makefile
├── README.md
└── src
    ├── debug
    │   ├── colors.h     # ANSI colors and formatting
    │   ├── debug.c      # Core debugging functionality
    │   ├── debug.h      # Debugging interface
    │   ├── printer.c    # Printing logic
    │   ├── printer.h    # Print-related declarations
    │   ├── timer.c      # Cross-platform high-resolution timer
    │   └── timer.h      # Timer interface
    └── main.c           # Example usage
```

## Customization

### Changing Colors

Modify ANSI definitions in `src/debug/colors.h`:

```h
#define ANSI_FG_RED       "\033[31m"
#define ANSI_FG_GREEN     "\033[32m"
#define ANSI_FG_YELLOW    "\033[33m"
#define ANSI_FG_BLUE      "\033[34m"
#define ANSI_FG_MAGENTA  "\033[35m"
#define ANSI_FG_CYAN     "\033[36m"
#define ANSI_FG_WHITE    "\033[37m"
```

### Adjusting Formatting

Customize the alignment, spacing, and formatting in `src/debug/printer.c`. The function `print_debug` manages log formatting, including prefixes and alignment.

## Future Improvements

- Configurable log levels at runtime.
- Output logs to file or streams.
- ~~Thread-safe implementation for multithreaded programs.~~
- Optional configuration via environment variables or external config files.

## License

This project is licensed under the MIT License. See [LICENSE](./LICENSE) for details.
