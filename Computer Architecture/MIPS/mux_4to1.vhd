library IEEE;
use ieee.STD_LOGIC_1164.ALL;

entity mux_4to1_ent is
Port(
  Selector  : in  STD_LOGIC_VECTOR (1 downto 0);
  A, B, C, D : in STD_LOGIC_VECTOR (7 downto 0);
  y : out STD_LOGIC_VECTOR (7 downto 0)
);
end mux_4to1_ent;

architecture mux_4to1_arch of mux_4to1_ent is 
begin 
    y <= A when Selector = "00" else 
     B when Selector = "01" else 
     C when Selector = "10" else 
     D when Selector = "11";
end mux_4to1_arch;