 library IEEE;
use ieee.STD_LOGIC_1164.ALL;
use IEEE.std_logic_unsigned.all;
use ieee.numeric_std.all;

entity data_path_ent is
Port ( counter_enable, clk, reset, enable, s0, s1, load, w, r : in  std_logic;
            data_address : in std_logic_vector(3 downto 0);
           less, equal ,greater  : out std_logic;
           overflow : out std_logic);
end data_path_ent;

architecture data_path_arch of data_path_ent is
    component memory_ent is Port ( R, W, clk, rst : in  STD_LOGIC;
                    Address : in STD_LOGIC_VECTOR (7 downto 0);
                    Data_In : in STD_LOGIC_VECTOR (3 downto 0);
                    Data_Out  : out STD_LOGIC_VECTOR (3 downto 0));
    end component;
    component mux_2to1_ent is Port(
                    Selector  : in  STD_LOGIC;
                    A, B : in STD_LOGIC_VECTOR (3 downto 0);
                    y : out STD_LOGIC_VECTOR (3 downto 0)
                    );
    end component;
    component full_adder4bit_ent is Port ( A : in STD_LOGIC_VECTOR (3 downto 0);
                   B : in STD_LOGIC_VECTOR (3 downto 0);
                   Cin : in STD_LOGIC;
                   S : out STD_LOGIC_VECTOR (3 downto 0);
                   Cout : out STD_LOGIC);
    end component;
    component reg_ent is Port (enable, clk, rst : in  STD_LOGIC;
                    Data_In : in STD_LOGIC_VECTOR (3 downto 0);
                    Data_Out  : out STD_LOGIC_VECTOR (3 downto 0));
    end component;
    component comparator_ent is Port ( input_a, input_b : in  std_logic_vector(3 downto 0);
           less,  equal,greater  : out std_logic);
    end component;
    
    component counter_ent is Port ( clk, reset, direction, enable : in  std_logic;
           output  : out std_logic_vector(3 downto 0);
           overflow : out std_logic);
    end component;
    
    signal cout_sig : std_logic;
    signal mux1_output, counter_output, mux2_output, reg_output, mem_output, fa_output : std_logic_vector(3 downto 0);
      begin
        counter: counter_ent port map(clk, reset, '1', counter_enable, counter_output, overflow);
        mux1: mux_2to1_ent port map(s0, data_address, counter_output, mux1_output);
        ram: memory_ent port map(r, w, clk, reset, mux1_output, mux2_output, mem_output);
        mux2: mux_2to1_ent port map(s1, fa_output, "0000", mux2_output);
        fa: full_adder4bit_ent port map(mem_output, "0001", '0', fa_output, cout_sig);
        reg: reg_ent port map(load, clk, '0', mem_output, reg_output);
        comparator: comparator_ent port map(reg_output, mem_output, less,  equal,greater);
  end data_path_arch;

