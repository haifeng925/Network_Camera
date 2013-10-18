--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   11:11:06 02/27/2013
-- Design Name:   
-- Module Name:   /home/marco/xilinx/14.3/ISE_DS/edk_user_repository/MyProcessorIPLib/pcores/camera_interface_module_v1_00_a/hdl/vhdl/my_deserializer_tb.vhd
-- Project Name:  camera_interface_module
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: my_deserializer
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
 
ENTITY my_deserializer_tb IS
END my_deserializer_tb;
 
ARCHITECTURE behavior OF my_deserializer_tb IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT my_deserializer
    PORT(
         RESET : IN  std_logic;
         BASE_ADDRESS : IN  std_logic_vector(0 to 31);
         START : IN  std_logic;
         PIXEL_DATA : IN  std_logic_vector(0 to 7);
         PIXEL_CLOCK : IN  std_logic;
         END_OF_LINE : IN  std_logic;
         END_OF_FRAME : IN  std_logic;
         TARGET_ADDRESS : OUT  std_logic_vector(0 to 31);
         OUT_DATA : OUT  std_logic_vector(0 to 31);
         OUT_DATA_VALID : OUT  std_logic;
         FRAME_FINISHED : OUT  std_logic
        );
    END COMPONENT;
    

   --Inputs
   signal RESET : std_logic := '0';
   signal BASE_ADDRESS : std_logic_vector(0 to 31) := (others => '0');
   signal START : std_logic := '0';
   signal PIXEL_DATA : std_logic_vector(0 to 7) := (others => '0');
   signal PIXEL_CLOCK : std_logic := '0';
   signal END_OF_LINE : std_logic := '0';
   signal END_OF_FRAME : std_logic := '0';

 	--Outputs
   signal TARGET_ADDRESS : std_logic_vector(0 to 31);
   signal OUT_DATA : std_logic_vector(0 to 31);
   signal OUT_DATA_VALID : std_logic;
   signal FRAME_FINISHED : std_logic;

   -- Clock period definitions
   constant PIXEL_CLOCK_period : time := 1 us;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: my_deserializer PORT MAP (
          RESET => RESET,
          BASE_ADDRESS => BASE_ADDRESS,
          START => START,
          PIXEL_DATA => PIXEL_DATA,
          PIXEL_CLOCK => PIXEL_CLOCK,
          END_OF_LINE => END_OF_LINE,
          END_OF_FRAME => END_OF_FRAME,
          TARGET_ADDRESS => TARGET_ADDRESS,
          OUT_DATA => OUT_DATA,
          OUT_DATA_VALID => OUT_DATA_VALID,
          FRAME_FINISHED => FRAME_FINISHED
        );

   -- Clock process definitions
   PIXEL_CLOCK_process :process
   begin
		PIXEL_CLOCK <= '1';
		wait for PIXEL_CLOCK_period/2;
		PIXEL_CLOCK <= '0';
		wait for PIXEL_CLOCK_period/2;
   end process;
	
	
   EOL_process :process
   begin
		END_OF_LINE <= '0';
		END_OF_FRAME <= '0';
		wait for PIXEL_CLOCK_period*2;
		END_OF_LINE <= '1';
		END_OF_FRAME <= '1';
		wait for PIXEL_CLOCK_period*8;
		END_OF_LINE <= '0';
		wait for PIXEL_CLOCK_period*2;
		END_OF_LINE <= '1';
		wait for PIXEL_CLOCK_period*8;
   end process;
 

   -- Stimulus process
   stim_proc: process
   begin		
      wait for PIXEL_CLOCK_period;
      -- hold reset state for 100 ns.
		RESET <='1';
      wait for PIXEL_CLOCK_period;	
		RESET <='0';
      wait for PIXEL_CLOCK_period*9;

      -- insert stimulus here 
		BASE_ADDRESS(28 to 31) <= "1000";
		START <= '0';
		PIXEL_DATA <= "00000001";
      wait for PIXEL_CLOCK_period*0.8;
		START <= '1';
		
		wait for PIXEL_CLOCK_period*0.2;
      wait for PIXEL_CLOCK_period;
		START <= '0';
      wait for PIXEL_CLOCK_period*7;
		
		
		
		
		
      wait;
   end process;

END;
