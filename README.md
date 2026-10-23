
# fprime-geometry-types

This project contains the generic geometry types with specific F' integration, broken out from the main HS2-CDH repo as they are project-agnostic. See https://github.com/UWCubeSat/HS2-CDH for further details.


Required tools:

    CMake 3.16 or newer
    GCC or Clang with C++17 support
    Python 3.9 or newer

F Prime tools:

pip install fprime-tools fprime-gds

## Getting Started

Clone the repository:

git clone https://github.com/UWCubeSat/fprime-geometry-types.git
cd HS2-CDH

Initialize the F Prime submodule:

git submodule update --init --recursive

(Optional) Create and activate a Python virtual environment:

python3 -m venv fprime-venv
source fprime-venv/bin/activate
pip install -r lib/fprime/requirements.txt
pip install fprime-tools fprime-gds

Generate build files:

fprime-util generate

Build the project:

fprime-util build


The F Prime commands and workflow used in this repository are based on the HS2-Software repository and the official F Prime documentation:

    https://nasa.github.io/fprime/
    https://fprime.jpl.nasa.gov/docs/

## Testing 

Tests can be run with:

    fprime-util check

Coverage for project components (recommended):

    fprime-util check --coverage --path geometry/ --recursive


## Formatting

To format files as per .clang-format specification, use the following:

    Ctrl-Shift-P
    Task: Run task
    Format C++ FSW files

Contributing

Do not push directly to the main branch.
Create a feature branch, commit your changes, and open a pull request for review.