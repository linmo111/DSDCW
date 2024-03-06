//// CORDIC parameters
//`define M  14; // No. of iterations
//`define W  32; // Bit width

// Interface

module CORDIC #(
	parameter M =16,
	parameter W=32,
	parameter EXONENT_BITS = 8,
	parameter MANTISSA_BITS = 23,
	parameter INTEGER_BITS = 2,
	parameter FRACTION_BITS = 30

	)(
	input [W-1:0] dataa, //this input is float 
	input [W-1:0] datab, 
	input clk,
//	input rst,
//	input clk_en,
	
	output reg [W-1:0] result, //output should also be float
	output wire [W-1:0] fixedpoint_in,
	output wire [W-1:0] fixedpoint_out
//	output reg [23:0] fixedmanti,
//	output reg [7:0] shiftnum
//	output reg [w-1:0] fixedpoint_in
	);

	// Signals
	reg signed [W-1:0] x [0:M-1];
	reg signed [W-1:0] y [0:M-1];
	reg signed [W-1:0] z [0:M-1]; // Pipeline registers
//	reg [M-1:0] di [0:M-1]; // M-bit direction vector
	reg signed [W-1:0] e [0:M-1];
	
  
  // Fixed point bits
	reg signed [W-1:0] fixed_in; 
//	reg 
	
	
	
//	reg [W-1:0] e [0:M-1] = {
//	 32'b00111111010010010000111111011011,
//	 32'b00111110111011010110001100110001,
//	 32'b00111110011110101101101110110000,
//	 32'b00111101111111001010000110001011,
//	 32'b00111101011111111010101011011110,
//	 
//	 32'b00111100111111111110101010101110,
//	 32'b00111100011111111111101010101010,
//	 32'b00111011111111111111111010101011,
//	 32'b00111011011111111111111110101010,
//	 32'b00111010111111111111111111101111,
//	 
//	 32'b00111010011111111111111111100110,
//	 32'b00111001111111111111111111010101,
//	 32'b00111001011111111111111111010101,
//	 32'b00111000111111111111111111010101,
//	 32'b00111000011111111111111111010101,
//	 
//	 32'b00110111111111111111111011000010,
//	 32'b00110111011111111111110010011100,
//    32'b00110110111111111111110010011100
//
//};
initial begin
//	e[0]=32'b00111111010010010000111111011011;
//	e[1]=32'b00111110111011010110001100110001;
//	e[2]=32'b00111110011110101101101110110000;
//	e[3]=32'b00111101111111001010000110001011;
//	e[4]=32'b00111101011111111010101011011110;
//	
//	e[5]=32'b00111100111111111110101010101110;
//	e[6]=32'b00111100011111111111101010101010;
//	e[7]=32'b00111011111111111111111010101011;
//	e[8]=32'b00111011011111111111111110101010;
//	e[9]=32'b00111010111111111111111111101111;
//	
//	e[10]=32'b00111010011111111111111111100110;
//	e[11]=32'b00111001111111111111111111010101;
//	e[12]=32'b00111001011111111111111111010101;
//	e[13]=32'b00111000111111111111111111010101;
//	e[14]=32'b00111000011111111111111111010101;
//	
//	e[15]=32'b00110111111111111111111011000010;
//	e[16]=32'b00110111011111111111110010011100;
//	e[17]=32'b00110110111111111111110010011100;
	e[0]=32'b00110010010000111111011010101000;
	e[1]=32'b00011101101011000110011100000101;
	e[2]=32'b00001111101011011011101011111100;
	e[3]=32'b00000111111101010110111010100110;
	e[4]=32'b00000011111111101010101101110110;
	
	e[5]=32'b00000001111111111101010101011011;
	e[6]=32'b00000000111111111111101010101010;
	e[7]=32'b00000000011111111111111101010101;
	e[8]=32'b00000000001111111111111111101010;
	e[9]=32'b00000000000111111111111111111101;
	
	e[10]=32'b00000000000011111111111111111110;
	e[11]=32'b00000000000001111111111111111111;
	e[12]=32'b00000000000000111111111111111111;
	e[13]=32'b00000000000000011111111111111111;
	e[14]=32'b00000000000000001111111111111111;
	e[15]=32'b00000000000000000111111111111111;
//	e[11]=32'b00111001111111111111111111010101;
//	e[12]=32'b00111001011111111111111111010101;
//	e[13]=32'b00111000111111111111111111010101;
//	e[14]=32'b00111000011111111111111111010101;
//	
//	e[15]=32'b00110111111111111111111011000010;
//	e[16]=32'b00110111011111111111110010011100;
//	e[17]=32'b00110110111111111111110010011100;

	
end

//conversion
wire [7:0] exp;
//wire [W-10:0] manti;
wire sign;
 assign exp = dataa[30:23];
// assign manti = dataa[22:0]; 
 assign sign= dataa[31];
 wire [23:0] fixed_mantissa;
 assign fixed_mantissa= {1'b1, dataa[22:0]};
 reg signed [7:0] shift_amount;
 always @(*) begin //from floating point input to 
 
    //24 bit
//	fixedmanti=fixed_mantissa;
   

  // Calculate the shift amount based on the exponent
  shift_amount = exp - 127 ;
//  shiftnum=exp-127;

  // Perform the shift operation
  if (shift_amount >= 24) begin
		// Shift left beyond the integer bits
		fixed_in = {sign, fixed_mantissa, 7'b0};
  end else if (shift_amount >= 0) begin
		// Shift left within the integer bits
		fixed_in = {sign, fixed_mantissa << shift_amount, 7'b0};
  end else begin
		// Shift right within the fractional bits
		if (shift_amount >= -30) begin
			 fixed_in = {sign, fixed_mantissa >> -shift_amount,7'b0};
		end else begin
			 fixed_in = {sign, 31'b0};
		end
  end
  
 end
 assign fixedpoint_in=fixed_in;

//reg [31:0] res;
//reg [31:0] expr;
 wire [31:0] tmp;
 wire [31:0] int_part;
 wire [31:0] frac_part;
 assign tmp=x[M-1];
 assign int_part = tmp[31:30];
 assign frac_part=tmp[29:0];
 reg [7:0] exponent;
 reg [22:0] mantissa;
 assign fixedpoint_out=x[M-1];
 always @(*) begin   //from fixed point to floating point output
    if (int_part == 2'b00) begin
            if (frac_part[29]) begin
                exponent = 127 - 1;
                mantissa = frac_part[28:6];
            end else if (frac_part[28]) begin
                exponent = 127 - 2;
                mantissa = frac_part[27:5];
            end else if (frac_part[27]) begin
                exponent = 127 - 3;
                mantissa = frac_part[26:4];
            end else if (frac_part[26]) begin
                exponent = 127 - 4;
                mantissa = frac_part[25:3];
            end else if (frac_part[25]) begin
                exponent = 127 - 5;
                mantissa = frac_part[24:2];
            end else if (frac_part[24]) begin
                exponent = 127 - 6;
                mantissa = frac_part[23:1];
            end else if (frac_part[23]) begin
                exponent = 127 - 7;
                mantissa = frac_part[22:0];
            end else begin
                exponent = 0;
                mantissa = 0;
            end
        end else begin
            exponent = 127 + int_part;
            mantissa = frac_part[29:7];
        end
	 
	 
	 
	 
		result= {tmp[31], exponent, mantissa};
  end
 
	// CORDIC rotations
	
	always @(posedge clk) begin
		x[0]=32'b00100110110111010011101101101010;
		y[0]=0;
		z[0] = fixed_in;
//		di[0]=fixed_in[W-1:W-M];
	
	end
	
	
	generate
	genvar i;
	for(i=0; i<M-1; i=i+1) begin : stages
		
	
		always@ (posedge clk ) begin
		
//				if (clk_en) begin
					
				if (z[i][31]==0) begin
					x[i+1]=x[i]- (y[i]>>>i) ;
					y[i+1]=y[i]+ (x[i]>>>i) ;
					z[i+1] =z[i]- (e[i]) ;
//					di[i+1]=di[i];
				end
				else begin
									
					x[i+1]=x[i]+ (y[i]>>>i) ;
					y[i+1]=y[i]- (x[i]>>>i) ;
					z[i+1] =z[i]+ (e[i]) ;
				
				end
			
		end
		
		
	
	end

	endgenerate

	// Assign output
//	assign result = x[M-1];
	

// Initial values

//	assign zi[0] = {1'b1, {(W-1){1'b0}}};

	

endmodule