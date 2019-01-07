#ifndef _PRE_H
#define	_PRE_H


#define DDR_(port)        DDR ## port
#define PORT_(port)       PORT ## port
#define PIN_(port)        PIN ## port
#define PINx_(port, pin)  P ## port ## pin


#define DDR(port)         DDR_(port)
#define PORT(port)        PORT_(port)
#define PIN(port)         PIN_(port)
#define PINx(port, pin)   PINx_(port, pin)



#endif
