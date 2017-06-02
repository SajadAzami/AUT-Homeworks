library IEEE;
use ieee.STD_LOGIC_1164.ALL;
use ieee.NUMERIC_STD.ALL;


entity shift_ent is
Port ( A : in STD_LOGIC_VECTOR (7 downto 0);
 B : in STD_LOGIC_VECTOR (7 downto 0);
 S : in STD_LOGIC;
 output : out STD_LOGIC_VECTOR (7 downto 0));
end shift_ent;

architecture shift_arch of shift_ent is
  signal temp: STD_LOGIC_VECTOR (7 downto 0):= "00000000";
  begin
  output <= A(7 - to_integer(unsigned(B)) downto 0) & temp(to_integer(unsigned(B)) - 1 downto 0) when S = '0' else 
       temp(to_integer(unsigned(B)) - 1 downto 0) & A(7 downto to_integer(unsigned(B))) when S = '1';
end;
