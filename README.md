Implémentation Modbus simple en C et Node.js :

* C
    * Un server : server.c
    * Un client : main.c
* Node.js
    * Un client : js/test.js

Librairies
==========

* C : [https://github.com/stephane/libmodbus](https://github.com/stephane/libmodbus)
* Node.js (Javascript) : [https://github.com/Cloud-Automation/modbus](https://github.com/Cloud-Automation/modbus)

Installation
---------------
Suivre les instructions sur GitHub

Compilation des programmes en C via GCC
========
    gcc server.c -o server `pkg-config --cflags --libs libmodbus`
