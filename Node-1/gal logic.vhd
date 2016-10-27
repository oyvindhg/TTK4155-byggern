library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity address_decoder is
	Port (
		a11 : In std_logic;
		a10 : In std_logic;
		a9  : In std_logic;

		ram_cs  : Out std_logic;
		adc_cs  : Out std_logic;
		oled_cs : Out std_logic;
		oled_dc : Out std_logic
	);
	attribute LOC : string;
	attribute LOC of ram_cs  : signal is "P19";
	attribute LOC of adc_cs  : signal is "P18";
	attribute LOC of oled_cs : signal is "P17";
	attribute LOC of oled_dc : signal is "P16";

	attribute LOC of a11 : signal is "P1";
	attribute LOC of a10 : signal is "P2";
	attribute LOC of a9  : signal is "P3";
end address_decoder;

architecture behave of address_decoder is begin
	ram_cs <= a11;
	adc_cs <= NOT (NOT a11 AND a10);
	oled_cs <= NOT (NOT a11 AND NOT a10);
	oled_dc <= NOT a11 AND NOT a10 AND a9;
end behave;

