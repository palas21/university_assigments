`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: ITU Computer Engineering Department
// Engineers: Yusuf Yildiz - 150210006
//            Safak Ozkan Pala - 150210016
// Project Name: BLG222E Project 2 CPUSystem
//////////////////////////////////////////////////////////////////////////////////

module CPUSystem(Clock, Reset, T);
    input Clock;    // Clock input
    input Reset;    // Reset input
    output reg [7:0] T;  // Input T as SC
    
reg[2:0] RF_OutASel, RF_OutBSel, RF_FunSel;
reg[3:0] RF_RegSel, RF_ScrSel;
reg[4:0] ALU_FunSel;
reg ALU_WF;
reg[1:0] ARF_OutCSel, ARF_OutDSel;
reg[2:0] ARF_FunSel, ARF_RegSel;
reg IR_LH, IR_Write, Mem_WR, Mem_CS;
reg[1:0] MuxASel, MuxBSel;
reg MuxCSel;
reg ResetAgain = 1;

wire Z, C, N, O;

ArithmeticLogicUnitSystem _ALUSystem(
    .RF_OutASel(RF_OutASel),   .RF_OutBSel(RF_OutBSel), 
    .RF_FunSel(RF_FunSel),     .RF_RegSel(RF_RegSel),
    .RF_ScrSel(RF_ScrSel),     .ALU_FunSel(ALU_FunSel),
    .ALU_WF(ALU_WF),           .ARF_OutCSel(ARF_OutCSel), 
    .ARF_OutDSel(ARF_OutDSel), .ARF_FunSel(ARF_FunSel),
    .ARF_RegSel(ARF_RegSel),   .IR_LH(IR_LH),
    .IR_Write(IR_Write),       .Mem_WR(Mem_WR),
    .Mem_CS(Mem_CS),           .MuxASel(MuxASel),
    .MuxBSel(MuxBSel),         .MuxCSel(MuxCSel),
    .Clock(Clock)
);
assign {Z,C,N,O} = _ALUSystem.ALU.FlagsOut;

// For instructions with address reference
reg [5:0] OPCODE_addr;     // OPCODE
reg [1:0] RSEL_addr;       // RSEL
reg [7:0] ADDRESS_addr;    // ADDRESS

// For instructions without address reference
reg [5:0] OPCODE_no_addr;     // OPCODE
reg S_no_addr;                // S
reg [2:0] DSTREGSEL_no_addr;  // DSTREG
reg [2:0] SREG1SEL_no_addr;   // SREG1
reg [2:0] SREG2SEL_no_addr;   // SREG2
    
// Temporary registers
reg [15:0] R_addr;
reg [15:0] DSTREG_no_addr;
reg [15:0] SREG1_no_addr;
reg [15:0] SREG2_no_addr; 
    
// Define states for the state machine
parameter IDLE = 2'b00;
parameter LOAD_LSB = 2'b01;
parameter LOAD_MSB = 2'b10;
parameter EXEC_INS = 2'b11;

// Define local signals for the state machine
reg [1:0] State = IDLE;
reg InstructionLoaded = 0;

task SetREGSel;
    input [2:0] REGSEL;
    input [2:0] FunSel;              
    case (REGSEL)                    
        3'b000: begin // PC
            ARF_RegSel = 3'b011;
            ARF_FunSel = FunSel;
        end
        3'b001: begin // PC
            ARF_RegSel = 3'b011;
            ARF_FunSel = FunSel;
        end
        3'b010: begin // SP
            ARF_RegSel = 3'b110;
            ARF_FunSel = FunSel;
        end
        3'b011: begin // AR
            ARF_RegSel = 3'b101;
            ARF_FunSel = FunSel;
        end
        3'b100: begin  // R1
            RF_RegSel = 4'b0111;
            RF_FunSel = FunSel;
        end
        3'b101: begin  // R2
            RF_RegSel = 4'b1011;
            RF_FunSel = FunSel;
        end
        3'b110: begin  // R3
            RF_RegSel = 4'b1101; 
            RF_FunSel = FunSel;           
        end
        3'b111: begin  // R4
            RF_RegSel = 4'b1110;
            RF_FunSel = FunSel;
        end
    endcase
endtask

task SetScratchSel; 
    input [1:0] SSEL_addr;
    input [2:0] FunSel;
    
    begin 
    case (SSEL_addr)
        2'b00: begin // S1
            RF_ScrSel = 4'b0111;
            RF_FunSel = FunSel;
         end
        2'b01: begin // S2
            RF_ScrSel = 4'b1011;
            RF_FunSel = FunSel;
        end
        2'b10: begin // S3
            RF_ScrSel = 4'b1101;
            RF_FunSel = FunSel;
        end
        2'b11: begin // S4
            RF_ScrSel = 4'b1110;
            RF_FunSel = FunSel;
        end
    endcase
    end
endtask

task clearRF;
    begin
        _ALUSystem.RF.R1.Q = 16'h0000;
        _ALUSystem.RF.R2.Q = 16'h0000;
        _ALUSystem.RF.R3.Q = 16'h0000;
        _ALUSystem.RF.R4.Q = 16'h0000;
        _ALUSystem.RF.S1.Q = 16'h0000;
        _ALUSystem.RF.S2.Q = 16'h0000;
        _ALUSystem.RF.S3.Q = 16'h0000;
        _ALUSystem.RF.S4.Q = 16'h0000;
    end    
endtask

task disableAll; 
    begin
        RF_RegSel = 4'b1111;
        RF_ScrSel = 4'b1111;
        ARF_RegSel = 3'b111;
        ALU_WF = 0;
        Mem_CS = 1;
        Mem_WR = 0;
    end
endtask

initial begin
    _ALUSystem.ARF.PC.Q = 16'h0000; // Set PC to 0 initally !!!
    ARF_OutDSel = 2'b00; // Give PC to Adress Out of the ARF for the memory
    Mem_CS = 0; // Enable memory
    Mem_WR = 0; // Activate read mode of the memory and give the M[PC] to the BUS with the MemOut.
    ALU_FunSel = 5'b10000;  // /16-bit A <- S1
    RF_OutASel = 3'b110;    // S3
    RF_OutBSel = 3'b111;    // S4
    _ALUSystem.ARF.SP.Q = 16'h00FF; // SP is initially 255.
    clearRF();
    ALU_WF = 0;
end

always @(posedge Clock or negedge Reset) begin
    if (!Reset | !ResetAgain) begin // When reset is zero or RestartAgain is zero. We use RestartAgain for the restart the CPU after the execution of the operation.
        disableAll();
        ResetAgain = 1;
        Mem_CS = 0;
        Mem_WR = 0;
        State <= LOAD_LSB;
        IR_LH = 0;
        IR_Write = 1;
        InstructionLoaded = 0;
        T = 1;  
        ARF_RegSel = 3'b011; // We choose the PC for the FunSel operation.
        ARF_FunSel = 3'b001; // We increament the selected register. PC = PC + 1
    end else begin
        case (State)
            LOAD_LSB: begin // Instruction is loaded
                State <= LOAD_MSB;
                IR_LH = 1;
                IR_Write = 1;
                InstructionLoaded = 0;
                T = T + T; // Increment SC
            end
            LOAD_MSB: begin // Transition to LOAD_MSB state
                State <= EXEC_INS;
                ARF_RegSel = 3'b111; // Disable ARF.
                IR_Write = 0;
                Mem_CS = 1; // Disable Memory.
                InstructionLoaded = 1;
            end
            default: ;
        endcase 
    end
end

// Decode the InstructionRegister    
always @* begin
    // Instructions with address reference
    OPCODE_addr = _ALUSystem.IROut[15:10];
    RSEL_addr = _ALUSystem.IROut[9:8];
    ADDRESS_addr = _ALUSystem.IROut[7:0];
    // Instructions without address reference
    DSTREGSEL_no_addr = _ALUSystem.IROut[8:6];
    SREG1SEL_no_addr = _ALUSystem.IROut[5:3];
    SREG2SEL_no_addr = _ALUSystem.IROut[2:0];    
end    
// Decode the OPCODE and execute instructions

always @(posedge Clock) begin
    
if(InstructionLoaded) begin
    case (OPCODE_addr)
        6'h00, 6'h01, 6'h02: begin // BRA BNE BQA PC = PC + VALUE
        if(OPCODE_addr == 6'h00 || (OPCODE_addr == 6'h01 && Z != 16'h0000) || (OPCODE_addr == 6'h02 && Z == 1)) begin 
            case(T)
                8'h04: begin // Get IR to S1
                    MuxASel = 2'b11;        // Select IROut[7:0] 
                    SetScratchSel(2'b00, 3'b111);   // Enable only S1
                    ALU_FunSel = 5'b10100;   // ALUOut = A + B
                    RF_OutASel = 3'b100;
                    RF_OutBSel = 3'b101;
                end
                8'h08: begin
                    SetScratchSel(2'b01, 3'b010);   // Enable only S2 and load
                    ARF_OutCSel = 2'b00;    // OutCSel = PC.
                    MuxASel = 2'b01;        // Select OutCSel
                end
                8'h10: begin
                    MuxBSel = 2'b00;        // Select ALUOut
                    ARF_RegSel = 3'b011;    // Enable PC
                    ARF_FunSel = 3'b010;    // Load
                    ResetAgain = 0;
                end
                endcase
            end
            else begin ResetAgain = 0; end
        end
        6'h03: begin // POP  SP = SP + 1, Rx = M[SP]
            case(T)
                8'h04: begin
                    SetREGSel(3'b010 ,3'b001); // increment the s
                end
                8'h08: begin
                    ARF_OutDSel = 2'b11; // sp is pointing memory
                    Mem_WR = 0; // read
                    Mem_CS = 0; // enable
                    MuxASel = 2'b10; // MemOut
                    SetREGSel({1'b1, RSEL_addr}, 3'b100); // rx is enabled and only low loaded.
                end
                8'h10: begin
                    SetREGSel({1'b1, RSEL_addr}, 3'b110); // rx is enabled and high part is loaded.
                    ARF_RegSel = 3'b111; // do not increment sp again beacuse this cell is now free.
                    ResetAgain = 0;
                end
            endcase
        end
        6'h04: begin // PSH  M[SP] ? Rx, SP ? SP - 1
            ALU_FunSel = 5'b10000; // A is ALUOut
            case(T)
                8'h04: begin
                    RF_OutASel = {1'b0, RSEL_addr};
                    MuxCSel = 1'b1; // MSB
                    Mem_CS = 0; // Enable Mem
                    Mem_WR = 1; // Write
                    ARF_OutDSel = 2'b11; // sp is pointing memory
                    SetREGSel(3'b010,3'b000); // sp is DEC.
                end
                8'h08: begin
                    MuxCSel = 1'b0; // LSB
                    ResetAgain = 0;
                end
            endcase
        end
        6'h0C, 6'h0D, 6'h0F, 6'h10, 6'h15, 6'h16, 6'h17, 6'h19, 6'h1A, 6'h1B, 6'h1C, 6'h1D: begin
            case (OPCODE_addr)
                6'h0C: ALU_FunSel = 5'b10111; // AND
                6'h0D: ALU_FunSel = 5'b11000; // ORR
                6'h0F: ALU_FunSel = 5'b11001; // XOR
                6'h10: ALU_FunSel = 5'b11010; // NAND
                6'h15: ALU_FunSel = 5'b10100; // ADD
                6'h16: ALU_FunSel = 5'b10101; // ADD Carry
                6'h17: ALU_FunSel = 5'b10110; // SUB
                6'h19: begin ALU_FunSel = 5'b10100; ALU_WF = _ALUSystem.IROut[9]; end // ADD w Flag
                6'h1A: begin ALU_FunSel = 5'b10110; ALU_WF = _ALUSystem.IROut[9]; end // SUB w Flag
                6'h1B: begin ALU_FunSel = 5'b10111; ALU_WF = _ALUSystem.IROut[9]; end // And w Flag
                6'h1C: begin ALU_FunSel = 5'b11000; ALU_WF = _ALUSystem.IROut[9]; end // OR w Flag
                6'h1D: begin ALU_FunSel = 5'b11001; ALU_WF = _ALUSystem.IROut[9]; end // XOR w Flag
            endcase
            if(!SREG1SEL_no_addr[2] && !SREG2SEL_no_addr[2]) begin // both sources are from ARF
                case(T) // 2 cycles needed to load to ALU
                    8'h04: begin
                        ARF_OutCSel = SREG1SEL_no_addr[1:0] ^ 2'b01; // mapping different for SREGSEL and ARF C Sel
                        MuxASel = 2'b01;
                        SetScratchSel(2'b00, 3'b010);
                        RF_OutASel = 3'b100;
                    end
                    8'h08: begin
                        ARF_OutCSel = SREG2SEL_no_addr[1:0] ^ 2'b01; // mapping different for SREGSEL and ARF C Sel
                        MuxASel = 2'b01;
                        SetScratchSel(2'b01, 3'b010);
                        RF_OutBSel = 3'b101;
                    end
                    8'h10: begin
                        RF_ScrSel = 4'b1111;
                        MuxBSel = 2'b00;
                        MuxASel = 2'b00;
                        SetREGSel(DSTREGSEL_no_addr,3'b010);
                        ResetAgain = 0;
                    end 
                endcase
                end else if (SREG1SEL_no_addr[2] && SREG2SEL_no_addr[2]) begin // if both is from RF
                case(T) // 2 cycles needed to load to ALU
                    8'h04: begin
                        RF_OutASel = {1'b0,SREG1SEL_no_addr[1:0]};
                        RF_OutBSel = {1'b0,SREG2SEL_no_addr[1:0]};
                        MuxBSel = 2'b00;
                        MuxASel = 2'b00;
                        SetREGSel(DSTREGSEL_no_addr,3'b010);
                        ResetAgain = 0;
                    end
                endcase    
                end else begin // if one is from rf and one is from arf
                case(T) // 2 cycles needed to load to ALU
                    8'h04: begin
                        if(!SREG1SEL_no_addr[2]) begin
                            ARF_OutCSel = SREG1SEL_no_addr[1:0] ^ 2'b01; // mapping different for SREGSEL and ARF C Sel
                            MuxASel = 2'b01;
                            SetScratchSel(2'b00, 3'b010);
                            RF_OutASel = 3'b100;
                            RF_OutBSel = {1'b0,SREG2SEL_no_addr[1:0]};
                        end else begin
                            ARF_OutCSel = SREG2SEL_no_addr[1:0] ^ 2'b01; // mapping different for SREGSEL and ARF C Sel
                            MuxASel = 2'b01;
                            SetScratchSel(2'b00, 3'b010);
                            RF_OutBSel = 3'b100;
                            RF_OutASel = {1'b0,SREG1SEL_no_addr[1:0]};
                        end
                    end
                    8'h08: begin
                        MuxBSel = 2'b00;
                        MuxASel = 2'b00;
                        SetREGSel(DSTREGSEL_no_addr,3'b010);
                        ResetAgain = 0;
                    end
                endcase
                end
        end
        6'h05, 6'h06: begin // INC DSTREG ? SREG1 + 1 // DEC DSTREG ? SREG1 - 1
            case(T)
                8'h04: begin
                    if(SREG1SEL_no_addr[2] == 0) begin
                        ARF_OutCSel = SREG1SEL_no_addr[1:0];
                        MuxBSel = 2'b01;
                        MuxASel = 2'b01;
                    end else begin
                        RF_OutASel = SREG1SEL_no_addr[1:0];
                        ALU_FunSel = 5'b10000;  // /16-bit A <- S1
                        MuxBSel = 2'b00;
                        MuxASel = 2'b00;
                    end
                    SetREGSel(DSTREGSEL_no_addr,3'b010);
                end
                8'h08: begin 
                    if (OPCODE_addr == 6'h05) begin SetREGSel(DSTREGSEL_no_addr,3'b001); end // INC
                    else begin SetREGSel(DSTREGSEL_no_addr,3'b000); end // DEC
                    ResetAgain = 0;
                end
            endcase
        end
        6'h07, 6'h08, 6'h09, 6'h0A, 6'h0B, 6'h0E, 6'h18: begin
            case (OPCODE_addr)
                6'h07: ALU_FunSel = 5'b11011; // LSL
                6'h08: ALU_FunSel = 5'b11100; // LSR
                6'h09: ALU_FunSel = 5'b11101; // ASR
                6'h0A: ALU_FunSel = 5'b11110; // CSL
                6'h0B: ALU_FunSel = 5'b11111; // CSR
                6'h0E: ALU_FunSel = 5'b10010; // NOT
                6'h18: begin ALU_FunSel = 5'b10000; ALU_WF = _ALUSystem.IROut[9]; end
            endcase
            if(!SREG1SEL_no_addr[2]) begin // if source is from ARF
                case(T)
                    8'h04: begin
                        ARF_OutCSel = SREG1SEL_no_addr[1:0] ^ 2'b01; // mapping different for SREGSEL and ARF C Sel
                        MuxASel = 2'b01;
                        SetScratchSel(2'b00, 3'b010);
                        RF_OutASel = 3'b100;
                    end
                    8'h08: begin
                        MuxBSel = 2'b00;
                        MuxASel = 2'b00;
                        SetREGSel(DSTREGSEL_no_addr,3'b010);
                        RF_ScrSel = 4'b1111;
                        ResetAgain = 0;
                    end
                endcase
            end else begin // if source is from RF
                case(T)
                    8'h04: begin
                        RF_OutASel = {1'b0,SREG1SEL_no_addr[1:0]};
                        MuxBSel = 2'b00;
                        MuxASel = 2'b00;
                        SetREGSel(DSTREGSEL_no_addr,3'b010);
                        ResetAgain = 0;
                    end
                endcase
            end
        end
        6'h11, 6'h14: begin // MOVH:  DSTREG[15:8] ? IMMEDIATE (8-bit) // MOVL: DSTREG[7:0] ? IMMEDIATE (8-bit)
            case(T)
                8'h04: begin // Set DREGSEL and write [15:7].
                    if(OPCODE_addr == 6'h11) begin SetREGSel({1'b1, RSEL_addr}, 3'b110); end
                    else begin SetREGSel({1'b1, RSEL_addr}, 3'b101); end
                    MuxASel = 2'b11;
                    ResetAgain = 0;
                end
            endcase
        end
        6'h12: begin // LDR(16-bit)  Rx = M[AR]
            case(T)
                8'h04: begin 
                    ARF_OutDSel = 2'b10; // AR is pointing memory
                    Mem_WR = 0; // read
                    Mem_CS = 0; // enable
                    MuxASel = 2'b10; // MemOut
                    SetREGSel({1'b1, RSEL_addr}, 3'b100);
                    ResetAgain = 0;
                end
            endcase
        end
        6'h13: begin // STR(16-bit) M[AR] = Rx (AR is 16-bit register)
            ALU_FunSel = 5'b10000; // A
            case(T)
                8'h04: begin
                    RF_OutASel = {1'b0, RSEL_addr}; // A -> Rx
                    ARF_OutDSel = 2'b10; // AR is pointing Memory.
                    MuxCSel = 1'b0; // We select [7:0] LSB for ALU_Out.
                    Mem_WR = 1; // Write mode is one.
                    Mem_CS = 0; // Memory enabled.
                    ResetAgain = 0;
                end
            endcase
        end
        6'h1E: begin // BX  M[SP] = PC, PC = Rx
            ALU_FunSel = 5'b10000; // ALUOut <- A
            case(T)
                8'h04: begin
                    RF_OutASel = 3'b100; // S1
                    ARF_OutDSel = 2'b11; // SP is pointing memory.
                    SetScratchSel(2'b00, 3'b010);   // Enable only S2 and load
                    ARF_OutCSel = 2'b00;    // OutCSel = PC.
                    MuxASel = 2'b01;        // Select OutCSel
                end
                8'h08: begin
                    Mem_CS = 0; // Enable
                    Mem_WR = 1; // Write
                    MuxCSel = 1'b1; // MSB
                    SetREGSel(3'b010,3'b000); // sp is DEC.
                end
                8'h10: begin
                    MuxCSel = 1'b0; // LSB
                    //ARF_RegSel = 3'b111; // Disable SP incrementation.
                end
                8'h20: begin
                    Mem_CS = 1; // Disable Memory
                    RF_OutASel = {1'b0, RSEL_addr}; // A -> Rx
                    MuxBSel = 2'b00;
                    SetREGSel(3'b000, 3'b100); // load into PC
                    ResetAgain = 0;
                end
            endcase
        end
        6'h1F: begin // BL PC = M[SP]
            case(T)
                8'h04: begin 
                    SetREGSel(3'b010 ,3'b001); // increment the sp
                end
                8'h08: begin
                    ARF_OutDSel = 2'b11; // sp is pointing memory
                    Mem_WR = 0; // read
                    Mem_CS = 0; // enable
                    MuxBSel = 2'b10; // MemOut
                    SetREGSel(3'b000, 3'b100); // pc is enabled and only low loaded.
                end
                8'h10: begin
                    SetREGSel(3'b010 ,3'b001); // increment the sp
                end
                8'h20: begin
                    SetREGSel(3'b000, 3'b110); // pc is enabled and high part is loaded.
                    ResetAgain = 0;
                end
            endcase
        end
        6'h20: begin // LDRIM // Rx = VALUE (VALUE defined in ADDRESS bits)
            case(T) 
                8'h04: begin // Get IR to S1
                    MuxASel = 2'b11;        // Select IROut[7:0] 
                    SetREGSel({1'b1, RSEL_addr}, 3'b100); // Register <- 8-bit Address lo
                    ResetAgain = 0;
                end
            endcase
        end
        6'h21: begin // STRIM  M[AR+OFFSET] ? Rx (AR is 16-bit register) (OFFSET defined in ADDRESS bits)
            case(T)
                8'h04: begin
                    ALU_FunSel = 5'b10100;   // ALUOut = A + B
                    MuxASel = 2'b11;        // Select IROut[7:0] 
                    SetScratchSel(2'b00, 3'b111);   // Enable only S1 sign extended.
                    RF_OutASel = 3'b100; //A is S1
                    RF_OutBSel = 3'b101; // B is S2
                    ARF_OutCSel = 2'b10; // AR 
                end
                8'h08: begin
                    MuxASel = 2'b01; // ar is selected
                    SetScratchSel(2'b01, 3'b010); // s2 is loaded with AR
                end
                8'h10: begin
                    MuxBSel = 2'b00; // ALUOUT
                    SetREGSel(3'b011, 3'b010); // ar is loaded with aluout
                    RF_ScrSel = 4'b1111;
                end
                8'h20: begin
                    ALU_FunSel = 5'b10000; // aluout is A.
                    RF_OutASel = {1'b0, RSEL_addr}; // rx is selected in a 
                    RF_RegSel = 4'b1111; // disabled rf
                    ARF_OutDSel = 2'b10; // ar is pointing mem
                    MuxCSel = 1'b0; // LSB
                    Mem_CS = 0;  // enabled
                    Mem_WR = 1;  // write
                    SetREGSel(3'b011 ,3'b001); // increment ar.
                end
                8'h40: begin
                    MuxCSel = 1'b1; // MSB
                    ResetAgain = 0;
                end  
            endcase
        end
    endcase
    T = T + T;
end
end
endmodule