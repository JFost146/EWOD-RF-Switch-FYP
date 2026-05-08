# Final Year Project  
## MEng Electrical and Electronic Engineering  
### Jack Foster — University of Birmingham

This repository contains the work completed for my final year MEng project at the University of Birmingham.

The project focuses on the development of an **electrowetting-on-dielectric (EWOD) circuit** designed to actuate a liquid droplet into a waveguide channel, where the liquid acts as part of an **RF switch**.

---

## Licence

This project is released under the **GNU General Public License v3.0**.

You are free to use, modify, and distribute the software and associated project files under the terms of the GPLv3. Any redistributed or modified versions must also comply with the GPLv3 terms.

A full copy of the licence is provided in the [`LICENSE`](license.txt) file.

Parts of this project are derived from or inspired by the GaudiLabs OpenDrop project and Nick de Smith’s Nixie high-voltage switching PSU. Please refer to the acknowledgements section for the original sources.

---

## Project Overview

The repository includes:

- KiCad circuit schematics and PCB design files
- Electrode board designs for EWOD testing
- Arduino-based control software
- RF switch simulation and measurement results
- Supporting notes and design references

---

## Circuit Basics

The `Circuit` folder contains the **KiCad 9.0** schematics, footprints, and manufacturing files used for the PCB.

The boards used in the project were manufactured by **JLCPCB** at approximately **£30 per board**. These boards used **ENIG plating** to optimise coupling between electrodes for EWOD operation. However, the design would likely still work with the cheaper **HASL** finish.

---

## Microcontroller and Software

The circuit was tested using a **Seeed Studio XIAO nRF52840**:

[Seeed Studio XIAO nRF52840 Documentation](https://wiki.seeedstudio.com/XIAO_BLE/)

The board should also be compatible with other microcontroller boards, as the controllable components operate using:

- `3V3`
- Clock signal
- Latch / chip-select signal

The controllable components are:

- Digital potentiometer
- High-voltage switch controller

The control code is written for **Arduino** and can be found in the `Software` folder.

---

## Board Setup and EWOD Testing

To use the board:

1. Snap off the electrode boards.
2. Solder all required components.
3. Connect an electrode board using fly-wires.
4. Add a hydrophobic oil layer to the electrodes.  
   - Silicone oil, **5 cSt**, is preferred.
5. Place a dielectric layer on top of the oil.  
   - Cling film can be used.
6. Add another oil layer on top of the dielectric.
7. Place the droplet above an electrode.
8. Observe the EWOD actuation.

---

## Notes and Testing Observations

- The potentiometer can be bypassed using the `R_pot_sub` resistor pads with either:
  - a `0 Ω` resistor, or
  - a solder bridge.

- Successful tests were proven at maximum voltage output, with the potentiometer set to `0 Ω`.

- EWOD actuation is likely to work at voltages of **200 V or higher**.

- The best EWOD results were achieved using the rectangular electrodes with droplets whose diameter was approximately equal to, or larger than, the width of one electrode.

- The board design is derived from the GaudiLabs OpenDrop board:  
  [GaudiLabs OpenDrop](https://www.gaudi.ch/OpenDrop/)

- The DC-DC converter design originates from Nick de Smith’s Nixie high-voltage switching PSU:  
  [Nick de Smith Nixie PSU](https://www.nick.desmith.net/Electronics/NixiePSU.html)

---

## Board Specifications

| Parameter | Value |
|---|---|
| Input voltage | 5 V |
| Input current at maximum output | 0.16 A |
| Theoretical input range | 4.5 V to 16 V |
| Electrode output voltage range | 50 V to 290 V |
| Electrode output current range | 2.3 µA to 13.2 µA |
| Number of electrode designs | 7 |
| Minimum standalone output | 50 V from XIAO nRF52840 USB input |

---

## RF Switch Investigation

The `Liquid Switch Tests` results contain:

- CST simulation results
- VNA measurement results
- RF switch response data for different liquids

These results investigate the behaviour of an RF switch when closed using various liquid materials.

---

## Switch Link

Add switch link here.

---

## Repository Structure

.
├── Circuit/
│   ├── KiCad schematics
│   ├── PCB footprints
│   └── Manufacturing files
│
├── Software/
│   └── Arduino control code
│
├── Liquid Switch Tests/
│   ├── CST simulation results
│   └── VNA measurement results
│
└── README.md

---

## Acknowledgements

This project builds on open-source and publicly documented work from:

- [GaudiLabs OpenDrop](https://www.gaudi.ch/OpenDrop/)
- [Nick de Smith’s Nixie HV Switching PSU](https://www.nick.desmith.net/Electronics/NixiePSU.html)

---

## Author

**Jack Foster**  
MEng Electrical and Electronic Engineering  
University of Birmingham


## Project Supervisor

**Prof. Yi Wang**
Department of Electronic, Electrical and Systems Engineering
University of Birmingham