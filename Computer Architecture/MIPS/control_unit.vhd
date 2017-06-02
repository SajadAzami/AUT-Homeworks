library IEEE;
use ieee.STD_LOGIC_1164.ALL;

entity control_unit_ent is
Port ( reset, clk, branch: in  std_logic;
          opcode : in std_logic_vector(3 downto 0);
          function_code : in std_logic_vector(2 downto 0);
          controller_pc_enable, controller_IRWirteL, controller_IRWirteH, controller_ALUSrcA, controller_rf_write, controller_rf_read, controller_MemtoReg, controller_RegDst, controller_IorD, controller_memread, controller_memwrite : out std_logic;
          controller_PCSource, controller_ALUSrcB : out std_logic_vector(1 downto 0);
          controller_alu_selector : out std_logic_vector(3 downto 0));
end control_unit_ent;

architecture control_unit_arch of control_unit_ent is
    type states is (s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14);
    signal current_state : states ;
    signal next_state : states ;
     begin
      process(clk)
        begin 
          if (clk ='1' and clk'event) then
            current_state <= next_state;
          end if; 
      end process;
      process(current_state, reset, opcode)
        begin
          if(reset = '1')then
          next_state <= s0;
          else 
          if(current_state = s0) then 
            next_state <= s1;
            controller_pc_enable <= '1';
            controller_IRWirteL <= '0';
            controller_IRWirteH <= '0';
            controller_ALUSrcA <= '0';
            controller_rf_write <= '0';
            controller_rf_read <= '0';
            controller_MemtoReg <= '0';
            controller_RegDst <= '0';
            controller_IorD <= '0';
            controller_memread <= '1';
            controller_memwrite <= '0';
            controller_PCSource <= "00";
            controller_ALUSrcB <= "01";
            controller_alu_selector <= "0000";
            
              elsif (current_state = s1)then
            next_state <= s2;
            controller_pc_enable <= '1';
            controller_IRWirteL <= '0';
            controller_IRWirteH <= '1';
            controller_ALUSrcA <= '0';
            controller_rf_write <= '0';
            controller_rf_read <= '0';
            controller_MemtoReg <= '0';
            controller_RegDst <= '0';
            controller_IorD <= '0';
            controller_memread <= '1';
            controller_memwrite <= '0';
            controller_PCSource <= "00";
            controller_ALUSrcB <= "01";
            controller_alu_selector <= "0000";
            
              elsif (current_state = s2)then
                  controller_pc_enable <= '0';
                  controller_IRWirteL <= '1';
                  controller_IRWirteH <= '0';
                  controller_ALUSrcA <= '0';
                  controller_rf_write <= '0';
                  controller_rf_read <= '0';
                  controller_MemtoReg <= '0';
                  controller_RegDst <= '0';
                  controller_IorD <= '0';
                  controller_memread <= '0';
                  controller_memwrite <= '0';
                  controller_PCSource <= "00";
                  controller_ALUSrcB <= "00";
                  controller_alu_selector <= "0000";
                if(opcode = "0000") then
                  next_state <= s3;
              elsif (opcode = "1111") then
                  next_state <= s10;
                else
                  next_state <= s5;
              end if;
              
              elsif (current_state = s3)then
            next_state <= s4;
            controller_pc_enable <= '0';
            controller_IRWirteL <= '0';
            controller_IRWirteH <= '0';
            controller_ALUSrcA <= '0';
            controller_rf_write <= '0';
            controller_rf_read <= '1';
            controller_MemtoReg <= '0';
            controller_RegDst <= '0';
            controller_IorD <= '0';
            controller_memread <= '0';
            controller_memwrite <= '0';
            controller_PCSource <= "00";
            controller_ALUSrcB <= "00";
            controller_alu_selector <= "0000";
            
              elsif (current_state = s4)then
            next_state <= s0;
            controller_pc_enable <= '0';
            controller_IRWirteL <= '0';
            controller_IRWirteH <= '0';
            controller_ALUSrcA <= '1';
            controller_rf_write <= '1';
            controller_rf_read <= '0';
            controller_MemtoReg <= '0';
            controller_RegDst <= '1';
            controller_IorD <= '0';
            controller_memread <= '0';
            controller_memwrite <= '0';
            controller_PCSource <= "00";
            controller_ALUSrcB <= "00";
            controller_alu_selector <= '0' & function_code;
            
             elsif (current_state = s5) then
            controller_pc_enable <= '0';
            controller_IRWirteL <= '0';
            controller_IRWirteH <= '0';
            controller_ALUSrcA <= '0';
            controller_rf_write <= '0';
            controller_rf_read <= '1';
            controller_MemtoReg <= '0';
            controller_RegDst <= '0';
            controller_IorD <= '0';
            controller_memread <= '0';
            controller_memwrite <= '0';
            controller_PCSource <= "00";
            controller_ALUSrcB <= "01";
            controller_alu_selector <= "0000";
               if (opcode = "0111") then
                  next_state <= s7;
                elsif (opcode = "1000") then
                  next_state <= s9;
                elsif (opcode = "1001" or opcode = "1010" or opcode = "1011"  or opcode = "1100" or opcode = "1101"  or opcode = "1110" ) then
                  next_state <= s11;
                else next_state <= s6;
               end if;
               
             elsif (current_state = s6) then
            next_state <= s0;
            controller_pc_enable <= '0';
            controller_IRWirteL <= '0';
            controller_IRWirteH <= '0';
            controller_ALUSrcA <= '1';
            controller_rf_write <= '1';
            controller_rf_read <= '0';
            controller_MemtoReg <= '0';
            controller_RegDst <= '0';
            controller_IorD <= '0';
            controller_memread <= '0';
            controller_memwrite <= '0';
            controller_PCSource <= "00";
            controller_ALUSrcB <= "10";
            if (opcode = "0001") then
              controller_alu_selector <= "0000";
            elsif (opcode = "0010") then
              controller_alu_selector <= "0010";
            elsif (opcode = "0011") then
              controller_alu_selector <= "0011";
            elsif (opcode = "0100") then
              controller_alu_selector <= "1000";
            elsif (opcode = "0101") then
              controller_alu_selector <= "0111";
          end if;
          
          elsif (current_state = s7) then
            next_state <= s8;
            controller_pc_enable <= '0';
            controller_IRWirteL <= '0';
            controller_IRWirteH <= '0';
            controller_ALUSrcA <= '1';
            controller_rf_write <= '0';
            controller_rf_read <= '0';
            controller_MemtoReg <= '1';
            controller_RegDst <= '0';
            controller_IorD <= '1';
            controller_memread <= '1';
            controller_memwrite <= '0';
            controller_PCSource <= "00";
            controller_ALUSrcB <= "10";
            controller_alu_selector <= "0000";
            
          elsif (current_state = s8) then
            next_state <= s0;
            controller_pc_enable <= '0';
            controller_IRWirteL <= '0';
            controller_IRWirteH <= '0';
            controller_ALUSrcA <= '0';
            controller_rf_write <= '1';
            controller_rf_read <= '0';
            controller_MemtoReg <= '1';
            controller_RegDst <= '0';
            controller_IorD <= '0';
            controller_memread <= '0';
            controller_memwrite <= '0';
            controller_PCSource <= "00";
            controller_ALUSrcB <= "00";
            controller_alu_selector <= "0000";
            
            elsif (current_state = s9) then
            next_state <= s0;
            controller_pc_enable <= '0';
            controller_IRWirteL <= '0';
            controller_IRWirteH <= '0';
            controller_ALUSrcA <= '1';
            controller_rf_write <= '0';
            controller_rf_read <= '0';
            controller_MemtoReg <= '0';
            controller_RegDst <= '0';
            controller_IorD <= '1';
            controller_memread <= '0';
            controller_memwrite <= '1';
            controller_PCSource <= "00";
            controller_ALUSrcB <= "10";
            controller_alu_selector <= "0000";
            
            elsif (current_state = s11) then
            controller_pc_enable <= '0';
            controller_IRWirteL <= '0';
            controller_IRWirteH <= '0';
            controller_ALUSrcA <= '1';
            controller_rf_write <= '0';
            controller_rf_read <= '0';
            controller_MemtoReg <= '0';
            controller_RegDst <= '0';
            controller_IorD <= '0';
            controller_memread <= '0';
            controller_memwrite <= '0';
            controller_PCSource <= "00";
            controller_ALUSrcB <= "00";
            controller_alu_selector <= "0000";
            if (branch = '0') then 
              next_state <= s0;
            else
              next_state <= s12;
          end if;
          
            elsif (current_state = s12) then
            next_state <= s0;
            controller_pc_enable <= '1';
            controller_IRWirteL <= '0';
            controller_IRWirteH <= '0';
            controller_ALUSrcA <= '0';
            controller_rf_write <= '0';
            controller_rf_read <= '0';
            controller_MemtoReg <= '0';
            controller_RegDst <= '0';
            controller_IorD <= '0';
            controller_memread <= '0';
            controller_memwrite <= '0';
            controller_PCSource <= "00";
            controller_ALUSrcB <= "10";
            controller_alu_selector <= "0000";   
            
            elsif (current_state = s10) then
            next_state <= s0;
            controller_pc_enable <= '1';
            controller_IRWirteL <= '0';
            controller_IRWirteH <= '0';
            controller_ALUSrcA <= '0';
            controller_rf_write <= '0';
            controller_rf_read <= '0';
            controller_MemtoReg <= '0';
            controller_RegDst <= '0';
            controller_IorD <= '0';
            controller_memread <= '0';
            controller_memwrite <= '0';
            controller_PCSource <= "10";
            controller_ALUSrcB <= "00";
            controller_alu_selector <= "0000"; 
        end if;   
        end if; 
        end process;  
      
 end control_unit_arch;
