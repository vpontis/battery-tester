Battery Tester
==============

Overview
--------

This repository contains code and instructions on how to test a battery using an Arduino. I set this up for a cell phone lithium-ion battery for [CoBattery](www.cobattery.com) but this set up can be generalized to other batteries.

Currently the code allows you to look at voltage and current over time as the battery discharges and gives an estimate of the battery's capacity.

Instructions 
------

###Materials

+ Arduino Uno
+ Wire
+ Resistors
+ Voltmeter
+ Breaboad
+ Arduino SD Card Add On and SD card (optional but helpful)

###Set Up


1. On a breadboard add resistor(s) and connect battery across resistors
1. Connect Arduino GND to battery ground and A0 to battery power
2. (Optional) Connect SD card to Arduino
3. Upload `measure_battery_voltage.ino` to the Arduino
2. Run `analyze_battery_data.py` on the text file generated by the Arduino. This will generate graphs and a capacity estimate.

Notes
-----

If you over-discharge your battery, do not recharge it. This is dangerous. Over discharing a battery can often cause irreparable chemical damage. 