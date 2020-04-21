`timescale 1ns/1ps
module fifo#(
   parameter integer DATA_W = 32,
   parameter integer LOG2_RAM_DEPTH = 2
   )(
input               clk,
input               arst_n,
input  [DATA_W-1:0] data_in,
input               rd_en,
input               wr_en,
output [DATA_W-1:0] data_out,
output              empty,
output              full
);    
 
// FIFO constants
parameter ADDR_W    = LOG2_RAM_DEPTH;
parameter RAM_DEPTH = 1 << LOG2_RAM_DEPTH;


//-----------Internal variables-------------------
wire [DATA_W-1:0] data_ram ;
reg [DATA_W-1:0] array [0:RAM_DEPTH-1];



wire [ADDR_W-1:0] rd_pointer;
wire [ADDR_W-1:0] wr_pointer;
wire [ADDR_W-1:0] status_cnt;

reg  [ADDR_W-1:0] rd_pointer_nxt;
reg  [ADDR_W-1:0] wr_pointer_nxt;
reg  [ADDR_W-1:0] status_cnt_nxt;

reg full_flag, empty_flag;
reg rd_pointer_wen,wr_pointer_wen;

assign full  = full_flag;
assign empty = empty_flag;

always@(*) full_flag  = status_cnt == RAM_DEPTH-1;
always@(*) empty_flag = status_cnt == 0;

//READ POINTER
reg_arstn #(ADDR_W,'b0)rd_pointer_reg(clk,arst_n,rd_pointer_nxt,rd_pointer,1'b1);
always@(*) rd_pointer_wen = rd_en;
always@(*)
   if(rd_pointer_wen)
      rd_pointer_nxt = rd_pointer+1;
   else
      rd_pointer_nxt = rd_pointer;

//WRITE POINTER
reg_arstn #(ADDR_W,'b0)wr_pointer_reg(clk,arst_n,wr_pointer_nxt,wr_pointer,1'b1);
always@(*) wr_pointer_wen = wr_en;
always@(*)
   if(wr_pointer_wen)
      wr_pointer_nxt = wr_pointer+1;
   else
      wr_pointer_nxt = wr_pointer;

//STATUS (know if full of empty)
reg_arstn #(ADDR_W,'b0)status_cnt_reg(clk,arst_n,status_cnt_nxt,status_cnt,1'b1);
always@(*) wr_pointer_wen = wr_en;
always@(*)begin
   if(wr_pointer_wen & ~rd_pointer_wen &  ~full_flag)begin
      status_cnt_nxt = status_cnt+1;
   end else begin
      if (~wr_pointer_wen & rd_pointer_wen & ~empty_flag) begin
         status_cnt_nxt = status_cnt-1;
      end else begin
         status_cnt_nxt = status_cnt;
      end
   end
end

reg [18:0] array_;
integer idx;
always@(posedge clk, negedge arst_n) begin
   if(arst_n==1'b0) begin
      for(idx=0;idx<RAM_DEPTH;idx=idx+1) begin
            array[idx] <= 0;
      end
   end else if(wr_pointer_wen) begin
      array[wr_pointer] <= data_in;
      array_ <=data_in;
   end
end

assign data_out = array[rd_pointer]; 



endmodule



