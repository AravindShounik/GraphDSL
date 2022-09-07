
all : lexer
	mkdir Outputs
	./a.out < Inputs/input1.gr > Outputs/output1.txt
	./a.out < Inputs/input2.gr > Outputs/output2.txt
	./a.out < Inputs/input3.gr > Outputs/output3.txt
	./a.out < Inputs/input4.gr > Outputs/output4.txt
	./a.out < Inputs/input5.gr > Outputs/output5.txt
	./a.out < Inputs/input6.gr > Outputs/output6.txt
	./a.out < Inputs/input7.gr > Outputs/output7.txt
	./a.out < Inputs/input8.gr > Outputs/output8.txt
	./a.out < Inputs/input9.gr > Outputs/output9.txt
	./a.out < Inputs/input10.gr > Outputs/output10.txt
	./a.out < Inputs/input11.gr > Outputs/output11.txt
	./a.out < Inputs/input12.gr > Outputs/output12.txt
	./a.out < Inputs/input13.gr > Outputs/output13.txt
	./a.out < Inputs/input14.gr > Outputs/output14.txt

lexer:
	flex lexer.l
	gcc lex.yy.c -ll

clean:
	rm -rf Outputs
	rm a.out
	rm lex.yy.c