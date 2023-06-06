#ifndef SORTING_SCREEN_CPP
#define SORTING_SCREEN_CPP

#include <stdio.h>
#include <windows.h>

#include "../headers/utility.h"
#include "../headers/userInterface.h"
#include "../headers/globals.h"

namespace SortingScreen {
  namespace Bar {
    struct Bar {
      int xPos;
      int yPos;
      int height;
    };

    void renderBar(Bar bar, int delay = 0) {
      for (auto i = 0; i < bar.height; i++) {
        Sleep(delay);
        Utility::setConsoleCursorPosition(bar.xPos, bar.yPos - i);
        printf("%c", Globals::BLOCK);
      }
    }

    Bar* getRandomizedBars() {
      Bar* bars = (Bar*) malloc(120 * sizeof(Bar));
      for (size_t i = 4; i < 113; i++){
        Bar bar = { (int) i, 21, rand() % 19 + 1 };
        bars[i] = bar;
      }

      return bars;
    }
  
    void animateRandomizedBars(Bar* bars){
      for (auto i = 4; i < 113; i++){
        Utility::setConsoleTextColor("FOREGROUND_BLUE");
        renderBar(bars[i], 1);
      }
      
      for (auto i = 4; i < 113; i++){
        Sleep(5);
        Utility::setConsoleTextColor("FOREGROUND_GREEN");
        renderBar(bars[i]);
      }

      for (auto i = 4; i < 113; i++){
        Utility::setConsoleTextColor("FOREGROUND_WHITE");
        renderBar(bars[i]);
      }
    }
  
    void clearBar(Bar bar){
      for (auto i = 0; i < 19; i++){
        Utility::setConsoleCursorPosition(bar.xPos, bar.yPos - i);
        printf(" ");
      }
    }

    void swapHeight(Bar* a, Bar* b){
      int temp = a->height;
      a->height = b->height;
      b->height = temp;
    }
  };

  namespace QuickSort {
    int partition(Bar::Bar* bars, int leftIndex, int rightIndex){

      int j = leftIndex - 1;
      for (int i = leftIndex; i < rightIndex; i++){
        Utility::setConsoleTextColor("FOREGROUND_RED");
        Bar::renderBar(bars[i]);
        Sleep(10);

        Utility::setConsoleTextColor("FOREGROUND_WHITE");
        Bar::renderBar(bars[i]);

        if (bars[i].height < bars[rightIndex].height){
          swapHeight(&bars[i], &bars[++j]);
          Bar::clearBar(bars[i]);
          Bar::clearBar(bars[j]);

          Bar::renderBar(bars[i]);
          Bar::renderBar(bars[j]);
          Sleep(10);
        }
      }
      
      swapHeight(&bars[rightIndex], &bars[++j]);
      clearBar(bars[rightIndex]);
      clearBar(bars[j]);

      Bar::renderBar(bars[rightIndex]);
      Utility::setConsoleTextColor("FOREGROUND_BLUE");
      Bar::renderBar(bars[j]);
      Utility::setConsoleTextColor("FOREGROUND_WHITE");

      Sleep(10);

      return j;
    }

    void quickSort(Bar::Bar* bars, int leftIndex = 4, int rightIndex = 112){
      if (leftIndex <= rightIndex){
        int midIndex = partition(bars, leftIndex, rightIndex);

        quickSort(bars, leftIndex, midIndex - 1);
        quickSort(bars, midIndex + 1, rightIndex);
      }
    }
  }

  namespace MergeSort{
    void merge(Bar::Bar* bars, int leftIndex, int middleIndex, int rightIndex){
      int leftArraySize = middleIndex - leftIndex + 1, rightArraySize = rightIndex - middleIndex;

      Bar::Bar* leftArray = (Bar::Bar*) malloc(leftArraySize * sizeof(Bar::Bar));
      for (int i = 0; i < leftArraySize; i++) leftArray[i] = bars[leftIndex + i];

      Bar::Bar* rightArray = (Bar::Bar*) malloc(rightArraySize * sizeof(Bar::Bar));
      for (int i = 0; i < rightArraySize; i++) rightArray[i] = bars[middleIndex + 1 + i];

      int leftArrayPointer, rightArrayPointer, mainArrayPointer = leftIndex;
      leftArrayPointer = rightArrayPointer = 0;

      Utility::setConsoleTextColor("FOREGROUND_BLUE");

      while (leftArrayPointer < leftArraySize && rightArrayPointer < rightArraySize){
        bars[mainArrayPointer++].height = 
          leftArray[leftArrayPointer].height < rightArray[rightArrayPointer].height ?  
            leftArray[leftArrayPointer++].height : rightArray[rightArrayPointer++].height;

        Bar::clearBar(bars[mainArrayPointer - 1]);
        Bar::renderBar(bars[mainArrayPointer - 1]);
        Sleep(10);
      }

      while (leftArrayPointer < leftArraySize) {
        bars[mainArrayPointer++].height = leftArray[leftArrayPointer++].height;
        Bar::clearBar(bars[mainArrayPointer - 1]);
        Bar::renderBar(bars[mainArrayPointer - 1]);
        Sleep(10);
      }

      while (rightArrayPointer < rightArraySize) {
        bars[mainArrayPointer++].height = rightArray[rightArrayPointer++].height;
        Bar::clearBar(bars[mainArrayPointer - 1]);
        Bar::renderBar(bars[mainArrayPointer - 1]);
        Sleep(10);
      }

      Utility::setConsoleTextColor("FOREGROUND_WHITE");
    }

    void mergeSort(Bar::Bar* bars, int leftIndex = 4, int rightIndex = 112){
      if (leftIndex < rightIndex){
        int middleIndex = (leftIndex + rightIndex) / 2;
        mergeSort(bars, leftIndex, middleIndex);
        mergeSort(bars, middleIndex + 1, rightIndex);

        for (short int i = leftIndex; i <= rightIndex; i++) {
          clearBar(bars[i]);
          Sleep(5);
        }

        merge(bars, leftIndex, middleIndex, rightIndex);
      }
    }
  }

  UserInterface::Button btnQuickSort;
  UserInterface::Button btnMergeSort;
  UserInterface::Button btnHeapSort;
  UserInterface::Button btnBack;

  Bar::Bar *bars;

  void initializeUIElements() {
    const short X = 5;
    const short Y = 24;
    const short GAP = 6;
    
    btnQuickSort.position = { X, Y };
    btnQuickSort.pixelPosition = { 60, 300, 580, 640 };
    strncpy(btnQuickSort.text, "Quick Sort", 20);

    btnMergeSort.position = { X + (22 * 1) + (GAP * 1), Y };
    btnMergeSort.pixelPosition = { 380, 620, 580, 640 };
    strncpy(btnMergeSort.text, "Merge Sort", 20);

    btnHeapSort.position = { X + (22 * 2) + (GAP * 2) + 1, Y };
    btnHeapSort.pixelPosition = { 700, 940, 580, 640 };
    strncpy(btnHeapSort.text, "Heap Sort", 20);

    btnBack.position = { X + (22 * 3) + (GAP * 3) + 1, Y };
    btnBack.pixelPosition = { 990, 1230, 580, 640 };
    strncpy(btnBack.text, "Back", 20);
  }

  void displayUIElements() {
    Utility::UI::animateOuterBorder(0);
    Utility::UI::animateInnerBorder(0);

    bars = Bar::getRandomizedBars();
    Bar::animateRandomizedBars(bars);

    UserInterface::renderButton(btnQuickSort);
    UserInterface::renderButton(btnMergeSort);
    UserInterface::renderButton(btnHeapSort);
    UserInterface::renderButton(btnBack);
  }

  bool handleClick(POINT cursorPosition) {
    if (UserInterface::isPointerInButtonPixelPosition(btnQuickSort, cursorPosition)){
      QuickSort::quickSort(bars);
      return false;
    } else if (UserInterface::isPointerInButtonPixelPosition(btnMergeSort, cursorPosition)){
      MergeSort::mergeSort(bars);
      return false;
    } else if (UserInterface::isPointerInButtonPixelPosition(btnHeapSort, cursorPosition)){
      Utility::setConsoleCursorPosition(0, 1);
      printf("Heap Sort");
    } else if (UserInterface::isPointerInButtonPixelPosition(btnBack, cursorPosition)){
      return false;
    }

    return true;
  }

  bool setEventHandlers() {
    POINT cursorPosition;
	  HWND hWnd = GetForegroundWindow();

    if (GetAsyncKeyState(VK_LBUTTON) & 1) {
      GetCursorPos(&cursorPosition);
      ScreenToClient(hWnd, &cursorPosition);
    
      if (!handleClick(cursorPosition)) return false;
    }

    return true;
  }

  void show() {
    Utility::clearScreen();

    initializeUIElements();
    displayUIElements();
    
    while (setEventHandlers());
  }
}

#endif