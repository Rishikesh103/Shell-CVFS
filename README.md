# Shell CVFS: A Custom Virtual File System in C++

A C++ simulation of an in-memory, inode-based virtual file system with an interactive command-line shell. This educational project demonstrates the core concepts of file system management found in operating systems.

---

## ✨ Key Features

* **💻 In-Memory Storage**: All file data and metadata are stored in RAM for extremely fast operations.
* **📂 Inode-Based Management**: Each file is represented by an inode that stores its metadata (name, size, permissions, etc.), mimicking file systems like ext4.
* **셸 Interactive Shell**: A user-friendly command-line interface to interact with the virtual file system.
* **⚙️ Core File Operations**: Supports essential file operations like `creat`, `write`, `read`, and `unlink`.
* **📊 File System Utilities**: Includes standard utility commands such as `ls` to list files and `stat` to display file statistics.
* **❓ User Assistance**: Comes with a `help` command for a quick overview and a `man` command for detailed command manuals.

---

## 🚀 Getting Started

Follow these instructions to download, compile, and run the project on your local machine.

### Prerequisites

You will need a **C++ compiler** (like G++) and **Git** installed on your system.

### Installation & Execution

1.  **Clone the Repository**:
    Open your terminal or command prompt and clone this repository using the following command:
    ```sh
    git clone [https://github.com/Rishikesh103/Shell-CVFS.git](https://github.com/Rishikesh103/Shell-CVFS.git)
    ```

2.  **Navigate to the Directory**:
    Change your current directory to the newly cloned project folder:
    ```sh
    cd Shell-CVFS
    ```

3.  **Compile the Program**:
    Compile the C++ source code into an executable file named `cvfs_shell`:
    ```sh
    g++ "Shell CVFS_Source_Code.cpp" -o cvfs_shell
    ```

4.  **Run the Shell**:
    Execute the compiled program to start the virtual file system shell:
    ```sh
    ./cvfs_shell
    ```
    You will be greeted with the `Shell CVFS >` prompt, ready to accept commands.

---

## 💻 Available Commands

| Command | Syntax | Description |
| :--- | :--- | :--- |
| `creat` | `creat <filename> <permission>` | Creates a new file. Permission: `1` (Read), `2` (Write), `3` (Read+Write). |
| `write` | `write <fd>` | Writes data to an open file, identified by its file descriptor (fd). |
| `read` | `read <fd> <bytes>` | Reads a specified number of bytes from an open file. |
| `ls` | `ls` | Lists all the files currently in the file system. |
| `stat` | `stat <filename>` | Displays detailed metadata for a file. |
| `unlink` | `unlink <filename>` | Deletes a file from the file system. |
| `man` | `man <command>` | Displays the manual page with details about a specific command. |
| `help` | `help` | Shows a quick list of all available commands. |
| `clear` | `clear` | Clears the terminal screen. |
| `exit` | `exit` | Terminates the shell and deallocates all in-memory resources. |

---

## 🚀 Example Usage

Here is a sample session demonstrating the workflow within the Shell CVFS:

```
Shell CVFS > creat my_note.txt 3
current inode remaining : 5
file is successfully created with FD : 0

Shell CVFS > write 0
Please enter the data that you want to write into the file
Hello Virtual File System!
18 bytes is successfully written into the file

Shell CVFS > ls
my_note.txt

Shell CVFS > stat my_note.txt
----------- Statistical Information of file ------------
file name : my_note.txt
file size is on disk : 100
actual file size : 18
Link Count : 1
file permission : 3
file type : regular file
--------------------------------------------------------

Shell CVFS > read 0 10
Read operation is successful
Data from file is : Hello Virt

Shell CVFS > unlink my_note.txt
Unlink operation is successfuly performed

Shell CVFS > exit
Thankyou for using Shell CVFS
Deallocating all resources....
```
