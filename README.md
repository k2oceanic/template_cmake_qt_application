# template_cmake_qt_application
This is a repository to use as a starting point for a QT Cmake package for use with Ubuntu.   It is configured based on the the names and context of the files within.

**include/<project_name>:** this directory should contian all your header files and .UI files  These are automatically added to the project and linked when you run cmake.  Whatever you set the <project_name> to will be the cmake pakcage name

**src/**  this folder contains all your cpp files associated with the headers described above. 

**nodes/**  this folder contains all of your main applications.   Anything in here will be made into an executable when you run cmake.   Therefore, every cpp file should contain an int main() function.
  
**rc/**  cmake will automatically read any .qrc files you have in this directory for use in your application. 

**CMakeLists.txt** this is mostly auto configured but you may need to open this to link additional libraries such as boost.

**snapcraft.yaml** this file allows you to convert this package into a snap package for installation onto your system.

## Building

This package can be built as follows assuming you are working in the package root directory

```
mkdir build
cd build
cmake ..
make
```

## Making it into a snap

Build the snap 
```
cd <package root directory>
snapcraft
```
install the snap on your system.   The dangerous flag is necessary because the package is unsigned by the snap store.
```
sudo snap install template-qt-snap_0.0.1_amd64.snap --dangerous
```
The application can be run by entering
```
template-qt-snap.my-application
```
