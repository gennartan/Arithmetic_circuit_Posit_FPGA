module ClkDomSyncOversample #(

	parameter WIDTH = 16
	)(
	input 			       clk_in,
	input [WIDTH-1:0]      data_in,
	input 			       clk_fast,
	input 			       rst,
	output reg [WIDTH-1:0] data_out,
	output reg		       pulse_out
	);

	reg clk_in_d;
	reg clk_in_dd;
	reg clk_in_ddd;
	reg [WIDTH-1:0] data_in_d;
	reg [WIDTH-1:0] data_in_dd;

	always@(posedge clk_fast, negedge rst) begin
	if(rst==0) begin 
		clk_in_d<=0;
		clk_in_dd<=0;
		clk_in_ddd<=0;
		data_in_d<=0;
		data_in_dd<=0;
		data_out<=0;
		pulse_out<=0;
	end else begin
		clk_in_d  <=clk_in;
		clk_in_dd <=clk_in_d;
		clk_in_ddd<=clk_in_dd;
		data_in_d <=data_in;
		data_in_dd<=data_in_d;
		
		if(clk_in_ddd==0 && clk_in_dd==1) begin
			pulse_out<=1;
			data_out<=data_in;
		end else begin
			pulse_out<=0;
			data_out<=0;
		end
	end
	end


endmodule

