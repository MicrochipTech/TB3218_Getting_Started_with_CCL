(TB3218) ATmega4809 CCL Examples
===

This repository contains examples of bare metal source code for Configurable Custom Logic (CCL) as described in TB3218 document from Microchip.
The repository contains an Atmel Studio Solution with multiple projects inside. Make sure you have the necessary tools:
1. ATmega4809 device (recommended is evaluation board ATmega4809 X-plained PRO)
2. Atmel Studio
3. ATmega4809 Device Packs

The following examples are inside this repository:
1. Logic AND Gate: how to use CCL to implement a simple logic AND gate
2. State Decoder: how to use CCL combinational logic to detect a specific state of the external signals
3. SR Latch: show how to use internal CCL sequential logic to create an SR Latch
4. Manchester Encoder: demonstrates how to use CCL in combination with other peripherals to implement a Manchester encoder