class InterfaceController {
    public:
        InterfaceController(uint8_t interface_pin, InterfaceController ic);
        void handle();

    protected:
        InterfaceController ic;
        uint8_t port_pin,
};