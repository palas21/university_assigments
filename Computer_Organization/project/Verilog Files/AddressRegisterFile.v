`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: ITU Computer Engineering Department
// Engineers: Yusuf Yildiz - 150210006
//            Safak Ozkan Pala - 150210016
// Project Name: BLG222E Project 2 AddressRegisterFile
//////////////////////////////////////////////////////////////////////////////////

module AddressRegisterFile (I, OutCSel, OutDSel, FunSel, RegSel, Clock, OutC, OutD);
    input [15:0] I;              // Data input
    input [1:0] OutCSel;         // Output C selection control
    input [1:0] OutDSel;         // Output D selection control
    input [2:0] FunSel;          // Function selection control
    input [2:0] RegSel;          // Address register selection control
    input Clock;                 // Clock input
    output reg [15:0] OutC;      // Output C
    output reg [15:0] OutD;       // Output D
// Define wires for enable inputs
reg PC_Enable, AR_Enable, SP_Enable;

// Define wires for register outputs
wire [15:0] Q_PC, Q_AR, Q_SP;

// Register behavior
always @(posedge Clock) begin
    // Enable address registers based on RegSel
    case (RegSel)
        4'b000: begin PC_Enable = 1; AR_Enable = 1; SP_Enable = 1; end
        4'b001: begin PC_Enable = 1; AR_Enable = 1; SP_Enable = 0; end
        4'b010: begin PC_Enable = 1; AR_Enable = 0; SP_Enable = 1; end
        4'b011: begin PC_Enable = 1; AR_Enable = 0; SP_Enable = 0; end
        4'b100: begin PC_Enable = 0; AR_Enable = 1; SP_Enable = 1; end
        4'b101: begin PC_Enable = 0; AR_Enable = 1; SP_Enable = 0; end
        4'b110: begin PC_Enable = 0; AR_Enable = 0; SP_Enable = 1; end
        4'b111: begin PC_Enable = 0; AR_Enable = 0; SP_Enable = 0; end
        default: ; // No address register enabled
    endcase
end

// Create address registers using the enable wires
Register PC (.I(I), .E(PC_Enable), .FunSel(FunSel), .Clock(Clock), .Q(Q_PC));
Register AR (.I(I), .E(AR_Enable), .FunSel(FunSel), .Clock(Clock), .Q(Q_AR));
Register SP (.I(I), .E(SP_Enable), .FunSel(FunSel), .Clock(Clock), .Q(Q_SP));

// Select output C based on OutCSel
always @(*) begin
    case (OutCSel)
        2'b00: OutC = Q_PC;
        2'b01: OutC = Q_PC;
        2'b10: OutC = Q_AR;
        2'b11: OutC = Q_SP; 
        default: ;
    endcase
end

// Select output D based on OutDSel
always @(*) begin
    case (OutDSel)
        2'b00: OutD = Q_PC;
        2'b01: OutD = Q_PC;
        2'b10: OutD = Q_AR;
        2'b11: OutD = Q_SP; 
        default: ;
    endcase
end

endmodule
