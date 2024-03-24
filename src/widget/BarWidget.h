// BarWidget.h

#ifndef BARWIDGET_H
#define BARWIDGET_H

#include <Arduino.h>
#include <TFT_eSPI.h>
#include "Widget.h"

class BarWidget : public Widget {
private:
    
    // style constants
    static const uint32_t clr_pr = TFT_WHITE;     // color of bar
    static const uint32_t clr_bg = TFT_BLACK;  // color behind bar
    static const uint32_t clr_rl = TFT_RED;      // redline color

    // object constants (set once on instantiation)
    uint16_t limiter;
    uint16_t barMin;
    uint16_t barMax;
    int r_x;     // x coord of limiter on bar

    // internal vars
    int       l_x = 0;      // last x coord (where edge of bar is)
    uint32_t  clr = clr_pr; // clr for bar-increases (segment-to-be-drawn)

public:
    // constructor
	BarWidget(TFT_eSPI* tft, int x, int y, int w, int h, uint16_t min, uint16_t max, uint16_t limit) : 
      Widget(*tft, x, y, w, h), 
      barMin(min), 
      barMax(max), 
      limiter(limit) {
        this->l_x = this->x;
        this->clr = clr_pr;
        this->r_x = int(this->w * (this->limiter / float(this->barMax))); 
      }
  BarWidget(TFT_eSPI* tft, const WidgetPlacement& p, uint16_t min, uint16_t max, uint16_t limit) : 
      Widget(*tft, p), 
      barMin(min), 
      barMax(max), 
      limiter(limit) {
        this->l_x = this->x;
        this->clr = clr_pr;
        this->r_x = int(this->w * (this->limiter / float(this->barMax))); 
      }
	
	//destructor
	~BarWidget() {}

    void init() override {
      tft.fillRect(this->x, this->y, this->w, this->h, this->clr_bg); //clear whatever existed behind bar
      l_x = this->x;  // zero-out last x
      clr = clr_pr;   // reset color
      update(barMin); // update visually
    }

    void clear() override { init(); }

    void update(char* s) override {}
    void update(float f) override {}
    void update(uint16_t val) override {
      
      if       (val > this->barMax) val = this->barMax;
	  else if  (val < this->barMin) val = this->barMin;
      //else....


      // current x (where edge of bar will move to)
      int c_x = this->x + int(this->w * (val / float(this->barMax)));    
      int l_x = this->l_x;
      int r_x = this->r_x;

      // decrease
      if (c_x < l_x) {

        // fill end with black 
        // (faster to subtract using black than clear+redraw bar)
        tft.fillRect(c_x, this->y, l_x-c_x, this->h, this->clr_bg); 

        // crossed over redline
        if ((c_x <= r_x) && (l_x > r_x)) {
          clr = clr_pr; // change color to primary
        }

      }
      // increased, cross over redline
      else if ((l_x <= r_x) && (c_x > r_x)) { 

        tft.fillRect(l_x, this->y, r_x-l_x, this->h, clr); // draw colored side of bar
        clr = clr_rl;                                             // change color to redline
        tft.fillRect(r_x, this->y, c_x-r_x, this->h, clr); // draw redline side of bar

      }
      // increased (no crossover)
      else if (l_x < c_x) {
        
        tft.fillRect(l_x, this->y, c_x-l_x, this->h, clr); // append segment to end
      }
      

      this->l_x = c_x;
      
    }

};

#endif // BARWIDGET_H
