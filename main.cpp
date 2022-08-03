#include <iostream>
#include "raylib.h"
#include <ctime>
#include <cstdlib>
#include <vector>

#define ScreenWidth 1200
#define ScreenHeight 800

#define MinWindowWidth 500
#define MinWindowHeight 800

#define FPS 120


#define SELECTED 2 
#define SORTED 1
#define NORMAL 0


int numOfColumn = 50;
int SortingSpeed = 61;


std::vector<std::pair<int, int>     > arr(numOfColumn);

Color findColor(int pillerState) {
    switch (pillerState) {
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
    
void Bubble_Sort_Button(float size, char Bubble_Sort_text[]);
void menue();
void button(float x, float y, char *Text, Color color, bool &state);
void Start_Button(float size, float font, char Start[]);
void bubblesort(std::vector<std::pair<int, int> > &arr);
void sortarray();
void ChangeSpeed(char operation, int &value);
void showEndingScreen();



void drawarr(std::vector<std::pair<int, int> > arr) {
    float barWidth = (float) GetScreenWidth() / numOfColumn;

    for(int i = 0; i < numOfColumn; i++) {
        Color color = findColor(arr[i].second);

        DrawRectangleV (Vector2{(float) i*barWidth, (float) GetScreenHeight() - arr[i].first},
                        Vector2{barWidth, (float) arr[i].first}, color);
    }
}

bool shouldRND = true;
bool shldmenue = true;
bool BubbleSortPressed = false;
bool addSpeed = false;
bool subSpeed = false;
bool addSize = false;
bool normalSize = false;
bool normalSpeed = false;
bool shouldShowStartOptions = false;
bool shouldStartGame = false;
bool shouldStartSorting = false;
bool NormalSize = false;
bool NormalSpeed= false;
bool subSize = false;
bool shouldShowMenuScreen = false;
bool shouldShowEndingScreen = false;





void menue(){
    float font = (2.5 * GetScreenWidth())/100;
    char Bubble_Sort_Text[] = "Bubble Sort!?";
    float tmp = MeasureText(Bubble_Sort_Text, font)/2;
    Bubble_Sort_Button(tmp, Bubble_Sort_Text);
    
    
    drawarr(arr);
}
void Bubble_Sort_Button(float size, char Bubble_Sort_text[]){
    Color color;
    if (BubbleSortPressed)
        color = DARKBROWN;
    else
        color = GREEN; 


    button(GetScreenWidth()/2- size, GetScreenHeight()/20, Bubble_Sort_text, color, BubbleSortPressed);
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



void ChangeSpeed(char operation, int &value) {
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
    Start_Button(tmp, font, StartText);

    tmp+= MeasureText(StartText, font) + 75;
    char RandomizeArrayText[] = "randomize array";
    button(tmp, GetScreenHeight()/20 + font*2, RandomizeArrayText, DARKGRAY, shouldRND);

    addSpeed = false;
    subSpeed = false;
    addSize = false;
    subSize = false;

    normalSize = false;
    normalSpeed = false;

    tmp = (84.2*GetScreenWidth())/100;
    char timeButtonText[] = "speed";

    button(tmp, GetScreenHeight()/20 + font*2, timeButtonText, DARKGRAY, normalSpeed);

    if(normalSpeed){
        ChangeSpeed('/', SortingSpeed);
        return;
    }

    tmp+= MeasureText(timeButtonText, font) + 20;
    char SpeedPlisButtonText[] = "+";
    button(tmp, GetScreenHeight()/20 + font*2, SpeedPlisButtonText, ORANGE, addSpeed);

    if(addSpeed) {
        ChangeSpeed('+', SortingSpeed);
        return;
    }

    tmp += MeasureText(SpeedPlisButtonText, font) +  20;
    char SpeedMinuesButtonText[] = "-";
    button(tmp, GetScreenHeight()/20 + font*2, SpeedMinuesButtonText, ORANGE, subSpeed);

    if(subSpeed) {
        ChangeSpeed('-', SortingSpeed);
        return;
    }

    tmp = (5*GetScreenWidth())/100;
    char SizeButtonText[] = "size";
    button(tmp, GetScreenHeight()/20 + font*2, SizeButtonText, DARKGRAY, normalSize);

    if(NormalSize) {
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


void Start_Button(float size, float font, char Start[]) {
    button(size, GetScreenHeight()/20 + font*2, Start, DARKGRAY, shouldStartSorting);

    return;
}


void sortarray() {
    bubblesort(arr);

    drawarr(arr);
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
                std::swap(arr[i], arr[i+1]);

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


void showEndingScreen() {
    drawarr(arr);

    shouldShowMenuScreen = true;
    shouldShowStartOptions = true;
    
}

void selectionsort(){

}

void insertionsort(){

}

//nlogn

void mergesort(){

}

void quicksort(){

}

void heapsort(){

}

//hybrid

void timsort(){

}

void introsort(){

}




int main() {
    
    
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(ScreenWidth, ScreenHeight, "First sorting test");
    SetWindowMinSize(MinWindowWidth, MinWindowHeight);


    SetTargetFPS(FPS);

    while(!WindowShouldClose()){
        
        if (shldmenue)
            menue();
        
        shouldShowStartOptions = false;
        if (BubbleSortPressed)
            shouldShowStartOptions = true;


        if (shouldShowStartOptions)
            showStartOptions();
        
        
        if(shouldRND)
            RNDarr(arr);
        
        if(shouldStartSorting){
            shouldShowMenuScreen = false;
            shouldShowStartOptions = false;

            SetTargetFPS(SortingSpeed);
            sortarray();
            
            shouldStartSorting = false;
            shouldShowEndingScreen = true;
            
        }
        
        if(shouldShowEndingScreen)
            showEndingScreen();
        
        BeginDrawing();

    
        ClearBackground(BLUE);

        EndDrawing();
    }
    
    CloseWindow();
    
    return 0;
}