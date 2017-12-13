[![Codacy Badge](https://api.codacy.com/project/badge/Grade/888b8d4704284ee4ae868ba1b815644a)](https://www.codacy.com/app/Haizzz/UWA-Makers-Tank-Project?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=UWA-Makers-Club/UWA-Makers-Tank-Project&amp;utm_campaign=Badge_Grade) 

### Description

This Github repository is for the arduino code of the tank project by the UWA Makers Club. This document contains the quickstart guide, features and workflow of this project.

### Structure

-   Entry point of the script is `makers_tank.ino`. This file should only contain high level function calls to operate the tank
-   Class declaration is included in `.h` files and their implementation in the corresponding `.cpp` file 

### Quickstart

1.  Download and install the [**Arduino IDE** ](https://www.arduino.cc/en/Main/Software) 
2.  Clone or manually download this repo into your sketch folder

**Note**: If you don't want to use the Arduino IDE (I don't) there are probably some build systems for your text editor (eg: Sublime text have [Arduino-cli](https://packagecontrol.io/packages/arduino-cli))

### Style and standards

While this isn't a corporate project, many people will potentially update and maintain it and so some standards of code should be maintained so that. General rules of programming applies:

-   Don't repeat yourself
-   Sensible function / variable name
-   Comment your code (pls document everything)
-   Don't push code to Github that doesn't work
-   Test your code
-   If your code contain bugs, fix it or ask someone for help or create an issue. Noone likes side effects
-   Functions should do what they say they do, no side effects
-   Constants should be in uppercase (eg: `ERROR_MARGIN`)
-   Private variables should have an underscore before their name (eg: `_motor_difference`)
-   Class names should be in camel case with a capital first letter (eg: `MotorControl`)

Some additional standards relevant to the project are:

*   Write scalable code. Don't put abitrary values in your code that might break if we change something. A prime example of this is adding a constant value specific to a hardware device on the tank. If that device breaks and we change it to use something else, you would have to go over the entire code base to change that value
*   Either camel case or snake case can be used for variable and function names. Just make sure that it's consistent in one file (if you're editing a file in snake case, use snake case)
    *   _snake case_: `beef_pie`
    *   _camel case_: `beefPie`

### Miscellaneous

We have an autonomous code review service called [Codacy](https://www.codacy.com/). I've never used it before, if you want something to change about it please let me know

### Workflow

Code inside the Master branch should always compile and work as intended. When creating new features, create a new branch for your feature and put in a pull request to master. Always try to get someone to look over your code using the reviewer feature on Github so that bugs can be caught before they get merged

### Contribute

If you would like to contribute to this document, feel free to edit it and make a pull request