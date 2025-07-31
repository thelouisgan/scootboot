---
title: "Scootboot"
author: "@louisgan"
description: "Powered attachment to shoes using motorised wheels to accelerate walking speeds"
created_at: "2025-07-14"
---

# 21 hours total (design+research)

## 18/07/2025 - 2 hours
### Researching, creating plan and initial BOM list

- I want to create my own DIY moonwalker boots, basically motor powered wheels attached to bottom of shoes
- Use metal baseplate and attach to shoes with velcro, with motor + electronics and battery on the baseplate
- Speed is controlled manually via RF using EdgeTX controller + RX which I have, so different from AI-powered smart speed control from [Moonwalkers](https://shiftrobotics.io/products/moonwalkers?srsltid=AfmBOoqtUeJfdKixhwpnNn_zGu1JXuPLj22AJFjQfRdvFxCT6fvGAdw2)
- Preferably Arduino or Raspberry Pi powered
- Motor mounted on the side, preferably have 4 wheels per boot and the back two wheels are motorised
- I want to use drone/RC car style LiPo battery 12V
- Factor in motor type, size, power, compatibility, feasibleness, and wheels
- If motor on side, will it be able to support wearer's weight up to eg. 60–80kg? or will the motor shaft attached to wheel be not strong enough and collapse
- Will torque be enough / speed?
- I could use rubber or skateboard wheels (Polyurethane)
- I want it to lightly assist in my walking like a travellator – so increase by a few km/h to my walking speed

**BOM per wheel:**
| Component                        | Specs / Notes                                                | Qty   | Unit Price (USD) | Total (USD) |
| -------------------------------- | ------------------------------------------------------------ | ----- | ---------------- | ----------- |
| **DC Gear Motor**                | 12V, 100 RPM, 10 Nm torque, 8mm shaft                        | 2     | \$18             | \$36        |
| **Motor Mount Bracket**          | L-bracket steel, supports 775/550 motors                     | 2     | \$3              | \$6         |
| **Motor Shaft Coupler**          | 8mm bore to wheel hub                                        | 2     | \$4              | \$8         |
| **Wheels (longboard-style)**     | 70mm–90mm polyurethane skateboard wheels with 608zz bearings | 4     | \$6              | \$24        |
| **Baseplate (Metal)**            | Aluminum, 3mm thick (cut to size \~30x10 cm)                 | 1     | \$10             | \$10        |
| **Velcro Straps + Padding**      | Heavy-duty                                                   | 2     | \$5              | \$10        |
| **Arduino Nano**                 | With CH340, for compactness                                  | 1     | \$3              | \$3         |
| **Dual Channel Motor Driver**    | 12V 10A BTS7960 or Cytron MD10C                              | 1     | \$10             | \$10        |
| **LiPo Battery**                 | 3S 12.6V 2200–3000mAh 30C                                    | 1     | \$20             | \$20        |
| **Voltage Regulator**            | 5V buck converter (for Arduino)                              | 1     | \$2              | \$2         |
| **XT60 Connectors + Wires**      | Power wiring                                                 | 1 set | \$2              | \$2         |
| **Power Switch**                 | Toggle with XT60 inline                                      | 1     | \$2              | \$2         |
| **Receiver (EdgeTX compatible)** | Already owned                                                | 0     | \$0              | \$0         |

Not including shipping/tax
Estimated total cost per boot: $133 USD
Estimated total cost for 1 pair: $266 USD

## 19/07/2025 - 2 hours
### Motor research & parts sourcing

[5840-31ZY Worm Gear Motor](https://shopee.com.my/5840-31ZY-Worm-Gear-Motor-12V-24V-Bidirectional-Short-Shaft-Forward-And-Reverse-7RPM~470RPM-Speed-Regulating-Metal-Gear-Motor-Micro-DC-Brushed-Motor-High-Torque-100KG.CM-i.1079294791.19693502809?xptdk=12a2a904-a9ec-4db9-a551-096a7e0f1152)
12V 60RPM including Motor Bracket
| Reduction ratio | Rated voltage  | Speed (RPM ±10%)  | Current (A) | Torque (KGfCM) | Power (W) |
| --------------- | -------------  | ----------------  | ----------- | -------------- | --------- |
| 100             | 12             | 60                | 1.6         | 16             | 19.2      |

<img width="511.4" height="446" alt="Screenshot 2025-07-21 at 5 09 03 PM" src="https://github.com/user-attachments/assets/48bcdb4b-c571-4ebf-be2e-46d48b1e0ce3" />
<img width="445.4" height="250" alt="Screenshot 2025-07-21 at 5 09 25 PM" src="https://github.com/user-attachments/assets/533d981e-3277-4e91-8000-605603e7a5b2" />
<img width="400" height="400" alt="image" src="https://github.com/user-attachments/assets/d5a3e74b-0a55-4cc0-89da-c3cb0f15ce12" />

MYR 72.39 = 17.09 USD
x4 = MYR 289.56 = 68.36 USD

-----------------------

12V/24V Large Torque 0.5KG.CM~100KG.CM 32GP-31ZY Micro Reduction DC Planetary Brush Motor
| Reduction ratio | Rated voltage  | Speed (RPM ±10%)  | Current (A) | Torque (KGfCM) | Power (W) |
| --------------- | -------------  | ----------------  | ----------- | -------------- | --------- |
| 100             | 12             | 65                | 1.8         | 14             | 21.6      |
8mm shaft diameter
<img width="400" height="400" alt="image" src="https://github.com/user-attachments/assets/ef894951-e283-49a8-b315-e0cefdc2671d" />
<img width="403" height="424" alt="Screenshot 2025-07-21 at 5 30 18 PM" src="https://github.com/user-attachments/assets/2b00f302-fa7c-4482-968d-0bccbfb49b08" />
<img width="598" height="332" alt="Screenshot 2025-07-21 at 5 30 47 PM" src="https://github.com/user-attachments/assets/27553787-cc6d-4523-8116-a14404c43292" />

Mass 335g, gearbox length 38mm
Larger footprint with added joints
Requires universal joint for 90deg shaft coupling

-----------------------

### Motor driver
**Cytron 13A Dual Channel Motor Driver - MDD10A**

<img width="475" height="269.5" alt="image" src="https://github.com/user-attachments/assets/a40c7999-b9c4-4a5b-ad03-cb7f7ca4c900" />

MYR 94.00 = USD 22.21
X2 = MYR 188 = USD 44.42

## 25/07/2025 - 2 hours
### Sketching exploded diagram & plan

<img width="904" height="766" alt="Screenshot 2025-07-25 at 8 25 25 PM" src="https://github.com/user-attachments/assets/4b117286-e340-405b-a94a-4ded7480fbfd" />

## 27/07/2025 - 2 hours
### Designing base plate shape and logo

<img width="1142" height="1105" alt="Screenshot 2025-07-28 at 2 26 02 AM" src="https://github.com/user-attachments/assets/c188afb8-5eec-457c-a878-39f25d04c9f3" />

## 28/07/2025 - 3.5 hours
### CAD Modelling of rear wheels and component research

<img width="2032" height="1161" alt="Screenshot 2025-07-29 at 9 38 43 PM" src="https://github.com/user-attachments/assets/27eefe80-2a3c-4876-836c-8f68bc2d38af" />

For the shaft coupling between the polyurethane wheels and the motor axle, I decided to weld the built in bearing to so that the torque is able to be transferred while allowing me to weld the 8mm motor axle directly into the 8mm bore for the inner bearing track. To prevent lateral slipping, I will be purchasing and using set screw collars outside the wheels on the axle, which I will purchase the longer 51mm shaft length for easier mounting.

## 29/07/2025 - 2 hours
### CAD for all electronics, front wheels and aluminium baseplate

<img width="1912" height="1185" alt="Screenshot 2025-07-30 at 1 15 26 AM" src="https://github.com/user-attachments/assets/d41ef09a-9f28-4eef-8201-922bd8a0e31d" />
<img width="1912" height="1185" alt="Screenshot 2025-07-30 at 1 15 39 AM" src="https://github.com/user-attachments/assets/840885ae-4dc2-429b-8faa-1341dc616fa0" />

## 30/07/2025 - 4.5 hours (correction from wakatime)
### Finished design for Aluminium baseplate (CNC) and TPU sole (3D print) milling + mounting holes

**Rear wheels mounting bracket:**
 - 8x M5x40 Countersunk Head Cap Screw
 - [8x Female Threaded Hex Standoff, 18-8 Stainless Steel, 10mm Hex, 16mm Long, M5 x 0.8mm Thread](https://www.mcmaster.com/94868A632/)
 - 8x M5X0.8 Chamfered Hexagon Thin Nut

**Front truck mounting bolts**
 - 4x M5x40 Countersunk Head Cap Screw
 - 4x M5X0.8 Chamfered Hexagon Thin Nut

**Electronics PCB (Arduino Nano + MDD10A Motor Driver)**
 - 6x M3X10 Countersunk Head Cap Screw
 - 6x M3X0.5 Chamfered Hexagon Thin Nut

<img width="1158" height="862" alt="Screenshot 2025-07-31 at 1 35 54 AM" src="https://github.com/user-attachments/assets/0d0292e6-b6a5-4813-8bd3-a21e87dc6f75" />
<img width="1919" height="1080" alt="Screenshot 2025-07-31 at 1 35 05 AM" src="https://github.com/user-attachments/assets/8b972db1-c798-4882-a5df-c8d9d3e8159f" />
<img width="2032" height="1105" alt="Screenshot 2025-07-30 at 7 45 59 PM" src="https://github.com/user-attachments/assets/e72adfaf-75a0-4322-b292-a12f30f251a5" />
<img width="1515" height="934" alt="Screenshot 2025-07-31 at 1 52 35 AM" src="https://github.com/user-attachments/assets/9fc5be30-6441-44b5-bed4-dc5fc761ca35" />

## 31/07/2025 - 3 hours
### Designing electronics schematic and firmware

![scootboot_schem](https://github.com/user-attachments/assets/88d3758d-c5ae-482e-ad5e-d1b97395409a)

- Ready to purchase parts and build
