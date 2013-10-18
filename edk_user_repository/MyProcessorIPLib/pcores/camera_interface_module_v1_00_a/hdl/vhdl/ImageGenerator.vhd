----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    17:12:04 12/18/2012 
-- Design Name: 
-- Module Name:    ImageGenerator - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.std_logic_unsigned.all;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity ImageGenerator is
	 generic (
	         width : integer:= 32; --640;
				height: integer:= 32 --480
				);
	 
    Port ( clk : in  STD_LOGIC;
           reset : in  STD_LOGIC;
           startingValue : in  STD_LOGIC_VECTOR (7 downto 0);
           Pixel_Data : out  STD_LOGIC_VECTOR (7 downto 0);
           Pixel_Clk : out  STD_LOGIC;
           EOL : out  STD_LOGIC;
           EOF : out  STD_LOGIC);
end ImageGenerator;

architecture Behavioral of ImageGenerator is
	
	
	signal pixel_data_i : std_logic_vector (7 downto 0);
	signal eol_i : std_logic;
	signal eof_i : std_logic;
	
	signal x_counter: integer;
	signal y_counter: integer;
	
begin

	px_count: process (clk, reset)
	begin
		if reset = '1' then
			x_counter <= 0;
			y_counter <= 0;
			eol_i <= '0';
			eof_i <= '0';
			pixel_data_i <= (others=>'0');
		else
			if clk'event and clk = '1' then
				eol_i <= '0';
				eof_i <= '0';
				x_counter <= x_counter + 1;
				pixel_data_i <= pixel_data_i + startingValue + '1';
				if x_counter = width then
					x_counter <= 0;
					eol_i <= '1';
					y_counter <= y_counter + 1;
					if y_counter = height then
						y_counter <= 0;
						eof_i <= '1';
					else
						eof_i <= '0';
					end if;
				else
					eol_i <= '0';
				end if;				
			end if;
		end if;	
	end process;
	
	eol <= not eol_i;
	eof <= not eof_i;
	pixel_data <= pixel_data_i;
	pixel_clk  <= clk;
	

end Behavioral;
