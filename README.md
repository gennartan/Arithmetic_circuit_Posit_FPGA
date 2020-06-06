# Arithmetic_circuit_Posit_FPGA

Implementation of __Arithmetic circuit__ in FPGA using __Posit__ representation. This repository is linked to a software implementation at [https://github.com/gennartan/spn_sw](https://github.com/gennartan/spn_sw)

## State of the Art

### Posit representation

The posit representation is an alternative method to floating point representation to write numbers in binary. The main difference is that the exponent is encoded using a variable size, which increase the range of numbers (Maximum exponent value is higher), and increase the precision when numbers are closer to 1 (More space for mantissa bits). More details can be found [here](https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=4&cad=rja&uact=8&ved=2ahUKEwjuuLry5_noAhVQsaQKHbURC0QQFjADegQIAhAB&url=http%3A%2F%2Fwww.johngustafson.net%2Fpdfs%2FBeatingFloatingPoint.pdf&usg=AOvVaw0HQ2rZQ3LnyQJrf-2Wg6z3).

In this project, there is a working implementation of posit addition and multiplication in hardware (system verilog). This implementation works properly except for the rounding after a multiplication.

### Arithmetic circuit (or Sum product network)

A sum product network is a new deep network model for graphical probabilistic inference. A lot of informations about SPNs can be found at [https://github.com/arranger1044/awesome-spn](https://github.com/arranger1044/awesome-spn).

The SPNs I used in this work comes from [https://github.com/UCLA-StarAI/Circuit-Model-Zoo](https://github.com/UCLA-StarAI/Circuit-Model-Zoo).


## Implementation

### Directory structure

```
.
+-- Arithmetic_circuit.srcs
|	+-- sources_1
|		+-- bd (don't care)
|		+-- new (Contains the useful sources in verilog and system verilog)
|			+-- sw (Python code to generate SPNs in FPGA from PSDD file)
|	+-- constrs_1 (Design constraints)
|	+-- sim_*
|		+-- Simulation sources for every part of the implementation
+-- Arithmetic_circuit.*
|	+-- (We do not care about content of every other directory)
```

### Usage

1. Edit the python file Arithmetic_circuit.srcs/sources_1/new/sw/main.py with the parameter you want for your SPN.

2. Open Vivado and generate bitstream.

3. Launch SDK, adapt the software to your usage and run it.