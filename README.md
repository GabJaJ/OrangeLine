# OrangeLine
OrangeLine VCV Plugin

New modules will first show up marked as [Beta].
Beta modules are published for early adopters and should not be considered stable.
They may even disappear again if the concept behind the module doesn't work es expected.
Functionality can change and no backward compatibility is promised between beta versions of a module.
So problems with upgrading between beta versions may arise.
After collecting feedback from the community and doing the polishing of GUI and functionality, those modules will hopefully enter a stable state.

When a module has reached its stable state, the [Beta] mark will disappear.
Modules not marked as beta will maintained in a backward compatible way if possible.

## Fence [Beta]

<p align="center"><img src="res/FenceWork.svg"></p>

### Short Description

The main function of Fence is to take a CV IN and send it to CV OUT, limited to certain range if possible.

This logically works by first substracting a defined STEP value from CV IN as long as the CV is larger than the upper limit of the range. Second, the STEP value is added to the CV as long it is smaller than the lower limit of the range.
Note that this may in a result in a CV OUT larger than the upper limit.

In quantized mode (green light), CV IN and STEP are quantized to semi tone voltages so CV OUT is quantized too. In quantized mode, STEP is working in a special way. Fence will first use a fixed step of 1V (1 octave). If the resulting cv is higher than the upper range limit, it uses STEP to determine an alternative note (alt = CV - 1 + STEP). If alt is in range or high < alt < CV, alt will be sent to CV OUT. This way you can allow Fence for example to replace a note by its 5th (STEP = 7 ST) or minor third (STEP = 3 ST) if those would fit in range. A STEP of 0 disables alternative notes and is fine in most use cases.

In shaper mode (red light) Fence processes CV IN as an audio signal [-5:5]V, applying the described algorythm to the audio signal. CV OUT in SHPR mode is centered and scaled to [-5:5]V.

When the mode light is off, Fence is working in raw mode processing signals between -10 and 10 V. All voltages are used as they are without any conversion. Still output is clamped to [-10:10]V.

Fence will send a TRG OUT whenever cv out is changing.

If TRG IN is connected, Fence will not work continously but more like a S&H when a trigger in is detected.

## Swing [Beta]

<p align="center"><img src="res/SwingImage.svg"></p>

### Short Description

Swing is a micro timing sequencer generating a micro timed clock to implement custom micro timing the easy way.

DIV controls how many beats are created for one clock in trg. 
LEN controls how many of the 16 timing settings will be applied before looping back to the first one.
Default setup is DIV 4 and LEN 16 which is fine for 16 16th of a 4/4 bar. For a simple swing LEN 2 is sufficient. You only have to dial in the first 2 knobs in this case.
AMT controls how much the timing knobs will influence the timing. AMT = 0% switches micro timing off.
The 16 timing knobs allow to setup the timing for each beat.
RST, BPM and CLK have to be connected to your clock. Swing will not work without BPM and Clock connected !
Start with setting up Clocked and connect the CLK and BPM to swing. With DIV 4 Swing will output a micro timed 16th clk.
tCLK (timed clock) will output the micro timed clock.
eCLK (early clock) will output a trg the eraliest time tCLK can appear. Use eCLK to run sequencers delivering values used when tCLK hits.
I recommend to always do a S&H of all values needed for a step when tCLK arrives to avoid note tails.
PHS and CMP are output to allow for further timing like humanization (a module using this will come!).



