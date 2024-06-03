`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: ITU Computer Engineering Department
// Engineer: Kadir Ozlem
// Project Name: BLG222E Project 1 Simulation
//////////////////////////////////////////////////////////////////////////////////

module ArithmeticLogicUnitSimulation();
    reg[15:0] A, B;
    reg[4:0] FunSel;
    reg WF;
    wire[15:0] ALUOut;
    wire[3:0] FlagsOut;
    integer test_no;
    wire Z, C, N, O;
    CrystalOscillator clk();
    ArithmeticLogicUnit ALU( .A(A), .B(B), .FunSel(FunSel), .WF(WF), 
                            .Clock(clk.clock), .ALUOut(ALUOut), .FlagsOut(FlagsOut));
        
    FileOperation F();
    
    assign {Z,C,N,O} = FlagsOut;
    
    initial begin
        F.SimulationName ="ArithmeticLogicUnit";
        F.InitializeSimulation(0);
        clk.clock = 0;
        
        //Test 1
        test_no = 1;
        A = 16'h1234;
        B = 16'h4321;
        ALU.FlagsOut = 4'b1111;
        FunSel =5'b10100;
        WF =1;
        #5
        F.CheckValues(ALUOut,16'h5555, test_no, "ALUOut");
        F.CheckValues(Z,1, test_no, "Z");
        F.CheckValues(C,1, test_no, "C");
        F.CheckValues(N,1, test_no, "N");
        F.CheckValues(O,1, test_no, "O");
        //Test 2
        test_no = 2;
        clk.Clock();
        
        F.CheckValues(ALUOut,16'h5555, test_no, "ALUOut");
        F.CheckValues(Z,0, test_no, "Z");
        F.CheckValues(C,0, test_no, "C");
        F.CheckValues(N,0, test_no, "N");
        F.CheckValues(O,0, test_no, "O");

        //Test 3
        test_no = 3;
        A = 16'h7777;
        B = 16'h8889;
        ALU.FlagsOut = 4'b0000;
        FunSel =5'b10101;
        WF =1;
        #5
        clk.Clock();
        
        F.CheckValues(ALUOut,16'h0001, test_no, "ALUOut");
        F.CheckValues(Z,1, test_no, "Z");
        F.CheckValues(C,1, test_no, "C");
        F.CheckValues(N,0, test_no, "N");
        F.CheckValues(O,0, test_no, "O");
        
//        F.FinishSimulation();
        // ADDITIONAL TEST CASES
        //Test 4 A XOR B 8 BIT
        test_no = 4;
        A = 8'b1010_1010;
        B = 8'b1100_1100;
        ALU.FlagsOut = 4'b0111; // does not affect the O flag
        FunSel =5'b01001;
        WF =1;
        #5
        clk.Clock();
        
        F.CheckValues(ALUOut,16'h0066, test_no, "ALUOut");
        F.CheckValues(Z,0, test_no, "Z");
        F.CheckValues(C,1, test_no, "C");
        F.CheckValues(N,0, test_no, "N");
        F.CheckValues(O,1, test_no, "O");
        
        //Test 5 A NAND B 8 BIT
        test_no = 5;
        A = 8'b0011_0011;
        B = 8'b1111_1111;
        ALU.FlagsOut = 4'b0000;
        FunSel =5'b01010;
        WF =1;
        #5
        clk.Clock();
        
        F.CheckValues(ALUOut,16'hffcc, test_no, "ALUOut");
        F.CheckValues(Z,0, test_no, "Z");
        F.CheckValues(C,0, test_no, "C");
        F.CheckValues(N,1, test_no, "N");
        F.CheckValues(O,0, test_no, "O");
        
        //Test 6  NOT A 8 BIT
        test_no = 6;
        A = 8'b10110101; //B5
        B = 8'b10110101; //45
        ALU.FlagsOut = 4'b0001; // it must not override the O flag since it is 00010
        FunSel =5'b00010;
        WF = 1;
        #5
        clk.Clock();

        F.CheckValues(ALUOut,8'b01001010, test_no, "ALUOut");
//        F.CheckValues(ALU.Result8Bit,8'b01001010, test_no, "ALU8Bit");
//        F.CheckValues(ALU.OperationArithmetic,8'b01001010, test_no, "ALUOpAr");
//        F.CheckValues(ALU.Flags,8'b01001010, test_no, "ALUFlags");
        F.CheckValues(Z,0, test_no, "Z");
        F.CheckValues(C,0, test_no, "C");
        F.CheckValues(N,0, test_no, "N");
        F.CheckValues(O,1, test_no, "O");
        
        //Test 7 A AND B 16 BIT
        test_no = 7;    
        A = 16'hacd5;
        B = 16'hf0f0;
        ALU.FlagsOut = 4'b0101; // does not affect the O flag and C flag
        FunSel =5'b10111;
        WF =1;
        #5
        clk.Clock();
        
        F.CheckValues(ALUOut,16'ha0d0, test_no, "ALUOut");
        F.CheckValues(Z,0, test_no, "Z");
        F.CheckValues(C,1, test_no, "C");
        F.CheckValues(N,1, test_no, "N");
        F.CheckValues(O,1, test_no, "O");
        
        //Test 8  A+B+C 8 BIT
        test_no = 8;
        A = 8'b10110101; //B5
        B = 8'b10110101; //45
        ALU.FlagsOut = 4'b0000;
        FunSel =5'b00101;
        WF = 1;
        #5
        clk.Clock();

        F.CheckValues(ALUOut,8'b01101011, test_no, "ALUOut");
        F.CheckValues(Z,0, test_no, "Z");
        F.CheckValues(C,1, test_no, "C");
        F.CheckValues(N,0, test_no, "N");
        F.CheckValues(O,1, test_no, "O");
         
        //Test 9 A-B 8 BIT
        test_no = 9;
        A = 8'b10111101; //B5
        B = 8'b00110101; //45
        ALU.FlagsOut = 4'b0000;
        FunSel =5'b00110;
        WF = 1;
        #5
        clk.Clock();

        F.CheckValues(ALUOut, 16'hff88, test_no, "ALUOut");
        F.CheckValues(Z,0, test_no, "Z");
        F.CheckValues(C,1, test_no, "C");
        F.CheckValues(N,1, test_no, "N");
        F.CheckValues(O,0, test_no, "O");

        //Test 10 A-B 8 BIT
        test_no = 10; // no overflow occurs (-) - (-) = (+) and carry occurs
        A = 8'b1110_0010; 
        B = 8'b1100_1110;
        ALU.FlagsOut = 4'b0000;
        FunSel =5'b00110;
        WF = 1;
        #5
        clk.Clock();

        F.CheckValues(ALUOut, 8'b0001_0100, test_no, "ALUOut");
        F.CheckValues(Z,0, test_no, "Z");
        F.CheckValues(C,1, test_no, "C");
        F.CheckValues(N,0, test_no, "N"); 
        F.CheckValues(O,0, test_no, "O");
        
        //Test 11 A-B 16 BIT
        test_no = 11;
        A = 16'hffbd; //B5
        B = 16'h0035; //45
        ALU.FlagsOut = 4'b0000;
        FunSel =5'b10110;
        WF = 1;
        #5
        clk.Clock();

        F.CheckValues(ALUOut,16'hff88, test_no, "ALUOut");
//        F.CheckValues(ALU.Result8Bit,8'b01001010, test_no, "ALU8Bit");
        F.CheckValues(Z,0, test_no, "Z");
        F.CheckValues(C,1, test_no, "C");
        F.CheckValues(N,1, test_no, "N");
        F.CheckValues(O,0, test_no, "O");
        
        //Test 12 A-B 8 BIT
        test_no = 12;
        A = 8'b1111_1101; // overflow occurs (-) - (+) = (+), carry occurs
        B = 8'b0111_1111;

        ALU.FlagsOut = 4'b0000;
        FunSel =5'b00110;
        WF = 1;
        #5
        clk.Clock();

        F.CheckValues(ALUOut, 8'b0111_1110, test_no, "ALUOut");
        F.CheckValues(Z,0, test_no, "Z");
        F.CheckValues(C,1, test_no, "C");
        F.CheckValues(N,0, test_no, "N"); 
        F.CheckValues(O,1, test_no, "O");
        
        //Test 13 A-B 16 BIT // (+) - (-) = (-), overflow occurs, no carry
        test_no = 13;
        A = 16'h4e20; 
        B = 16'h9e58; 
        ALU.FlagsOut = 4'b0000;
        FunSel =5'b10110;
        WF = 1;
        #5
        clk.Clock();

        F.CheckValues(ALUOut,16'hafc8, test_no, "ALUOut");
        F.CheckValues(Z,0, test_no, "Z");
        F.CheckValues(C,0, test_no, "C");
        F.CheckValues(N,1, test_no, "N");
        F.CheckValues(O,1, test_no, "O");
        
        //Test 14 LSL A 16 BIT
        test_no = 14;
        A = 16'hc000; 
        B = 16'h0000;

        ALU.FlagsOut = 4'b0000;
        FunSel =5'b11011;
        WF = 1;
        #5
        clk.Clock();

        F.CheckValues(ALUOut, 16'h8000, test_no, "ALUOut");
        F.CheckValues(Z,0, test_no, "Z");
        F.CheckValues(C,1, test_no, "C");
        F.CheckValues(N,1, test_no, "N"); 
        F.CheckValues(O,0, test_no, "O");
        
        //Test 15 LSR A 16 BIT
        test_no = 15;
        A = 16'h0001; 
        B = 16'h0000;

        ALU.FlagsOut = 4'b0001; // it must not override the O Flag
        FunSel =5'b11100;
        WF = 1;
        #5
        clk.Clock();

        F.CheckValues(ALUOut, 16'h0000, test_no, "ALUOut");
        F.CheckValues(Z,1, test_no, "Z");
        F.CheckValues(C,1, test_no, "C");
        F.CheckValues(N,0, test_no, "N"); 
        F.CheckValues(O,1, test_no, "O");
        
        //Test 16 ASR A 16 BIT // with N = 0
        test_no = 16;
        A = 16'he003; 
        B = 16'h0000;

        ALU.FlagsOut = 4'b0001; // it must not override the O Flag
        FunSel =5'b11101;
        WF = 1;
        #5
        clk.Clock();

        F.CheckValues(ALUOut, 16'hf001, test_no, "ALUOut");
        F.CheckValues(Z,0, test_no, "Z");
        F.CheckValues(C,1, test_no, "C");
        F.CheckValues(N,0, test_no, "N"); 
        F.CheckValues(O,1, test_no, "O"); // does not affect the O
        
        //Test 17 ASR A 16 BIT // with N = 1
        test_no = 17;
        A = 16'he003; 
        B = 16'h0000;

        ALU.FlagsOut = 4'b0110; // it must not override the O Flag
        FunSel =5'b11101;
        WF = 1;
        #5
        clk.Clock();

        F.CheckValues(ALUOut, 16'hf001, test_no, "ALUOut");
        F.CheckValues(Z,0, test_no, "Z");
        F.CheckValues(C,1, test_no, "C");
        F.CheckValues(N,1, test_no, "N"); 
        F.CheckValues(O,0, test_no, "O"); // does not affect the O
        
        //Test 18 CSR A 16 BIT // O = 1
        test_no = 18;
        A = 16'h0000; 
        B = 16'h0000;

        ALU.FlagsOut = 4'b0101; // it must not override the O Flag
        FunSel =5'b11111;
        WF = 1;
        #5
        clk.Clock();

        F.CheckValues(ALUOut, 16'h8000, test_no, "ALUOut");
        F.CheckValues(Z,0, test_no, "Z");
        F.CheckValues(C,0, test_no, "C");
        F.CheckValues(N,1, test_no, "N"); 
        F.CheckValues(O,1, test_no, "O"); // does not affect the O
        
        //Test 19 CSR A 16 BIT // O = 0
        test_no = 19;
        A = 16'h0001; 
        B = 16'h0000;

        ALU.FlagsOut = 4'b0010; // it must not override the O Flag
        FunSel =5'b11111;
        WF = 1;
        #5
        clk.Clock();

        F.CheckValues(ALUOut, 16'h0000, test_no, "ALUOut");
        F.CheckValues(Z,1, test_no, "Z");
        F.CheckValues(C,1, test_no, "C");
        F.CheckValues(N,0, test_no, "N"); 
        F.CheckValues(O,0, test_no, "O"); // does not affect the O

        //Test 20 CSL A 16 BIT // O = 1
        test_no = 20;
        A = 16'h8000; 
        B = 16'h0000;

        ALU.FlagsOut = 4'b0001; // it must not override the O Flag
        FunSel =5'b11110;
        WF = 1;
        #5
        clk.Clock();

        F.CheckValues(ALUOut, 16'h0000, test_no, "ALUOut");
        F.CheckValues(Z,1, test_no, "Z");
        F.CheckValues(C,1, test_no, "C");
        F.CheckValues(N,0, test_no, "N"); 
        F.CheckValues(O,1, test_no, "O"); // does not affect the O
        
        //Test 21 CSL A 16 BIT // O = 0
        test_no = 21;
        A = 16'hc000; 
        B = 16'h0000;

        ALU.FlagsOut = 4'b0100; // it must not override the O Flag
        FunSel =5'b11110;
        WF = 1;
        #5
        clk.Clock();

        F.CheckValues(ALUOut, 16'h8001, test_no, "ALUOut");
        F.CheckValues(Z,0, test_no, "Z");
        F.CheckValues(C,1, test_no, "C");
        F.CheckValues(N,1, test_no, "N"); 
        F.CheckValues(O,0, test_no, "O"); // does not affect the O
        
        //Test 22 CSL A 16 BIT // O = 0
        test_no = 22;
        A = 16'hca30; 
        B = 16'h0000;

        ALU.FlagsOut = 4'b0100; // it must not override the O Flag
        FunSel =5'b11110;
        WF = 1;
        #5
        clk.Clock();

        F.CheckValues(ALUOut, 16'h9461, test_no, "ALUOut");
        F.CheckValues(Z,0, test_no, "Z");
        F.CheckValues(C,1, test_no, "C");
        F.CheckValues(N,1, test_no, "N"); 
        F.CheckValues(O,0, test_no, "O"); // does not affect the O
        
        //Test 23 LSL A 8 BIT
        test_no = 23;
        A = 8'b1100_0001; 
        B = 8'b0000_0000;

        ALU.FlagsOut = 4'b0001; // O = 1
        FunSel =5'b01011;
        WF = 1;
        #5
        clk.Clock();

        F.CheckValues(ALUOut, 16'hff82, test_no, "ALUOut");
        F.CheckValues(Z,0, test_no, "Z");
        F.CheckValues(C,1, test_no, "C");
        F.CheckValues(N,1, test_no, "N"); 
        F.CheckValues(O,1, test_no, "O");
        
        //Test 24 LSR A 8 BIT
        test_no = 24;
        A = 8'b0000_0001; 
        B = 16'h0000;

        ALU.FlagsOut = 4'b0011; // it must not override the O Flag
        FunSel =5'b01100;
        WF = 1;
        #5
        clk.Clock();

        F.CheckValues(ALUOut, 16'h0000, test_no, "ALUOut");
        F.CheckValues(Z,1, test_no, "Z");
        F.CheckValues(C,1, test_no, "C");
        F.CheckValues(N,0, test_no, "N"); 
        F.CheckValues(O,1, test_no, "O");
        
        //Test 25 ASR A 8 BIT // with N = 0
        test_no = 25;
        A = 8'b1100_0011; 
        B = 16'h0000;

        ALU.FlagsOut = 4'b0011; // it must not override the O Flag
        FunSel =5'b01101;
        WF = 1;
        #5
        clk.Clock();

        F.CheckValues(ALUOut, 16'hffe1, test_no, "ALUOut");
        F.CheckValues(Z,0, test_no, "Z");
        F.CheckValues(C,1, test_no, "C");
        F.CheckValues(N,1, test_no, "N"); 
        F.CheckValues(O,1, test_no, "O"); // does not affect the O
        
        //Test 26 ASR A 8 BIT // with N = 1
        test_no = 26;
        A = 8'b0001_1100; 
        B = 16'h0000;

//        ALU.FlagsOut = 4'b0110; // taken from above as 0111
        FunSel =5'b01101;
        WF = 1;
        #5
        clk.Clock();

        F.CheckValues(ALUOut, 8'b0000_1110, test_no, "ALUOut");
        F.CheckValues(Z,0, test_no, "Z");
        F.CheckValues(C,0, test_no, "C");
        F.CheckValues(N,1, test_no, "N"); // actually N = 0 but it must not change the N
        F.CheckValues(O,1, test_no, "O"); // does not affect the O
        
        //Test 27 CSR A 8 BIT // O = 1
        test_no = 27;
        A = 8'b0000_0000; 
        B = 16'h0000;

        ALU.FlagsOut = 4'b0101; // it must not override the O Flag
        FunSel =5'b01111;
        WF = 1;
        #5
        clk.Clock();

        F.CheckValues(ALUOut, 16'hff80, test_no, "ALUOut");
        F.CheckValues(Z,0, test_no, "Z");
        F.CheckValues(C,0, test_no, "C");
        F.CheckValues(N,1, test_no, "N"); 
        F.CheckValues(O,1, test_no, "O"); // does not affect the O
        
        //Test 28 CSR A 8 BIT // O = 0
        test_no = 28;
        A = 8'b0000_0001; 
        B = 16'h0000;

        ALU.FlagsOut = 4'b0010; // it must not override the O Flag
        FunSel =5'b01111;
        WF = 1;
        #5
        clk.Clock();

        F.CheckValues(ALUOut, 16'h0000, test_no, "ALUOut");
        F.CheckValues(Z,1, test_no, "Z");
        F.CheckValues(C,1, test_no, "C");
        F.CheckValues(N,0, test_no, "N"); 
        F.CheckValues(O,0, test_no, "O"); // does not affect the O

//        //Test 32 CSR A 8 BIT // O = 0
//        test_no = 32;
////        A = 8'b0000_0001; 
////        B = 16'h0000;

////        ALU.FlagsOut = 4'b0010; // it must not override the O Flag
////        FunSel =5'b01111;
////        WF = 1;
//        #5
//        clk.Clock();

//        F.CheckValues(ALUOut, 16'hff80, test_no, "ALUOut");
//        F.CheckValues(Z,0, test_no, "Z");
//        F.CheckValues(C,0, test_no, "C");
//        F.CheckValues(N,1, test_no, "N"); 
//        F.CheckValues(O,0, test_no, "O"); // does not affect the O
        
        //Test 29 CSL A 8 BIT // O = 1
        test_no = 29;
        A = 8'b1000_0110; 
        B = 16'h0000;

        ALU.FlagsOut = 4'b0101; // it must not override the O Flag
        FunSel =5'b01110;
        WF = 1;
        #5
        clk.Clock();

        F.CheckValues(ALUOut, 16'h000d, test_no, "ALUOut");
        F.CheckValues(Z,0, test_no, "Z");
        F.CheckValues(C,1, test_no, "C");
        F.CheckValues(N,0, test_no, "N"); 
        F.CheckValues(O,1, test_no, "O"); // does not affect the O
        
        //Test 30 CSL A 8 BIT // O = 0
        test_no = 30;
        A = 8'b1000_0000; 
        B = 16'h0000;

        ALU.FlagsOut = 4'b0000; // it must not override the O Flag
        FunSel =5'b01110;
        WF = 1;
        #5
        clk.Clock();

        F.CheckValues(ALUOut, 16'h0000, test_no, "ALUOut");
        F.CheckValues(Z,1, test_no, "Z");
        F.CheckValues(C,1, test_no, "C");
        F.CheckValues(N,0, test_no, "N"); 
        F.CheckValues(O,0, test_no, "O"); // does not affect the O
        
        //Test 31 CSL A 8 BIT // O = 0
        test_no = 31;
        A = 8'b0110_0001; 
        B = 16'h0000;

        ALU.FlagsOut = 4'b0100; // it must not override the O Flag
        FunSel =5'b01110;
        WF = 1;
        #5
        clk.Clock();

        F.CheckValues(ALUOut, 16'hffc3, test_no, "ALUOut");
        F.CheckValues(Z,0, test_no, "Z");
        F.CheckValues(C,0, test_no, "C");
        F.CheckValues(N,1, test_no, "N"); 
        F.CheckValues(O,0, test_no, "O"); // does not affect the O
        
        F.FinishSimulation();
    end
endmodule