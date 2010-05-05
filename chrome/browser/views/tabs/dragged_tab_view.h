// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_VIEWS_TABS_DRAGGED_TAB_VIEW_H_
#define CHROME_BROWSER_VIEWS_TABS_DRAGGED_TAB_VIEW_H_

#include "app/slide_animation.h"
#include "base/callback.h"
#include "build/build_config.h"
#include "gfx/point.h"
#include "gfx/size.h"
#include "views/view.h"

namespace views {
#if defined(OS_WIN)
class WidgetWin;
#elif defined(OS_LINUX)
class WidgetGtk;
#endif
}
namespace gfx {
class Point;
}
class NativeViewPhotobooth;
class Tab;
class TabRenderer;

class DraggedTabView : public views::View,
                       public AnimationDelegate {
 public:
  // Creates a new DraggedTabView using |renderer| as the View. DraggedTabView
  // takes ownership of |renderer|.
  DraggedTabView(views::View* renderer,
                 const gfx::Point& mouse_tab_offset,
                 const gfx::Size& contents_size,
                 const gfx::Size& min_size);
  virtual ~DraggedTabView();

  // Moves the DraggedTabView to the appropriate location given the mouse
  // pointer at |screen_point|.
  void MoveTo(const gfx::Point& screen_point);

  // Sets the offset of the mouse from the upper left corner of the tab.
  void set_mouse_tab_offset(const gfx::Point& offset) {
    mouse_tab_offset_ = offset;
  }

  // Notifies the DraggedTabView that it has become attached to a TabStrip.
  void Attach(int selected_width);

  // Resizes the dragged tab to a width of |width|.
  void Resize(int width);

  // Notifies the DraggedTabView that it has been detached from a TabStrip.
  void Detach(NativeViewPhotobooth* photobooth);

  // Notifies the DraggedTabView that it should update itself.
  void Update();

  // Animates the DraggedTabView to the specified bounds, then calls back to
  // |callback|.
  void AnimateToBounds(const gfx::Rect& bounds, Callback0::Type* callback);

  // Returns the size of the DraggedTabView. Used when attaching to a TabStrip
  // to determine where to place the Tab in the attached TabStrip.
  const gfx::Size& attached_tab_size() const { return attached_tab_size_; }

 private:
  // Overridden from AnimationDelegate:
  virtual void AnimationProgressed(const Animation* animation);
  virtual void AnimationEnded(const Animation* animation);
  virtual void AnimationCanceled(const Animation* animation);

  // Overridden from views::View:
  virtual void Paint(gfx::Canvas* canvas);
  virtual void Layout();
  virtual gfx::Size GetPreferredSize();

  // Paint the view, when it's attached to a TabStrip.
  void PaintAttachedTab(gfx::Canvas* canvas);

  // Paint the view, when it's not attached to any TabStrip.
  void PaintDetachedView(gfx::Canvas* canvas);

  // Paint the view, when "Show window contents while dragging" is disabled.
  void PaintFocusRect(gfx::Canvas* canvas);

  // Resizes the container to fit the content for the current attachment mode.
  void ResizeContainer();

  // Utility for scaling a size by the current scaling factor.
  int ScaleValue(int value);

  // The window that contains the DraggedTabView.
#if defined(OS_WIN)
  scoped_ptr<views::WidgetWin> container_;
#elif defined(OS_LINUX)
  scoped_ptr<views::WidgetGtk> container_;
#endif

  // The renderer that paints the Tab shape.
  scoped_ptr<views::View> renderer_;

  // True if the view is currently attached to a TabStrip. Controls rendering
  // and sizing modes.
  bool attached_;

  // True if "Show window contents while dragging" is enabled.
  bool show_contents_on_drag_;

  // The unscaled offset of the mouse from the top left of the dragged Tab.
  // This is used to maintain an appropriate offset for the mouse pointer when
  // dragging scaled and unscaled representations, and also to calculate the
  // position of detached windows.
  gfx::Point mouse_tab_offset_;

  // The size of the tab renderer when the dragged tab is attached to a
  // tabstrip.
  gfx::Size attached_tab_size_;

  // A handle to the DIB containing the current screenshot of the TabContents
  // we are dragging.
  NativeViewPhotobooth* photobooth_;

  // Size of the TabContents being dragged.
  gfx::Size contents_size_;

  // The animation used to slide the attached view to its final location.
  SlideAnimation close_animation_;

  // A callback notified when the animation is complete.
  scoped_ptr<Callback0::Type> animation_callback_;

  // The start and end bounds of the animation sequence.
  gfx::Rect animation_start_bounds_;
  gfx::Rect animation_end_bounds_;

  DISALLOW_COPY_AND_ASSIGN(DraggedTabView);
};

#endif  // CHROME_BROWSER_VIEWS_TABS_DRAGGED_TAB_VIEW_H_
