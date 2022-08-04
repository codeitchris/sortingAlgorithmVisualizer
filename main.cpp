#include <iostream>
#include "raylib.h"
#include <ctime>
#include <cstdlib>
#include <vector>
#include <utility>

#define ScreenWidth 1200
#define ScreenHeight 800

#define MinWindowWidth 500
#define MinWindowHeight 800

#define FPS 120

#define LOCALMINUM 4
#define POSITIONVAL 3
#define SELECTED 2 
#define SORTED 1
#define NORMAL 0



int numOfColumn = 50;
int SortingSpeed = 61;


std::vector<std::pair<int, int>     > arr(numOfColumn);

Color findColor(int pillerState) {
    switch (pillerState) {
        case LOCALMINUM:
            return RED;
            break;
        case POSITIONVAL:
            return DARKGRAY;
            break;
        case SELECTED:
            return LIGHTGRAY;
            break;
        case SORTED:
            return GREEN;
            break;
        default:
            return GOLD;
            break;
    }
    }
    
void openerbutton(float size, char Bubble_Sort_text[]);
void opener();
void button(float x, float y, char *Text, Color color, bool &state);
void bubblesort(std::vector<std::pair<int, int> > &arr);
void whichSort();
void speedFunction(char operation, int &value);
void endScreen();
void nSquaredSortOptions();
void nLogNsortOptions();
void hybridSortOptions();
void complexityChoice();



void drawarr(std::vector<std::pair<int, int> > arr) {
    float barWidth = (float) GetScreenWidth() / numOfColumn;

    for(int i = 0; i < numOfColumn; i++) {
        Color color = findColor(arr[i].second);

        DrawRectangleV (Vector2{(float) i*barWidth, (float) GetScreenHeight() - arr[i].first},
                        Vector2{barWidth, (float) arr[i].first}, color);
    }
}

bool shouldRND = true;
bool shldmenue = false;
bool shldopener = true;
bool speedPlus = false;
bool speedDec = false;
bool addSize = false;
bool normSize = false;
bool normSpeed = false;
bool doStartOptions = false;
bool shldSort = false;
bool subSize = false;
bool doMenue = false;
bool doEnding = false;
bool bubbleSortbool = false;
bool selectionSortbool = false;
bool insertionSortbool = false;
bool mergeSortbool = false;
bool quickSortbool = false;
bool heapSortbool = false;
bool timSortbool = false;
bool introSortbool = false;
bool nsquaredsortoptionbool = false;
bool nlognsortotionbool = false;
bool hybridbool = false; 
bool openerButtonPressed = false;





void opener(){
    float font = (2.5 * GetScreenWidth())/100;
    char opening_text[] = "You want some sorting!?";
    float tmp = MeasureText(opening_text, font)/2;
    openerbutton(tmp, opening_text);
    
    
    drawarr(arr);
}
void openerbutton(float size, char Bubble_Sort_text[]){
    Color color;
    if (openerButtonPressed)
        color = DARKBROWN;
    else
        color = GREEN; 


    button(GetScreenWidth()/2- size, GetScreenHeight()/20, Bubble_Sort_text, color, openerButtonPressed);
}

void button(float x, float y, char *Text, Color color, bool &state){
    float font = (2.5*GetScreenWidth())/100;
    Rectangle r1 = {
        .x =x,
        .y=y,
        .width = (float) MeasureText(Text, font),
        .height = (float) font,
    };


    if(CheckCollisionPointRec(GetMousePosition(), r1)){
        DrawText(Text, x,y,font,RED);
        if(IsMouseButtonPressed(0)){
           if(state == true)
                state = false;
            else
                state = true;
           
           return; 
        }
    } else {
        DrawText(Text, x,y,font,color);
    }

    return;
}



void RNDarr(std::vector<std::pair<int, int> >& arr) {
    
    for(int i =0; i<numOfColumn; i++)
        arr[i] = {GetRandomValue(40,MinWindowHeight - 80), NORMAL};
    
    
    shouldRND = false;
    return;
}



void speedFunction(char operation, int &value) {
    switch(operation)
    {
        case '-':
            value = value - 10 > 0 ? value - 10 : value;
            break;
        case '+':
            value += 10;
            break;

        default:
            value = 61;
            break;
    }
    SetTargetFPS(SortingSpeed);
}

void ChangeSize(char operation, int &value) {
    switch(operation)
    {
        case '-':
            if(value > 5){
                value -=5;
                for (int i =0; i<5; i++){
                    arr.pop_back();
                }
            }
            break;
        case '+':
            value += 5;
            for (int i =0; i<5; i++){
                    arr.push_back({GetRandomValue(40, MinWindowWidth-80), NORMAL});
                }
            break;
        default:
           while(numOfColumn > 50){
               numOfColumn--;
               arr.pop_back();
           }
           while(numOfColumn < 50){
               numOfColumn++;
               arr.push_back({GetRandomValue(40, MinWindowWidth-80), NORMAL});
           }
           break;
    }

    for(int i = 0; i < numOfColumn; i++){
        arr[i].second = NORMAL;
    }
    drawarr(arr);
}

void showStartOptions() {

    float font = (2.5*GetScreenWidth())/100;

    char StartText[] = "start sorting";
    float tmp=(27*GetScreenWidth())/100;
    button(tmp, GetScreenHeight()/20 + font*2, StartText, DARKGRAY, shldSort);
    if(shldSort){
        return;
    }
        

    tmp+= MeasureText(StartText, font) + 75;
    char RandomizeArrayText[] = "randomize array";
    button(tmp, GetScreenHeight()/20 + font*2, RandomizeArrayText, DARKGRAY, shouldRND);

    speedPlus = false;
    speedDec = false;
    addSize = false;
    subSize = false;

    normSize = false;
    normSpeed = false;

    tmp = (84.2*GetScreenWidth())/100;
    char timeButtonText[] = "speed";

    button(tmp, GetScreenHeight()/20 + font*2, timeButtonText, DARKGRAY, normSpeed);

    if(normSpeed){
        speedFunction('/', SortingSpeed);
        return;
    }

    tmp+= MeasureText(timeButtonText, font) + 20;
    char SpeedPlisButtonText[] = "+";
    button(tmp, GetScreenHeight()/20 + font*2, SpeedPlisButtonText, ORANGE, speedPlus);

    if(speedPlus) {
        speedFunction('+', SortingSpeed);
        return;
    }

    tmp += MeasureText(SpeedPlisButtonText, font) +  20;
    char SpeedMinuesButtonText[] = "-";
    button(tmp, GetScreenHeight()/20 + font*2, SpeedMinuesButtonText, ORANGE, speedDec);

    if(speedDec) {
        speedFunction('-', SortingSpeed);
        return;
    }

    tmp = (5*GetScreenWidth())/100;
    char SizeButtonText[] = "size";
    button(tmp, GetScreenHeight()/20 + font*2, SizeButtonText, DARKGRAY, normSize);

    if(normSize) {
        ChangeSize('/', numOfColumn);
        return;
    }

    tmp += MeasureText(SizeButtonText, font) +20;
    char SizePlusButton[] = "+";
    button(tmp, GetScreenHeight()/20 + font*2, SizePlusButton, ORANGE, addSize);

    if (addSize) {
        ChangeSize('+', numOfColumn);
        return;
    }

    tmp += MeasureText(SizePlusButton, font) +20;
    char SizeMinusButton[] = "-";
    button(tmp, GetScreenHeight()/20 + font*2, SizeMinusButton, ORANGE, subSize);

    if(subSize){
        ChangeSize('-', numOfColumn);
        return;
    }

}







// n^2 complexity

void bubblesort(std::vector<std::pair<int, int> > &arr){
    bool swapped;
    int endingPoint = numOfColumn;
    do {
        swapped = false;
        for (int i = 0; i< endingPoint - 1; i++){

            arr[i].second = SELECTED;

            if (arr[i] > arr[i+1]){
                std::swap(arr[i].first, arr[i+1].first);

                swapped = true;
            }

            BeginDrawing();

            ClearBackground(BLUE);

            for(int k = numOfColumn - 1; k>= endingPoint; k--)
                arr[k].second = SORTED;
            
            drawarr(arr);

            for(int k = i; k>= 0; k--)
                arr[k].second = NORMAL;
            EndDrawing();


        }
        endingPoint--;
    } while(swapped);

    for (int i = numOfColumn - 1; i>= 0; i--){
        arr[i].second = SORTED;
    }
}
void selectionsort(std::vector<std::pair<int, int> > &arr){
    int localmin = 0;
    int oldnews = 0;
    int endpt = numOfColumn;
    bool swapped;
    do {
    for(int i = 0; i < endpt-1; i++){
        swapped = false;
        localmin = i+1;
        arr[i].second = POSITIONVAL;
        for(int j = i + 1; j < endpt-1; j++){
            arr[j].second = SELECTED;
            if (arr[j].first < arr[i].first){
                if(arr[j].first < arr[localmin].first ){
                    oldnews = localmin;
                    localmin = j;
                    arr[localmin].second = LOCALMINUM;
                    arr[oldnews].second = SELECTED;
                }
            }
        }
        if(arr[localmin].first < arr[i].first){
            std::swap(arr[i], arr[localmin]);
            swapped = true;
        }  
            BeginDrawing();

            ClearBackground(BLUE);

            for(int k = numOfColumn - 1; k>= endpt; k--)
                arr[k].second = SORTED;
            
            drawarr(arr);

            for(int k = i; k>= 0; k--)
                arr[k].second = NORMAL;
            EndDrawing();
    } 
    } while(swapped);

    for (int i = numOfColumn - 1; i>= 0; i--){
        arr[i].second = SORTED;
    }
}

void insertionsort(std::vector<std::pair<int, int> > &arr){

}

//nlogn

void mergesort(std::vector<std::pair<int, int> > &arr){

}

void quicksort(std::vector<std::pair<int, int> > &arr){

}

void heapsort(std::vector<std::pair<int, int> > &arr){

}

//hybrid

void timsort(std::vector<std::pair<int, int> > &arr){

}

void introsort(std::vector<std::pair<int, int> > &arr){

}

void whichSort(int x, int y) {
    if(x == 0){
        if(y == 0){
            bubblesort(arr);
            drawarr(arr);
        }
        if (y== 1){
            selectionsort(arr);
            drawarr(arr);
        }
        if ( y== 2){
            insertionsort(arr);
            drawarr(arr);
        }
    }

    if(x == 1){
        if(y == 0){
            mergesort(arr);
            drawarr(arr);
        }
        if (y== 1){
            quicksort(arr);
            drawarr(arr);
        }
        if ( y== 2){
            heapsort(arr);
            drawarr(arr);
        }
    }

    if(x == 2){
        if(y == 0){
            timsort(arr);
            drawarr(arr);
        }
        if (y== 1){
            introsort(arr);
            drawarr(arr);
        }
    }
    

    
}


void endScreen() {
    drawarr(arr);

    doMenue = true;
    doStartOptions = true;
    
}

int typeSortcounter = 0;


bool nSquaredComplexity = false;
bool nlognComplexity = false;
bool hybridcomplexity = false;




void complexityChoice() {
    float font = (2.5*GetScreenWidth())/100;

    char nSquaredText[] = "n-Squared";
    float tmp=(27.0*GetScreenWidth())/100;
    button(tmp, GetScreenHeight()/20 + font*2, nSquaredText, DARKGRAY, nSquaredComplexity);

    if(nSquaredComplexity){
        typeSortcounter = 0;
        return;
    }

    tmp+= MeasureText(nSquaredText, font) + 100;
    char nlogntext[] = "nLog(n)";
    button(tmp, GetScreenHeight()/20 + font*2, nlogntext, DARKGRAY, nlognComplexity);

    if(nlognComplexity){
        typeSortcounter = 1;
        return;
    }

    tmp+= MeasureText(nlogntext, font) + 100;
    char hybridtext[] = "hybrid";
    button(tmp, GetScreenHeight()/20 + font*2, hybridtext, DARKGRAY, hybridcomplexity);

    if(hybridcomplexity){
        typeSortcounter = 2;
        return;
    }
}


int sortCount = 0;


void nSquaredSortOptions() {
    float font = (2.5*GetScreenWidth())/100;
    float tmp = (15.0*GetScreenWidth())/100;


    char bubblesortText[] = "bubble sort";
    button(tmp, GetScreenHeight()/20 + font*2, bubblesortText, DARKGRAY, bubbleSortbool);
    if(bubbleSortbool){
        sortCount = 0;
        return;
    }
    

    tmp += MeasureText(bubblesortText, font) + 80;
    char selectionSortText[] = "selection sort";
    
    button(tmp, GetScreenHeight()/20 + font*2, selectionSortText, DARKGRAY, selectionSortbool);
    if(selectionSortbool){
        sortCount = 1;
        return;
    }
    
    tmp+= MeasureText(selectionSortText, font) + 80;
    char insertionSortText[] = "insertion sort";
    button(tmp, GetScreenHeight()/20 + font*2, insertionSortText, DARKGRAY, insertionSortbool);
    if(insertionSortbool){
        sortCount = 2;
        return;
    }

}

void nLogNsortOptions(){
    float font = (2.5*GetScreenWidth())/100;
    float tmp=(20.0*GetScreenWidth())/100;
    
    char mergeSortText[] = "merge sort";
    button(tmp, GetScreenHeight()/20 + font*2, mergeSortText, DARKGRAY, mergeSortbool);
    if(mergeSortbool){
        sortCount = 0;
        return;
    }


    tmp+= MeasureText(mergeSortText, font) + 80;
    char quickSortText[] = "quick sort";
    button(tmp, GetScreenHeight()/20 + font*2, quickSortText, DARKGRAY, quickSortbool);
    if(selectionSortbool){
        sortCount = 1;
        return;
    }


    tmp += MeasureText(quickSortText, font) +  80;
    char heapSortText[] = "heap sort";
    button(tmp, GetScreenHeight()/20 + font*2, heapSortText, DARKGRAY, heapSortbool);
    if(heapSortbool){
        sortCount = 2;
        return;
    }
    
}
 
void hybridSortOptions(){
    float font = (2.5*GetScreenWidth())/100;
    float tmp=(15.0*GetScreenWidth())/100;

    char timSortText[] = "timsort";
    button(tmp, GetScreenHeight()/20 + font*2, timSortText, DARKGRAY, timSortbool);
    if(timSortbool){
        sortCount = 0;
        return;
    }

    tmp += MeasureText(timSortText, font) + 80;
    char introSortText[] = "introsort";
    button(tmp, GetScreenHeight()/20 + font*2, introSortText, DARKGRAY, introSortbool);
    if(introSortbool){
        sortCount = 1;
        return;
    }

}



int main() {
    
    
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(ScreenWidth, ScreenHeight, "begin");
    SetWindowMinSize(MinWindowWidth, MinWindowHeight);


    SetTargetFPS(FPS);

    while(!WindowShouldClose()){
        
        if (shldopener)
            opener();
        
        
        if(openerButtonPressed) 
            complexityChoice();
        
        
        if(nSquaredComplexity){
            openerButtonPressed = false;
            nSquaredSortOptions();
        } 
        if(nlognComplexity){
            openerButtonPressed = false;
            nLogNsortOptions();
        } 
        if(hybridcomplexity){
            openerButtonPressed = false;
            hybridSortOptions();
        }
        
        if (bubbleSortbool){
            nSquaredComplexity = false;
            doStartOptions = true;
        }
        if(insertionSortbool){
            nSquaredComplexity = false;
            doStartOptions = true;
        }
        if(selectionSortbool){
            nSquaredComplexity = false;
            doStartOptions = true;
        }
        if(mergeSortbool){
            nlognComplexity = false;
            doStartOptions = true;
        }
        if(quickSortbool ){
            nlognComplexity = false;
            doStartOptions = true;
        }
        if(heapSortbool){
            nlognComplexity = false;
            doStartOptions = true;
        }
        if(timSortbool){
            hybridcomplexity = false; 
            doStartOptions = true;
        }
        if(introSortbool) {
            hybridcomplexity = false; 
            doStartOptions = true;
        }

        if (doStartOptions)
            showStartOptions();
        
        
        if(shouldRND)
            RNDarr(arr);
        
        if(shldSort){
            doMenue = false;
            doStartOptions = false;

            SetTargetFPS(SortingSpeed);
            whichSort(typeSortcounter, sortCount);
            
            shldSort = false;
            doEnding = true;
            
        }
        
        if(doEnding)
            endScreen();
        
        BeginDrawing();

    
        ClearBackground(BLUE);

        EndDrawing();
    }
    
    CloseWindow();
    
    return 0;
}