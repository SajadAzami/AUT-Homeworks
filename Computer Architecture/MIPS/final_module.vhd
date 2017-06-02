library IEEE;
use ieee.STD_LOGIC_1164.ALL;
use IEEE.std_logic_unsigned.all;
use ieee.numeric_std.all;

entity final_module_ent is
Port ( clk, reset : in  std_logic);
end final_module_ent;

architecture final_module_arch of final_module_ent is
    component data_path_ent is Port ( clk, rst : in  std_logic;
           controller_pc_enable, controller_IRWirteL, controller_IRWirteH, controller_ALUSrcA, controller_rf_write, controller_rf_read, controller_MemtoReg, controller_RegDst, controller_IorD, controller_memread, controller_memwrite : in std_logic;
           controller_PCSource, controller_ALUSrcB : in std_logic_vector(1 downto 0);
           controller_alu_selector : in std_logic_vector(3 downto 0);
           branch : out std_logic;
           function_code : out std_logic_vector(2 downto 0);
           opcode : out std_logic_vector(3 downto 0)
           );
    end component;
    component control_unit_ent is Port ( reset, clk, branch: in  std_logic;
          opcode : in std_logic_vector(3 downto 0);
          function_code : in std_logic_vector(2 downto 0);
          controller_pc_enable, controller_IRWirteL, controller_IRWirteH, controller_ALUSrcA, controller_rf_write, controller_rf_read, controller_MemtoReg, controller_RegDst, controller_IorD, controller_memread, controller_memwrite : out std_logic;
          controller_PCSource, controller_ALUSrcB : out std_logic_vector(1 downto 0);
          controller_alu_selector : out std_logic_vector(3 downto 0));
    end component;
    signal sig_branch : std_logic;
    signal sig_controller_pc_enable, sig_controller_IRWirteL, sig_controller_IRWirteH, sig_controller_ALUSrcA, sig_controller_rf_write, sig_controller_rf_read, sig_controller_MemtoReg, sig_controller_RegDst, sig_controller_IorD, sig_controller_memread, sig_controller_memwrite : std_logic;
    signal sig_controller_PCSource, sig_controller_ALUSrcB : std_logic_vector(1 downto 0);
    signal sig_controller_alu_selector : std_logic_vector(3 downto 0);
    signal sig_function_code : std_logic_vector(2 downto 0);
    signal sig_opcode : std_logic_vector(3 downto 0);
      begin
        datapath: data_path_ent port map(clk, reset, sig_controller_pc_enable, sig_controller_IRWirteL, sig_controller_IRWirteH, sig_controller_ALUSrcA, sig_controller_rf_write, sig_controller_rf_read, sig_controller_MemtoReg, sig_controller_RegDst, sig_controller_IorD, sig_controller_memread, sig_controller_memwrite,sig_controller_PCSource, sig_controller_ALUSrcB, sig_controller_alu_selector, sig_branch, sig_function_code, sig_opcode);
        controller: control_unit_ent port map(reset, clk, sig_branch, sig_opcode, sig_function_code,sig_controller_pc_enable, sig_controller_IRWirteL, sig_controller_IRWirteH, sig_controller_ALUSrcA, sig_controller_rf_write, sig_controller_rf_read, sig_controller_MemtoReg, sig_controller_RegDst, sig_controller_IorD, sig_controller_memread, sig_controller_memwrite, sig_controller_PCSource, sig_controller_ALUSrcB, sig_controller_alu_selector);
      end final_module_arch;
      