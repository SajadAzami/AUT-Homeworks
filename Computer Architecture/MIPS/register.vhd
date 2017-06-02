library IEEE;
use IEEE.std_logic_unsigned.all;
USE ieee.numeric_std.ALL;
use ieee.STD_LOGIC_1164.ALL;

entity reg_ent is
Port (enable, clk, rst : in  STD_LOGIC;
      Data_In : in STD_LOGIC_VECTOR (7 downto 0);
      Data_Out  : out STD_LOGIC_VECTOR (7 downto 0));
end reg_ent;

architecture reg_arch of reg_ent is
   
    begin
      process(clk,rst)
         variable temp : std_logic_vector(7 downto 0);
        begin
        if (clk'event and clk = '1') then
          if (rst = '1') then
              temp := "00000000";
          end if;
          if (enable = '1') then
            temp := Data_In;
        else temp := temp;
		  end if;
		  		  end if;
		  		  
      Data_Out <= temp;
      end process;
end reg_arch;