// Image display widget methods for the Fast Light Tool Kit (FLTK).
//
// Copyright 2002-2005 by Michael Sweet.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2, or (at your option)
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// Contents:
//
//   Fl_Image_Display::Fl_Image_Display()  - Create a new image display widget.
//   Fl_Image_Display::~Fl_Image_Display() - Destroy an image display widget.
//   Fl_Image_Display::draw()              - Draw the image display widget.
//   Fl_Image_Display::handle()            - Handle events in the widget.
//   Fl_Image_Display::image_cb()          - Provide a single line of an image.
//   Fl_Image_Display::position()          - Reposition the image on the screen.
//   Fl_Image_Display::resize()            - Resize the image display widget.
//   Fl_Image_Display::scale()             - Scale the image.
//   Fl_Image_Display::scrollbar_cb()      - Update the display based on the
//                                           scrollbar position.
//   Fl_Image_Display::set_gamma()         - Set the display gamma...
//   Fl_Image_Display::update_scrollbars() - Update the scrollbars.
//   Fl_Image_Display::update_mouse_xy()   - Update the mouse X and Y values.
//   Fl_Image_Display::value()             - Set the image to be displayed.
//
// Copyright 2010-2011 by Phong VO

#include "Fl_Image_Display.H"
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>
#include <stdio.h>
#include <math.h>
#include <memory.h>

//
// Absolute value macro...
//

#define abs(a) ((a) < 0 ? -(a) : (a))


//
// Scrollbar width...
//

#define SBWIDTH	17


//
// Gamma lookup table...
//

uchar	Fl_Image_Display::gamma_lut_[256];


//
// 'Fl_Image_Display::Fl_Image_Display()' - Create a new image display widget.
//

Fl_Image_Display::Fl_Image_Display(int        X,
					// I - X position
                                   int        Y,
					// I - Y position
				   int        W,
					// I - Width
				   int        H,
					// I - Height
				   const char *L)
					// I - Label string
  : Fl_Group(X, Y, W, H, L),
    xscrollbar_(X, Y + H - SBWIDTH, W - SBWIDTH, SBWIDTH),
    yscrollbar_(X + W - SBWIDTH, Y, SBWIDTH, H - SBWIDTH)
{
  end();

  box(FL_DOWN_BOX);

  value_   = 0;
  factor_  = 0.0;
  mode_    = FL_IMAGE_PAN;
  mouse_x_ = 0;
  mouse_y_ = 0;

  xscrollbar_.type(FL_HORIZONTAL);
  xscrollbar_.callback(scrollbar_cb, this);

  yscrollbar_.type(FL_VERTICAL);
  yscrollbar_.callback(scrollbar_cb, this);
  active_blocks_ = 0;
  off_screen_ = 0;
  nblocks_=0;
  iconsize_=20;
  nblocksx_ = nblocksy_ = 0;
  show_preview = 0;
  resize(X, Y, W, H);
}


//
// 'Fl_Image_Display::~Fl_Image_Display()' - Destroy an image display widget.
//

Fl_Image_Display::~Fl_Image_Display()
{
}


//
// 'Fl_Image_Display::draw()' - Draw the image display widget.
//

void
Fl_Image_Display::draw()
{
  int	xoff, yoff;			// Offset of image relative to interior of widget
  int	X, Y, W, H;			// Interior of widget

  // First of all, if there are active blocks, so let draw it on top
  //fl_overlay_clear();

#ifdef DEBUG
  puts("Fl_Image_Display::draw()");
#endif // DEBUG

  // the outer window subtracted by box thickness
  X = x() + Fl::box_dx(box());
  Y = y() + Fl::box_dy(box());
  W = w() - Fl::box_dw(box());
  H = h() - Fl::box_dh(box());

  if (factor_)
  {
    xscrollbar_.show();
    yscrollbar_.show();
    // if there are scrollbars
    W -= SBWIDTH;
    H -= SBWIDTH;
  }
  else
  {
    xscrollbar_.hide();
    yscrollbar_.hide();
  }

  if (damage() & FL_DAMAGE_SCROLL)
    fl_push_clip(X, Y, W, H);

  // if zoom in
  if (factor_)
	  // draw a new box covering the image with the presence of scrollbars
    draw_box(box(), x(), y(), w() - SBWIDTH, h() - SBWIDTH, color());
  else
    draw_box();

  if (damage() & FL_DAMAGE_SCROLL)
    fl_pop_clip();
  else if (factor_)
  {
    fl_color(FL_GRAY);
    fl_rectf(x() + w() - SBWIDTH, y() + h() - SBWIDTH, SBWIDTH, SBWIDTH);
  }

/*
#ifdef DEBUG
  if (value_)
    printf("    value_=%p, w()=%d, h()=%d\n", value_, value_->w(), value_->h());
#endif // DEBUG
*/
  // if there is an image need displayed
  if (value_ && value_->w() && value_->h())
  {
#ifdef DEBUG
    printf("    value_=%p, w()=%d, h()=%d\n", value_, value_->w(), value_->h());
#endif // DEBUG

    fl_push_clip(X, Y, W, H);

    if (xsize_ <= W)
      xoff = (W - xsize_) / 2; // the distance from the (X,Y) to the top-left of image drawing region
    else
      xoff = 0;

    if (ysize_ <= H)
      yoff = (H - ysize_) / 2;
    else
      yoff = 0;

    xoff += X; // the absolute position from which the image is drawed
    yoff += Y;

    xstep_ = value_->w() / xsize_;
    xmod_  = value_->w() % xsize_;

#ifdef DEBUG
    printf("    xoff=%d, yoff=%d, xsize_=%d, ysize_=%d, xstep_=%d, xmod_=%d\n",
           xoff, yoff, xsize_, ysize_, xstep_, xmod_);
#endif // DEBUG

    // draw a part of image, says a sub-rectangular region (xoff,yoff)x(widge size)
    // typedef void(* Fl_Draw_Image_Cb)(void *data, int x, int y, int w, uchar *buf)
    fl_draw_image(image_cb, this, xoff, yoff,
                  xsize_ > W ? W : xsize_,
		  ysize_ > H ? H : ysize_, value_->d());

    if (nblocks_ > 0)
  	  draw_overlay();

    draw_preview();

    fl_pop_clip();
  }

  draw_label(X, Y, W, H - 2 * labelsize());

  if (factor_)
  {
    if (damage() & FL_DAMAGE_SCROLL)
    {
      update_child(xscrollbar_);
      update_child(yscrollbar_);
    }
    else
    {
      draw_child(xscrollbar_);
      draw_child(yscrollbar_);
    }
  }
}


//
// 'Fl_Image_Display::handle()' - Handle events in the widget.
//

int					// O - 1 if handled, 0 otherwise
Fl_Image_Display::handle(int event)	// I - Event to handle
{
  if (value_)
    switch (event)
    {
      case FL_SHORTCUT :
		  switch (Fl::event_key())
		  {
			case ' ' : // Advance (slideshow)
			case FL_BackSpace : // Previous (slideshow)
				if (!(Fl::event_state() & (FL_SHIFT | FL_CTRL | FL_ALT | FL_META)))
			{
			  do_callback();
				  return (1);
			}
			break;

			case '-' : // Zoom out
				if (factor_)
				  scale(factor_ * 0.8f);
			else
			  scale((float)xsize_ / (float)value_->w() * 0.8f);

			return (1);

			case '=' : // Zoom in
				if (factor_)
				  scale(factor_ * 1.25f);
			else
			  scale((float)xsize_ / (float)value_->w() * 1.25f);

			return (1);
		  }
		  break;

      case FL_PUSH :
          if (Fl::event_x() < (x() + w() - SBWIDTH) &&
	      Fl::event_y() < (y() + h() - SBWIDTH))
          {
			update_mouse_xy();

			last_x_   = Fl::event_x_root();
			last_y_   = Fl::event_y_root();

			start_x_  = mouse_x_;
			start_y_  = mouse_y_;

			start_ex_ = Fl::event_x();
			start_ey_ = Fl::event_y();

			return (1);
          }
          break;

      case FL_DRAG :
          if (mode_ == FL_IMAGE_PAN)
			position(xscrollbar_.value() + last_x_ - Fl::event_x_root(),
					 yscrollbar_.value() + last_y_ - Fl::event_y_root());
          else if (mode_ != FL_IMAGE_ZOOM_OUT)
          {
			window()->make_current();

			fl_overlay_rect(start_ex_, start_ey_,
							Fl::event_x() - start_ex_,
							Fl::event_y() - start_ey_);
          }

		  last_x_ = Fl::event_x_root();
		  last_y_ = Fl::event_y_root();
		  update_mouse_xy();
		  return (1);

      case FL_RELEASE :
	  update_mouse_xy();

          switch (mode_)
		  {
			case FL_IMAGE_ZOOM_IN :
				window()->make_current();
				fl_overlay_clear();

				if (Fl::event_button() == FL_LEFT_MOUSE)
				{
					int W, H;
					W = w() - SBWIDTH - Fl::box_dw(box());
					H = h() - SBWIDTH - Fl::box_dh(box());

					if (abs(start_ex_ - Fl::event_x()) > 2 ||
							abs(start_ey_ - Fl::event_y()) > 2)
					{
						// Zoom to box...
						float xfactor, yfactor;

						xfactor = (float)W / (float)abs(mouse_x_ - start_x_);
						yfactor = (float)H / (float)abs(mouse_y_ - start_y_);

						scale(xfactor < yfactor ? xfactor : yfactor);
						position((int)((mouse_x_ < start_x_ ? mouse_x_ : start_x_) * scale()),
								 (int)((mouse_y_ < start_y_ ? mouse_y_ : start_y_) * scale()));
					}
					else
					{
						if (factor_)
							  scale(factor_ * 1.25f);
						else
							scale((float)xsize_ / (float)value_->w() * 1.25f);

						position((int)((mouse_x_ < start_x_ ? mouse_x_ : start_x_) * scale()) - W / 2,
							 (int)((mouse_y_ < start_y_ ? mouse_y_ : start_y_) * scale()) - H / 2);
					}
				}
				break;

			case FL_IMAGE_ZOOM_OUT :
				if (factor_)
				  scale(factor_ * 0.8f);
				else
				  scale((float)xsize_ / (float)value_->w() * 0.8f);
				break;

			case FL_IMAGE_CLICK :
				window()->make_current();
				fl_overlay_clear();

				// hist test for activators
				selection (mouse_x_,mouse_y_,start_x_,start_y_);
				do_callback();
				break;
          }
	  return (1);
    }

  return (Fl_Group::handle(event));
}


//
// 'Fl_Image_Display::image_cb()' - Provide a single line of an image.
//

void
Fl_Image_Display::image_cb(void  *p,	// I - Image display widget
                           int   X,		// I - X offset of the image (not widget)
			   int   Y,					// I - Y offset of the image (not widget)
			   int   W,					// I - Width of image row
			   uchar *D)				// O - Image data
{
  Fl_Image_Display	*display;	// Display widget
  Fl_Image			*img;		// Image to display
  const uchar		*inptr;		// Pointer into image
  int			xerr,		// Bresenheim values
				xstep,
				xmod,
				xsize;


  display = (Fl_Image_Display *)p;
  img     = display->value_; // the image data from which data is retrieved

  xstep = display->xstep_ * img->d();
  xmod  = display->xmod_;
  xsize = display->xsize_;
  xerr  = (X * xmod) % xsize;

  if (xsize > (display->w() - Fl::box_dw(display->box()) - SBWIDTH))
    X = (X + display->xscrollbar_.value()) * (img->w() - 1) / (xsize - 1);
  else
    X = X * (img->w() - 1) / (xsize - 1);

  if (display->ysize_ > (display->h() - Fl::box_dh(display->box()) - SBWIDTH))
    Y = (Y + display->yscrollbar_.value()) * (img->h() - 1) /
        (display->ysize_ - 1);
  else
    Y = Y * (img->h() - 1) / (display->ysize_ - 1);

  inptr = (const uchar *)img->data()[0] + (Y * img->w() + X) * img->d();

  switch (img->d())
  {
    case 1 :
	for (; W > 0; W --)
	{
	  *D++ = gamma_lut_[*inptr];

	  inptr += xstep;
	  xerr  += xmod;

	  if (xerr >= xsize)
	  {
	    xerr  -= xsize;
	    inptr += img->d();
	  }
	}
        break;
    case 3 :
	for (; W > 0; W --)
	{
	  *D++ = gamma_lut_[inptr[0]];
	  *D++ = gamma_lut_[inptr[1]];
	  *D++ = gamma_lut_[inptr[2]];

	  inptr += xstep;
	  xerr  += xmod;

	  if (xerr >= xsize)
	  {
	    xerr  -= xsize;
	    inptr += img->d();
	  }
	}
	break;
  }
}


//
// 'Fl_Image_Display::position()' - Reposition the image on the screen.
//

void
Fl_Image_Display::position(int X,	// I - New X offset
                           int Y)	// I - New Y offset
{
  int	W, H;				// Interior size


  W = w() - SBWIDTH;
  H = h() - SBWIDTH;

  if (X < 0)
    X = 0;
  else if (X > (xsize_ - W))
    X = xsize_ - W;

  if (Y < 0)
    Y = 0;
  else if (Y > (ysize_ - H))
    Y = ysize_ - H;

  xscrollbar_.value(X, W, 0, xsize_);
  yscrollbar_.value(Y, H, 0, ysize_);

  damage(FL_DAMAGE_SCROLL);
}


//
// 'Fl_Image_Display::resize()' - Resize the image display widget.
//

void
Fl_Image_Display::resize(int X,		// I - New X position
                         int Y,		// I - New Y position
			 int W,		// I - New width
			 int H)		// I - New height
{
  Fl_Widget::resize(X, Y, W, H);

  xscrollbar_.resize(X, Y + H - SBWIDTH, W - SBWIDTH, SBWIDTH);
  yscrollbar_.resize(X + W - SBWIDTH, Y, SBWIDTH, H - SBWIDTH);

  W -= Fl::box_dw(box()) + SBWIDTH;
  H -= Fl::box_dh(box()) + SBWIDTH;

  if (factor_ == 0.0f && value_)
  {
    xsize_ = W;

    if (xsize_ > (value_->w() * 4))
      xsize_ = value_->w() * 4;

    ysize_ = xsize_ * value_->h() / value_->w();

    if (ysize_ > H)
    {
      ysize_ = H;

      if (ysize_ > (value_->h() * 4))
	ysize_ = value_->h() * 4;

      xsize_ = ysize_ * value_->w() / value_->h();
    }
  }

  update_scrollbars();

  redraw();
}


//
// 'Fl_Image_Display::scale()' - Scale the image.
//

void
Fl_Image_Display::scale(float factor)	// I - Scaling factor (0 = auto)
{
  int	X, Y, W, H;			// Interior of widget
  float	ratio;				// Scaling ratio


  if (factor > 10.0f)
    factor = 10.0f;

  // Make sure that the image doesn't get scaled to nothin'...
  if (value_)
  {
    if (factor > 0.0f && (value_->w() * factor) < 32.0f && value_->w() > 32)
      factor = 32.0f / value_->w();

    if (factor > 0.0f && (value_->h() * factor) < 32.0f && value_->h() > 32)
      factor = 32.0f / value_->h();
  }

  if (factor_ == 0.0f)
    ratio = 0.0f;
  else
    ratio = factor / factor_;

  factor_ = factor;

  //redraw();

  if (!value_ || !value_->w() || !value_->h())
    return;


  W = w() - SBWIDTH - Fl::box_dw(box());
  H = h() - SBWIDTH - Fl::box_dh(box());

  if (factor_ == 0.0f)
  {
    xsize_ = W;

    if (xsize_ > (value_->w() * 4))
      xsize_ = value_->w() * 4;

    ysize_ = xsize_ * value_->h() / value_->w();

    if (ysize_ > H)
    {
      ysize_ = H;

      if (ysize_ > (value_->h() * 4))
	ysize_ = value_->h() * 4;

      xsize_ = ysize_ * value_->w() / value_->h();
    }

    X = 0;
    Y = 0;
  }
  else
  {
    xsize_ = (int)((float)value_->w() * factor_ + 0.5f);
    ysize_ = (int)((float)value_->h() * factor_ + 0.5f);

    if (xsize_ <= W)
    {
      // The image will be centered...
      X = 0;
    }
    else if (ratio == 0.0)
    {
      // Previous zoom was auto-fit, center it...
      X = (xsize_ - W) / 2;
    }
    else
    {
      // Try to center on the previous location...
      X = (int)((xscrollbar_.value() + W / 2) * ratio) - W / 2;
    }

    if (ysize_ <= H)
    {
      // The image will be centered...
      Y = 0;
    }
    else if (ratio == 0.0)
    {
      // Previous zoom was auto-fit, center it...
      Y = (ysize_ - H) / 2;
    }
    else
    {
      // Try to center on the previous location...
      Y = (int)((yscrollbar_.value() + H / 2) * ratio) - H / 2;
    }
  }

  redraw();

  // Update the scrollbars...
  if (X < 0)
    X = 0;
  else if (X > (xsize_ - W))
    X = xsize_ - W;

  xscrollbar_.value(X, W, 0, xsize_);

  if (xsize_ <= W)
    xscrollbar_.deactivate();
  else
    xscrollbar_.activate();

  if (Y < 0)
    Y = 0;
  else if (Y > (ysize_ - H))
    Y = ysize_ - H;

  yscrollbar_.value(Y, H, 0, ysize_);

  if (ysize_ <= H)
    yscrollbar_.deactivate();
  else
    yscrollbar_.activate();
}


//
// 'Fl_Image_Display::scrollbar_cb()' - Update the display based on the scrollbar position.
//

void
Fl_Image_Display::scrollbar_cb(Fl_Widget *w,
					// I - Widget
                               void      *d)
					// I - Image display widget
{
  Fl_Image_Display	*img = (Fl_Image_Display *)d;


  img->damage(FL_DAMAGE_SCROLL);
}


//
// 'Fl_Image_Display::set_gamma()' - Set the display gamma...
//

void
Fl_Image_Display::set_gamma(float val)	// I - Gamma value
{
  int	i;				// Looping var


  val /= 2.2;

  for (i = 0; i < 256; i ++)
    gamma_lut_[i] = (int)(255.0 * pow(i / 255.0, val) + 0.5);
}


//
// 'Fl_Image_Display::update_mouse_xy()' - Update the mouse X and Y values.
//

void
Fl_Image_Display::update_mouse_xy()
{
  int	X, Y;				// X,Y position
  int	W, H;				// Width and height


  //
  X = Fl::event_x() - x() - Fl::box_dx(box());
  Y = Fl::event_y() - y() - Fl::box_dy(box());

  // the actual canvas size
  W = w() - SBWIDTH - Fl::box_dw(box());
  H = h() - SBWIDTH - Fl::box_dh(box());

  if (!value_ || xsize_ <= 0 || ysize_ <= 0)
  {
    mouse_x_ = -1;
    mouse_y_ = -1;
  }

  // if not zoomed at all
  if (xsize_ < W)
  {
    X -= (W - xsize_) / 2;

    if (X < 0)
      mouse_x_ = 0;
    else if (X >= xsize_)
      mouse_x_ = value_->w();
    else
      mouse_x_ = X * value_->w() / xsize_;
  }
  else
    mouse_x_ = (xscrollbar_.value() + X) * value_->w() / xsize_;

  if (ysize_ < H)
  {
    Y -= (H - ysize_) / 2;

    if (Y < 0)
      mouse_y_ = 0;
    else if (Y >= ysize_)
      mouse_y_ = value_->h();
    else
      mouse_y_ = Y * value_->h() / ysize_;
  }
  else
    mouse_y_ = (yscrollbar_.value() + Y) * value_->h() / ysize_;

  if (mouse_x_ < 0)
    mouse_x_ = 0;
  else if (mouse_x_ > value_->w())
    mouse_x_ = value_->w();

  if (mouse_y_ < 0)
    mouse_y_ = 0;
  else if (mouse_y_ > value_->h())
    mouse_y_ = value_->h();

//  printf("xscrollbar_=%d, yscrollbar_=%d\n", xscrollbar_.value(),
//         yscrollbar_.value());
//  printf("mouse_x_=%d, mouse_y_=%d\n", mouse_x_, mouse_y_);
}


//
// 'Fl_Image_Display::update_scrollbars()' - Update the scrollbars.
//

void
Fl_Image_Display::update_scrollbars()
{
  int	X, Y;				// X/Y offsets
  int	W, H;				// Interior size


  if (value_)
  {
    W = w() - SBWIDTH - Fl::box_dw(box());
    H = h() - SBWIDTH - Fl::box_dh(box());

    X = xscrollbar_.value();
    if (X > (xsize_ - W))
      X = xsize_ - W;
    else if (X < 0)
      X = 0;

    xscrollbar_.value(X, W, 0, xsize_);

    if (xsize_ <= W)
      xscrollbar_.deactivate();
    else
      xscrollbar_.activate();

    Y = yscrollbar_.value();
    if (Y > (ysize_ - H))
      Y = ysize_ - H;
    else if (Y < 0)
      Y = 0;

    yscrollbar_.value(Y, H, 0, ysize_);

    if (ysize_ <= H)
      yscrollbar_.deactivate();
    else
      yscrollbar_.activate();
  }
  else
  {
    xscrollbar_.value(0, 1, 0, 1);
    yscrollbar_.value(0, 1, 0, 1);
  }
}


//
// 'Fl_Image_Display::value()' - Set the image to be displayed.
//

void
Fl_Image_Display::value(Fl_Shared_Image *v)
					// I - Image to display
{
  value_ = v;
  scale(0.0f);
}

int
Fl_Image_Display::activate_blocks(int *indexes, int n)
{
	if (indexes == 0 || n <= 0)
		return 0;

	if (active_blocks_ != 0)
		delete active_blocks_;

	active_blocks_ = new int[n];
	int k = 0;
	for (int i = 0; i < n ; ++i)
	{
		if (indexes[i] < 0)
			continue;
		active_blocks_[k++] = indexes[i];
	}
	nblocks_ = k;
	redraw();

	return 1;
}

int
Fl_Image_Display::activate_location_window(int i)
{
	show_preview = i;
	redraw();
	return 1;
}

void
Fl_Image_Display::set_grid(int nblockx, int nblocky)
{
	nblocksx_ = nblockx;
	nblocksy_ = nblocky;
}

void
Fl_Image_Display::set_preview(Fl_Shared_Image* prev)
{
	previm_ = prev;
	previm_xsize_ = previm_->w();
	previm_ysize_ = previm_->h();
	//previm_xsize_ = xsize;
	//previm_ysize_ = ysize;
}

void
Fl_Image_Display::draw_overlay(void)
{
	if (nblocksx_ == 0 || nblocksy_ == 0)
	{
		fprintf(stderr,"Grid needs to be set");
		return;
	}

	int idx, idy, x_, y_;
	int lboundx,uboundx,lboundy,uboundy;
	int X,Y,W,H,xoff,yoff;
	int absx_, absy_;

	X = x() + Fl::box_dx(box());
	Y = y() + Fl::box_dy(box());
	W = w() - Fl::box_dw(box());
	H = h() - Fl::box_dh(box());

	if (factor_)
	{
		W -= SBWIDTH;
		H -= SBWIDTH;
	}

    if (xsize_ <= W)
    {
      xoff = (W - xsize_) / 2; // the distance from the (X,Y) to the top-left of image drawing region
      lboundx = 0;
    }
    else
    {
      lboundx = xscrollbar_.value();
      xoff = 0;
    }

    if (ysize_ <= H)
    {
      yoff = (H - ysize_) / 2;
      lboundy = 0;
    }
    else
    {
      yoff = 0;
      lboundy = yscrollbar_.value();
    }

    xoff += X; // the absolute position from which the image is drawed
    yoff += Y;

    uboundx = lboundx + W;
    uboundy = lboundy + H;

    float szblockx_ = float(xsize_)/nblocksx_;
    float szblocky_ = float(ysize_)/nblocksy_;

    int minW = value_->w() < value_->h() ? value_->w() : value_->h();
    int minw = xsize_ < ysize_ ? xsize_ : ysize_;

    int iconsize = floor(iconsize_*float(minw)/float(minW));
    if (iconsize < iconsize_/2)
       iconsize = iconsize_/2;
    if (iconsize > iconsize_)
    	iconsize = iconsize_;

#ifdef DEBUG
    printf("icon size=%d\n",iconsize);
#endif

#ifdef DEBUG
    printf("szblock=(%d,%d)\n",szblockx_,szblocky_);
#endif

	// draw directly onto the on-screen buffer
	for ( int i = 0 ; i < nblocks_ ; ++i )
	{
		// the coordinate (x,y) of the activated point
		idx = (active_blocks_[i]-1)%nblocksx_;
		idy = (active_blocks_[i]-1)/nblocksx_;

		if (idy > nblocksy_)
			continue;

		x_ = round(idx * szblockx_ + szblockx_/2);
		y_ = round(idy * szblocky_ + szblocky_/2);

#ifdef DEBUG
		printf("block_id=%d\n",active_blocks_[i]);
		printf("id=(%d,%d)\n",x_,y_);
#endif
		// intersection test the activated point against the canvas
		if (x_ < lboundx || x_ > uboundx ||
				y_ < lboundy || y_ > uboundy)
			continue;

		// solve the absolute coordinate of the activated point
		absx_ = xoff + x_ - lboundx;
		absy_ = yoff + y_ - lboundy;

#ifdef DEBUG
		printf("offset=(%d,%d)\n",xoff,yoff);
#endif

		fl_rect(absx_-iconsize/2,absy_-iconsize/2,iconsize,iconsize,FL_RED);
		fl_rectf(absx_-iconsize/2+1,absy_-iconsize/2+1,iconsize-2,iconsize-2,0,255,0);

	}
}

void
Fl_Image_Display::draw_preview(void)
{
	if (previm_ == 0)
	{
		fprintf(stderr,"Preview image not loaded!");
		return;
	}

	if (!show_preview)
		return;

	int idx, idy, x_, y_;
	int lboundx,uboundx,lboundy,uboundy;
	int X,Y,W,H,xoff,yoff;
	int absx_, absy_;

	X = x() + Fl::box_dx(box());
	Y = y() + Fl::box_dy(box());
	W = w() - Fl::box_dw(box());
	H = h() - Fl::box_dh(box());

	if (factor_)
	{
		W -= SBWIDTH;
		H -= SBWIDTH;
	}

	// xsize_ is the width of current image-show
    if (xsize_ <= W)
    {
    	// xoff: offset of image-show relative to UI component
    	xoff = (W - xsize_) / 2; // the distance from the (X,Y) to the top-left of image drawing region
    	lboundx = 0;
    }
    else
    {
    	lboundx = xscrollbar_.value();
    	xoff = 0;
    }

    if (ysize_ <= H)
    {
      yoff = (H - ysize_) / 2;
      lboundy = 0;
    }
    else
    {
      yoff = 0;
      lboundy = yscrollbar_.value();
    }

    xoff += X; // the absolute position from which the image is drawed
    yoff += Y;

    uboundx = lboundx + W;
    uboundy = lboundy + H;

	// draw directly onto the on-screen buffer
#ifdef DEBUG
		printf("id=(%d,%d)\n",x_,y_);
#endif

	if (previm_xsize_ >= xsize_ || previm_ysize_ >= ysize_)
		return;

	int border = 4;
	int previm_left = X + W - previm_xsize_ - border;
	int previm_top = Y + H - previm_ysize_ - border;

	previm_->draw(previm_left,previm_top);
	//fl_draw_image(previm_->data_,previm_left,previm_top,previm_xsize_,previm_ysize_);

	fl_rect(previm_left - 2, previm_top - 2, previm_xsize_ + 4, previm_ysize_ + 4,FL_RED);

	int ldot = floor(float(lboundx)/float(xsize_)*previm_xsize_);
	int tdot = floor(float(lboundy)/float(ysize_)*previm_ysize_);

	int rdot = ceil(float(uboundx)/float(xsize_)*previm_xsize_);
	int bdot = ceil(float(uboundy)/float(ysize_)*previm_ysize_);

	if (rdot > previm_->w())
		rdot = previm_->w();

	if (bdot > previm_->h())
		bdot = previm_->h();

	fl_line_style(FL_SOLID,2);
	fl_rect(previm_left + ldot - 1,previm_top + tdot - 1, rdot - ldot + 2,bdot - tdot + 2,FL_BLUE);
	fl_line_style(FL_SOLID,1);
	//fl_rectf(absx_-iconsize/2+1,absy_-iconsize/2+1,iconsize-2,iconsize-2,0,255,0);
}

void
Fl_Image_Display::selection(int p1x, int p1y, int p2x, int p2y)
{
	int xmin, xmax, ymin, ymax;

	if (p1x < p2x)
	{
		xmin = p1x;
		xmax = p2x;
	}
	else
	{
		xmin = p2x;
		xmax = p1x;
	}

	if (p1y < p2y)
	{
		ymin = p1y;
		ymax = p2y;
	}
	else
	{
		ymin = p2y;
		ymax = p1y;
	}

	// convert the bounding box into image-based coordinate
    float szblockx_ = float(value_->w())/nblocksx_;
    float szblocky_ = float(value_->h())/nblocksy_;

    int idx,idy,x_,y_,absx_,absy_;

    int* selected = new int[nblocks_];
    int n = 0;

    //printf("mouse-select: ");
	for ( int i = 0 ; i < nblocks_ ; ++i )
	{
		// the coordinate (x,y) of the activated point
		idx = (active_blocks_[i]-1)%nblocksx_;
		idy = (active_blocks_[i]-1)/nblocksx_;

		if (idy > nblocksy_)
		{
			//selected[i] = -1;
			continue;
		}

		x_ = round(idx * szblockx_ + szblockx_/2);
		y_ = round(idy * szblocky_ + szblocky_/2);

		if (xmin > x_ || xmax < x_ ||
				ymin > y_ || ymax < y_)
		{
			//selected[i] = -1;
			continue;
		}

		selected[n++] = active_blocks_[i];
		//printf("%d, ",active_blocks_[i]);
	}

	//printf ("\n");

	if (n == 0)
	{
		//fprintf (stdout,"keke \n");
		return;
	}

	//printf ("%d points selected\n",n);
	spac_setbound(selected,n);
	delete selected;
}
//
// End of "$Id: Fl_Image_Display.cxx 321 2005-01-23 03:52:44Z easysw $".
//
