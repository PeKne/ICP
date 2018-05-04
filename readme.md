# Block editor

School project to ICP class (The c++ Programming Language). Application is mathematical scheme editor.
Every scheme is set  of graphical blocks connected by links.There is specified few block types,
every type hold different mathematical operation (+, - * etc.).Block contains input and output ports.
Block holds numeral value and distributes it through output block to other block.
That is basic idea how this application works.

### Prerequisites

Qt version 5.5 and C++ compiler is required for compiling this application.

## Makefile

For compile of application run makefile make command from command line.

```
user@machine:/path/to/project$ make
```

For generating of Doxygen documentation run 'make doc'.
```
user@machine:/path/to/project$ make doxygen
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
Open binary file blockeditor in root file of project with 'make run' command.

```
user@machine:/path/to/project$ make run
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
 after Drag-and-drop from output port of one block into input port of another block. Right click on Block destroys that block.

## Examples
In directory *examples* you can find saved schemes which represents functionality of application.
Every file in that directory is one saved scheme and represents different functionality.

## Authors

* **Marek Kalabza** - *xkalab09*
* **Petr Knetl** - *xknetl00*
