# C++ Bank Management System
> 💻 **Developer:** [Halim Wagih](https://github.com/HalimWagih66)


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

<ul>
  <li><strong>Bank-Management-system-using-c++/</strong>
    <ul>
      <li><strong>core/</strong>
        <ul>
          <li><code>constants/</code> – File paths and constants</li>
          <li><code>system_utilities/</code> – System-level helpers (memory management)</li>
          <li><code>utils/</code> – Utility functions</li>
          <li><code>headers/</code> – Utility headers (file, string, input)</li>
          <li><code>implementations/</code> – Utility implementations</li>
        </ul>
      </li>
      <li><strong>features/</strong>
        <ul>
          <li><code>auth_manager/</code> – User authentication logic</li>
          <li><code>bank_system/</code> – Client account operations</li>
          <li><code>manage_users/</code> – User CRUD operations</li>
        </ul>
      </li>
      <li><strong>data/</strong>
        <ul>
          <li><code>Users.txt</code> – User credentials and data</li>
          <li><code>Clients.txt</code> – Client account information</li>
        </ul>
      </li>
      <li><strong>src/</strong>
        <ul>
          <li><code>Bank_Management_system_using_c++.cpp</code> – Main program file</li>
        </ul>
      </li>
      <li><code>Bank-Management-system-using-c++.sln</code> – Visual Studio solution file</li>
      <li><code>README.md</code> – Project documentation</li>
    </ul>
  </li>
</ul>



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

- On launch, log in with your credentials (default admin user may be `Admin.Halim and Password: 12345678aE$`).
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

- Developed by [Halim Wagih](https://github.com/HalimWagih66)
- Built using Visual Studio 2022
