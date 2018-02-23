# Winbond's Extension Adapter Mode #

This mode brings a subset of ISA to your LPT Port. 
With just a couple of logic devices you have digital IO or Soundcards, ...
on your LPT port.

This is just a proof-of-concept test of extadp-mode. I couldn't find anything
about this topic apart from a few datasheets on the internet.

I tested all this on an Pentium 90 with ISA slots. I disabled everything on
an ISA controller with a winbond chip, except for the LPT part.
The OS was DamnSmallLinux with gcc-dsl-extension for compiling the code.
