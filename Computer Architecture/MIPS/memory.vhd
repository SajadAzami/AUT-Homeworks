library IEEE;
use IEEE.std_logic_unsigned.all;
USE ieee.numeric_std.ALL;
use ieee.STD_LOGIC_1164.ALL;

entity memory_ent is
Port ( R, W, clk, rst : in  STD_LOGIC;
      Address : in STD_LOGIC_VECTOR (7 downto 0);
      Data_In : in STD_LOGIC_VECTOR (7 downto 0);
      Data_Out  : out STD_LOGIC_VECTOR (7 downto 0));
end memory_ent;

architecture memory_arch of memory_ent is
  type memory_array is array(0 to 255) of STD_LOGIC_VECTOR (7 downto 0);
  signal mem_signal : memory_array;
    begin
      process(clk)
        begin
        if (clk'event and clk = '1') then
		  if ( rst = '1')  then
          --ITypes: mem_signal <= ("00000000", "01010000", "00000001", "00101001", "00000000", "01101010", "00000000", "01110011", "00000000", "01111100", others => "00000000");
          mem_signal <= ("01000111","01000010","01010111","10000011", "01111110" , "01000101","10001110","01000011","10010010","11000101","10100010","01100000", others => "00000000");
        elsif ( R = '1') then
          Data_Out <= mem_signal(to_integer(unsigned(Address)));
        elsif ( W = '1' ) then
          mem_signal(to_integer(unsigned(Address))) <= Data_In;
        end if;
		  end if;
      end process;
end memory_arch;