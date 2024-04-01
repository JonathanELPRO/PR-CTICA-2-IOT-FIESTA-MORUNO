class Temperature {
private:
    double value;

public:
    Temperature(double initialValue);
    double* getPointerValue();
    double getValue();
    void setValue(double newValue);
};
