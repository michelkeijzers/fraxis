# ESP32 Pin Management

## Kicad mismatch

There is a mismatch between both available symbols on the schema editor and the (single) foot print.

Below is the mapping which has been changed to support the correct foot print.

Order is top/bottom, left to right for a landscape placed ESP32 footprint.

| Footprint Name          | Pin Nr | (Old) Schematics Name  | Function |
| ----------------------- | ------ | ---------------------- | -------- |
| (Bottom, left to right) | -      | -                      | -        |
| 3V3                     | 1      | LNA_IN/RF              |          |
| 3V3                     | 2      |                        |          |
| EN/RESET                | 3      |                        |          |
| GPIO4                   | 4      |                        |          |
| GPIO5                   | 5      | GPIO0/BOOT             |          |
| GPIO6                   | 6      | GPIO1/ADC1_CH0         |          |
| GPIO7                   | 7      | GPIO2/ADC1_CH1         |          |
| GPIO15                  | 8      | GPIO3/ADC1_CH2         |          |
| GPIO16                  | 9      | GPIO4/ADC1_CH3         |          |
| GPIO17                  | 10     | GPIO5/ADC1_CH4         |          |
| GPIO18                  | 11     | GPIO6/ADC1_CH5         |          |
| GPIO8                   | 12     | GPIO7/ADC1_CH6         |          |
| GPIO3                   | 13     | GPIO8/ADC1_CH7         |          |
| GPIO46                  | 14     | GPIO9/ADC1_CH8         |          |
| GPIO9                   | 15     | ??                     |          |
| GPIO10                  | 16     | GPIO11/ADC2_CH0        |          |
| GPIO11                  | 17     | GPIO12/ADC2_CH1        |          |
| GPIO12                  | 18     | GPIO13/ADC2_CH2        |          |
| GPIO13                  | 19     | GPIO14/ADC2_CH3        |          |
| GPIO14                  | 20     |                        |          |
| 5V                      | 21     | GPIO15/ADC2_CH4/XTAL.. |          |
| GND                     | 22     | GPIO16/ADC2_CH5/XTAL.. |          |
| (Top, right to left)    | -      | -                      | -        |
| GND                     | 23     | GPIO17/ADC2_CH6        |          |
| GND                     | 24     | GPIO18/ADC2_CH7        |          |
| GPIO19                  | 25     |                        |          |
| GPIO20                  | 26     |                        |          |
| GPIO21                  | 27     | GPIO21                 |          |
| GPIO47                  | 28     | GPIO26/SPI_CS1         |          |
| GPIO48                  | 29     |                        |          |
| GPIO45                  | 30     | GPIO27/SPIHD           |          |
| GPIO0                   | 31     | GPIO28/SPIWP           |          |
| GPIO35                  | 32     | GPIO29/SPICS0          |          |
| GPIO36                  | 33     | GPIO30/SPICLK          |          |
| GPIO37                  | 34     | GPIO31/SPIQ            |          |
| GPIO38                  | 35     | GPIO32/SPID            |          |
| GPIO39/MTCK             | 36     | GPIO48/SPICLK_N        |          |
| GPIO40/MTDO             | 37     | GPIO47/SPICLK_P        |          |
| GPIO41/MTDI             | 38     | SPIO33                 |          |
| GPIO42/MTMS             | 39     | SPIO34                 |          |
| GPIO02                  | 40     | GPIO35                 |          |
| GPIO01                  | 41     | GPIO36                 |          |
| GPIO44/UORXD            | 42     | GPIO37                 |          |
| GPIO43/UOTXD            | 43     | GPIO38                 |          |
| GND                     | 44     | GND                    |          |
