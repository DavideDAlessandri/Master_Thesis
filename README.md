# Master Thesis repository

- [ESP32 Scripts](#esp32-scripts)
- [micro-ROS](#micro-ros)
- [PLC Programs](#plc-programs)
- [Python Scripts](#python-scripts)
- [Visual Studio 2022 Projects](#visual-studio-2022-projects)


[![Video](https://github.com/DavideDAlessandri/Master_Thesis/blob/main/Visual%20Studio%202022%20Projects/pic2.png?raw=true)](https://youtu.be/hE-AuwIRyF0 "Video")

---
## ESP32 Scripts
### Structure
The files are organized following the chapter of the thesis, each folder corresponds to a chapter and contains the relative scripts. 

### Usage
To use these scripts, install the Arduino IDE or Arduino CLI and configure it for programming ESP32 microcontrollers. The necessary libraries are either installed by the Arduino IDE or can be found in the 'ESP32 Scripts' folder.

---
## micro-ROS
### Structure
This folder contains the PlatformIO project that enables the communication of the sensor data to a ROS topic. 

### Requirements
- PlatformIO [local installation](https://docs.platformio.org/en/stable/core/installation.html) or [PlatformIO IDE for VSCode](https://platformio.org/install/ide?install=vscode)
- PlatformIO Core version 6.1.0 or greater
- PlatformIO needs  `git`, `cmake` and `pip3` to handle micro-ROS internal dependencies:

  ```bash
  apt install -y git cmake python3-pip
  ```

See [micro-ROS for PlatformIO](https://github.com/micro-ROS/micro_ros_platformio) GitHub page for further information.


### Usage

Once the project is updated on an ESP32 microcontroller is possible to test the transmission by connecting via USB the microcontroller to a computer with ROS2 installed and with a **micro-ROS Agent** running. 
It is possible to use a **micro-ROS Agent** just by using this docker command:

```bash
# Serial micro-ROS Agent
docker run -it --rm -v /dev:/dev -v /dev/shm:/dev/shm --privileged --net=host microros/micro-ros-agent:$ROS_DISTRO serial --dev [YOUR BOARD PORT] -v6
```

See [micro-ROS for PlatformIO](https://github.com/micro-ROS/micro_ros_platformio) GitHub page for further information.


---
## PLC Programs
This folder contains the PLC program designed for using the skin with a Keba controller. The program contains both the 'stop on object detected' and 'hand guiding' programs.

---
## Python Scripts
### Structure
The scripts are organized following the tests conducted in the thesis, each folder corresponds to a test conducted in a specific section of the thesis.

### Usage
To use these scripts please install the required libraries listed in the import section of each file.

---
## Visual Studio 2022 Projects
### Structure
This folder contains the Visual Studio project containing the graphic tool to evaluate the correct functioning of the sensors:

![alt text](https://github.com/DavideDAlessandri/Master_Thesis/blob/main/Visual%20Studio%202022%20Projects/pic.png?raw=true)

### Usage
To use this tool, open the project in Visual Studio 2022 and build it. Alternatively, go to "Visual Studio 2022 Projects/Esp32_24_sensors/Esp32_24_sensors/obj/Debug" and run the ".exe" file. This tool works in association with the relative ESP32 script.

---
## Author
Davide D'Alessandri
