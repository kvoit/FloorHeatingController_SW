#pragma once

class Messenger {
    public:
    virtual bool sendMessage(const char* channel, const char* msg, bool retain=true) = 0;
};