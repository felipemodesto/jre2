# JRE2 Implementation Project

---

## About

This implementation of the Java Runtime Environment V2 is designed to read and interpret .class byte-code Java files, and was developed with academic/educational purposes.
The project requires that standard Java libraries be present, the compiled .class files corresponding to each package are available as part of the file tree.

All but the following instructions have been implemented:

  ⋅⋅*	checkcast - Check whether object is of given type
  ⋅⋅*	getstatic - Get static field from class
  ⋅⋅*	monitorenter - Enter monitor for object
  ⋅⋅*	monitorexit - Exit monitor for object
  ⋅⋅*	putstatic - Set static field in class

For the most part, any simple Java-based source-code should function as expected.

This project was developed during 2009 and has been uploaded for record-keeping of legacy projects.
Originally, its purpose was to allow for increased understanding of the java environment, and to promote C development experience.

The source code was developed taking into consideration the limitations of C99.

Code documentation is, in its majority, in Portuguese, as it's my mother tongue.
The JRE2 specification is available on-line, should it be necessary.

Several .class test-files were made available at the time of the project implementation to evaluate the implementation and ensure its validity.

---

## Compilation and Code Execution

Project compilation is quite simple, just run a GCC command specifying the c99 standard and the -lm command. Adding -lm is shorthand and ensures that your compiler remembers to add the Math library. e.g.:

`>> gcc *.c -lm -std=c99 -o jre2.out`

To run a .class file, run the executable followed by the class file name. e.g.:

`>> ./jre2.out Main`

In this example, the code will attempt to load and run the file Main.class. This example assumes that both files are in the same directory.
Note that the executable file expects the Java folder to be in the same directory as the resulting executable.
If necessary move either your binary or the Java file contents so they are in the same directory.
This necessary as the project relies in many packages built atop of the basic virtual machine functions.