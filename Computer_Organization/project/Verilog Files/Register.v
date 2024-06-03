`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: ITU Computer Engineering Department
// Engineers: Yusuf Yildiz - 150210006
//            Safak Ozkan Pala - 150210016
// Project Name: BLG222E Project 2 Register
//////////////////////////////////////////////////////////////////////////////////

module Register (I, E, FunSel, Clock, Q);
    input wire [15:0] I; // reg
    input wire E;
    input wire [2:0] FunSel; // reg
    input wire Clock;
    output reg [15:0] Q;
    always @(posedge Clock) begin
        case ({E, FunSel})
            // Case 1: Retain Value
            4'b0_000: Q <= Q;
            // Case 2: Decrement
            4'b1_000: Q <= Q - 1;
            // Case 3: Increment
            4'b1_001: Q <= Q + 1;
            // Case 4: Load
            4'b1_010: Q <= I;
            // Case 5: Clear
            4'b1_011: Q <= 16'h0;
            // Case 6: Clear and Write Low
            4'b1_100: begin 
                Q[15:8] <= 8'h0;
                Q[7:0] <= I[7:0];
            end
            // Case 7: Only Write Low
            4'b1_101: Q[7:0] <= I[7:0];
            // Case 8: Only Write High
            4'b1_110: Q[15:8] <= I[7:0];
            // Case 9: Sign Extend and Write Low
            4'b1_111: begin
                Q[15:8] <= {I[7], I[7]}; // Sign extend
                Q[7:0] <= I[7:0];
            end
        endcase
    end

endmodule
