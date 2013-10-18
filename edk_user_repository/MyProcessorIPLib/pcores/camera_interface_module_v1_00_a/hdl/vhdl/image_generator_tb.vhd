--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   10:54:33 02/27/2013
-- Design Name:   
-- Module Name:   /home/marco/xilinx/14.3/ISE_DS/edk_user_repository/MyProcessorIPLib/pcores/camera_interface_module_v1_00_a/hdl/vhdl/image_generator_tb.vhd
-- Project Name:  camera_interface_module
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: ImageGenerator
-- 
-- Dependencies:
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
--
-- Notes: 
-- This testbench has been automatically generated using types std_logic and
-- std_logic_vector for the ports of the unit under test.  Xilinx recommends
-- that these types always be used for the top-level I/O of a design in order
-- to guarantee that the testbench will bind correctly to the post-implementation 
-- simulation model.
--------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY image_generator_tb IS
END image_generator_tb;
 
ARCHITECTURE behavior OF image_generator_tb IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT ImageGenerator
    PORT(
         clk : IN  std_logic;
         reset : IN  std_logic;
         startingValue : IN  std_logic_vector(7 downto 0);
         Pixel_Data : OUT  std_logic_vector(7 downto 0);
         Pixel_Clk : OUT  std_logic;
         EOL : OUT  std_logic;
         EOF : OUT  std_logic
        );
    END COMPONENT;
    

   --Inputs
   signal clk : std_logic := '0';
   signal reset : std_logic := '0';
   signal startingValue : std_logic_vector(7 downto 0) := (others => '0');

 	--Outputs
   signal Pixel_Data : std_logic_vector(7 downto 0);
   signal Pixel_Clk : std_logic;
   signal EOL : std_logic;
   signal EOF : std_logic;

   -- Clock period definitions
   constant clk_period : time := 1 us;
   constant Pixel_Clk_period : time := 1 us;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: ImageGenerator PORT MAP (
          clk => clk,
          reset => reset,
          startingValue => startingValue,
          Pixel_Data => Pixel_Data,
          Pixel_Clk => Pixel_Clk,
          EOL => EOL,
          EOF => EOF
        );

   -- Clock process definitions
   clk_process :process
   begin
		clk <= '0';
		wait for clk_period/2;
		clk <= '1';
		wait for clk_period/2;
   end process;
 
   Pixel_Clk_process :process
   begin
		Pixel_Clk <= '0';
		wait for Pixel_Clk_period/2;
		Pixel_Clk <= '1';
		wait for Pixel_Clk_period/2;
   end process;
 

   -- Stimulus process
   stim_proc: process
   begin		
      wait for clk_period*10;
      -- insert stimulus here 
		reset <= '1';
		wait for clk_period;
		reset <= '0';
		wait for clk_period*5;
		startingValue <= (others=>'0');
		wait for clk_period*5;
		
		

      wait;
   end process;

END;
