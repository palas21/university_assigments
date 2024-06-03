`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: ITU Computer Engineering Department
// Engineers: Yusuf Yildiz - 150210006
//            Safak Ozkan Pala - 150210016
// Project Name: BLG222E Project 2 ArithmeticLogicUnitSystem
//////////////////////////////////////////////////////////////////////////////////

module ArithmeticLogicUnitSystem(RF_OutASel, RF_OutBSel, RF_FunSel, RF_RegSel, RF_ScrSel,
ALU_FunSel, ALU_WF, ARF_OutCSel, ARF_OutDSel, ARF_FunSel, ARF_RegSel, IR_LH, IR_Write, Mem_WR, Mem_CS, MuxASel, MuxBSel, MuxCSel, Clock);
    input [2:0] RF_OutASel, RF_OutBSel, RF_FunSel;
    input [3:0] RF_RegSel, RF_ScrSel;
    input [4:0] ALU_FunSel;
    input ALU_WF; 
    input [1:0] ARF_OutCSel, ARF_OutDSel;
    input [2:0] ARF_FunSel, ARF_RegSel;
    input IR_LH, IR_Write, Mem_WR, Mem_CS;
    input [1:0] MuxASel, MuxBSel;
    input MuxCSel;
    input Clock;
    
// Define internal wires for intermediate signals
    wire [15:0] OutA, OutB, OutC, Address, ALUOut, IROut;
    reg [15:0] MuxAOut, MuxBOut;
    reg [7:0] MuxCOut;
    wire [7:0] MemOut;
    wire [3:0] Flags;
    
InstructionRegister IR (.I(MemOut), .Write(IR_Write),   .LH(IR_LH), .Clock(Clock), .IROut(IROut));

Memory MEM (.Address(Address), .Data(MuxCOut), .WR(Mem_WR), .CS(Mem_CS), .Clock(Clock), .MemOut(MemOut)); 

AddressRegisterFile ARF (.I(MuxBOut), .OutCSel(ARF_OutCSel), .OutDSel(ARF_OutDSel),
 .FunSel(ARF_FunSel), .RegSel(ARF_RegSel), .Clock(Clock), .OutC(OutC), .OutD(Address));    
 
RegisterFile RF (.I(MuxAOut), .OutASel(RF_OutASel), .OutBSel(RF_OutBSel), .FunSel(RF_FunSel), 
 .RegSel(RF_RegSel), .ScrSel(RF_ScrSel), .Clock(Clock), .OutA(OutA), .OutB(OutB));
 
ArithmeticLogicUnit ALU (.A(OutA), .B(OutB), .FunSel(ALU_FunSel), .WF(ALU_WF), .Clock(Clock), .ALUOut(ALUOut), .FlagsOut(Flags));
 // we need to create previous module instances and give the inputs to these modules, then connect the outputs of them to each other 


always @(*) begin
    case(MuxASel)
        2'b00: MuxAOut = ALUOut;          // ALUOut
        2'b01: MuxAOut = OutC;         // ARF OutC
        2'b10: MuxAOut = {8'b00000000, MemOut}; // Memory Output (extended with zeros)
        2'b11: MuxAOut = IROut[7:0];                // IR (7:0)
    endcase
    
    case(MuxBSel)
        2'b00: MuxBOut = ALUOut;          // ALUOut
        2'b01: MuxBOut = OutC;         // ARF OutC
        2'b10: MuxBOut = {8'b00000000, MemOut}; // Memory Output (extended with zeros)
        2'b11: MuxBOut = IROut[7:0];                // IR (7:0)
    endcase
    
    MuxCOut = (MuxCSel == 0) ? ALUOut[7:0] : ALUOut[15:8];
end 
endmodule