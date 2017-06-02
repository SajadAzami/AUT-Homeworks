library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
 
entity full_adder_8bit_ent is
 Port ( A : in STD_LOGIC_VECTOR (7 downto 0);
 B : in STD_LOGIC_VECTOR (7 downto 0);
 Cin : in STD_LOGIC;
 S : out STD_LOGIC_VECTOR (7 downto 0);
 Cout : out STD_LOGIC);
end full_adder_8bit_ent;
 
architecture full_adder_8bit_arch of full_adder_8bit_ent is
component full_adder_ent is Port(A:in std_logic; 
                    B:in std_logic;
                    Cin:in std_logic; 
                    S:out std_logic;
                    Cout:out std_logic
                    );
end component;
signal c1 , c2 , c3, c4, c5, c6, c7: std_logic;
begin
  ha1: full_adder_ent port map(a(0),b(0),cin,S(0),c1);
  ha2: full_adder_ent port map(a(1),b(1),c1,S(1),c2);
  ha3: full_adder_ent port map(a(2),b(2),c2,S(2),c3);
  ha4: full_adder_ent port map(a(3),b(3),c3,S(3),c4);
  ha5: full_adder_ent port map(a(4),b(4),c4,S(4),c5);
  ha6: full_adder_ent port map(a(5),b(5),c5,S(5),c6);
  ha7: full_adder_ent port map(a(6),b(6),c6,S(6),c7);
  ha8: full_adder_ent port map(a(7),b(7),c7,S(7),cout);
 
end full_adder_8bit_arch;

