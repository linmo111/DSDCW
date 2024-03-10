//// CORDIC parameters
//`define M  14; // No. of iterations
//`define W  32; // Bit width

// Interface

module CORDIC #(
	parameter M =22,
	parameter W=32,
	parameter FixedW=26,
	parameter EXONENT_BITS = 8,
	parameter MANTISSA_BITS = 23,
	parameter INTEGER_BITS = 2,
	parameter FRACTION_BITS = 24

	)(
	input [W-1:0] dataa, //this input is float 
//	input [W-1:0] datab, 
	input clk,
	input rst,
//	input clk_en,
	
	output reg [W-1:0] result, //output should also be float
	output wire [FixedW-1:0] fixedpoint_in,
	output wire [FixedW-1:0] fixedpoint_out
//	output reg [23:0] fixedmanti,
//	output reg [7:0] shiftnum
//	output reg [w-1:0] fixedpoint_in
	);

	// Signals
	reg signed [FixedW-1:0] x [0:M-1];
	reg signed [FixedW-1:0] y [0:M-1];
	reg signed [FixedW-1:0] z [0:M-1]; // Pipeline registers
//	reg [M-1:0] di [0:M-1]; // M-bit direction vector
	reg signed [FixedW-1:0] e [0:M-1];
	
  
  // Fixed point bits
	reg signed [FixedW-1:0] fixed_in; 
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
//initial begin
//
//	e[0]=32'b00110010010000111111011010101000;
//	e[1]=32'b00011101101011000110011100000101;
//	e[2]=32'b00001111101011011011101011111100;
//	e[3]=32'b00000111111101010110111010100110;
//	e[4]=32'b00000011111111101010101101110110;
//	
//	e[5]=32'b00000001111111111101010101011011;
//	e[6]=32'b00000000111111111111101010101010;
//	e[7]=32'b00000000011111111111111101010101;
//	e[8]=32'b00000000001111111111111111101010;
//	e[9]=32'b00000000000111111111111111111101;
//	
//	e[10]=32'b00000000000011111111111111111110;
//	e[11]=32'b00000000000001111111111111111111;
//	e[12]=32'b00000000000000111111111111111111;
//	e[13]=32'b00000000000000011111111111111111;
//	e[14]=32'b00000000000000001111111111111111;
//	e[15]=32'b00000000000000000111111111111111;
//	e[16]=32'b00000000000000000011111111111111;
//	e[17]=32'b00000000000000000001111111111111;
//	e[18]=32'b00000000000000000000111111111111;
//	e[19]=32'b00000000000000000000011111111111;
//   e[20]=32'b00000000000000000000001111111111;
//   e[21]=32'b00000000000000000000000111111111;
////	e[12]=32'b00111001011111111111111111010101;
////	e[13]=32'b00111000111111111111111111010101;
////	e[14]=32'b00111000011111111111111111010101;
////	
////	e[15]=32'b00110111111111111111111011000010;
////	e[16]=32'b00110111011111111111110010011100;
////	e[17]=32'b00110110111111111111110010011100;
//
//	
//end

initial begin

	e[0]=26'b00110010010000111111011010;
	e[1]=26'b00011101101011000110011100;
	e[2]=26'b00001111101011011011101011;
	e[3]=26'b00000111111101010110111010;
	e[4]=26'b00000011111111101010101101;
	
	e[5]=26'b00000001111111111101010101;
	e[6]=26'b00000000111111111111101010;
	e[7]=26'b00000000011111111111111101;
	e[8]=26'b00000000001111111111111111;
	e[9]=26'b00000000000111111111111111;

	e[10]=26'b00000000000011111111111111;
	e[11]=26'b00000000000001111111111111;
	e[12]=26'b00000000000000111111111111;
	e[13]=26'b00000000000000011111111111;
	e[14]=26'b00000000000000001111111111;
	e[15]=26'b00000000000000000111111111;
	e[16]=26'b00000000000000000011111111;
	e[17]=26'b00000000000000000001111111;
	e[18]=26'b00000000000000000000111111;
	e[19]=26'b00000000000000000000011111;
   e[20]=26'b00000000000000000000001111;
   e[21]=26'b00000000000000000000000111;
//	e[12]=32'b00111001011111111111111111010101;
//	e[13]=32'b00111000111111111111111111010101;
//	e[14]=32'b00111000011111111111111111010101;
//	
//	e[15]=32'b00110111111111111111111011000010;
//	e[16]=32'b00110111011111111111110010011100;
//	e[17]=32'b00110110111111111111110010011100;

	
end


//conversion
//wire [31:0] tt;
wire [7:0] exp;
//wire [W-10:0] manti;
wire sign;
 assign exp = dataa[30:23];
// assign manti = dataa[22:0]; 
 assign sign= 1'b0;//cos is symmetric anyways
 
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
//		fixed_in = {sign, fixed_mantissa, 7'b0};
		fixed_in = {sign, fixed_mantissa, 1'b0};
  end else if (shift_amount >= 0) begin
		// Shift left within the integer bits
//		fixed_in = {sign, fixed_mantissa << shift_amount, 7'b0};
		fixed_in = {sign, fixed_mantissa << shift_amount, 1'b0};
  end else begin
		// Shift right within the fractional bits
		if (shift_amount >= -30) begin
//			 fixed_in = {sign, fixed_mantissa >> -shift_amount,7'b0};
			 fixed_in = {sign, fixed_mantissa >> -shift_amount,1'b0};
		end else begin
//			 fixed_in = {sign, 31'b0};
			 fixed_in = {sign, 25'b0};
		end
  end
  
 end
 assign fixedpoint_in=fixed_in;

//reg [31:0] res;
//reg [31:0] expr;
 wire [FixedW-1:0] tmp;
 wire  int_part;
 wire [FRACTION_BITS-1:0] frac_part;
 assign tmp=x[M-1];
 assign int_part = tmp[FixedW-2];
 assign frac_part=tmp[FixedW-3:0];
 reg [7:0] exponent;
 reg [22:0] mantissa;
 assign fixedpoint_out=x[M-1];
 always @(*) begin   //from fixed point to floating point output
    if (int_part == 0) begin
            if (frac_part[23]) begin
                exponent = 127 - 1;
                mantissa = frac_part[23:1]<<<1;
//            end else if (frac_part[22]) begin
//                exponent = 127 - 2;
//                mantissa = frac_part[22:0];
//            end else if (frac_part[27]) begin
//                exponent = 127 - 3;
//                mantissa = frac_part[26:4];
//            end else if (frac_part[26]) begin
//                exponent = 127 - 4;
//                mantissa = frac_part[25:3];
//            end else if (frac_part[25]) begin
//                exponent = 127 - 5;
//                mantissa = frac_part[24:2];
//            end else if (frac_part[24]) begin
//                exponent = 127 - 6;
//                mantissa = frac_part[23:1];
//            end else if (frac_part[23]) begin
//                exponent = 127 - 7;
//                mantissa = frac_part[22:0];
            end else begin
                exponent = 127-2;
                mantissa = frac_part[22:0]<<<1;
            end
        end else begin
            exponent = 127 + int_part;
            mantissa = frac_part[23:1];
        end
	 
	 
	 
	 
		result= {tmp[FixedW-1], exponent, mantissa};
  end
 
	// CORDIC rotations
	
	always @(posedge clk) begin
		if (rst)	begin
			x[0]<=0;
			y[0]<=0;
			z[0]<=0;
		end
		else begin
			x[0]<=26'b00100110110111010011101101;
			y[0]<=0;
			z[0]<= fixed_in;
	//		di[0]=fixed_in[W-1:W-M];
		end
	end
	
	genvar i;
	generate
	for(i=0; i<M-1; i=i+8) begin : stages	
		always@ (posedge clk ) begin
		
//				if (clk_en) begin
					
				if (z[i][FixedW-1]==0) begin
					x[i+1]=x[i]- (y[i]>>>i) ;
					y[i+1]=y[i]+ (x[i]>>>i) ;
					z[i+1]=z[i]- (e[i]) ;

				end
				else begin
									
					x[i+1]=x[i]+ (y[i]>>>i) ;
					y[i+1]=y[i]- (x[i]>>>i) ;
					z[i+1]=z[i]+ (e[i]) ;
				
				end
				if ((i+2)<M) begin
					if (z[i+1][FixedW-1]==0) begin
						x[i+2]=x[i+1]- (y[i+1]>>>i+1) ;
						y[i+2]=y[i+1]+ (x[i+1]>>>i+1) ;
						z[i+2]=z[i+1]- (e[i+1]) ;

					end
					else begin
										
						x[i+2]=x[i+1]+ (y[i+1]>>>i+1) ;
						y[i+2]=y[i+1]- (x[i+1]>>>i+1) ;
						z[i+2]=z[i+1]+ (e[i+1]) ;			
					end
				end
				if ((i+3)<M) begin
					if (z[i+2][FixedW-1]==0) begin
						x[i+3]=x[i+2]- (y[i+2]>>>i+2) ;
						y[i+3]=y[i+2]+ (x[i+2]>>>i+2) ;
						z[i+3]=z[i+2]- (e[i+2]) ;

					end
					else begin
										
						x[i+3]=x[i+2]+ (y[i+2]>>>i+2) ;
						y[i+3]=y[i+2]- (x[i+2]>>>i+2) ;
						z[i+3]=z[i+2]+ (e[i+2]) ;			
					end
				end
				if ((i+4)<M) begin
					if (z[i+3][FixedW-1]==0) begin
						x[i+4]=x[i+3]- (y[i+3]>>>i+3) ;
						y[i+4]=y[i+3]+ (x[i+3]>>>i+3) ;
						z[i+4]=z[i+3]- (e[i+3]) ;
					end
					else begin
										
						x[i+4]=x[i+3]+ (y[i+3]>>>i+3) ;
						y[i+4]=y[i+3]- (x[i+3]>>>i+3) ;
						z[i+4]=z[i+3]+ (e[i+3]) ;			
					end
				end
				if ((i+5)<M) begin
					if (z[i+4][FixedW-1]==0) begin
						x[i+5]=x[i+4]- (y[i+4]>>>i+4) ;
						y[i+5]=y[i+4]+ (x[i+4]>>>i+4) ;
						z[i+5]=z[i+4]- (e[i+4]) ;
					end
					else begin
										
						x[i+5]=x[i+4]+ (y[i+4]>>>i+4) ;
						y[i+5]=y[i+4]- (x[i+4]>>>i+4) ;
						z[i+5]=z[i+4]+ (e[i+4]) ;			
					end
				end
				if ((i+6)<M) begin
					if (z[i+5][FixedW-1]==0) begin
						x[i+6]=x[i+5]- (y[i+5]>>>i+5) ;
						y[i+6]=y[i+5]+ (x[i+5]>>>i+5) ;
						z[i+6]=z[i+5]- (e[i+5]) ;
					end
					else begin
										
						x[i+6]=x[i+5]+ (y[i+5]>>>i+5) ;
						y[i+6]=y[i+5]- (x[i+5]>>>i+5) ;
						z[i+6]=z[i+5]+ (e[i+5]) ;			
					end
				end
				if ((i+7)<M) begin
					if (z[i+6][FixedW-1]==0) begin
						x[i+7]<=x[i+6]- (y[i+6]>>>i+6) ;
						y[i+7]<=y[i+6]+ (x[i+6]>>>i+6) ;
						z[i+7]<=z[i+6]- (e[i+6]) ;
					end
					else begin
										
						x[i+7]<=x[i+6]+ (y[i+6]>>>i+6) ;
						y[i+7]<=y[i+6]- (x[i+6]>>>i+6) ;
						z[i+7]<=z[i+6]+ (e[i+6]) ;			
					end
				end
				if ((i+8)<M) begin
					if (z[i+7][FixedW-1]==0) begin
						x[i+8]<=x[i+7]- (y[i+7]>>>i+7) ;
						y[i+8]<=y[i+7]+ (x[i+7]>>>i+7) ;
						z[i+8]<=z[i+7]- (e[i+7]) ;
					end
					else begin
										
						x[i+8]<=x[i+7]+ (y[i+7]>>>i+7) ;
						y[i+8]<=y[i+7]- (x[i+7]>>>i+7) ;
						z[i+8]<=z[i+7]+ (e[i+7]) ;			
					end
				end
			
		end
	
	end

	endgenerate

	// Assign output
//	assign result = x[M-1];
	

// Initial values

//	assign zi[0] = {1'b1, {(W-1){1'b0}}};

	

endmodule