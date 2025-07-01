module invert (input wire a, output wire o);
    assign o = !a;
endmodule

module xor2(input wire i0, i1, output wire o);
    assign o = i0 ^ i1;
endmodule

module xor3(input wire i0, i1, i2, output wire o);
    wire t;
    xor2 x1(i0, i1, t);
    xor2 x2(t, i2, o);
endmodule

module circuitclight(input wire A, B, C, output wire o);
    wire t1;
    xor3 x3(A, B, C, t1);  
    invert no(t1, o);
endmodule

module clight_tb;
    reg A, B, C;
    wire o;
    circuitclight uut(.A(A), .B(B), .C(C), .o(o));
    integer i;

    initial begin
        $dumpfile("clights.vcd");
        $dumpvars(0, clight_tb);

        for (i = 0; i < 8; i = i + 1) begin
            {A, B, C} = i;
            #10;
        end
        $finish; 
    end
endmodule