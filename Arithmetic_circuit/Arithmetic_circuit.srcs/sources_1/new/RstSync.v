module RstSync (
	input clk,
	input rst_in,
	output rst_out
	);

	wire rst_d;
	reg_arstn #(1,'b0) reg1 (clk, rst_in, 1'b1,  rst_d,   1'b1);
	reg_arstn #(1,'b0) reg2 (clk, rst_in, rst_d, rst_out, 1'b1);

endmodule
