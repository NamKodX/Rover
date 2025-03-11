/*
  L298ND.h
  ver. 2022.01
*/
// ensure this library description is only included once
#ifndef L298ND_h
#define L298ND_h

class L298ND {
  public:
    // Constructor
    L298ND();
    // Destructor
    ~L298ND();

    // Functions
    void initialization();
    void testing(uint8_t velocity);
    void toForward(uint8_t velocity);
    void toBackward(uint8_t velocity); 
    void toRight(uint8_t velocity);
    void toLeft(uint8_t velocity);
		void fastStop();
    void toStop();
};
#endif
