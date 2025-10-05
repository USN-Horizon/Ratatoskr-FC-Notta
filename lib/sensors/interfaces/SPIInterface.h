class SPIInterface {
public:
    virtual bool transfer(const uint8_t* tx, uint8_t* rx, size_t len) = 0;
    virtual ~SPIInterface() = default;
};
