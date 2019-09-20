class PortController {
    public:
        PortController(uint8_t port_pin, InterfaceController ic);
        void handle();

    protected:
        InterfaceController ic;
        uint8_t port_pin,
};

