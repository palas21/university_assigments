`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: ITU Computer Engineering Department
// Engineers: Yusuf Yildiz - 150210006
//            Safak Ozkan Pala - 150210016
// Project Name: BLG222E Project 2 InstructionRegister
//////////////////////////////////////////////////////////////////////////////////

module InstructionRegister (I, Write, LH, Clock, IROut);
    input wire [7:0] I;     // 8-bit input data
    input wire Write;       // Write control signal
    input wire LH;          // Load Lower/Higher control signal
    input wire Clock;       // Clock input
    output reg [15:0] IROut;// 16-bit output data
    // Register behavior
    always @(posedge Clock) begin
        if (Write) begin
            if (LH) // Load Higher
                IROut[15:8] <= I;
            else    // Load Lower
                IROut[7:0] <= I;
        end
    end

endmodule
