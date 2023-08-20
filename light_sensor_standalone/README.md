# Standalone Light Sensor project

This is a submodule of the "Smart Home" project. The goal is to design and implement the hardware and software
of a basic light sensor, based on a single LDR resistor. The light intensity (illuminance) measured by the 
analog circuit is converted into a digital signal, and then sent to the Smart Home's server via WiFi.

## Main components

This system is composed by an analog and a digital circuits:

### Analog circuit
- 1x Rail-to-Rail operational amplifier (OpAmp), OP295GPZ
- 1x Voltage switcher, LMC7660
- 1x LDR photoresistor, GL7516
- 2x red LEDs to signal a healthy power supply
- 1x green LED to signal a working output
- 3x resistors: 51k ohms for LDR circuit, 10K for Voltage switcher and a RLED suitable for a 3v3 power supply

### Digital circuit

The digital part is composed by the Wemos D1 mini board, which is ESP8266 based. I have chosen this one
because it's WiFi capable and it has a built-in ADC module whilst keeping low power consumption. In addition, 
it supports: UART, I2C and SPI serial buses which can be very useful if we escalate the circuit with an additional system, e.g.: a temperature sensor. Finally, the board let's me feed the entire system via a 5V USB-based charger, 
making unnecesary to use batteries.
