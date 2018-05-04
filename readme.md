# Block editor

School project to ICP class (The c++ Programming Language). Application is mathematical scheme editor.
Every scheme is set  of graphical blocks connected my links.There is specified few block types,
every type hold different mathematical operation (+, - * etc.).Block contains input and output ports.
Block holds numeral value and distributes it through output block to other block.
That is basic idea how this application works.

### Prerequisites

Qt version 5 and C++ compiler is required for compiling this application.

## Installation

Run makefile make command from command line.

```
user@machine:/path/to/project$ make
```

For generating of Doxygen documentation run 'make doc'.
```
user@machine:/path/to/project$ make doc
```

For creating zip archive of project run 'make zip'.
```
user@machine:/path/to/project$ make zip
```
For remove of all built files run 'make clean'.
```
user@machine:/path/to/project$ make clean
```

## Running the application
Open binary file blockeditor in root file of project.

```
user@machine:/path/to/project$ ./blockeditor
```

## Controls of GUI application

### Menubar

Top bar is divided into three menus:
* Scheme
  * New - creates new empty scheme
  * Save - save current scheme into file
  * Load - load existing scheme from file

* Block - add different kinds of block into scheme
* Action
  * Debug - calculate on uncalculated block of scheme
  * Run - calculate every block of scheme
  * Stop - remove values from all ready calculated blocks

### Mouse Control

Moving with blocks is possible as Drag-and-drop action. New link is created
 after Drag-and-drop from one port to another one. Right click on Block destroys that block.

```
Give an example
```

## Authors

* **Marek Kalabza** - *xkalab00*
* **Petr Knetl** - *xknetl00*
