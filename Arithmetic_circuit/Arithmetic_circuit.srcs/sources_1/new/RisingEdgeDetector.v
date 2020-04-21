`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/05/2017 04:07:22 PM
// Design Name: 
// Module Name: RisingEdgeDetector
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module RisingEdgeDetector(
    input clk,
    input rst,
    input in,
    output reg out
    );
    
    reg in_d;
    
    always@(posedge clk, negedge rst)begin
    if(rst==0) begin
        in_d<=0;
        out<=0;
    end else begin
        in_d<=in;
        out<=in && ~in_d;
    end
    end
    
    
    
endmodule