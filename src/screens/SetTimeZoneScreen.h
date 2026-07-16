#ifndef SET_TIME_ZONE_SCREEN_H
#define SET_TIME_ZONE_SCREEN_H

#include "config.h"

typedef void (*OnSaveCallback)(int8_t value);

RTC_DATA_ATTR bool isSetTimeZoneScreenActive = false;

class SetTimeZoneScreen
{
public:
  SetTimeZoneScreen(GxEPD2_BW<WatchyDisplay, WatchyDisplay::HEIGHT> *display, OnSaveCallback onSaveCallback)
  {
    this->display = display;
    this->onSaveCallback = onSaveCallback;
  }

  void open()
  {
    isSetTimeZoneScreenActive = true;
    this->render();
  }

  void close()
  {
    isSetTimeZoneScreenActive = false;
  }

  void onPressOk()
  {
    onSaveCallback(VALUES[this->selectedItem]);
    this->close();
  }

  void onPressBack()
  {
    this->close();
  }

  void onPressUp()
  {
    this->selectedItem--;
    if (this->selectedItem < FIRST_ITEM_INDEX)
    {
      this->selectedItem = LAST_ITEM_INDEX;
    }
    this->render(true);
  }

  void onPressDown()
  {
    this->selectedItem++;
    if (this->selectedItem > LAST_ITEM_INDEX)
    {
      this->selectedItem = FIRST_ITEM_INDEX;
    }
    this->render(true);
  }

  bool isActive()
  {
    return isSetTimeZoneScreenActive;
  }

private:
  static const byte ITEMS_SIZE = 27;
  static const byte FIRST_ITEM_INDEX = 0;
  static const byte LAST_ITEM_INDEX = ITEMS_SIZE - 1;
  static constexpr int8_t VALUES[ITEMS_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, -12, -11, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1};

  OnSaveCallback onSaveCallback;

  int8_t selectedItem = 0;
  GxEPD2_BW<WatchyDisplay, WatchyDisplay::HEIGHT> *display;

  void render(bool partial = false)
  {
    display->setFullWindow();
    display->fillScreen(UI_BACKGROUND_COLOR);
    display->setFont(&FreeMonoBold9pt7b);

    int16_t x1, y1;
    uint16_t w, h;
    int16_t yPos;

    const byte MAX_ITEMS_SHOWN = 5;
    const char *LABELS[ITEMS_SIZE] = {
        "+00:00",
        "+01:00",
        "+02:00",
        "+03:00",
        "+04:00",
        "+05:00",
        "+06:00",
        "+07:00",
        "+08:00",
        "+09:00",
        "+10:00",
        "+11:00",
        "+12:00",
        "+13:00",
        "+14:00",
        "-12:00",
        "-11:00",
        "-10:00",
        "-09:00",
        "-08:00",
        "-07:00",
        "-06:00",
        "-05:00",
        "-04:00",
        "-03:00",
        "-02:00",
        "-01:00"};

    for (byte i = 0; i < MAX_ITEMS_SHOWN; i++)
    {
      yPos = MENU_HEIGHT + (MENU_HEIGHT * i);
      display->setCursor(0, yPos);

      if (this->selectedItem == FIRST_ITEM_INDEX)
      {
        if (i == 0)
        {
          display->getTextBounds(LABELS[i], 0, yPos, &x1, &y1, &w, &h);
          display->fillRect(x1 - 1, y1 - 10, 200, h + 15, UI_FOREGROUND_COLOR);
          display->setTextColor(UI_BACKGROUND_COLOR);
          display->println(LABELS[i]);
        }
        else
        {
          display->setTextColor(UI_FOREGROUND_COLOR);
          display->println(LABELS[i]);
        }
      }
      else if (this->selectedItem == FIRST_ITEM_INDEX + 1)
      {
        if (i == 1)
        {
          display->getTextBounds(LABELS[i], 0, yPos, &x1, &y1, &w, &h);
          display->fillRect(x1 - 1, y1 - 10, 200, h + 15, UI_FOREGROUND_COLOR);
          display->setTextColor(UI_BACKGROUND_COLOR);
          display->println(LABELS[i]);
        }
        else
        {
          display->setTextColor(UI_FOREGROUND_COLOR);
          display->println(LABELS[i]);
        }
      }
      else if (this->selectedItem == LAST_ITEM_INDEX - 1)
      {
        if (i == MAX_ITEMS_SHOWN - 2)
        {
          display->getTextBounds(LABELS[LAST_ITEM_INDEX - (MAX_ITEMS_SHOWN - 1 - i)], 0, yPos, &x1, &y1, &w, &h);
          display->fillRect(x1 - 1, y1 - 10, 200, h + 15, UI_FOREGROUND_COLOR);
          display->setTextColor(UI_BACKGROUND_COLOR);
          display->println(LABELS[LAST_ITEM_INDEX - (MAX_ITEMS_SHOWN - 1 - i)]);
        }
        else
        {
          display->setTextColor(UI_FOREGROUND_COLOR);
          display->println(LABELS[LAST_ITEM_INDEX - (MAX_ITEMS_SHOWN - 1 - i)]);
        }
      }
      else if (this->selectedItem == LAST_ITEM_INDEX)
      {
        if (i == MAX_ITEMS_SHOWN - 1)
        {
          display->getTextBounds(LABELS[LAST_ITEM_INDEX - (MAX_ITEMS_SHOWN - 1 - i)], 0, yPos, &x1, &y1, &w, &h);
          display->fillRect(x1 - 1, y1 - 10, 200, h + 15, UI_FOREGROUND_COLOR);
          display->setTextColor(UI_BACKGROUND_COLOR);
          display->println(LABELS[LAST_ITEM_INDEX - (MAX_ITEMS_SHOWN - 1 - i)]);
        }
        else
        {
          display->setTextColor(UI_FOREGROUND_COLOR);
          display->println(LABELS[LAST_ITEM_INDEX - (MAX_ITEMS_SHOWN - 1 - i)]);
        }
      }
      else
      {
        if (i == 2)
        {
          display->getTextBounds(LABELS[this->selectedItem - 2 + i], 0, yPos, &x1, &y1, &w, &h);
          display->fillRect(x1 - 1, y1 - 10, 200, h + 15, UI_FOREGROUND_COLOR);
          display->setTextColor(UI_BACKGROUND_COLOR);
          display->println(LABELS[this->selectedItem - 2 + i]);
        }
        else
        {
          display->setTextColor(UI_FOREGROUND_COLOR);
          display->println(LABELS[this->selectedItem - 2 + i]);
        }
      }
    }

    display->display(partial);
  }
};

#endif
