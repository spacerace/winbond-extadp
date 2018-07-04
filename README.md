# Winbond's Extension Adapter Mode # 
 
This mode brings a subset of ISA to your LPT Port. 
 
With just a couple of logic devices you have digital IO or devices connected 
to your computer. 
 
This feature is available on some winbond controller chips. Here's a list: 
* w83877 
* w83877f 
 
The LPT-signals are not mapped to LPT-function anymore, they turn into a small 
subset of your ISA-bus. These are the signals: 
* `XD0-XD7  -  8bit data bus`
* `XA0-XA2  -  8bit address bus`
* `/XWR     -  low-active write signal`
* `/XRD     -  low-active read signal`
  
 
This is just a proof-of-concept test of extadp-mode. I couldn't find anything 
about this topic apart from a few datasheets on the internet. 
 
I tested all this on an Pentium 90 with ISA slots. I disabled everything on 
an ISA controller with a winbond chip, except for the LPT part. 
 
The OS was DamnSmallLinux with gcc-dsl-extension for compiling the code. 

# Datasheet W83877F #
All known information is in datasheet on pages: 53, 67, 68.
 
# Schematics #
 
Address decoding takes /XWR, /XRD and XA0-XA2. The logic ICs used are 74HCT138 
and 74HCT14. When decoding read and write signals 2x 74HCT138 is needed. 
This is the full decoding circuit for R and W. It gives a maximum of 8 output
and 8 input /CS signals.
![Address Decoding](https://github.com/spacerace/winbond-extadp/blob/master/schematics_png/addr_decode_rw_8bytes_color.png)
 
 
The full circuit for one 8bit output port is this, just add up to 7 more 
74HCT273 for 64 digital outputs. 
 
![8bit output port](https://github.com/spacerace/winbond-extadp/blob/master/schematics_png/74273_output_port.png)  


