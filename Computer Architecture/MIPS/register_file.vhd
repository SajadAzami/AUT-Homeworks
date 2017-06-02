library IEEE;
use IEEE.std_logic_unsigned.all;
USE ieee.numeric_std.ALL;
use ieee.STD_LOGIC_1164.ALL;

entity register_file_ent is
Port ( R, W, clk, rst : in  STD_LOGIC;
      read1, read2, write_address : in STD_LOGIC_VECTOR (2 downto 0);
      write_data : in STD_LOGIC_VECTOR (7 downto 0);
      read_out_1, read_out_2 : out STD_LOGIC_VECTOR (7 downto 0));
end register_file_ent;

architecture register_file_arch of register_file_ent is
  type memory_array is array(0 to 7) of STD_LOGIC_VECTOR (7 downto 0);
  signal mem_signal : memory_array;
    begin
      process(clk)
        begin
        if (clk'event and clk = '1') then
		  if ( rst = '1')  then
          mem_signal <= ("00000010", "00000010", "00000000", "00000010", "11100000",
           "00000000", "00000000", "00000001");
        elsif ( R = '1') then
          read_out_1 <= mem_signal(to_integer(unsigned(read1)));
          read_out_2 <= mem_signal(to_integer(unsigned(read2)));
        elsif ( W = '1' ) then
          mem_signal(to_integer(unsigned(write_address))) <= write_data;
        end if;
		  end if;
      end process;
end register_file_arch;
