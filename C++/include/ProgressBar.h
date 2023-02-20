#ifndef H_PR0GR3SS_BAR_H
#define H_PR0GR3SS_BAR_H

#include <iostream>

struct ProgressBar
{
    static void display(int epoch, int totalEpoch, int imagesDone, int totalImages);
};

#endif

