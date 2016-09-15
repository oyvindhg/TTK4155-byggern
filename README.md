# Byggern
Embedded code for a ping pong playing machine


NOTES DURING PROJECT

SRAM Data Memory
	
	When the XMEM interface is enabled, it will override the settings in the Data Direction registers
	corresponding to the ports dedicated to the interface. For details about this port override, see the
	alternate functions in section “I/O-Ports” on page 63. 
	
	The XMEM interface will autodetect whether an access is internal or external. If the access is external, 
	the XMEM interface will output address, data, and the control signals on the ports according to Figure 13 
	(this figure shows the wave forms without wait-states).

	When ALE goes from high to low, there is a valid address on AD7:0. ALE is low during a data transfer.
	
SRAM Adress choice

	We have chosen to set bit A0 (most significant bit) of the adress to constant ground. This is because
	the adress is not needed. We only need 2048 adresses for our SRAM. removing A0 gives us exactly (2^11).
	It is still included in the GAL-logic however, for correct decoding. If we need to include more sram
	in later stages of the project / future applications, then this adress-bit would need to be transferred 
	from our Atmega162

SFIOR - Special Function IO Register

	Bit 6 – XMBK: External Memory Bus Keeper Enable
	Writing XMBK to one enables the Bus Keeper on the AD7:0 lines. When the Bus Keeper is
	enabled, AD7:0 will keep the last driven value on the lines even if the XMEM interface has tristated
	the lines. Writing XMBK to zero disables the Bus Keeper. XMBK is not qualified with SRE,
	so even if the XMEM interface is disabled, the bus keepers are still activated as long as XMBK is
	one.
