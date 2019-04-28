----------------------------------------------------------------------------------
-- Company: PWr
-- Engineer: Jakub Balcerzak, Stanislaw Straburzynski
-- 
-- Create Date:    10:51:28 04/03/2019 
-- Design Name:    UCiSW2 Projekt
-- Module Name:    FSM_BEEP - Behavioral 
-- Project Name:   Akcelerometr
-- Target Devices: Spartan3E Starter Board
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity FSM_BEEP is
    Port ( Error : in  STD_LOGIC_VECTOR (12 downto 0);
           VolUp : in STD_LOGIC;
           VolDown : in STD_LOGIC;
           Start : out  STD_LOGIC;
           Cmd : out  STD_LOGIC_VECTOR (3 downto 0);
           Addr : out  STD_LOGIC_VECTOR (3 downto 0);
           Data : out  STD_LOGIC_VECTOR (11 downto 0);
           Blank : out STD_LOGIC_VECTOR (15 downto 0);
           Clk_50MHz : in  STD_LOGIC);
end FSM_BEEP;

architecture Behavioral of FSM_BEEP is

	--two bit internal signal that describe error as 4 levels
   signal Err2b : unsigned(1 downto 0) := to_unsigned(0, 2);
	--Ts is the interval between next two Start impulses
   signal Ts : unsigned(10 downto 0) := to_unsigned(0,11);
	--start_counter stores current value of Clk_50MHz(mod)Ts counter
   signal start_counter : unsigned(10 downto 0) := to_unsigned(0,11);
	--obsolete signal for data_counter process (cannot use output signal Start directly)
   signal start_internal : std_logic := '0';
	--data_internal is as well number of current step as counter level
   signal data_internal : unsigned(4 downto 0) := to_unsigned(0, 5);
   
   signal volume : unsigned(3 downto 0) := to_unsigned(5, 4);
   
begin
----------------------------------------------------------------------------------------
   volume_level : process(Clk_50MHz, VolUp, VolDown)
   begin
      if rising_edge(Clk_50MHz) then
         if (VolUp = '1' and volume < to_unsigned(8, 4)) then
            volume <= volume + 1;
         elsif (VolDown = '1' and volume > to_unsigned(0, 4)) then
            volume <= volume - 1;
         end if;
      end if;
   end process;
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
   start_impulse : process(Clk_50MHz)
	--process realize Clk_50MHz(mod)Ts counter function
   begin
      if rising_edge(Clk_50MHz) then
         if (start_counter = Ts) then
            start_internal <= '1';
            start_counter <= to_unsigned(0,11);
         else
            start_internal <= '0';
            start_counter <= start_counter + 1;
         end if;
      end if;
   end process start_impulse;
----------------------------------------------------------------------------------------   
   data_counter : process(Clk_50MHz, start_internal)
	--counts the number of steps
	--there are 32 steps for one triangle signal generation
   begin
      if rising_edge(Clk_50MHz) and start_internal = '1' then
         if (data_internal = to_unsigned(31,5)) then
            data_internal <= to_unsigned(0,5);
         else
            data_internal <= data_internal + 1;
         end if;
      end if;
   end process data_counter;
----------------------------------------------------------------------------------------
	--Ts interval implies the signal frequency
	--as error level goes up the frequency is lower
   Ts<=  to_unsigned(195,11) when Err2b="00" else
         to_unsigned(390,11) when Err2b="01" else
         to_unsigned(781,11) when Err2b="10" else
         to_unsigned(1562,11) when Err2b="11";
----------------------------------------------------------------------------------------   
   --those signals are being described in parallel
   Start <= start_internal;
   Cmd <= "0011";
   Addr <= "1111";
----------------------------------------------------------------------------------------
   Data <=  std_logic_vector(data_internal)              & "0000000" when volume = "1000" else
            "0" & std_logic_vector(data_internal)        & "000000" when volume = "0111" else
            "00" & std_logic_vector(data_internal)       & "00000" when volume = "0110" else
            "000" & std_logic_vector(data_internal)      & "0000" when volume = "0101" else
            "0000" & std_logic_vector(data_internal)     & "000" when volume = "0100" else
            "00000" & std_logic_vector(data_internal)    & "00" when volume = "0011" else
            "000000" & std_logic_vector(data_internal)   & "0" when volume = "0010" else
            "0000000" & std_logic_vector(data_internal) when volume = "0001" else
            "000000000000";   
----------------------------------------------------------------------------------------
   Blank <= "1111111100000000" when volume = "1000" else
            "1111111110000000" when volume = "0111" else
            "1111111111000000" when volume = "0110" else
            "1111111111100000" when volume = "0101" else
            "1111111111110000" when volume = "0100" else
            "1111111111111000" when volume = "0011" else
            "1111111111111100" when volume = "0010" else
            "1111111111111110" when volume = "0001" else
            "1111111111111111";   
----------------------------------------------------------------------------------------
end Behavioral;

