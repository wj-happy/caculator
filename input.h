#ifndef INPUT_H
#define INPUT_H

const int maxBuf = 100;
const int tokNumber = 1;
const int tokError = 2;

class Input
{
public:
    Input();
    int Token() const { return _token; }
    int Number() const;
private:
    int _token;
    char _buf[maxBuf];
};

#endif // INPUT_H
