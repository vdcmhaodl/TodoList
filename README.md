# ToDoList GUI Application

A modern, feature-rich to-do list application built with Qt 6.9.1 and C++17. Manage your daily tasks and one-time tasks with an intuitive graphical interface.

## Features

- ✅ **Add Tasks**: Create one-time or daily recurring tasks
- 📅 **Date Picker**: Select task due dates with an interactive calendar
- ✔️ **Mark Done**: Mark tasks as complete with a single click
- 🗑️ **Delete Tasks**: Remove tasks from your list
- 💾 **Auto-save**: Tasks are automatically saved to a file
- 📊 **Task View**: Display tasks in a table with columns for name, date, type, and status
- 🔄 **Daily Tasks**: Automatically refresh daily tasks each day
- 📱 **Responsive UI**: User-friendly interface with proper spacing and text wrapping

## System Requirements

### macOS & Linux
- **Qt 6.9.1** or later
- **CMake 3.16** or later
- **C++ compiler** (supporting C++17):
  - macOS: Xcode (Apple Clang)
  - Linux: GCC 7+ or Clang 5+

### Windows
- **Qt 6.9.1** or later
- **CMake 3.16** or later
- **Visual Studio 2019** or later with C++17 support
- **MSVC compiler**

## Installation

### macOS

1. **Install Xcode Command Line Tools**
   ```bash
   xcode-select --install
   ```

2. **Install Qt 6.9.1** (using Homebrew)
   ```bash
   brew install qt@6
   ```

3. **Install CMake**
   ```bash
   brew install cmake
   ```

### Linux (Ubuntu/Debian)

1. **Install Dependencies**
   ```bash
   sudo apt-get update
   sudo apt-get install build-essential cmake qt6-base-dev qt6-tools-dev
   ```

2. **Alternatively, install Qt from qt.io** if the package version doesn't match 6.9.1

### Windows

1. **Download and install Visual Studio 2019 or later** with C++ development tools
2. **Download Qt 6.9.1** from [qt.io](https://www.qt.io/download)
3. **Install CMake** from [cmake.org](https://cmake.org/download/)

## Building the Project

### macOS & Linux

1. **Navigate to the project directory**
   ```bash
   cd /path/to/First\ Project
   ```

2. **Create and enter build directory**
   ```bash
   cd ToDoListGUI
   mkdir -p build
   cd build
   ```

3. **Configure with CMake**
   ```bash
   cmake ..
   ```

4. **Build the project**
   ```bash
   cmake --build .
   ```

### Windows (Command Prompt)

1. **Navigate to the project directory**
   ```cmd
   cd \path\to\First Project\ToDoListGUI
   mkdir build
   cd build
   ```

2. **Configure with CMake**
   ```cmd
   cmake .. -G "Visual Studio 16 2019"
   ```

3. **Build the project**
   ```cmd
   cmake --build . --config Release
   ```

## Running the Application

### macOS

```bash
open build/ToDoListGUI.app
```

Or from the build directory:
```bash
./build/ToDoListGUI.app/Contents/MacOS/ToDoListGUI
```

### Linux

```bash
./build/ToDoListGUI
```

### Windows

```cmd
build\Release\ToDoListGUI.exe
```

## Usage

### Adding a Task

1. Enter the task name in the **"Enter Task Name"** field
2. Select task type from the dropdown:
   - **One-time Task**: Single task with a specific due date
   - **Daily Task**: Recurring task (date is set to today automatically)
3. If "One-time Task" is selected, choose a due date using the calendar picker
4. Click **"+ ADD TASK"** button

### Managing Tasks

- **View Tasks**: All tasks are displayed in the table with columns for Task, Due Date, Type, and Status
- **Mark as Done**: Select a task and click **"Mark Done ✅"** button
- **Delete Task**: Select a task and click **"Delete Task 🗑️"** button

### Task Status Indicators

- 🔄 **Pending**: Task not yet completed
- ✅ **Done**: Task marked as complete
- ⚠️ **Overdue**: Task due date has passed
- 📋 **Daily**: Recurring daily task (resets each day if marked done)

## File Structure

```
First Project/
├── add_Task.h / add_Task.cpp          # Task class definitions
├── handle_date.h / handle_date.cpp    # Date handling utilities
├── logic.h / logic.cpp                # Platform/task management logic
├── main.cpp                            # Main entry point
├── tasks.txt                           # Task data storage
├── README.md                           # This file
└── ToDoListGUI/
    ├── CMakeLists.txt                 # Build configuration
    ├── main.cpp                        # Qt application entry
    ├── mainwindow.h / mainwindow.cpp   # Main window logic
    ├── mainwindow.ui                   # UI definition
    ├── build/                          # Build output directory
    └── ToDoListGUI.app                 # macOS application bundle
```

## Data Storage

Tasks are stored in `tasks.txt` file in the project root directory. The file format is:

```
<number_of_tasks>
<task_type>|<date>|<is_done>|<task_name>
...
```

Example:
```
2
daily|13/12/2025|1|punch nlk
onetime|14/12/2025|0|drink coca
```

## Troubleshooting

### Build Errors

**CMake not found**
- Ensure CMake is installed and added to PATH
- On macOS: `brew install cmake`
- On Linux: `sudo apt-get install cmake`
- On Windows: Download from cmake.org

**Qt not found**
- Ensure Qt 6.9.1 is installed
- Set `Qt6_DIR` environment variable if CMake cannot find Qt:
  ```bash
  export Qt6_DIR=/path/to/Qt/6.9.1/lib/cmake/Qt6
  ```

**Compiler errors**
- Ensure C++17 is supported
- Update your compiler to the latest version

### Runtime Errors

**Tasks not saving**
- Ensure the application has write permissions to the project directory
- Check that `tasks.txt` file is not write-protected

**Tasks not loading**
- Verify `tasks.txt` exists in the project root directory
- Check file formatting is correct

## Development

### Requirements for Development
- Qt Creator IDE (optional but recommended)
- Git for version control

### Opening in Qt Creator

1. Launch Qt Creator
2. Go to **File → Open File or Project**
3. Select `ToDoListGUI/CMakeLists.txt`
4. Click **Configure Project**
5. Build with **Ctrl+B** (Cmd+B on macOS)
6. Run with **Ctrl+R** (Cmd+R on macOS)

## License

This project is provided as-is for educational purposes.

## Contributing

Contributions are welcome! Feel free to fork the repository and submit pull requests.

## Support

For issues or questions, please check the troubleshooting section or create an issue in the repository.

---

**Last Updated**: December 17, 2025
**Version**: 1.0.0
**Built with**: Qt 6.9.1, C++17, CMake 3.16+
