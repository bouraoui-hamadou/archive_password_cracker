# ZIP Archive Password Cracker

## Overview

This C++ program is a ZIP Archive Password Cracker that uses the libarchive library to attempt to crack encrypted ZIP archives. It employs a password guessing mechanism to find the correct password by trying all possible combinations of characters defined in the characters vector. The program displays each attempted password combination in real-time and extracts the files if the correct password is found. It also tracks the number of tested combinations, the elapsed time, and displays the results at the end of the process.

## Coroutines in C++

The program uses C++ coroutines to implement the CombinationGenerator class, which generates all possible combinations of characters for the password guessing process. Coroutines are a powerful feature in modern C++ that allows the program to suspend and resume its execution, making it suitable for managing asynchronous tasks and iterating over a large number of possibilities efficiently.

## Limitations

- This code is designed purely for educational purposes. While it demonstrates the concept of password cracking and showcases the use of coroutines in C++, it is not intended for real-world use. There are more performant and secure password-cracking solutions available, and unauthorized access to encrypted content is illegal and unethical.

- One limitation of this solution is the use of the libarchive library, which requires opening and closing the ZIP file for each new password combination. This approach can be slow and inefficient, especially for large ZIP archives.

## Future Improvements

There are several potential enhancements to consider for future iterations of this project:

1. **Multithreading**: Implementing multithreading can speed up the password cracking process by parallelizing the attempts on different CPU cores.

2. **Custom ZIP Library for C++**: Developing a custom ZIP library specifically designed for C++ can improve performance and provide more flexibility in managing ZIP archives.

3. **Password Control Support**: Adding support for specifying password control criteria (e.g., minimum and maximum password length, specific character sets) can help narrow down the search space and improve the efficiency of the password cracking process.

4. **Password Dictionaries**: Implementing password dictionaries to try common passwords or custom wordlists can be more effective in certain scenarios.

Remember, using password cracking techniques to gain unauthorized access to encrypted content is illegal and unethical. Always use such tools responsibly and with proper authorization.

---

**Copyright Notice**

The code provided here is the intellectual property of Bouraoui Hamadou and is protected under copyright laws. Redistribution and use in source and binary forms, with or without modification, are permitted under the conditions specified in the license statement.

Before using or modifying this code, please ensure that you have read and understood the license terms. Unauthorized distribution or use of this code for malicious purposes is strictly prohibited.

