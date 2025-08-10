Codeless Host Application 
=========================

codeless_host_app is a graphic user interface application, written in python, to send commands to the connected Codeless device.
The user is able to:

* connect or disconnect to the serial port of the Codeless device,
* send AT commands and see their output, 
* enter, exit and resume binary mode easily. If the remote device, which is connected with the Codeless device, sends AT+BINREQ, local device automatically responds with AT+BINREQACK. If the remote device sends AT+BINREQEXIT, then the local device exits automatically binary mode using sequence of AT and AT+BNREQEXITACK commands, 
* send a file (text or binary) while the device operates in binary mode,
* keep a log file of any received file from the remote host (SAVE LOG button)
* keep a log file of all the commands that are sent to the local device (under current folder <timestamp>_console.log) 
* send a batch file, containing a set of AT commands with a new line separated, --> is the indication of input command, <-- is the indication of the command reply, OK or ERROR is the default terminating strings and anything in between is for validation that the command is executed with the correct parameters 
   eg.:

    --> AT+GAPSTATUS 
    
    <-- AT+GAPSTATUS
    
    0,0
    
    OK
   
* stop the executed batch file, if any command responds with an error,
* be notified by an indication that the binary mode is on (blue color) and off (yellow led),
* reconnect or change any of the serial's port parameters without pressing Disconnect option from the menu.


Requirements
============
Pyhton
------
Required version is Python 2.7.15

Installation
------------
1. Download the Python installer from `Python 2.7.15 <https://www.python.org/ftp/python/2.7.15/python-2.7.15.amd64.msi>`_
2. Add Python to PATH


PyInstaller
-----------
PyInstaller freezes (packages) Python applications into stand-alone executables.

Installation
------------
1. ```pip install PyInstaller==3.6```
2. Rename pyinstaller.exe to pyinstaller2.7.exe 

Create the executable under current folder
------------------------------------------
1. Open any command prompt.
2. Navigate to the codeless-pytohn folder. 
3. Execute following command to generate the .exe file 

```pyinstaller27.exe -n codeless_host --onefile gui_app\codeless_host_app.py --windowed -i gui_app\Dialog_D-Symbol_Color_RGB_Small_icon.ico --add-data "gui_app\Dialog_D-Symbol_Color_RGB_Small_icon.ico;." --hidden-import pygatt --distpath gui_app\```