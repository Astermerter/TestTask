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
                first_num = 123; // ������� ��������� ����� � c++
                second_num = 345;
                #10;
                $display("solution %d * %d is %d", first_num, second_num, solution);

                first_num = 154;
                second_num = 654;
                #10;
                $display("solution %d * %d is %d", first_num, second_num, solution);

                first_num = 186;
                second_num = 348;
                #10;
                $display("solution %d * %d is %d", first_num, second_num, solution);
                $finish;
        end
endmodule
