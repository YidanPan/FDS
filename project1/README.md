# Project 1: Performance Measurement

## 1. Project Structure

This submission package is strictly organized to fulfill the project evaluation criteria. The directory structure is as follows:

```text
Project_Submission/
├── README.md                  # This root documentation file
├── document/                  # Contains the project report
│   └── report.pdf             # Detailed analysis, complexity derivation, and plots
└── code/                      # Contains source codes and scripts 
    ├── binary(iterative).c    # Iterative Binary Search
    ├── binary(recursive).c    # Recursive Binary Search
    ├── sequential(iterative).c# Iterative Sequential Search
    ├── sequential(recursive).c# Recursive Sequential Search
    ├── plot_drawing.py        # Python script for plotting performance curves
    ├── project_test.c         # Integrated test file
    └── README.md              # Detailed compilation & execution guide for the code
```

## 2. Start
Please navigate to the code/ directory for detailed compilation and execution instructions.

All four search algorithms are implemented as standalone C programs to ensure independent and accurate performance measurement. The testing framework measures the worst-case scenario by searching for an element not present in the generated array.

## 3.Environment Requirements
- **C Compiler**: GCC or any C99 standard compliant compiler.

- **Data Visualization**: Python 3.x with the matplotlib library installed (only required if you wish to re-run plot_drawing.py to generate the graph).

## 4.Anonymous Declaration & Compliance
- **Blind Review Ready**: All materials in this package have been thoroughly checked to ensure no personal identification is present, maintaining the strict integrity of the blind peer-review process.

- **Documentation Rate**: Extensive inline comments are provided in all .c files to explain base cases, recursive logic, and time/space complexity justifications, strictly following the grading rubric.