# Task Finder

**Description:**

Task Finder is a command-line program designed to perform various tasks concurrently based on user input. It allows users to execute tasks such as writing to files, creating files, generating sound alerts, and displaying messages.


**Features:**

- **Concurrent Task Execution:** Task Finder can execute multiple tasks simultaneously, each in its own child process.
  
- **Task Types:** Supports the following types of tasks:
  - Writing content to a file
  - Creating a new file
  - Generating a continuous sound alert
  - Displaying a message

---

**Compilation:**

To compile the program, use the following command:

```bash
gcc task_handler.c -o task_finder
```

This command compiles `task_handler.c` and creates an executable named `task_finder`.

---

**Usage:**

Run the compiled program `task_finder` with the following command format:

```bash
./task_finder <task1> [arguments1] <task2> [arguments2] ...
```

Replace `<task>` with one of the following:
- `write`: To write content to a file.
- `create`: To create a new file.
- `alert`: To generate a continuous sound alert for the specified duration.
- `display`: To display a message on the console.

Provide appropriate `[arguments]` based on the selected task.

---

**Example Usage:**

- To write content to a file:

```bash
./task_finder write filename.txt "Hello, world!"
```

- To create a new file:

```bash
./task_finder create newfile.txt
```

- To generate a continuous sound alert for 5 seconds:

```bash
./task_finder alert 5
```

- To display a message:

```bash
./task_finder display "This is a sample message."
```

---

**Error Handling:**

The program checks for insufficient arguments and provides usage instructions for each task. It also handles errors in file operations and system calls using appropriate error messages.

---

**Conclusion:**

Task Finder provides a simple and efficient way to perform various tasks concurrently from the command line. Whether it's writing to files, creating files, generating alerts, or displaying messages, Task Finder offers flexibility and ease of use.

---
