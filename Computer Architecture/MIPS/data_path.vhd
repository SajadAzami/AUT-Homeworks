 library IEEE;
use ieee.STD_LOGIC_1164.ALL;
use IEEE.std_logic_unsigned.all;
use ieee.numeric_std.all;

entity data_path_ent is
Port ( clk, rst : in  std_logic;
           controller_pc_enable, controller_IRWirteL, controller_IRWirteH, controller_ALUSrcA, controller_rf_write, controller_rf_read, controller_MemtoReg, controller_RegDst, controller_IorD, controller_memread, controller_memwrite : in std_logic;
           controller_PCSource, controller_ALUSrcB : in std_logic_vector(1 downto 0);
           controller_alu_selector : in std_logic_vector(3 downto 0);
           branch : out std_logic;
           function_code : out std_logic_vector(2 downto 0);
           opcode : out std_logic_vector(3 downto 0)
           );
end data_path_ent;

architecture data_path_arch of data_path_ent is
  
    component memory_ent is Port ( R, W, clk, rst : in  STD_LOGIC;
      Address : in STD_LOGIC_VECTOR (7 downto 0);
      Data_In : in STD_LOGIC_VECTOR (7 downto 0);
      Data_Out  : out STD_LOGIC_VECTOR (7 downto 0));
    end component;
    
    component mux_2to1_generic_ent is generic(n:integer); Port(
      Selector : in  STD_LOGIC;
      A, B : in STD_LOGIC_VECTOR (n downto 0);
      y : out STD_LOGIC_VECTOR (n downto 0));
    end component;
    
    component mux_4to1_ent is Port(
      Selector  : in  STD_LOGIC_VECTOR (1 downto 0);
      A, B, C, D : in STD_LOGIC_VECTOR (7 downto 0);
      y : out STD_LOGIC_VECTOR (7 downto 0));
    end component;
    
    component reg_ent is Port (enable, clk, rst : in  STD_LOGIC;
      Data_In : in STD_LOGIC_VECTOR (7 downto 0);
      Data_Out  : out STD_LOGIC_VECTOR (7 downto 0));
    end component;
    
    component register_file_ent is Port ( R, W, clk, rst : in  STD_LOGIC;
      read1, read2, write_address : in STD_LOGIC_VECTOR (2 downto 0);
      write_data : in STD_LOGIC_VECTOR (7 downto 0);
      read_out_1, read_out_2 : out STD_LOGIC_VECTOR (7 downto 0));
    end component;
    
    component alu_ent is Port(
      Selector  : in  STD_LOGIC_VECTOR (3 downto 0);
      A, B : in STD_LOGIC_VECTOR (7 downto 0);
      cin : in STD_LOGIC;
      cout, branch : out STD_LOGIC;
      output : out STD_LOGIC_VECTOR (7 downto 0));
    end component;

    signal alu_cout : std_logic;
    signal mux1_output : std_logic_vector(2 downto 0);
    signal ir_out : std_logic_vector(15 downto 0);
    signal alu_output, mux4_output, zero_concated, mux3_output, mux2_output, memory_out, read_out_1, read_out_2, mux5_output, pc_output, mux0_output : std_logic_vector(7 downto 0);
      begin
        opcode <= ir_out(15 downto 12);
        function_code <= ir_out(2 downto 0);
        zero_concated <= "00" & ir_out(5 downto 0);
        pc: reg_ent port map (controller_pc_enable, clk, rst, mux5_output, pc_output);
        mux0: mux_2to1_generic_ent generic map (7) port map (controller_IorD, pc_output, alu_output, mux0_output);
        memory: memory_ent port map (controller_memread, controller_memwrite, clk, rst, mux0_output, read_out_2, memory_out);
        irl: reg_ent port map (controller_IRWirteL, clk, rst, memory_out, ir_out (7 downto 0));
        irh: reg_ent port map (controller_IRWirteH, clk, rst, memory_out, ir_out (15 downto 8));
        mux1: mux_2to1_generic_ent generic map (2) port map (controller_RegDst, ir_out(8 downto 6), ir_out(5 downto 3) , mux1_output);
        mux2: mux_2to1_generic_ent generic map (7) port map (controller_MemtoReg, alu_output, memory_out , mux2_output);
        register_file: register_file_ent port map (controller_rf_read, controller_rf_write, clk, rst, ir_out(11 downto 9), ir_out(8 downto 6), mux1_output, mux2_output, read_out_1, read_out_2);
        mux3: mux_2to1_generic_ent generic map (7) port map (controller_ALUSrcA, pc_output, read_out_1, mux3_output);
        mux4: mux_4to1_ent port map (controller_ALUSrcB, read_out_2, "00000001", zero_concated, "00000000", mux4_output);
        alu: alu_ent port map (controller_alu_selector, mux3_output, mux4_output, '0', alu_cout, branch, alu_output);
        mux5: mux_4to1_ent port map (controller_PCSource, alu_output, alu_output, ir_out (7 downto 0), "00000000", mux5_output);

  end data_path_arch;
