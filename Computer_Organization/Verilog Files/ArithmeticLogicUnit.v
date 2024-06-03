`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: ITU Computer Engineering Department
// Engineers: Yusuf Yildiz - 150210006
//            Safak Ozkan Pala - 150210016
// Project Name: BLG222E Project 2 ArithmeticLogicUnit
//////////////////////////////////////////////////////////////////////////////////

module ArithmeticLogicUnit (A, B, FunSel, WF, Clock, ALUOut, FlagsOut);
    input [15:0] A;             // Input A
    input [15:0] B;             // Input B
    input [4:0] FunSel;         // Function selection control
    input WF;                   // Write Flag
    input Clock;                // Clock input
    output reg [15:0] ALUOut;   // Output ALUOut
    output reg [3:0] FlagsOut;  // Output flags: Z, C, N, O
    
reg [16:0] Result;     // Result of ALU operation in 16-bit
reg [8:0] Result8Bit;  // Result of ALU operation in 8-bit
reg [3:0] Flags;       // Flags: Z, C, N, O
reg Operation16Bit;
reg OperationArithmetic;
reg AdditionFlag;
reg ASRFlag;
reg OperationShiftFlag;
reg CircularShiftFlag;

// ALU operations
always @(*) begin
    OperationArithmetic = 0; // set to 0 in every time
    Operation16Bit = 0;
    ASRFlag = 0;
    OperationShiftFlag = 0;
    CircularShiftFlag = 0;
    Flags = FlagsOut; // assign the real FlagsOut to the temporary Flags
    
    case (FunSel)
        5'b00000: begin Result8Bit = A[7:0]; end // A (8-bit)
//        5'b00000: begin Result = {{A[7], A[7]}, A[7:0]}; Operation16Bit = 0; end // A (8-bit)
        5'b10000: begin Result = A; Operation16Bit = 1; end // A (16-bit)
        
        5'b00001: begin Result8Bit = B[7:0]; end // B (8-bit)
//        5'b00001: begin Result = {{B[7], B[7]}, B[7:0]}; Operation16Bit = 0; end // B (8-bit)
        5'b10001: begin Result = B; Operation16Bit = 1; end // B (16-bit)
        
        5'b00010: begin Result8Bit = ~A[7:0]; end // NOT A (8-bit)
//        5'b00010: begin Result = ~{{A[7], A[7]}, A[7:0]}; Operation16Bit = 0; end // NOT A (8-bit)
        5'b10010: begin Result = ~A; Operation16Bit = 1; end // NOT A (16-bit) // for not considering Carry is set in if block
//        5'b10010: begin Result = {1'b0, ~A}; Operation16Bit = 1; end // NOT A (16-bit)
                                                                                        // 0 added in the front
        5'b00011: begin Result8Bit = ~B[7:0]; end // NOT B (8-bit)
//        5'b00011: begin Result = ~{{B[7], B[7]}, B[7:0]}; Operation16Bit = 0; end // NOT B (8-bit)
        5'b10011: begin Result = ~B; Operation16Bit = 1; end // NOT B (16-bit)
//        5'b10011: begin Result = {1'b0, ~B}; Operation16Bit = 1; end // NOT B (16-bit)
        
        5'b00100: begin Result8Bit = A[7:0] + B[7:0]; OperationArithmetic = 1; AdditionFlag = 1; end // A + B (8-bit)
//        5'b00100: begin Result = {{8{A[7]}}, A[7:0]} + {{8{B[7]}}, B[7:0]}; Operation16Bit = 0; OperationArithmetic = 1; end // A + B (8-bit)
        5'b10100: begin Result = A + B; Operation16Bit = 1; OperationArithmetic = 1; AdditionFlag = 1; end // A + B (16-bit)
        
        5'b00101: begin Result8Bit = A[7:0] + B[7:0] + FlagsOut[2]; OperationArithmetic = 1; AdditionFlag = 1; end // A + B + Carry (8-bit)
//        5'b00101: begin Result = {{8{A[7]}}, A[7:0]} + {{8{B[7]}}, B[7:0]} + FlagsOut[2]; Operation16Bit = 0; OperationArithmetic = 1; end // A + B + Carry (8-bit)
        5'b10101: begin Result = A + B + FlagsOut[2]; Operation16Bit = 1; OperationArithmetic = 1; AdditionFlag = 1; end // A + B + Carry (16-bit)
        
        5'b00110: begin // A - B (8-bit)
            OperationArithmetic = 1; 
            AdditionFlag = 0;
//            Result = {{9{A[7]}}, A[7:0]} - {{9{B[7]}}, B[7:0]};
            Result8Bit = A[7:0] - B[7:0];
            Result8Bit[8] = ~(|(A[7:0] < B[7:0])); // for the overflow flag
        end 
        5'b10110: begin // A - B (16-bit)
            Result = A - B; 
            Operation16Bit = 1; 
            OperationArithmetic = 1; 
            AdditionFlag = 0;
            Result[16] = ~(|(A < B)); // for the overflow flag
        end 

        5'b00111: begin Result8Bit = A[7:0] & B[7:0]; end // A AND B (8-bit)
        5'b10111: begin Result = A & B; Operation16Bit = 1; end // A AND B (16-bit)

        5'b01000: begin Result8Bit = A[7:0] | B[7:0]; end // A OR B (8-bit)
        5'b11000: begin Result = A | B; Operation16Bit = 1; end // A OR B (16-bit)
        
        5'b01001: begin Result8Bit = A[7:0] ^ B[7:0]; end // A XOR B (8-bit)
        5'b11001: begin Result = A ^ B; Operation16Bit = 1; end // A XOR B (16-bit)
        
        5'b01010: begin Result8Bit = ~(A[7:0] & B[7:0]); end // A NAND B (8-bit)
        5'b11010: begin Result = ~(A & B); Operation16Bit = 1; end // A NAND B (16-bit)
        
        // SHIFT Operations
        5'b01011: begin // LSL A (8-bit)
            Result8Bit = (A[7:0] << 1); 
            Flags[2] = A[7];
            OperationShiftFlag = 1;
            OperationArithmetic = 1; 
        end
        5'b11011: begin // LSL A (16-bit)
            Result = (A << 1); 
            Flags[2] = A[15];
            OperationShiftFlag = 1;
            Operation16Bit = 1;
            OperationArithmetic = 1; 
        end
        5'b01100: begin // LSR A (8-bit)
            Flags[2] = A[0];
            Result8Bit = (A[7:0] >> 1); 
            OperationShiftFlag = 1;
            OperationArithmetic = 1; 
        end
        5'b11100: begin // LSR A (16-bit)
            Flags[2] = A[0];
            Result = (A >> 1); 
            OperationShiftFlag = 1;
            Operation16Bit = 1;
            OperationArithmetic = 1; 
        end
        5'b01101: begin // ASR A (8-bit)
            Result8Bit = {A[7], A[7:1]}; 
            Flags[2] = A[0]; // Set the carry as A[0]
            ASRFlag = 1; 
            OperationShiftFlag = 1;
            OperationArithmetic = 1; 
        end 
        5'b11101: begin // ASR A (16-bit)
            Result = {A[15], A[15:1]}; 
            Flags[2] = A[0]; // Set the carry as A[0]
            ASRFlag = 1; 
            OperationShiftFlag = 1; 
            Operation16Bit = 1;
            OperationArithmetic = 1; 
        end 
        5'b01110: begin // CSL A (8-bit) // Result is recalculated because Flags change with Clock, so update the result in Clock block
            Result8Bit = {{A[7:0], Flags[2]}};
            Flags[2] = Result8Bit[8]; // Update carry flag with MSB of A
            Result8Bit = (Result8Bit << 1); // Shift A left by one bit
            Result8Bit = Result8Bit[8:1];
            OperationShiftFlag = 1;
            OperationArithmetic = 1; 
            CircularShiftFlag = 1;
        end
        5'b11110: begin // CSL A (16-bit) // Result is recalculated because Flags change with Clock, so update the result in Clock block
            Result = {{A, Flags[2]}};
            Flags[2] = Result[16]; // Update carry flag with MSB of A
            Result = (Result << 1); // Shift A left by one bit
            Result = Result[16:1];
            OperationShiftFlag = 1;
            Operation16Bit = 1;
            OperationArithmetic = 1; 
            CircularShiftFlag = 1;
        end
        5'b01111: begin // CSR A (8-bit) // Result is recalculated because Flags change with Clock, so update the result in Clock block
            Result8Bit = {{Flags[2], A[7:0]}};
            Flags[2] = Result8Bit[0];
            Result8Bit = (Result8Bit >> 1);
            OperationShiftFlag = 1;
            OperationArithmetic = 1; 
            CircularShiftFlag = 1;
        end
        5'b11111: begin // CSR A (16-bit) // Result is recalculated because Flags change with Clock, so update the result in Clock block
            Result = {{Flags[2], A}};
            Flags[2] = Result[0];
            Result = (Result >> 1);
            OperationShiftFlag = 1;
            Operation16Bit = 1;
            OperationArithmetic = 1; 
            CircularShiftFlag = 1;
        end
    endcase
    
    if (Operation16Bit == 1) begin     
//        Flags[2] = Result[16]; // Set the C Flag
        if (OperationArithmetic == 1) begin 
            if (~OperationShiftFlag) begin
                Flags[2] = Result[16]; // Set the C Flag if not shift operation since it is set in Shift Operations already
                if (AdditionFlag && (A[15] == B[15]) && (Result[15] != A[15])) begin  // Same sign, different result sign (original check)
                    Flags[0] = 1;
                end else if (~AdditionFlag && (A[15] != B[15]) && (B[15] == Result[15])) begin  // Different sign, same result sign (overflow)
                    Flags[0] = 1;
                end else begin
                    Flags[0] = 0;
                end  
            end
        end
//        end else begin
//            Flags[0] = 0; // Overflow can not occur in other than the arithmetic operation
//        end      

        Flags[3] = (Result[15:0] == 16'h0000) ? 1 : 0;       // Z flag
        if (~ASRFlag) Flags[1] = Result[15];               // N flag
        
        if (~CircularShiftFlag) ALUOut = Result[15:0]; 
    end else begin
//        Flags[2] = Result8Bit[8]; // Set the C Flag
        if (OperationArithmetic == 1) begin
            if (~OperationShiftFlag) begin
                Flags[2] = Result8Bit[8]; // Set the C Flag if not shift operation since it is set in Shift Operations already
                if (AdditionFlag && (A[7] == B[7]) && (Result8Bit[7] != A[7])) begin  // Same sign, different result sign (original check)
                    Flags[0] = 1;
                end else if (~AdditionFlag && (A[7] != B[7]) && (B[7] == Result8Bit[7])) begin  // Different sign, same result sign (overflow)
                    Flags[0] = 1;
                end else begin
                    Flags[0] = 0;
                end  
            end
        end     
                
        Flags[3] = (Result8Bit[7:0] == 8'h00) ? 1 : 0;       // Z flag
        if (~ASRFlag) Flags[1] = Result8Bit[7];               // N flag
        
        if (~CircularShiftFlag) ALUOut = {{8{Result8Bit[7]}}, Result8Bit[7:0]}; // pad with the sign bit
    end
    
end

// Set flags based on ALU operation
always @(posedge Clock) begin
    if (CircularShiftFlag == 1) begin
        if (Operation16Bit == 1) begin 
            ALUOut = Result[15:0]; 
        end else begin 
            ALUOut = {8'h00, Result8Bit[7:0]}; 
        end
    end
    if (WF == 1) begin
        FlagsOut = Flags;
    end
    
end

endmodule
