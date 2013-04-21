Summary
========

WebAppMgr is responsible for running Enyo applications on webOS

This variant of WebAppMgr works with WebKit1 and can be built against either Qt4.8.3 or Qt5.


How to Build on Linux
=====================

### Building the latest "stable" version

Clone the repository openwebos/build-desktop and follow the instructions in the README file.

### Building your local clone

First follow the directions to build the latest "stable" version.

To build your local clone of WebAppMgr instead of the "stable" version installed with the build-webos-desktop script:

* Open the customize/location.sh script with a text editor
* Locate the line:  export WEBAPPMANAGER....
* Uncomment the line and change "${BASE}/webappmanager" to use the folder containing your clone, for example "${HOME}/github/webappmanager"
* Save your changes
* Remove the file ~/luna-desktop-binaries/webappmanager/luna-desktop-build*.stamp
* Start the build

# Copyright and License Information

All content, including all source code files and documentation files in this repository except otherwise noted are: 

 Copyright (c) 2008-2013 Hewlett-Packard Development Company, L.P.

All content, including all source code files and documentation files in this repository except otherwise noted are:
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this content except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
