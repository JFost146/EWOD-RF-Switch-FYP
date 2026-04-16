#Final Year Project - MEng Electrical and Electronic Engineering
#Jack Foster, University of Birmingham

This repo is the culmination of work done for the purpose of the final year project for a final year MEng at the University of Birmingham. It details the work done towards an electrowetting on dielectric (EWOD) circuit for the purpose of actuating a liquid into a waveguide channel, acting as an RF switch.


#Circuit Basics

Under the Circuit folder are the KiCAD 9.0 schematics and footprints used for this project, as well as all design files needed to get the board manufactured. The results achieved used JLCPCB, and came to around £30 per board. This, however, is using ENIG plating to optimise the coupling between electrodes for the purpose of EWOD, and would likely still be successful with the significantly cheaper alternative.

The circuit runs using a Xiao nRF52840 but is able to function with any microcontroller board, since the controllable components are the digital potentiometer and the high voltage switch controller, both of which run from 3V3, a clk, and a latch/ CS pin. The code is Arduino, found under the Software folder.

To use the board, snap off the electrode boards, solder all components, then connect an electrode board using fly-wires. Add a hydrophobic oil layer (preferably silicon oil, 5 cSt) to the electrodes, then a dielectric (cling film works!) on top of this, then another oil layer on the dielectric. Place the droplet on top of this above an electrode, then observe the EWOD.

notes: 
-successful tests are proven with maximum voltage output (potentiometer at 0 Ohms), and are likely to work at 200 V or more.
-the best EWOD results are found using the rectangular electrodes with droplets of diameter larger of order with or larger than the width of one electrode.
-the board design is derived from GaudiLab board: https://www.gaudi.ch/OpenDrop/
--the DC:DC converter design originates with Nick de Smith's nixie HV switching PSU: https://www.nick.desmith.net/Electronics/NixiePSU.html 



#RF Switch Investigation

Under the liquid switch tests results are the simulation results from CST, and the actual results found by VNA testing the switch. These detail an RF switch response to being closed using different liquids.

Switch link: 