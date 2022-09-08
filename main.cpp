#include <iostream>
#include "raylib.h"
#include <ctime>
#include <cstdlib>
#include <vector>
#include <utility>


// Global definitions
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
//Function declerations so I can use functions anywhere
void openerbutton(float size, char Bubble_Sort_text[]);
void opener();
void button(float x, float y, char *Text, Color color, bool &state);
void bubblesort(std::vector<std::pair<int, int> > &arr);
void whichSort();
void speedFunction(char operation, int &value);
void endScreen();
void nSquaredSortOptions();
void nLogNsortOptions();
void complexityChoice();


void mergesort(std::vector<std::pair<int, int> >& arr, int min, int max);
void merge(std::vector<std::pair<int, int> >& arr, int min, int mid, int max);

void heapSort(std::vector<std::pair<int, int> >& arr, int n);
void heapify(std::vector<std::pair<int, int> >& arr, int n, int counter);
void maxHeap(std::vector<std::pair<int, int> >& arr, int n);




void drawarr(std::vector<std::pair<int, int> > arr) {
    float barWidth = (float) GetScreenWidth() / numOfColumn;

    for(int i = 0; i < numOfColumn; i++) {
        Color color = findColor(arr[i].second);

        DrawRectangleV (Vector2{(float) i*barWidth, (float) GetScreenHeight() - arr[i].first},
                        Vector2{barWidth, (float) arr[i].first}, color);
    }
}
// Bollean declerations, yeah there is ALOT of them, big project!
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
bool nsquaredsortoptionbool = false;
bool nlognsortotionbool = false;
bool openerButtonPressed = false;
bool backButtonPressed = false;



// Open screen code
void opener(){
    float font = (2.5 * GetScreenWidth())/100;
    char opening_text[] = "You want some sorting!?";
    float tmp = MeasureText(opening_text, font)/2;
    openerbutton(tmp, opening_text);
    
    char backButton[] = "back to start";
    float tmp2 = MeasureText(backButton, font)/2;
    button(GetScreenWidth()/10 - tmp2, GetScreenHeight()/30, backButton, DARKGRAY, backButtonPressed);    
    drawarr(arr);
}

//Code for the buttons
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


//Randomizes the array
void RNDarr(std::vector<std::pair<int, int> >& arr) {
    
    for(int i =0; i<numOfColumn; i++)
        arr[i] = {GetRandomValue(40,MinWindowWidth - 30), NORMAL};
    
    
    shouldRND = false;
    return;
}


//Code to change speed at which we sort
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
//Changes size of the array
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
// Code for the buttons on starting screen
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







// n^2 complexity implementations

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
int varcounter = 0;
void insertionsort(std::vector<std::pair<int, int> > &arr){
    bool swapped;
    int endpt = numOfColumn;
    do
    {
    for(int i = 1; i < numOfColumn; i++){
        swapped = false;
        varcounter = i;
        arr[i].second = LOCALMINUM;
        if (arr[varcounter].first < arr[varcounter-1].first){
            do
            {
                std::swap(arr[varcounter], arr[varcounter-1]);
                swapped = true;
                if (varcounter != 0)
                    varcounter--;
            } while (arr[varcounter].first < arr[varcounter-1].first);
        
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
    } while (swapped);

    for (int i = numOfColumn - 1; i>= 0; i--){
        arr[i].second = SORTED;
    }

}

//nlogn implementations

void merge(std::vector<std::pair<int, int> >& arr, int min, int mid, int max){
    
    int lWalk = min;
    int copyWalk = min;
    int rWalk = mid +1;
    int endpt = numOfColumn;

    int lEnd = (mid+max)/2;
    int rBeg = lEnd +1;

    bool swapped;
    std::vector<std::pair<int, int> > arrCopy = arr;

    do
    {
    swapped = false;
    while(lWalk <= mid && rWalk<=max){
        if(arr[lWalk].first < arr[rWalk].first){
             arrCopy[copyWalk] = arr[lWalk];
             lWalk++;
             copyWalk++;
             swapped =true;
            BeginDrawing();

            ClearBackground(BLUE);

            for(int k = numOfColumn - 1; k>= endpt; k--)
                arr[k].second = SORTED;
            
            drawarr(arr);

            for(int k = lWalk; k>= 0; k--)
                arr[k].second = NORMAL;
            EndDrawing();
        } else{
            arrCopy[copyWalk] = arr[rWalk];
            rWalk++;
            copyWalk++;
            swapped =true;
            BeginDrawing();

            ClearBackground(BLUE);

            for(int k = numOfColumn - 1; k>= endpt; k--)
                arr[k].second = SORTED;
            
            drawarr(arr);

            for(int k = rWalk; k>= 0; k--)
                arr[k].second = NORMAL;
            EndDrawing();
        }
        
    }

    while (lWalk <= mid){
        arrCopy[copyWalk] = arr[lWalk];
        lWalk++;
        copyWalk++;
        swapped =true;
            BeginDrawing();

            ClearBackground(BLUE);

            for(int k = numOfColumn - 1; k>= endpt; k--)
                arr[k].second = SORTED;
            
            drawarr(arr);

            for(int k = lWalk; k>= 0; k--)
                arr[k].second = NORMAL;
            EndDrawing();
    }

    while (rWalk <= max){
        arrCopy[copyWalk] = arr[rWalk];
        rWalk++;
        copyWalk++;
        swapped =true;
            BeginDrawing();

            ClearBackground(BLUE);

            for(int k = numOfColumn - 1; k>= endpt; k--)
                arr[k].second = SORTED;
            
            drawarr(arr);

            for(int k = rWalk; k>= 0; k--)
                arr[k].second = NORMAL;
            EndDrawing();
    }

    for(int i = 0; i < arrCopy.size(); i++) {
        arr[i] = arrCopy[i];
    }


    } while (swapped);
    


    for (int i = numOfColumn - 1; i>= 0; i--){
        arr[i].second = SORTED;
    }

}


void mergesort(std::vector<std::pair<int, int> >& arr, int min, int max){
    if(min < max) {
        int midPoint = (min + max)/2;
        mergesort(arr, min, midPoint);
        mergesort(arr, midPoint + 1, max);
        merge(arr, min, midPoint, max);
    }
}

int itemFromLeft = 0;

void quick(std::vector<std::pair<int, int> >& arr, int L, int R,  int pivot){
    bool swapped;
    int endpt= numOfColumn;
    do
    {
        swapped = false;
        while(L <= R){
        arr[L].second=LOCALMINUM;
        while(arr[L].first < arr[pivot].first){
            
            L++;

        }
        
        while(arr[R].first > arr[pivot].first){
            R--;

        }

        if(L <= R){
            std::swap(arr[L], arr[R]);
            swapped = true;
            L++;
            R--;
            BeginDrawing();

            ClearBackground(BLUE);

            for(int k = numOfColumn - 1; k>= endpt; k--)
                arr[k].second = SORTED;
            
            drawarr(arr);

            for(int k = L; k>= 0; k--)
                arr[k].second = NORMAL;
            EndDrawing();
        } 
        }
        itemFromLeft = L;
    } while (swapped);
    
    
    for (int i = numOfColumn - 1; i>= 0; i--){
        arr[i].second = SORTED;
    } 

}

void quickSort(std::vector<std::pair<int, int> >& arr, int L, int R){
    if (L >= R){
        return;
    }
    else {
    int pivotPoint = (L + R)/2;
    quick(arr, L, R, pivotPoint);
    int index = itemFromLeft;
    quickSort(arr, L, index-1);
    quickSort(arr, index, R);
    }
}

void heapSort(std::vector<std::pair<int, int> >& arr, int n){
    int endingPoint = numOfColumn;
    bool swapped;

    maxHeap(arr, n);
    do
    {
        swapped = false;
        for(int i = n-1; i >=0; i--){
        arr[0].second = LOCALMINUM;
        std::swap(arr[0], arr[i]);
        heapify(arr,i,0);

            BeginDrawing();

            ClearBackground(BLUE);

            for(int k = numOfColumn - 1; k>= endingPoint; k--)
                arr[k].second = SORTED;
            
            drawarr(arr);

            for(int k = i; k>= 0; k--)
                arr[k].second = NORMAL;
            EndDrawing();
    }
    } while (swapped);
    
    for (int i = 0; i<= numOfColumn - 1; i++){
        SetTargetFPS(80);
        arr[i].second = SORTED;
    } 

}

void heapify(std::vector<std::pair<int, int> >& arr, int n, int counter){
    int left = 2*counter + 1;
    int right = 2*counter + 2;
    int max = counter;
    


            
    if(left < n && arr[left].first > arr[counter].first){
        max = left;
        //arr[max].second = SELECTED;
    }
        
    
    if(right < n && arr[right].first > arr[max].first){
        max = right;
        //arr[max].second = SELECTED;
    }
        
    
    if(max != counter){
        arr[max].second = SELECTED;
        std::swap(arr[counter], arr[max]);
        heapify(arr, n, max);
    }
    
     
        


}

void maxHeap(std::vector<std::pair<int, int> >& arr, int n){
    for(int k = n/2 - 1; k >= 0; k--){
        heapify(arr, n, k);
    }

}

// Code to tell what button was pressed for the type of sorting
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
            mergesort(arr, 0, numOfColumn-1);
            drawarr(arr);
        }
        if (y== 1){
            quickSort(arr, 0, numOfColumn-1);
            drawarr(arr);
        }
        if ( y== 2){
            heapSort(arr, numOfColumn);
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


// Buttons for the complexity / type of sorrting used


void complexityChoice() {
    float font = (2.5*GetScreenWidth())/100;

    char nSquaredText[] = "n-Squared";
    float tmp=(30.0*GetScreenWidth())/100;
    button(tmp, GetScreenHeight()/23 + font*2, nSquaredText, DARKGRAY, nSquaredComplexity);

    if(nSquaredComplexity){
        typeSortcounter = 0;
        return;
    }

    tmp+= MeasureText(nSquaredText, font) + 225;
    char nlogntext[] = "nLog(n)";
    button(tmp, GetScreenHeight()/23 + font*2, nlogntext, DARKGRAY, nlognComplexity);

    if(nlognComplexity){
        typeSortcounter = 1;
        return;
    }


}


int sortCount = 0;


void nSquaredSortOptions() {
    float font = (2.5*GetScreenWidth())/100;
    float tmp = (20.0*GetScreenWidth())/100;


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
    button(tmp, GetScreenHeight()/15 + font*2, mergeSortText, DARKGRAY, mergeSortbool);
    if(mergeSortbool){
        sortCount = 0;
        return;
    }


    tmp+= MeasureText(mergeSortText, font) + 125;
    char quickSortText[] = "quick sort";
    button(tmp, GetScreenHeight()/15 + font*2, quickSortText, DARKGRAY, quickSortbool);
    if(selectionSortbool){
        sortCount = 1;
        return;
    }


    tmp += MeasureText(quickSortText, font) +  125;
    char heapSortText[] = "heap sort";
    button(tmp, GetScreenHeight()/15 + font*2, heapSortText, DARKGRAY, heapSortbool);
    if(heapSortbool){
        sortCount = 2;
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
        
        
        if(openerButtonPressed) {
            complexityChoice();
        }
            
        // Naviagates through bool's of buttons and triggers
        //code based on the bool's states.
        if(backButtonPressed){
            openerButtonPressed = false;
            nSquaredComplexity = false;
            nlognComplexity = false;
            bubbleSortbool = false;
            selectionSortbool = false;
            insertionSortbool = false;
            mergeSortbool = false;
            quickSortbool = false;
            heapSortbool = false;
            doStartOptions = false;
            doMenue = false;
            shldmenue = false;
            doEnding = false;
            opener();
        }


        if(nSquaredComplexity){
            openerButtonPressed = false;
            nSquaredSortOptions();
        } 
        if(nlognComplexity){
            openerButtonPressed = false;
            nLogNsortOptions();
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