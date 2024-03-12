`timescale 1 ns / 100 ps
module tb ();

	//Inputs to DUT are reg type
	reg [31:0] dataa;
	reg [31:0] datab; 
	reg clk;
	reg rst;
	reg clk_en;
	//Output from DUT is wire type
	wire [31:0] result;
	wire [31:0]multa;
	wire [31:0]multb;
	wire [31:0]multc;
	wire [31:0]multd;
		wire [31:0]multe;
	wire [31:0]adda;
	wire [31:0]addb;
	wire [31:0] sub;
	wire [31:0] cordic;
	
//	wire [25:0] fixedpoint_in;
//	wire [25:0] fixedpoint_out;
//	wire [23:0] fixedmanti;
//	wire [7:0] shiftnum;

	//Instantiate the DUT
	//mul refers to the verilog module defined by the LPM_MULT ip
	FX unit(
		.dataa(dataa),
		.datab(datab), 
		.rst(rst),
		.multar(multa),
		.multbr(multb),
		.multcr(multc),
		.multdr(multd),
		.multer(multe),
		.addar(adda),
		.addbr(addb),
		.subr(sub),
		.cordicr(cordic),
		
//		.fixedpoint_in(fixedpoint_in),
//		.fixedpoint_out(fixedpoint_out),
//		.fixedmanti(fixedmanti),
//		.shiftnum(shiftnum),
		.clk_en(clk_en),
		.clk(clk),
		.result(result)
	);

	// ---- If a clock is required, see below ----
	// //Create a 50MHz clock
	always
		#10 clk = ~clk;
	// -----------------------

	//Initial Block
	initial
	begin
		clk_en=1;
		$display($time, " << Starting Simulation >> ");
		
		// intialise/set input
		clk = 1'b0;
		rst = 1;
		
		// If using a clock
		
		
		// Wait 10 cycles (corresponds to timescale at the top) 
		#20
		
		@(posedge clk); 
		rst<=0;
		// set dataa and datab
		dataa <= 32'b01000011000000000000000000000000;
		datab <= 32'b01000000000000000000000000000000;
//		#20
//		dataa <= 32'b00111110100001100000101010010010;
////		datab <= 32'd23;
//		
//		#20
//
//		dataa <= 32'b00111111000001100000101010010010;
////		datab <= 32'd22;
////		
		
//		
		#1000
		$display($time, "<< Simulation Complete >>");
		$stop;
	end

endmodule
