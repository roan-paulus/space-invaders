#ifndef UI_FRAME_H
#define UI_FRAME_H

#include <vector>

class Frame {
    std::vector<Frame*> children {};
    Frame* parent = nullptr;

    void append(Frame* child_frame) {
        children.push_back(child_frame);
        child_frame->parent = this;
    }
};

#endif
