#include <iostream>
#include <map>

enum class LedColor { RED, YELLOW, WHITE, BLUE };

class LedController {
private:
    std::map<LedColor, bool> statesOfLeds;

public:
    LedController();
    ~LedController();
    void setLedState(LedColor color, bool state);
    bool getLedState(LedColor color);
    void setAllLedStatesToFalse();
};
