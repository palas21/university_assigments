`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: ITU Computer Engineering Department
// Engineers: Yusuf Yildiz - 150210006
//            Safak Ozkan Pala - 150210016
// Project Name: BLG222E Project 2 RegisterFile
//////////////////////////////////////////////////////////////////////////////////

module RegisterFile (I, OutASel, OutBSel, FunSel,
RegSel, ScrSel, Clock, OutA, OutB);
    input [15:0] I;              // Data input
    input [2:0] OutASel;         // Output A selection control
    input [2:0] OutBSel;         // Output B selection control
    input [2:0] FunSel;          // Function selection control
    input [3:0] RegSel;          // General purpose register selection control
    input [3:0] ScrSel;          // Scratch register selection control
    input Clock;                 // Clock input
    output reg [15:0] OutA;      // Output A
    output reg [15:0] OutB;      // Output B

// Define wires for enable inputs
reg R1_Enable, R2_Enable, R3_Enable, R4_Enable;
reg S1_Enable, S2_Enable, S3_Enable, S4_Enable;

// Define wires for register outputs
wire [15:0] Q_R1, Q_R2, Q_R3, Q_R4, Q_S1, Q_S2, Q_S3, Q_S4;

// Register behavior
always @(posedge Clock) begin
    // Enable general purpose registers based on RegSel
    case (RegSel)
        4'b0000: begin R1_Enable = 1; R2_Enable = 1; R3_Enable = 1; R4_Enable = 1; end
        4'b0001: begin R1_Enable = 1; R2_Enable = 1; R3_Enable = 1; R4_Enable = 0; end
        4'b0010: begin R1_Enable = 1; R2_Enable = 1; R3_Enable = 0; R4_Enable = 1; end
        4'b0011: begin R1_Enable = 1; R2_Enable = 1; R3_Enable = 0; R4_Enable = 0; end
        4'b0100: begin R1_Enable = 1; R2_Enable = 0; R3_Enable = 1; R4_Enable = 1; end
        4'b0101: begin R1_Enable = 1; R2_Enable = 0; R3_Enable = 1; R4_Enable = 0; end
        4'b0110: begin R1_Enable = 1; R2_Enable = 0; R3_Enable = 0; R4_Enable = 1; end
        4'b0111: begin R1_Enable = 1; R2_Enable = 0; R3_Enable = 0; R4_Enable = 0; end
        4'b1000: begin R1_Enable = 0; R2_Enable = 1; R3_Enable = 1; R4_Enable = 1; end
        4'b1001: begin R1_Enable = 0; R2_Enable = 1; R3_Enable = 1; R4_Enable = 0; end
        4'b1010: begin R1_Enable = 0; R2_Enable = 1; R3_Enable = 0; R4_Enable = 1; end
        4'b1011: begin R1_Enable = 0; R2_Enable = 1; R3_Enable = 0; R4_Enable = 0; end
        4'b1100: begin R1_Enable = 0; R2_Enable = 0; R3_Enable = 1; R4_Enable = 1; end
        4'b1101: begin R1_Enable = 0; R2_Enable = 0; R3_Enable = 1; R4_Enable = 0; end
        4'b1110: begin R1_Enable = 0; R2_Enable = 0; R3_Enable = 0; R4_Enable = 1; end
        4'b1111: begin R1_Enable = 0; R2_Enable = 0; R3_Enable = 0; R4_Enable = 0; end
        default: ;  // All registers retain their values
    endcase

    // Enable scratch registers based on ScrSel
    case (ScrSel)
        4'b0000: begin S1_Enable = 1; S2_Enable = 1; S3_Enable = 1; S4_Enable = 1; end
        4'b0001: begin S1_Enable = 1; S2_Enable = 1; S3_Enable = 1; S4_Enable = 0; end
        4'b0010: begin S1_Enable = 1; S2_Enable = 1; S3_Enable = 0; S4_Enable = 1; end
        4'b0011: begin S1_Enable = 1; S2_Enable = 1; S3_Enable = 0; S4_Enable = 0; end
        4'b0100: begin S1_Enable = 1; S2_Enable = 0; S3_Enable = 1; S4_Enable = 1; end
        4'b0101: begin S1_Enable = 1; S2_Enable = 0; S3_Enable = 1; S4_Enable = 0; end
        4'b0110: begin S1_Enable = 1; S2_Enable = 0; S3_Enable = 0; S4_Enable = 1; end
        4'b0111: begin S1_Enable = 1; S2_Enable = 0; S3_Enable = 0; S4_Enable = 0; end
        4'b1000: begin S1_Enable = 0; S2_Enable = 1; S3_Enable = 1; S4_Enable = 1; end
        4'b1001: begin S1_Enable = 0; S2_Enable = 1; S3_Enable = 1; S4_Enable = 0; end
        4'b1010: begin S1_Enable = 0; S2_Enable = 1; S3_Enable = 0; S4_Enable = 1; end
        4'b1011: begin S1_Enable = 0; S2_Enable = 1; S3_Enable = 0; S4_Enable = 0; end
        4'b1100: begin S1_Enable = 0; S2_Enable = 0; S3_Enable = 1; S4_Enable = 1; end
        4'b1101: begin S1_Enable = 0; S2_Enable = 0; S3_Enable = 1; S4_Enable = 0; end
        4'b1110: begin S1_Enable = 0; S2_Enable = 0; S3_Enable = 0; S4_Enable = 1; end
        4'b1111: begin S1_Enable = 0; S2_Enable = 0; S3_Enable = 0; S4_Enable = 0; end
        default: ;  // All registers retain their values
    endcase
       
end

// Create registers using the enable wires
Register R1(.I(I), .E(R1_Enable), .FunSel(FunSel), .Clock(Clock), .Q(Q_R1));
Register R2(.I(I), .E(R2_Enable), .FunSel(FunSel), .Clock(Clock), .Q(Q_R2));
Register R3(.I(I), .E(R3_Enable), .FunSel(FunSel), .Clock(Clock), .Q(Q_R3));
Register R4(.I(I), .E(R4_Enable), .FunSel(FunSel), .Clock(Clock), .Q(Q_R4));
Register S1(.I(I), .E(S1_Enable), .FunSel(FunSel), .Clock(Clock), .Q(Q_S1));
Register S2(.I(I), .E(S2_Enable), .FunSel(FunSel), .Clock(Clock), .Q(Q_S2));
Register S3(.I(I), .E(S3_Enable), .FunSel(FunSel), .Clock(Clock), .Q(Q_S3));
Register S4(.I(I), .E(S4_Enable), .FunSel(FunSel), .Clock(Clock), .Q(Q_S4));

// Select output A based on OutASel
always @(*) begin
    case (OutASel)
        3'b000: OutA = Q_R1;
        3'b001: OutA = Q_R2;
        3'b010: OutA = Q_R3;
        3'b011: OutA = Q_R4;
        3'b100: OutA = Q_S1;
        3'b101: OutA = Q_S2;
        3'b110: OutA = Q_S3;
        3'b111: OutA = Q_S4;
        default: OutA = 16'h0; // Default case
    endcase
end

// Select output B based on OutBSel
always @(*) begin
    case (OutBSel)
        3'b000: OutB = Q_R1;
        3'b001: OutB = Q_R2;
        3'b010: OutB = Q_R3;
        3'b011: OutB = Q_R4;
        3'b100: OutB = Q_S1;
        3'b101: OutB = Q_S2;
        3'b110: OutB = Q_S3;
        3'b111: OutB = Q_S4;
        default: OutB = 16'h0; // Default case
    endcase
end
endmodule