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





// n^2 complexity

void bubblesort(int sz, int arr[10]){
    for(int i = 0; i < sz - 1; i++) {
        for(int j = 0; j < sz - 1; j++) {
            while (arr[j] > arr[j+1]){
                int x = arr[j];
                int y = arr[j+1];
                std::swap(x, y);
                arr[j] = x;
                arr[j+1] = y;
            } 
        }
    }
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
    //bubblesort(arrSize, arr);
    
    
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(ScreenWidth, ScreenHeight, "First sorting test");
    SetWindowMinSize(MinWindowWidth, MinWindowHeight);


    SetTargetFPS(FPS);

    while(!WindowShouldClose()){
        
        if (shldmenue)
            menue();
        
        if(shouldRND)
            RNDarr(arr);
        
        BeginDrawing();

    
        ClearBackground(BLUE);

        EndDrawing();
    }
    
    CloseWindow();
    
    return 0;
}