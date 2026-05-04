Author: William Truman  
Software version 1.7  

README Created 29/04/26  
README Last updated 02/05/26  
Github repository: https://github.com/superweasel111/PFE_PROJECT_WILLT

# Description #
waveform_analyser reads a table of 1000 rows of data for a 3-phase waveform.

The table must have a header, and 8 columns in the exact order of [Timestamp, A voltage, B voltage, C voltage, Line current, Frequency, Power factor, thd percent]. The header must be on line 1, with data lines to follow with no breaks.

It then performs the necessary calculations to report the following as part of a results.txt file written in the same directory as the executable:
- DC offset (Mean)
- RMS
- Amplitude
- Whether the RMS was compliant within a 10% tolerance band
- Any timestamps at which voltage clipped (exceeded 324.9V)

# Required Software #
These instructions assume you have a gcc compiler installed. For the easiest installation, you may choose to use a prebuilt package as is available from such websites as [WinLibs](https://winlibs.com/)

# Error codes #
1: Invalid usage (wrong number of arguments)  
404: File not found (File input points to NULL)

# Compile and Run (CLion) #
1. Open the project in CLion
2. Select the desired CMake profile (Debug/Release)
3. Build the project via the 'Build' button (alternatively CTRL+F9)
4. The executable will be located in
`cmake-build-debug/`
or
`cmake-build-release/`
respectively.

5. To run from the terminal:  
> cd cmake-build-debug

or  

> cd cmake-build-release  

And then, to use the program,  
> ./waveform_analyser \<input_file>  

The input file must be in the current working directory, or a relative/absolute file path must be provided. File extensions such as .txt or .csv must be included. If there are spaces or other special characters in the file path, wrap it in speech marks.  

# Compile and Run (executable using gcc) #

## Compilation ##
1. Navigate to project directory in CLion terminal:
> cd \<path to project>
2. Compile to target directory (defaults to project directory if not specified):
> gcc *.c -o \<path>/waveform_analyser -lm  
  
If there are spaces or other special characters in the file path, wrap it in speech marks.

## Running ##
1. Open cmd terminal
2. Navigate to executable directory
> cd \<path to executable directory>
3. To use the program:
> waveform_analyser <input_file>

The file must be in the same directory as the program executable.

[README.md](https://github.com/user-attachments/files/27302529/README.md)
