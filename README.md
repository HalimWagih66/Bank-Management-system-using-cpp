# C++ Bank Management System

A modular, file-based bank management system written in C++14. This project provides a simple yet extensible platform for managing users and client accounts, supporting core banking operations such as deposit, withdrawal, and user administration. The system is designed with maintainability and scalability in mind, using object-oriented principles and the Singleton pattern for key managers.

---

## Features

- **User Management**
  - Add, update, delete, and list users
  - User authentication (login)
  - Permission management for user roles

- **Client Account Management**
  - Add, update, delete, and list client accounts
  - Deposit and withdraw operations
  - Search and view client details

- **File-Based Storage**
  - All data is stored in plain text files for easy inspection and backup
  - Automatic loading and saving of users and clients

- **Input Validation**
  - Comprehensive input validation for usernames, passwords, and account data

- **Console Interface**
  - Clear, menu-driven console UI
  - User-friendly prompts and formatted output

---

## Project Structure

Bank-Management-system-using-c++/
│
├── core/ # Core system components
│ ├── constants/ # File paths and constants
│ ├── system utilities/ # System-level helpers (memory management)
│ └── utils/ # Utility functions
│ ├── headers/ # Utility headers (file, string, input)
│ └── implementations/ # Utility implementations
│
├── features/ # Main system features
│ ├── auth manager/ # User authentication logic
│ ├── bank system/ # Client account operations
│ └── manage users/ # User CRUD operations
│
├── data/ # Data storage files
│ ├── Users.txt # User credentials and data
│ └── Clients.txt # Client account information
│
├── src/ # Source code
│ └── Bank_Management_system_using_c++.cpp # Main program file
│
├── Bank-Management-system-using-c++.sln # Visual Studio solution file
└── README.md # Project documentation


---

## Getting Started

### Prerequisites

- **Compiler:** Visual Studio 2022 or any C++14-compatible compiler
- **OS:** Windows (tested), but should be portable to other platforms with minor adjustments

### Build Instructions

1. **Clone the repository:**


2. **Open the project in Visual Studio 2022:**
- Open `Bank-Management-system-using-c++.sln`

3. **Build the solution:**
- Press `Ctrl+Shift+B` or use the __Build Solution__ command.

4. **Run the application:**
- Set `src/Bank_Management_system_using_c++.cpp` as the startup project.
- Press `F5` or use the __Start Debugging__ command.

---

## Usage

- On launch, log in with your credentials (default admin user may be `Admin`).
- Navigate through the main menu to manage users or client accounts.
- All changes are saved automatically to the `data/` directory.

---

## Extensibility

- The system is designed for easy extension:
- Add new features by creating new modules in the `features/` directory.
- Utility functions can be extended in the `core/utils/` directory.
- Storage can be migrated to a database by abstracting file operations.

---

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request for review. For major changes, open an issue first to discuss your ideas.

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

## Acknowledgments

- Developed using Visual Studio 2022
- Inspired by classic console-based management systems
