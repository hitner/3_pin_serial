#pragma once 

typedef unsigned long sp_baudrate_t;

typedef int sp_result_t;


enum Parity {
    PARITY_EVEN,                                          // !< Even parity.
    PARITY_ODD,                                           // !< Odd parity.
    PARITY_NONE,
};



class SerialPort
{
public:
    SerialPort(const char * device);

    SerialPort(const char * device, sp_baudrate_t baudrate,
        Parity parity);
    
    bool Close();

    int GetFd() const;

    void SetReadTimeout(int millisecond);

    int GetReadTimeout()const;

    sp_result_t Read(char * buffer, int buffer_size);

    sp_result_t ReadUntilTimeout(char * buffer, int buffer_size, int timout_millisecond);

    sp_result_t Write(const char * ouput, int length);

private:
    int fd_;
    int readTimeout_;
};