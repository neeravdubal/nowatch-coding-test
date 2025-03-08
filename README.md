# Circular Buffer Heart Rate Monitor

## Overview
This project demonstrates the implementation of a circular (ring) buffer in C along with a heart rate monitor application. The circular buffer is used for storing heart rate data (generated randomly between 44 bpm and 185 bpm) in real time. Every second, a new heart rate value is generated, stored in the circular buffer (with overwrite behavior when full), and the Exponential Moving Average (EMA) is computed and displayed.

The project consists of:
- A circular buffer library with functions to initialize, add, remove elements, and check the buffer’s status.
- A heart rate monitor application that uses the circular buffer.
- Comprehensive unit tests written using Google Test.
- A cross-platform Makefile for building the application and tests.
- Detailed instructions in this README.

## Project Structure
- **circular_buffer.h**: API declarations for the circular buffer.
- **circular_buffer.c**: Implementation of the circular buffer functions.
- **heart_rate_monitor.c**: Main application that generates, stores, and computes EMA on heart rate values.
- **test_circular_buffer.cpp**: Extensive unit tests using Google Test.
- **Makefile**: Build instructions for compiling the code on Mac, Linux, and Windows.
- **README.md**: This document.

## Prerequisites
- A C compiler (gcc) and a C++ compiler (g++).
- [Google Test](https://github.com/google/googletest) library installed for unit testing.
- For Windows, ensure that the Windows SDK is installed (for Sleep functionality).

## Building and Running

### 1. Build the Application
To compile the heart rate monitor application, run:
```bash
make all
