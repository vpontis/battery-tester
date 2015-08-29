#! /usr/bin/python

import sys, re, numpy as np, matplotlib.pyplot as plt

def get_elem(i):
  def func(lis):
    if lis:
      return lis[i]
    else:
      return 0
  return func

def get_times_and_voltages_from_file(filename):
  f = open(filename)
  lines = f.read().splitlines()
  lines = map(lambda x: map(float, re.findall(r"\d+", x)), lines)

  lines = filter(lambda x: (not not x), lines)
  seconds, voltages = [], []

  for v, t in lines:
    seconds.append(t)
    voltages.append(v)
  seconds = np.array(seconds)
  voltages = np.array(voltages)
  return seconds, voltages


if __name__ == '__main__':
  seconds, voltages = get_times_and_voltages_from_file(sys.argv[1])

  # time to minutes
  minutes = map(lambda x: x/60, seconds)

  # convert from analog reading to voltage
  # m is the conversion from the digital output of the arduino (out of 1024) to voltage
  m = 0.0044573848597141271
  voltages = map(lambda x: x*m, voltages)

  plt.plot(minutes, voltages, 'ro')
  plt.ylabel('Voltage (V)')
  plt.xlabel('Time (min)')
  plt.show()

  resistance = raw_input("Please enter the resistance (Ohms): ")
  resistance = float(resistance)

  # we get current by v = ir --> i = v/r
  currents = map(lambda x: x/resistance, voltages)

  plt.plot(minutes, currents, 'ro')
  plt.ylabel('Current (A)')
  plt.xlabel('Time (min)')
  plt.show()

  # integrate current over time to get charge
  # capacity in amp seconds
  capacity = np.trapz(currents, x=seconds)
  # convert capacity to milli amp hours
  capacity = capacity * 1000 / 3600

  print 'The measured capacity is ' + str(capacity)
  
