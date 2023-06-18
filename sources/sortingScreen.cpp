#ifndef SORTING_SCREEN_CPP
#define SORTING_SCREEN_CPP

#include <stdio.h>
#include <windows.h>

#include "../headers/utility.h"
#include "../headers/userInterface.h"
#include "../headers/globals.h"

namespace SortingScreen {
  int numberOfBarsSorted;

  double getProgressPercentage() {
    double percentage = (numberOfBarsSorted / 109.0) * 100;
    if (percentage > 100) percentage = 100;

    return percentage;
  }

  void displaySortingStatistics() {
    const short X = 22;
    const short Y = 25;

    Utility::setConsoleTextColor("FOREGROUND_WHITE");

    Utility::setConsoleCursorPosition(X, Y);
    printf("Bars Sorted: %d/%d", numberOfBarsSorted, 109);

    Utility::setConsoleCursorPosition(X + 50, Y);
    printf("Bars Sorted: %.1f%%", getProgressPercentage());
  }

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
        printf("%c", Globals::BLOCK_PIECE);
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
  
    void animateRandomizedBars(Bar* bars) {
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
  
    void clearBar(Bar bar) {
      for (auto i = 0; i < 19; i++){
        Utility::setConsoleCursorPosition(bar.xPos, bar.yPos - i);
        printf(" ");
      }
    }

    void swapHeight(Bar* a, Bar* b) { 
      int temp = a->height;
      a->height = b->height;
      b->height = temp;
    }
  };

  namespace QuickSort {
    int partition(Bar::Bar* bars, int leftIndex, int rightIndex) {
      int j = leftIndex - 1;
      for (int i = leftIndex; i < rightIndex; i++) {
        Utility::setConsoleTextColor("FOREGROUND_RED");
        Bar::renderBar(bars[i]);
        Sleep(10);

        Utility::setConsoleTextColor("FOREGROUND_WHITE");
        Bar::renderBar(bars[i]);

        if (bars[i].height < bars[rightIndex].height) {
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

      numberOfBarsSorted++;
      displaySortingStatistics();

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

  namespace MergeSort {
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

        if (leftIndex == 4 && rightIndex == 112) {
          numberOfBarsSorted++;
          displaySortingStatistics();
        }

        Utility::setConsoleTextColor("FOREGROUND_BLUE");
        Bar::clearBar(bars[mainArrayPointer - 1]);
        Bar::renderBar(bars[mainArrayPointer - 1]);
        Sleep(10);
      }

      while (leftArrayPointer < leftArraySize) {
        bars[mainArrayPointer++].height = leftArray[leftArrayPointer++].height;
        Utility::setConsoleTextColor("FOREGROUND_BLUE");
        Bar::clearBar(bars[mainArrayPointer - 1]);
        Bar::renderBar(bars[mainArrayPointer - 1]);
        
        if (leftIndex == 4 && rightIndex == 112) {
          numberOfBarsSorted++;
          displaySortingStatistics();
        }
        
        Sleep(10);
      }

      while (rightArrayPointer < rightArraySize) {
        bars[mainArrayPointer++].height = rightArray[rightArrayPointer++].height;
        Utility::setConsoleTextColor("FOREGROUND_BLUE");
        Bar::clearBar(bars[mainArrayPointer - 1]);
        Bar::renderBar(bars[mainArrayPointer - 1]);
        
        if (leftIndex == 4 && rightIndex == 112) {
          numberOfBarsSorted++;
          displaySortingStatistics();
        }
        
        Sleep(10);
      }

      Utility::setConsoleTextColor("FOREGROUND_WHITE");

      free(leftArray);
      free(rightArray);
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

  namespace HeapSort {
    void heapify(Bar::Bar *bars, int N, int i) {
      int largest = i;
      int left = 2 * i + 1;
      int right = 2 * i + 2;

      if (left < N && bars[left].height > bars[largest].height) largest = left;
      if (right < N && bars[right].height > bars[largest].height) largest = right;

      if (largest != i) {
        Utility::setConsoleTextColor("FOREGROUND_GREEN");
        Bar::renderBar(bars[largest]);

        Utility::setConsoleTextColor("FOREGROUND_RED");
        Bar::renderBar(bars[i]);

        Bar::clearBar(bars[i]);
        Bar::clearBar(bars[largest]);
        Bar::swapHeight(&bars[i], &bars[largest]);

        Utility::setConsoleTextColor("FOREGROUND_GREEN");
        Bar::renderBar(bars[largest]);
        Bar::renderBar(bars[i]);

        Sleep(10);

        heapify(bars, N, largest);
      }
    }

    void heapSort(Bar::Bar *bars, int N) {
      for (int i = N / 2 - 1; i >= 0; i--) heapify(bars, N, i);

      for (int i = 0; i < 109; i++) {
        Bar::clearBar(bars[i]);
        Utility::setConsoleTextColor("FOREGROUND_GREEN");
        Bar::renderBar(bars[i]);
        Sleep(1);
      }

      for (int i = N - 1; i >= 0; i--) {
        Bar::clearBar(bars[0]);
        Bar::clearBar(bars[i]);
        
        Bar::swapHeight(&bars[0], &bars[i]);

        Utility::setConsoleTextColor("FOREGROUND_RED");
        Bar::renderBar(bars[0]);

        Utility::setConsoleTextColor("FOREGROUND_BLUE");
        Bar::renderBar(bars[i]);

        numberOfBarsSorted++;
        displaySortingStatistics();

        Sleep(10);

        heapify(bars, i, 0);
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

    bars = Bar::getRandomizedBars();
    numberOfBarsSorted = 0;
  }

  void displayUIElements() {
    Utility::UI::animateOuterBorder(0);
    Utility::UI::animateInnerBorder(0);

    Utility::setConsoleCursorPosition(50, 25);
    printf("Randomizing Bars");

    Bar::animateRandomizedBars(bars);

    Utility::UI::clearButtons();

    UserInterface::renderButton(btnQuickSort);
    UserInterface::renderButton(btnMergeSort);
    UserInterface::renderButton(btnHeapSort);
    UserInterface::renderButton(btnBack);
  }

  void animateBarsSorted(Bar::Bar *bars, short startIndex = 4, short endIndex = 112) {
    Utility::setConsoleTextColor("FOREGROUND_GREEN");
    
    for (short i = startIndex; i <= endIndex; i++) {
      Bar::renderBar(bars[i]);
      Sleep(5);
    }
  }

  void waitForLeftClick() {
    Utility::UI::clearButtons();

    const short X = 22;
    const short Y = 25;

    Utility::setConsoleTextColor("FOREGROUND_WHITE");

    Utility::setConsoleCursorPosition(X + 20, Y);
    Utility::animateString("Sorted! Click Anywhere to Continue", 5);

    Utility::UI::waitForLeftClick();
  }

  bool handleClick(COORD cursorPosition) {
    if (UserInterface::isCursorInButton(btnQuickSort, cursorPosition)){
      Utility::UI::clearButtons();
      displaySortingStatistics();

      QuickSort::quickSort(bars);
      animateBarsSorted(bars);

      waitForLeftClick();

      return true;
    } else if (UserInterface::isCursorInButton(btnMergeSort, cursorPosition)){
      Utility::UI::clearButtons();
      displaySortingStatistics();

      MergeSort::mergeSort(bars);
      animateBarsSorted(bars);

      waitForLeftClick();
      
      return true;
    } else if (UserInterface::isCursorInButton(btnHeapSort, cursorPosition)){
      Bar::Bar *toSort = (Bar::Bar*) malloc(120 * sizeof(Bar::Bar));
      for (size_t i = 4; i < 113; i++){
        toSort[i - 4].xPos = bars[i].xPos;
        toSort[i - 4].yPos = bars[i].yPos;
        toSort[i - 4].height = bars[i].height;
      }

      Utility::UI::clearButtons();
      displaySortingStatistics();

      HeapSort::heapSort(toSort, 109);
      animateBarsSorted(toSort, 0, 109);

      waitForLeftClick();
      free(toSort);

      return true;
    } else if (UserInterface::isCursorInButton(btnBack, cursorPosition)){
      return true;
    }

    return false;
  }

  bool setEventHandlers() {
    COORD cursorPosition = Utility::UI::waitForLeftClick();

    return handleClick(cursorPosition);
  }

  void show() {
    Utility::clearScreen();

    initializeUIElements();
    displayUIElements();
    
    while (!setEventHandlers());

    free(bars);
  }
}

#endif