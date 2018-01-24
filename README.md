# GC-C-IRMS_Data_Model

This software was developed in conjunction with a GC-C-IRMS instrument designed to measure the carbon isotope ratio of the methane, ethane, and propane present in a gas sample.  A GC-C-IRMS consists of three distinct modules: a Gas Chromatograph (GC), a Combustion Oven (C), and an Isotope Ratio Mass Spectrometer (IRMS). The GC module first accepts the sample and separates the three hydrocarbon components of interest. As the components exit the GC, they are then directed to the second module, a Combustion Oven maintained at a high temperature and supplied with auxiliary oxygen. This results in oxidation of the hydrocarbons to water and carbon dioxide. The water is removed, while the carbon dioxide is finally sent to the mass spectrometer, which directly measures the carbon isotope ratio of the carbon dioxide, and thus, indirectly measures that of the three hydrocarbons.

The software was designed to model the measurement process, accounting for all potential sources of noise and their contribution to the total.  The primary goal was to determine the total signal and allowable noise level neccessary in order to produce the desired instrument precision.  Additional goals included testing how reductions in different noise sources affected performance, the effect of other measurement parameters, etc.

This software outputs artifical chromatograms in the form of sets of .asc files which can be processed using the GC-C-IRMS_Data_Processor package or [PeakSimple.](http://www.srigc.com/pages/software_downloads/)


Created by Blake Leonard.

blake@leonardlabs.net