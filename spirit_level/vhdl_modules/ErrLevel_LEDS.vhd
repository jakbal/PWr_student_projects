----------------------------------------------------------------------------------
-- Company: PWr
-- Engineer: Jakub Balcerzak, Stanislaw Straburzynski
-- 
-- Create Date:    10:51:28 04/03/2019 
-- Design Name:    UCiSW2 Projekt
-- Module Name:    ErrLevel_LEDS - Behavioral 
-- Project Name:   Akcelerometr
-- Target Devices: Spartan3E Starter Board
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity ErrLevel_LEDS is
    Port ( Error : in  STD_LOGIC_VECTOR (12 downto 0);
           LED : out  STD_LOGIC_VECTOR (7 downto 0));
end ErrLevel_LEDS;

architecture Behavioral of ErrLevel_LEDS is

	--two bit internal signal that describes error as 4 levels
	signal Err2b : unsigned(1 downto 0) := to_unsigned(0, 2);

begin
----------------------------------------------------------------------------------------
   convert_error : process(Error)
	--converting the 13b error vector of square's position
   begin
      if (Unsigned(Error)<=to_unsigned(25,13)) then
         Err2b<="00";
      elsif (Unsigned(Error)<=to_unsigned(100,13)) then
         Err2b<="01";
      elsif (Unsigned(Error)<=to_unsigned(200,13)) then
         Err2b<="10";
      else
         Err2b<="11";
      end if;
   end process convert_error;
----------------------------------------------------------------------------------------
	--as more led lights means the error is higher
	LED<= "00011000" when Err2b="00" else
         "00111100" when Err2b="01" else
         "01111110" when Err2b="10" else
         "11111111" when Err2b="11";
---------------------------------------------------------------------------------------- 
end Behavioral;

