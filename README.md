# Fibered Job System (C++) 

This project is a lightweight, header-only fibered-based job system in C++, inspired by **Chrystian Gyrling's talk at GDC 2015**. It is designed to efficiently manage and schedule tasks in concurrent applications using fibers for cooperative multitasking. The system is easy to integrate into your project as a **header** file.

## Features

- **Fibered-based task scheduling**: Uses fibers for cooperative multitasking.
- **Header-only**: The entire implementation can be included as a single `.hpp` file for simplicity.
- **CMake integration**: Easily integrates into your project via CMake.
- **Catch2 testing**: Unit tests are written with Catch2 for easy verification and validation of the system.
- **Modular and flexible**: Can be included directly as a header in your project.

## Requirements

### Users:
- **C++11 or later**: The system requires C++11 or a more recent version of the C++ standard.
### (Contributors:
- **CMake**: Used for building and configuration.
- **Catch2**: A modern, test-driven framework for unit testing.
### )

## Usage

### As a Header-only System

1. Simply copy the `Fibered.hpp` into your project.

2. Include the header where you need it:

   ```cpp
   #include "Fibered.hpp"
   ```

## Running Tests

The project uses **Catch2** for testing. To run tests:

1. Build the project with CMake:

   ```bash
   cmake -S . -B build
   cmake --build build
   ```

2. Run the tests:

   ```bash
   ./build/tests
   ```

## Contributing

Feel free to open issues or submit pull requests. This project is open-source, and contributions are welcome!

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## References

- Chrystian Gyrling's GDC 2015 Talk: [Fibered-based Job System](https://www.gdcvault.com/play/1022186/Parallelizing-the-Naughty-Dog-Engine)
