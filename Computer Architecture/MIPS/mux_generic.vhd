library IEEE;
use ieee.STD_LOGIC_1164.ALL;

entity mux_2to1_generic_ent is generic(n:integer);
Port(
  Selector : in  STD_LOGIC;
  A, B : in STD_LOGIC_VECTOR (n downto 0);
  y : out STD_LOGIC_VECTOR (n downto 0)
);
end mux_2to1_generic_ent;

architecture mux_2to1_generic_arch of mux_2to1_generic_ent is 
begin 
    y <= A when Selector = '0' else 
     B when Selector = '1';
end mux_2to1_generic_arch;