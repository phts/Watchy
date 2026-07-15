#ifndef SET_TIME_ZONE_SCREEN_H
#define SET_TIME_ZONE_SCREEN_H

#include "config.h"
#include "Display.h"

class SetTimeZoneScreen
{
public:
  SetTimeZoneScreen(GxEPD2_BW<WatchyDisplay, WatchyDisplay::HEIGHT> *display)
  {
    this->display = display;
  }

  void open()
  {
    this->active = true;
    this->render();
  }

  void close()
  {
    this->active = false;
  }

  void onPressOk()
  {
  }

  void onPressBack()
  {
    this->close();
  }

  void onPressUp()
  {
    this->selectedItem--;
    if (this->selectedItem < this->FIRST_ITEM_INDEX)
    {
      this->selectedItem = this->LAST_ITEM_INDEX;
    }
    this->render(true);
  }

  void onPressDown()
  {
    this->selectedItem++;
    if (this->selectedItem > this->LAST_ITEM_INDEX)
    {
      this->selectedItem = this->FIRST_ITEM_INDEX;
    }
    this->render(true);
  }

  bool isActive()
  {
    return this->active;
  }

private:
  const byte ITEMS_SIZE = 38;
  const byte FIRST_ITEM_INDEX = 0;
  const byte LAST_ITEM_INDEX = ITEMS_SIZE - 1;

  bool active = false;
  byte selectedItem = 0;
  GxEPD2_BW<WatchyDisplay, WatchyDisplay::HEIGHT> *display;

  void render(bool partial = false)
  {
    display->setFullWindow();
    display->fillScreen(GxEPD_WHITE);
    display->setFont(&FreeMonoBold9pt7b);

    int16_t x1, y1;
    uint16_t w, h;
    int16_t yPos;

    const byte MAX_ITEMS_SHOWN = 5;
    const char *ITEMS[] = {
        "+00:00",
        "+01:00",
        "+02:00",
        "+03:00",
        "+03:30",
        "+04:00",
        "+04:30",
        "+05:00",
        "+05:30",
        "+05:45",
        "+06:00",
        "+06:30",
        "+07:00",
        "+08:00",
        "+08:45",
        "+09:00",
        "+09:30",
        "+10:00",
        "+10:30",
        "+11:00",
        "+12:00",
        "+12:45",
        "+13:00",
        "+14:00",
        "-12:00",
        "-11:00",
        "-10:00",
        "-09:30",
        "-09:00",
        "-08:00",
        "-07:00",
        "-06:00",
        "-05:00",
        "-04:00",
        "-03:30",
        "-03:00",
        "-02:00",
        "-01:00"};

    for (byte i = 0; i < MAX_ITEMS_SHOWN; i++)
    {
      yPos = MENU_HEIGHT + (MENU_HEIGHT * i);
      display->setCursor(0, yPos);

      if (this->selectedItem == this->FIRST_ITEM_INDEX)
      {
        if (i == 0)
        {
          display->getTextBounds(ITEMS[i], 0, yPos, &x1, &y1, &w, &h);
          display->fillRect(x1 - 1, y1 - 10, 200, h + 15, GxEPD_BLACK);
          display->setTextColor(GxEPD_WHITE);
          display->println(ITEMS[i]);
        }
        else
        {
          display->setTextColor(GxEPD_BLACK);
          display->println(ITEMS[i]);
        }
      }
      else if (this->selectedItem == this->FIRST_ITEM_INDEX + 1)
      {
        if (i == 1)
        {
          display->getTextBounds(ITEMS[i], 0, yPos, &x1, &y1, &w, &h);
          display->fillRect(x1 - 1, y1 - 10, 200, h + 15, GxEPD_BLACK);
          display->setTextColor(GxEPD_WHITE);
          display->println(ITEMS[i]);
        }
        else
        {
          display->setTextColor(GxEPD_BLACK);
          display->println(ITEMS[i]);
        }
      }
      else if (this->selectedItem == this->LAST_ITEM_INDEX - 1)
      {
        if (i == MAX_ITEMS_SHOWN - 2)
        {
          display->getTextBounds(ITEMS[this->LAST_ITEM_INDEX - MAX_ITEMS_SHOWN - 1 + i], 0, yPos, &x1, &y1, &w, &h);
          display->fillRect(x1 - 1, y1 - 10, 200, h + 15, GxEPD_BLACK);
          display->setTextColor(GxEPD_WHITE);
          display->println(ITEMS[this->LAST_ITEM_INDEX - MAX_ITEMS_SHOWN - 1 + i]);
        }
        else
        {
          display->setTextColor(GxEPD_BLACK);
          display->println(ITEMS[this->LAST_ITEM_INDEX - MAX_ITEMS_SHOWN - 1 + i]);
        }
      }
      else if (this->selectedItem == this->LAST_ITEM_INDEX)
      {
        if (i == MAX_ITEMS_SHOWN - 1)
        {
          display->getTextBounds(ITEMS[this->LAST_ITEM_INDEX - MAX_ITEMS_SHOWN - 1 + i], 0, yPos, &x1, &y1, &w, &h);
          display->fillRect(x1 - 1, y1 - 10, 200, h + 15, GxEPD_BLACK);
          display->setTextColor(GxEPD_WHITE);
          display->println(ITEMS[this->LAST_ITEM_INDEX - MAX_ITEMS_SHOWN - 1 + i]);
        }
        else
        {
          display->setTextColor(GxEPD_BLACK);
          display->println(ITEMS[this->LAST_ITEM_INDEX - MAX_ITEMS_SHOWN - 1 + i]);
        }
      }
      else
      {
        if (i == 2)
        {
          display->getTextBounds(ITEMS[this->selectedItem - 2 + i], 0, yPos, &x1, &y1, &w, &h);
          display->fillRect(x1 - 1, y1 - 10, 200, h + 15, GxEPD_BLACK);
          display->setTextColor(GxEPD_WHITE);
          display->println(ITEMS[this->selectedItem - 2 + i]);
        }
        else
        {
          display->setTextColor(GxEPD_BLACK);
          display->println(ITEMS[this->selectedItem - 2 + i]);
        }
      }
    }

    display->display(partial);
  }
};

#endif
