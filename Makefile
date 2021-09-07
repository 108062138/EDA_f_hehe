all:verilogopt.cpp
    g++ -o verilogopt verilogopt.cpp
clean:
    rm -f verilogopt.out