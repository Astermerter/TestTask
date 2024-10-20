module main(
        input [15:0] first_num, 
        input [15:0] second_num, 
        output reg [31:0] solution 
);
    function [63:0] karatsuba;
        input [63:0] num1; 
        input [63:0] num2;
        reg [63:0] temp_num1;
        reg [63:0] f1, f2, s1, s2; 
        reg [63:0] p1, p2, p3, p4; 
        reg [63:0] buf1, buf2, i, m, digit_count;

        begin
            digit_count = 0;
            temp_num1 = num1; 
            while (temp_num1 > 0) begin
                temp_num1 = temp_num1 / 10; 
                digit_count = digit_count + 1;
            end
            
            
            m = (digit_count) >> 1;
            
            if (digit_count > 1) begin
                buf1 = 10;
                buf2 = 10;
                for (i = 0; i < m-1; i++) begin
                    buf1 = (buf1 << 3) + (buf1 << 1); 
                end
                for (i = 0; i < (m << 1) - 1; i++) begin
                    buf2 = (buf2 << 3) + (buf2 << 1);
                end

                
                f1 = num1 / buf1; 
                f2 = num1 % buf1; 
                s1 = num2 / buf1; 
                s2 = num2 % buf1; 


                p1 = pf1(f1, s1);  
                p2 = pf1(f2, s2);  
                p3 = pf1(f1 + f2, s1 + s2); 
                p4 = p3 - p2 - p1;

                for (i = 0; i < m; i++) begin
                    p4 = (p4 << 3) + (p4 << 1); 
                end
                for (i = 0; i < (m << 1); i++) begin
                    p1 = (p1 << 3) + (p1 << 1);
                end

                karatsuba = p1 + p4 + p2;

            end else begin
                karatsuba = 0;
                for (i = 0; i < num2; i++) begin
                    karatsuba += num1;
                end
            end
        end
    endfunction
    function [63:0] pf1;
        input [63:0] num1; 
        input [63:0] num2;
        reg [63:0] temp_num1;
        reg [63:0] f1, f2, s1, s2; 
        reg [63:0] p1, p2, p3, p4; 
        reg [63:0] buf1, buf2, i, m, digit_count;

        begin
            
            digit_count = 0;
            temp_num1 = num1; 
            while (temp_num1 > 0) begin
                temp_num1 = temp_num1 / 10; 
                digit_count = digit_count + 1;
            end
            
            
            m = (digit_count) >> 1;
            
            if (digit_count > 1) begin
                buf1 = 10;
                buf2 = 10;
                for (i = 0; i < m-1; i++) begin
                    buf1 = (buf1 << 3) + (buf1 << 1); 
                end
                for (i = 0; i < (m << 1) - 1; i++) begin
                    buf2 = (buf2 << 3) + (buf2 << 1);
                end

                
                f1 = num1 / buf1; 
                f2 = num1 % buf1; 
                s1 = num2 / buf1; 
                s2 = num2 % buf1; 

                p1 = pf2(f1, s1);  
                p2 = pf2(f2, s2);  
                p3 = pf2(f1 + f2, s1 + s2); 
                p4 = p3 - p2 - p1;

                for (i = 0; i < m; i++) begin
                    p4 = (p4 << 3) + (p4 << 1); 
                end
                for (i = 0; i < (m << 1); i++) begin
                    p1 = (p1 << 3) + (p1 << 1);
                end

                pf1 = p1 + p4 + p2;

            end else begin
                pf1 = 0;
                for (i = 0; i < num2; i++) begin
                    pf1 += num1;
                end
            end
        end
    endfunction
    function [63:0] pf2;
        input [63:0] num1; 
        input [63:0] num2;
        reg [63:0] temp_num1;
        reg [63:0] f1, f2, s1, s2; 
        reg [63:0] p1, p2, p3, p4; 
        reg [63:0] buf1, buf2, i, m, digit_count;

        begin
            
            digit_count = 0;
            temp_num1 = num1; 
            while (temp_num1 > 0) begin
                temp_num1 = temp_num1 / 10; 
                digit_count = digit_count + 1;
            end
            
            
            m = (digit_count) >> 1;
            
            if (digit_count > 1) begin
                buf1 = 10;
                buf2 = 10;
                for (i = 0; i < m-1; i++) begin
                    buf1 = (buf1 << 3) + (buf1 << 1); 
                end
                for (i = 0; i < (m << 1) - 1; i++) begin
                    buf2 = (buf2 << 3) + (buf2 << 1);
                end

                
                f1 = num1 / buf1; 
                f2 = num1 % buf1; 
                s1 = num2 / buf1; 
                s2 = num2 % buf1; 


                p1 = pf3(f1, s1);  
                p2 = pf3(f2, s2);  
                p3 = pf3(f1 + f2, s1 + s2); 
                p4 = p3 - p2 - p1;
                
                for (i = 0; i < m; i++) begin
                    p4 = (p4 << 3) + (p4 << 1); 
                end
                for (i = 0; i < (m << 1); i++) begin
                    p1 = (p1 << 3) + (p1 << 1);
                end
                pf2 = p1 + p4 + p2;

            end else begin
                pf2 = 0;
                for (i = 0; i < num2; i++) begin
                    pf2 += num1;
                end
            end
        end
    endfunction
    function [63:0] pf3;
        input [63:0] num1; 
        input [63:0] num2;
        reg [63:0] temp_num1;
        reg [63:0] f1, f2, s1, s2; 
        reg [63:0] p1, p2, p3, p4; 
        reg [63:0] buf1, buf2, i, m, digit_count;

        begin
            
            digit_count = 0;
            temp_num1 = num1; 
            while (temp_num1 > 0) begin
                temp_num1 = temp_num1 / 10; 
                digit_count = digit_count + 1;
            end
            
            
            m = (digit_count) >> 1;
            
            if (digit_count > 1) begin
                buf1 = 10;
                buf2 = 10;
                for (i = 0; i < m-1; i++) begin
                    buf1 = (buf1 << 3) + (buf1 << 1); 
                end
                for (i = 0; i < (m << 1) - 1; i++) begin
                    buf2 = (buf2 << 3) + (buf2 << 1);
                end

                
                f1 = num1 / buf1; 
                f2 = num1 % buf1; 
                s1 = num2 / buf1; 
                s2 = num2 % buf1; 
                
                p1 = 0;
                for (i = 0; i < s1; i++) begin
                    p1 +=f1;
                end
                p2 = 0;
                for (i = 0; i < s2; i++) begin
                    p2 +=f2;
                end
                p3 = 0;
                for (i = 0; i < (s1 + s2); i++) begin
                    p3 +=(f1 + f2);
                end
                p4 = p3 - p2 - p1;

                for (i = 0; i < m; i++) begin
                    p4 = (p4 << 3) + (p4 << 1); 
                end
                for (i = 0; i < (m << 1); i++) begin
                    p1 = (p1 << 3) + (p1 << 1);
                end
                pf3 = p1 + p4 + p2;

            end else begin
                pf3 = 0;
                for (i = 0; i < num2; i++) begin
                    pf3 += num1;
                end
            end
        end
    endfunction
    always @(*) begin
            solution = karatsuba(first_num, second_num);
        end
endmodule