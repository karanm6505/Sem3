`timescale 1ns / 1ps

module half_adder(input a, b, output s, c_out);
  assign S = a ^ b;
  assign c_out = a & b;
endmodule

module tb_top;
  reg a, b;
  wire s, c_out;
  
  half_adder ha(a, b, s, c_out);
  

    initial begin
        $dumpfile("ha.vcd");
        $dumpvars(0, tb_top);
  
    a = 0; b = 0;
    #10;
    a = 0; b = 1;
    #10;
    a = 1; b = 0;
    #10;
    a = 1; b = 1;
     
        
  end
endmodule