module xor_2(input wire a, b, output wire o);
    assign o = a ^ b;
endmodule

module and_2(input wire a, b, output wire o);
    assign o = a & b;
endmodule

module or_2(input wire a, b, output wire o);
    assign o = a | b;
endmodule

module fulladder(input wire a, b, c, output wire c_out, s);
    wire t1, t2, t3, t4, t5;

    xor_2 x1(a, b, t1);
    xor_2 x2(c, t1, s);

    and_2 a1(a, b, t2);
    and_2 a2(a, c, t3);
    and_2 a3(b, c, t4);

    or_2 o1(t2, t3, t5);
    or_2 o2(t5, t4, c_out);  
endmodule

module ripplecarryadder(input wire a0,a1,a2,a3,b0,b1,b2,b3,cin,output wire s0,s1,s2,s3,c3);
    wire c0,c1,c2;
    fulladder fa1(a0,b0,cin,c0,s0);
    fulladder fa2(a1,b1,c0,c1,s1);
    fulladder fa3(a2,b2,c1,c2,s2);
    fulladder fa4(a3,b3,c2,c3,s3);
endmodule
module ripplecarryadder_tb;

    reg [3:0] a; // 4-bit register for 'a'
    reg [3:0] b; // 4-bit register for 'b'
    reg cin;

    wire [3:0] s; // 4-bit wire for sum
    wire c3;

    ripplecarryadder rca (
        .a0(a[0]), .a1(a[1]), .a2(a[2]), .a3(a[3]),
        .b0(b[0]), .b1(b[1]), .b2(b[2]), .b3(b[3]),
        .cin(cin),
        .s0(s[0]), .s1(s[1]), .s2(s[2]), .s3(s[3]),
        .c3(c3)
    );

    initial begin
        $dumpfile("ripplecarryadder_tb.vcd");
        $dumpvars(0, ripplecarryadder_tb);

        // Test case 1
        a = 4'b0000;
        b = 4'b0000;
        cin = 0;
        #10;

        // Test case 2
        a = 4'b1010;
        b = 4'b0101;
        cin = 0;
        #10;

        // Test case 3
        a = 4'b1111;
        b = 4'b1111;
        cin = 0;
        #10;

        // Test case 4
        a = 4'b1100;
        b = 4'b1010;
        cin = 1;
        #10;

        $finish;
    end

endmodule