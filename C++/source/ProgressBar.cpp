#include "ProgressBar.h"


void ProgressBar::display(int epoch, int totalEpoch, int imagesDone, int totalImages)
{
    float percent = (float)(imagesDone) * 100.0f / ((float)totalImages);
    printf("epoch %d/%d : ", epoch, totalEpoch);
    printf("[");
    int i = 0;
    for(; i<percent; i++)
        printf("=");
    printf(">");
    i++;
    for(; i<100; i++)
        printf(" ");
    printf("] %3.3f%     \r", percent);
    fflush(stdout);
    
}
