class Execute
{

public:
    Execute() {}
    unsigned int executeOperation(unsigned int op, unsigned int src1, unsigned int src2);

private:
    unsigned int add(unsigned int src1, unsigned int src2) { return src1 + src2; };  //returns a value
    unsigned int sub(unsigned int src1, unsigned int src2) { return src1 - src2; };  //returns a value
    unsigned int mult(unsigned int src1, unsigned int src2) { return src1 * src2; }; //returns a value
    unsigned int div(unsigned int src1, unsigned int src2) { return src1 / src2; };  //returns a value
    unsigned int mod(unsigned int src1, unsigned int src2) { return src1 % src2; };  //returns a value
    unsigned int beq(unsigned int src1, unsigned int src2) { return ((src1 - src2) == 0) ? 1 : 0;}; //returns a t/f
    unsigned int bne(unsigned int src1, unsigned int src2){ return ((src1 - src2) != 0) ? 1 : 0;}; //returns a t/f
};