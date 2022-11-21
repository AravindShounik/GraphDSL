./main < Inputs/input.gr
llc test.ll && gcc test.s -o test
./test
echo $?
# rm test test.s