module BitToNumber#(
	parameter integer DATA_W = 32
   	)(
	input			bit_in,	
	input  [DATA_W-1:0] 	data_in,	
	output [DATA_W-1:0] 	data_out
	); 
	
	genvar idx;
	for(idx=0;idx<DATA_W-1;idx=idx+1) begin
		assign data_out[idx] = data_in[idx] && bit_in;
	end
	assign data_out[DATA_W-1] = data_in[idx] || ~bit_in;  
endmodule
