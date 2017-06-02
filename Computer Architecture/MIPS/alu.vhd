library IEEE;
use ieee.STD_LOGIC_1164.ALL;

entity alu_ent is
Port(
  Selector  : in  STD_LOGIC_VECTOR (3 downto 0);
  A, B : in STD_LOGIC_VECTOR (7 downto 0);
  cin : in STD_LOGIC;
  cout, branch : out STD_LOGIC;
  output : out STD_LOGIC_VECTOR (7 downto 0)
);
end alu_ent;

architecture alu_arch of alu_ent is 
component full_adder_8bit_ent is Port ( A : in STD_LOGIC_VECTOR (7 downto 0);
 B : in STD_LOGIC_VECTOR (7 downto 0);
 Cin : in STD_LOGIC;
 S : out STD_LOGIC_VECTOR (7 downto 0);
 Cout : out STD_LOGIC);
end component;

component shift_ent is Port ( A : in STD_LOGIC_VECTOR (7 downto 0);
 B : in STD_LOGIC_VECTOR (7 downto 0);
 S : in STD_LOGIC;
 output : out STD_LOGIC_VECTOR (7 downto 0));
end component;

signal output_fa, output_rshift, output_lshift, output_sub, output_slt, output_xor, output_nor, output_or, output_and: STD_LOGIC_VECTOR (7 downto 0);
signal b_not: STD_LOGIC_VECTOR (7 downto 0);
begin 
  b_not <= not B;
  output_or <= A or B;
  output_and <= A and B;
  output_xor <= A xor B;
  output_nor <= A nor B;
  output_slt <= "00000000" when A > B else "00000001";
  rshift: shift_ent port map(A,B,'1',output_rshift);
  lshift: shift_ent port map(A,B,'0',output_lshift);
  
  fa: full_adder_8bit_ent port map(A, B, cin, output_fa, Cout);
  sub: full_adder_8bit_ent port map(A, b_not, '1', output_sub, Cout);
    
  output <= output_fa when Selector = "0000" else 
  output_sub when Selector = "0001" else 
  output_or when Selector = "0011" else 
  output_and when Selector = "0010" else
  output_xor when Selector = "0100" else
  output_nor when Selector = "0101" else
  output_slt when Selector = "0110" else
  output_rshift when Selector = "0111" else 
  output_lshift when Selector = "1000" else
  "00000000";
  branch <= '1' when (Selector = "1001" and A = B) or (Selector = "1010" and not(A = B))
   or (Selector = "1011" and A < B) or (Selector = "1100" and A > B) 
   or (Selector = "1101" and A <= B) or (Selector = "1110" and A >= B) else '0';

  
end;