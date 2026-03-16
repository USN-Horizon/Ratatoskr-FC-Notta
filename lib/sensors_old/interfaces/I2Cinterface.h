class I2CInterface {
public:
    virtual bool write(uint8_t addr, const uint8_t* data, size_t len) = 0;
    virtual bool read(uint8_t addr, uint8_t* data, size_t len) = 0;
    virtual ~I2CInterface() = default;
};
