module dut(out,in);
	output[39:0] out;
	input[19:0] in;
wire origtmp1;
wire origtmp10;
wire origtmp11;
wire origtmp12;
wire origtmp13;
wire origtmp14;
wire origtmp15;
wire origtmp16;
wire origtmp17;
wire origtmp18;
wire origtmp19;
wire origtmp2;
wire origtmp20;
wire origtmp21;
wire origtmp22;
wire origtmp23;
wire origtmp24;
wire origtmp25;
wire origtmp26;
wire origtmp28;
wire origtmp3;
wire origtmp4;
wire origtmp5;
wire origtmp6;
wire origtmp7;
wire origtmp8;
wire origtmp9;
assign origtmp1 = origtmp5 ^ in[6];
assign origtmp10 = origtmp20 | in[2];
assign origtmp11 = origtmp22 ^ origtmp16;
assign origtmp12 = origtmp6 & in[6];
assign origtmp13 = in[17] & in[10];
assign origtmp14 = in[6] | in[16];
assign origtmp15 = origtmp2 & origtmp13;
assign origtmp16 = in[9] | origtmp7;
assign origtmp17 = in[16];
assign origtmp18 = origtmp8;
assign origtmp19 = origtmp4 | origtmp21;
assign origtmp2 = in[17] | origtmp10;
assign origtmp20 = in[7] | in[10];
assign origtmp21 = origtmp18 ^ in[4];
assign origtmp22 = origtmp12 ^ in[7];
assign origtmp23 = in[18] | origtmp24;
assign origtmp24 = in[13] & in[12];
assign origtmp25 = origtmp26 | origtmp23;
assign origtmp26 = 1'b0 | in[1];
assign origtmp27 = 1'b0;
assign origtmp28 = in[19] ^ in[19];
assign origtmp29 = 1'b0;
assign origtmp3 = origtmp1 & origtmp11;
assign origtmp30 = 1'b1;
assign origtmp4 = origtmp14 ^ origtmp15;
assign origtmp5 = in[2] | origtmp9;
assign origtmp6 = in[10] ^ in[15];
assign origtmp7 = in[11] & in[0];
assign origtmp8 = in[14] | in[3];
assign origtmp9 = in[4] | origtmp17;
assign out[0] = origtmp3 ^ origtmp19;
assign out[14] = in[5];
assign out[15] = in[4];
assign out[16] = in[3];
assign out[17] = in[2];
assign out[18] = in[2];
assign out[19] = in[2];
assign out[1] = origtmp25 ^ in[1];
assign out[20] = in[0];
assign out[26] = in[7];
assign out[27] = in[13];
assign out[28] = in[12];
assign out[29] = in[11];
assign out[2] = in[5] | 1'b0;
assign out[36] = in[17];
assign out[37] = in[16];
assign out[3] = in[19] | origtmp28;
assign out[4] = 1'b1;
assign out[5] = 1'b0;
assign out[6] = 1'b0;
assign out[7] = 1'b0;
assign out[8] = 1'b0;
assign out[9] = 1'b1;
assign out[39:38] = in[16:15];
assign out[35:32] = in[18:15];
assign out[31:30] = in[16:15];
assign out[25:23] = in[7:5];
assign out[22:21] = in[3:2];
assign out[13:10] = in[5:2];
endmodule

module tb();
    wire[39:0] results;
    reg[19:0] data;
    dut duttest(results[39:0], data[19:0]);
	initial begin
		f=$fopen("output.txt","w");
	end
    initial begin
//        $readmemb("data.txt", data);
		for (data = 20'b0000_0000_0000_0000; data<20'b0000_1111_1111_1111 ; data=data+20'b0000_0000_0000_0001) begin
			$fwrite(f,"input data:%b ",data);
			$fwrite(f," and output res: %b\n",results);
		end
//        $writememb("results.txt", results);
    end 
	initial begin
		$fclose(f);
	end
endmodule
