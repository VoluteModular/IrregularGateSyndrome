# Irregular Gate Syndrome
A 3U 6HP Eurorack Random Gate Module

This module started as a random trigger and gate module, and evolved into a multi-function gate trigger generator. It has two inputs and six outputs, each with an LED, three knobs, a mode select button and mode LED. The schematic and code is open-source, and PCBs / panels are available as well as partial / full kits.

It currently has 3 modes: Mode 1 - random gate generator. Mode 2 - Clock divider. Mode 3 Clock divider with swing. <planned>Mode 4 Euclidian generator.

Here is a video that demonstrates the module.

This module serves several interesting functions. 
The first is as a random trigger and gate generator. When a gate or trigger is connected to the input jack, a random trigger and a random gate is sent on channels 1 through 3. The amount of randomness is dependent on the position of each channel's probability knob. If the knob is fully clock-wise, there is a 100% probability that the gate and trigger will be sent. If the knob is in the middle, there is a 50% chance a trigger and gate will be sent. If the knob is fully counter-clockwise, then no gates will be sent at all. Each trigger and gate is independent for each knob, so if there is a 50% chance that a trigger for channel 1 will be sent, then there is another 50% chance that the channel 1 gate will be sent.

There are two trigger lengths available: 4ms and 100ms. This is set by the dip pins on the back of the module.
There are two modes for the gates. One mode is that the gate is exactly long as the duration of the incoming trigger, so when a trigger is received, the gate will be on, and when the next trigger is received the gate will turn off. The second gate mode is that the gate is randomly turned on, and also randomly turned off depending on the probabity knob.

There is an second input
