# ubit_project
ECOM042: Embedded Systems Project

In order to run this project, make sure to install zephyr and the required dependencies in your system.

[Zephyr RTOS](http://docs.zephyrproject.org/getting_started/getting_started.html)

Download or clone this project, open the file /ubit_project/CMakeLists.txt and modify lines 1, 2 and 3 to your current zephyr and zephyr-sdk installation path. After everything is setup, enter the /ubit_project/ directory and execute the commands below to build and run (linux/macOS):

	$ mkdir build && cd build
	$ cmake ..
	$ make -j4
	$ sudo make flash
