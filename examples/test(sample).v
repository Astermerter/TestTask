module test;
        reg [15:0] first_num;
        reg [15:0] second_num;
        wire [31:0] solution;

        main uut(
                .first_num(first_num),
                .second_num(second_num),
                .solution(solution)
        );

        initial begin
                first_num = 123; 
                second_num = 345;
                #10;
                if (solution == first_num*second_num) begin
                        $display("Test Passed");
                end else begin
                        $display("Test error");
                end
                first_num = 154;
                second_num = 654;
                #10;
                if (solution == first_num*second_num) begin
                        $display("Test Passed");
                end else begin
                        $display("Test error");
                end
                first_num = 186;
                second_num = 348;
                #10;
                if (solution == first_num*second_num) begin
                        $display("Test Passed");
                end else begin
                        $display("Test error");
                end
                $finish;
        end
endmodule
