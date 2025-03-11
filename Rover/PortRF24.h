 /*
  PortRF24.h
  ver. 2022.01
	namik.can@hotmail.com
*/
// ensure this library description is only included once
#ifndef PortRF24_h
#define PortRF24_h

class PortRF24 {
  public:
    // Constructor
    PortRF24();
    // Destructor
    ~PortRF24();

    // Functions
    void initialization();
		void resetData();
		void displayResults();	
		void speedStepX2(uint8_t dstep);
    void speedStepY2(uint8_t dstep);
    void patrol();
};
#endif
