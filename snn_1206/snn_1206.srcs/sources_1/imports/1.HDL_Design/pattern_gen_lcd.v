/*-------------------------------------------------------------------------
--                                                                         
--   Copyright (c) Libertron Co., LTD. 2013                               
--   ALL RIGHTS RESERVED                                                   
--                                                                         
--   THIS PROGRAM IS THE PROPERTY OF Libertron Co., LTD. AND IS            
--   BEING PROVIDED TO YOU PURSUANT TO A LICENSE AGREEMENT THAT            
--   SETS FORTH CERTAIN TERMS AND CONDITIONS FOR USE OF THIS PROGRAM.      
--   YOU MAY NOT COPY, DISTRIBUTE, USE OR OTHERWISE CREATE DERIVATIVES     
--   OF THIS SOFTWARE EXCEPT AS PROVIDED IN THE LICENSE AGREEMENT.         
-- IP Name       :                                       
-- IP Revision   :                                                         
-- File Name     : pattern_gen_lcd.v                                            
-- File Revision : 1.0                                                     
-- Date          : 2014/12/10                                              
-- Authors       : Libertron R&D Center                                    
-- 2020/05/06    : 수정 : IP 이름을 pattern_gen_lcd에서 pattern_gen_PARALLEL_IF으로 변경, 들여쓰기 일부 수정
-- 2020/08/10    : pattern_gen_PARALLEL_IF -> pattern_gen_LCD_IF
-- 2020/09/08    : 신호 timing 개선
-------------------------------------------------------------------------*/
`timescale 1ns/ 100ps


module pattern_gen_LCD_IF
#(
   parameter Tvw       = 12'd32   ,//VSYNC Pulse Width
   parameter Tvbp      = 12'd65   ,//VSYNC Back Porch
   parameter Tvfp      = 12'd65   ,//Vertical Front Porch
   parameter Tvdw      = 12'd1150 ,//Vertical valid data width
   parameter Thw       = 12'd32   ,//HSYNC Pulse Width        
   parameter Thbp      = 12'd65   ,//HSYNC Back Porch         
   parameter Thfp      = 12'd65   ,//Hertical Front Porch     
   parameter Thdw      = 12'd1150  //Hertical valid data width
)
(
/*****************************************************
** Input Signal Define                              **
*****************************************************/
input wire        clk       ,
input wire        rstb      ,
/*****************************************************
** Output Signal Define                             **
*****************************************************/ 
output reg        pat_vs    ,
output reg        pat_hs    ,
output reg        pat_de    ,
output reg        pat_load_en
);
/*****************************************************
** Parameter Definition                             **
*****************************************************/
localparam Tvp       = Tvw + Tvbp + Tvfp + Tvdw;//VSYNC Period   
localparam Thp       = Thfp + Thw + Thbp + Thdw;//HSYNC Period                
/*****************************************************
** Reg Definition                                  **
*****************************************************/
reg   [11:0]  hcnt       ;
reg   [11:0]  vcnt       ;
reg   [15:0]  pat_hcnt   ;
reg   [12:0]  pat_vcnt   ;

/*****************************************************
** Wire Definition                                 **
*****************************************************/

/*****************************************************
** HSYNC Period/VSYNC Period Count
*****************************************************/
always @(posedge clk or negedge rstb) begin 
   if (!rstb) begin
       hcnt   <= 12'd0;
       vcnt   <= 12'd0;
   end
   else begin
      /** HSYNC Period **/
      if (hcnt == (Thp - 1)) begin
         hcnt <= 12'd0;
      end
      else begin
         hcnt <= hcnt + 1'b1;
      end
      /** VSYNC Period **/
      if (hcnt == (Thp - 1)) begin
         if (vcnt == (Tvp - 1)) begin
            vcnt <= 12'd0;
         end
         else begin
            vcnt <= vcnt + 1'b1;
         end
      end
   end
end
/*****************************************************
** VSYNC  Signal Gen.
*****************************************************/
always @(posedge clk or negedge rstb) begin 
   if (!rstb) begin
       pat_vs       <= 1'b0;
   end
   else begin
      if (hcnt == (Thp - 1)) begin
         if (vcnt == (Tvfp - 1)) begin
            pat_vs <= 1'b0;
         end
         else if (vcnt == (Tvfp + Tvw - 1)) begin
            pat_vs <= 1'b1;
         end
      end
   end
end
/*****************************************************
** HSYNC Signal Gen.
*****************************************************/
always @(posedge clk or negedge rstb) begin 
   if (!rstb) begin
       pat_hs <= 1'b0;
   end
   else begin
      if ((hcnt == (Thfp - 1))) begin
         pat_hs <= 1'b0;
      end
      else if (hcnt == (Thfp + Thw - 1)) begin
         pat_hs <= 1'b1;
      end
   end
end
/*****************************************************
** HSYNC/VSYNC Data Enable Signal Gen.
*****************************************************/
always @(posedge clk or negedge rstb) begin 
   if (!rstb) begin
       pat_de   <= 1'b0;
   end
   else begin
      if ((vcnt >= (Tvw + Tvbp + Tvfp))) begin
         if (hcnt == (Thfp + Thw + Thbp - 1)) begin
            pat_de <= 1'b1;
         end
         else if (hcnt == (Thp - 1))begin
            pat_de <= 1'b0;
         end
      end
      else begin
         pat_de <= 1'b0;
      end
   end
end
/*****************************************************
** Data Load Enable Signal Gen.
*****************************************************/
always @(posedge clk or negedge rstb) begin 
   if (!rstb) begin
       pat_load_en <= 'b0;
       pat_hcnt    <= 'd0;
   end
   else begin
      if ((vcnt >= (Tvw + Tvbp + Tvfp + 0 ))) begin
         if (hcnt == (Thfp + Thw + Thbp - 2)) begin
            pat_load_en <= 1'b1;
         end
         else if (hcnt == (Thp - 2)) begin
            pat_load_en <= 1'b0;
         end
      end
      else begin
         pat_load_en <= 1'b0;
      end
      /*********************************************************************/
      //if (pat_load_en) begin
      if (pat_de) begin
         pat_hcnt <= pat_hcnt + 'b1;
      end
      else begin
          pat_hcnt <= 'd0;
      end 
   end
end
/*****************************************************
**  
*****************************************************/
always @(posedge clk or negedge rstb) begin 
   if (!rstb) begin
       pat_vcnt <= 'd0;
   end
   else begin
      if ((vcnt >= (Tvw + Tvbp)) && (vcnt <= (Tvp - Tvfp - 1))) begin
         if (hcnt == (Thp - 1)) begin
            pat_vcnt <= pat_vcnt + 'd3;
         end
      end
      else begin
      	 pat_vcnt <= 'd0;
      end
   end
end
/*****************************************************
** 
*****************************************************/

//assign pat_data = pat_hcnt[7:0] ;

/*****************************************************
** 
*****************************************************/


endmodule        