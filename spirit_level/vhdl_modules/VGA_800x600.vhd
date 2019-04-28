----------------------------------------------------------------------------------
-- Company: PWr
-- Engineer: Jakub Balcerzak, Stanislaw Straburzynski
-- 
-- Create Date:    10:51:28 04/03/2019 
-- Design Name:    UCiSW2 Projekt
-- Module Name:    VGA_800x600 - Behavioral 
-- Project Name:   Akcelerometr
-- Target Devices: Spartan3E Starter Board
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity VGA_800x600 is

    Port ( CLK_50MHz : in  STD_LOGIC;
           RGB : in  STD_LOGIC_VECTOR (2 downto 0);
           VGA_R : out  STD_LOGIC;
           VGA_G : out  STD_LOGIC;
           VGA_B : out  STD_LOGIC;
           VGA_HS : out  STD_LOGIC;
           VGA_VS : out  STD_LOGIC;
           PIX_X : out  STD_LOGIC_VECTOR (10 downto 0);
           PIX_Y : out  STD_LOGIC_VECTOR (9 downto 0)
           );
			  
end VGA_800x600;

architecture Behavioral of VGA_800x600 is

	--2 signals are describing horizontal and vertical pixel counters
	signal h_cnt : integer range 0 to 1039 := 0;
	signal v_cnt : integer range 0 to 665 := 0;
	
begin
----------------------------------------------------------------------------------------
counters :process(CLK_50MHz)
	begin
		if rising_edge(CLK_50MHz) then
			if (h_cnt = 1039) then
            h_cnt <= 0;
				if (v_cnt = 665) then
					v_cnt <= 0;
				else
               v_cnt <= v_cnt + 1;
				end if;
			else
				h_cnt <= h_cnt + 1;
			end if;
		end if;
	end process;
----------------------------------------------------------------------------------------
h_sync :process(h_cnt)
begin
   if h_cnt >= 0 and h_cnt < 120 then 
      VGA_HS <= '0';
   else 
      VGA_HS <= '1';
   end if;
end process;
----------------------------------------------------------------------------------------
v_sync :process(v_cnt)
begin
   if v_cnt >= 0 and v_cnt < 6 then 
      VGA_VS <= '0';
   else 
      VGA_VS <= '1';
   end if;
end process;
----------------------------------------------------------------------------------------
color :process(h_cnt, v_cnt, RGB)
	begin
      if (h_cnt >= 184 and h_cnt <= 983) and ( v_cnt >= 29 and v_cnt <= 628 )then
         VGA_R <= RGB(2);
			VGA_G <= RGB(1);
			VGA_B <= RGB(0);
      else 
			VGA_R <= '0';
			VGA_G <= '0';
			VGA_B <= '0';
		end if;

	end process;
----------------------------------------------------------------------------------------	
	PIX_X <= STD_LOGIC_VECTOR(to_unsigned(h_cnt,11));
   PIX_Y <= STD_LOGIC_VECTOR(to_unsigned(v_cnt,10));
----------------------------------------------------------------------------------------
end Behavioral;

