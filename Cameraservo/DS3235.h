#ifndef DS3235_H
#define DS3235_H

class DS3235 {
public:
    DS3235(void) {};
    virtual ~DS3235(void) {};
    void begin(int pin, int ch);
    void write(int angle); // from -90 to +90
    void plus(void);
    void minus(void);
private:
    int _ch;
    int _angle;
    int _min = 26;  // (26/1024)*20ms ≒ 0.5 ms  (-90°)
    int _max = 128; // (128/1024)*20ms = 2.5 ms (+90°)
};

#endif 
