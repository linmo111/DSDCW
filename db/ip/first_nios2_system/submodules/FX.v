module FX (
    input wire clk,
    input wire clk_en,
    input wire rst,
    input wire[31:0] dataa, //input x[i]
    input	wire [31:0] datab, //input sum
	 output wire [31:0]multar,
	 output wire [31:0]multbr,
	 output wire [31:0]multcr,
	 output wire [31:0]multdr,
	 output wire [31:0]multer,
	 output wire [31:0]addar,
	 output wire [31:0]addbr,
	 output wire [31:0] subr,
	 output wire [31:0] cordicr,
    output wire [31:0] result
);

//y = 0.5*x + (x^2)*cos((x-128)/128) 
    wire [31:0] multa_res;
	 wire [31:0] multb_res;
	 wire [31:0] multc_res;
	 wire [31:0] multd_res;
	 wire [31:0] multe_res;
    wire [31:0] adda_res;
	 wire [31:0] addb_res;
    wire [31:0] sub_res;
	 wire [31:0] cordic_res;
	 
		//32'b00111111000000000000000000000000  // 0.5
		//01000011000000000000000000000000 //128
		//00111100000000000000000000000000 //1/128
		
    // Instantiate the Fp_mult IP
	 
	 
	 
	 
    fp_multiplier multa ( //X^2
        .clock(clk),
        .dataa(dataa),
        .datab(dataa),
        .clk_en(clk_en),
        .aclr(rst),
        .result(multa_res)
    );
	 
	 fp_multiplier multb (//0.5x
        .clock(clk),
        .dataa(dataa),
        .datab(32'b00111111000000000000000000000000),
        .clk_en(clk_en),
        .aclr(rst),
        .result(multb_res)
    );
	fp_multiplier multc (// /128
        .clock(clk),
        .dataa(sub_res),
        .datab(32'b00111100000000000000000000000000),
        .clk_en(clk_en),
        .aclr(rst),
        .result(multc_res)
    );
	 
	 	fp_multiplier multd (// x**2 * cos
        .clock(clk),
        .dataa(cordic_res),
        .datab(multa_res),
        .clk_en(clk_en),
        .aclr(rst),
        .result(multd_res)
    );
	 fp_multiplier multe (// x**2 * cos
        .clock(clk),
        .dataa(datab),
        .datab(32'b00111111100000000000000000000000),//1
        .clk_en(clk_en),
        .aclr(rst),
        .result(multe_res)
    );

    // Instantiate the Fp_add IP
    fp_adder adda (//   a +b
        .clock(clk),
        .dataa(multd_res),
        .datab(addb_res),
        .clk_en(clk_en),
        .aclr(rst),
        .result(adda_res)
    );
	 fp_adder addb ( // fx1+fx
        .clock(clk),
        .dataa(multb_res),
        .datab(datab),
        .clk_en(clk_en),
        .aclr(rst),
        .result(addb_res)
    );
//	fp_subtractor addb ( // fx1+fx
//        .clock(clk),
//        .dataa(datab),
//        .datab(-adda_res),
//        .clk_en(clk_en),
//        .aclr(rst),
//        .result(addb_res)
//    );


    // Instantiate the Fp_sub IP
    fp_subtractor sub (//x-128
        .clock(clk),
        .dataa(dataa),
        .datab(32'b01000011000000000000000000000000 ),
        .clk_en(clk_en),
        .aclr(rst),
        .result(sub_res)
    );
	 CORDIC cordic(
        .clk(clk),
        .dataa(multc_res),
        .rst(rst),
        .result(cordic_res)
    );

    // Assign the final result
    assign result = adda_res;
	 assign multar=multa_res;
	 assign multbr=multb_res;
	 assign multcr=multc_res;
	 assign multdr=multd_res;
	 assign multer=multe_res;
	 assign addar=adda_res;
	 assign addbr=addb_res;
	 assign subr=sub_res;
	 assign cordicr=cordic_res;

endmodule