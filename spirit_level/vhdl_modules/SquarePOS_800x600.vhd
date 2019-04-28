----------------------------------------------------------------------------------
-- Company: PWr
-- Engineer: Jakub Balcerzak, Stanislaw Straburzynski
-- 
-- Create Date:    10:52:19 04/03/2019 
-- Design Name:    UCiSW2 Projekt
-- Module Name:    SquarePOS_800x600 - Behavioral 
-- Project Name:   Akcelerometr
-- Target Devices: Spartan3E Starter Board
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity SquarePOS_800x600 is
    Port ( PIX_X : in  STD_LOGIC_VECTOR (10 downto 0);
           PIX_Y : in  STD_LOGIC_VECTOR (9 downto 0);
		     X : in STD_LOGIC_VECTOR (15 downto 0);
		     Y : in STD_LOGIC_VECTOR (15 downto 0);
		     Error : out STD_LOGIC_VECTOR (12 downto 0);
		     SetOffset : in STD_LOGIC;
           Clk_50MHz : in STD_LOGIC;
           RGB : out  STD_LOGIC_VECTOR (2 downto 0));
end SquarePOS_800x600;

architecture Behavioral of SquarePOS_800x600 is

   --2 signals describes the middle internal point of the square
	signal Square_X : signed(12 downto 0) := to_signed(584, 13);
	signal Square_Y : signed(12 downto 0) := to_signed(329, 13);
   --2 signals contains value of offset that calibrates X Y axis
	signal X_OFF : signed(9 downto 0) := to_signed(0, 10);
	signal Y_OFF : signed(9 downto 0) := to_signed(0, 10);
   --2 signals that are obsolete to proceede with pixel's coordinates comparisions
   signal tempPIX_X : unsigned(11 downto 0) := to_unsigned(0, 12);
	signal tempPIX_Y : unsigned(10 downto 0) := to_unsigned(0, 11);
	
begin
----------------------------------------------------------------------------------------
	read_accel : process(Clk_50MHz, PIX_X, PIX_Y) --proces dziala
   --once per screen refreshment the Square_X, Square_Y are being updated
   begin
		if rising_edge(Clk_50MHz) and tempPIX_X = to_unsigned(983, 12) and tempPIX_Y = to_unsigned(628, 11)  then
			Square_X <= to_signed(584, 13) - signed(X (9 downto 0)) + X_OFF;
			Square_Y <= to_signed(329, 13) + signed(Y (9 downto 0)) - Y_OFF;
		end if;
	end process read_accel;
----------------------------------------------------------------------------------------
	set_offset : process(Clk_50MHz, SetOffset) --proces dziala poprawnie
   --when btn_north pressed accelerometer is being calibrated
	begin
		if rising_edge(Clk_50MHz) and SetOffset='1' then
			X_OFF <= signed(X (9 downto 0));
			Y_OFF <= signed(Y (9 downto 0));
		end if;
	end process set_offset;
----------------------------------------------------------------------------------------
	pixel_color : process(PIX_X, PIX_Y) -- proces dziala
   --process controls the color of pixels
   --responsible for displaying square
	begin   
		if (signed(tempPIX_X) >= (Square_X - to_signed(50,7)) and signed(tempPIX_X) <= (Square_X + to_signed(50,7))
		    and signed(tempPIX_Y) >= (Square_Y - to_signed(50,7)) and signed(tempPIX_Y) <= (Square_Y + to_signed(50,7))) then
			RGB <= "010";
      elsif (tempPIX_X = to_unsigned(584,12) or tempPIX_Y = to_unsigned(329, 11)) then
         RGB <= "111";
      else
         RGB <= "101";
		end if;
	end process pixel_color;
----------------------------------------------------------------------------------------
   set_error : process(Square_X, Square_Y)
   --sets higher abs value of move in X or Y axis
   begin
      if (abs(Square_X - to_signed(584,13)) > abs(Square_Y - to_signed(329,13))) then
         Error <= std_logic_vector(abs(Square_X - to_signed(584,13)));
      else
         Error <= std_logic_vector(abs(Square_Y - to_signed(329,13)));
      end if;
   end process set_error;
----------------------------------------------------------------------------------------
   --those signals are being recounted in parallel
   tempPIX_X(10 downto 0) <= unsigned(PIX_X);
   tempPIX_Y(9 downto 0) <= unsigned(PIX_Y);
----------------------------------------------------------------------------------------
end Behavioral;